#pragma once
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>
#include <features/data/tune.hh>
#include <features/features.hh>
#include <sdk/core/access.hh>
#include <sdk/globals.hh>
#include <sdk/hw2/combat/weapon.hh>
#include <features/impl/progress.hh>

namespace features::detail {

    [[nodiscard]] inline bool is_same_object(const sdk::UObject* object, std::int32_t index) {
        return object && index >= 0 && sdk::objects::at(index) == object;
    }

    struct stats_original {
        std::int32_t index = -1;
        sdk::hw2::weapon_stats stats;
    };

    struct fire_cadence {
        std::chrono::steady_clock::time_point last;
        double owed = 0.0;

        void forget() noexcept { owed = 0.0; last = {}; }

        [[nodiscard]] int owed_shots(float per_second) noexcept {
            const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
            const double elapsed = std::chrono::duration<double>(now - last).count();
            const std::chrono::steady_clock::time_point previous = last;

            last = now;

            if (per_second <= 0.0f) { owed = 0.0; return 0; }

            if (previous == std::chrono::steady_clock::time_point{}) { owed = 0.0; return 1; }
            if (elapsed <= 0.0 || elapsed > tune::auto_fire_gap_ceiling) { owed = 0.0; return 0; }

            owed += elapsed * static_cast<double>(per_second);

            const int shots = static_cast<int>(owed);
            owed -= static_cast<double>(shots);

            return shots > tune::auto_fire_burst_ceiling ? tune::auto_fire_burst_ceiling : shots;
        }
    };

    inline fire_cadence auto_fire_cadence;

    struct gun_original {
        std::int32_t index = -1;
        double bot_damage = 1.0;
        int ammo_per_mag = 0;
        sdk::FLinearColor color_a;
        sdk::FLinearColor color_b;
        bool is_painted = false;
    };

    struct thrown_item {
        sdk::AActor* actor = nullptr;
        sdk::hw2::actor_kind kind = sdk::hw2::actor_kind::other;
    };

    struct level_sweep {
        std::vector<sdk::AActor*> bullets;
        std::vector<thrown_item> throwables;
        std::vector<sdk::AActor*> other_guns;

        std::vector<sdk::APawn*> characters;
        int human_controllers = 0;
    };

    inline std::unordered_map<sdk::UObject*, stats_original> stats_originals;
    inline std::unordered_map<sdk::AActor*, gun_original> gun_originals;
    inline std::unordered_map<sdk::AActor*, std::int32_t> launched;
    inline level_sweep sweep;
    inline std::atomic<bool> is_weapon_pass_queued{ false };

    [[nodiscard]] inline sdk::APawn* own_pawn() {
        sdk::APlayerController* controller = own_controller();

        return controller ? controller->Pawn() : nullptr;
    }

    [[nodiscard]] inline sdk::APawn* own_character() {
        sdk::APawn* pawn = own_pawn();

        return pawn && sdk::hw2::kind_of(pawn) == sdk::hw2::actor_kind::character ? pawn : nullptr;
    }

    [[nodiscard]] inline std::vector<sdk::AActor*> own_weapons() {
        std::vector<sdk::AActor*> found;

        const sdk::APawn* pawn = own_character();
        if (!pawn) return found;

        const sdk::hw2::weapon_slot slots[] = { sdk::hw2::weapon_slot::primary, sdk::hw2::weapon_slot::secondary, sdk::hw2::weapon_slot::current };

        for (const sdk::hw2::weapon_slot slot : slots) {
            sdk::AActor* weapon = sdk::hw2::weapon_of(pawn, slot);
            if (weapon && std::find(found.begin(), found.end(), weapon) == found.end()) found.push_back(weapon);
        }

        return found;
    }

    inline const stats_original* original_stats(sdk::UObject* settings) {
        if (!settings) return nullptr;

        const auto found = stats_originals.find(settings);
        if (found != stats_originals.end() && is_same_object(settings, found->second.index)) return &found->second;

        stats_original entry;
        entry.index = settings->index();
        if (!sdk::hw2::read_stats(settings, entry.stats)) return nullptr;

        return &(stats_originals[settings] = entry);
    }

    inline gun_original* original_gun(sdk::AActor* weapon) {
        if (!weapon) return nullptr;

        const auto found = gun_originals.find(weapon);
        if (found != gun_originals.end() && is_same_object(weapon, found->second.index)) return &found->second;

        gun_original entry;
        entry.index = weapon->index();
        entry.bot_damage = sdk::hw2::bot_damage_of(weapon);
        entry.ammo_per_mag = sdk::hw2::ammo_per_mag_of(weapon);
        entry.color_a = sdk::hw2::skin_color_a_of(weapon);
        entry.color_b = sdk::hw2::skin_color_b_of(weapon);

        return &(gun_originals[weapon] = entry);
    }

    [[nodiscard]] inline bool is_launched(sdk::AActor* actor) {
        const auto found = launched.find(actor);

        return found != launched.end() && is_same_object(actor, found->second);
    }

    inline void forget_stale() {
        for (auto entry = gun_originals.begin(); entry != gun_originals.end();)
            entry = is_same_object(entry->first, entry->second.index) ? std::next(entry) : gun_originals.erase(entry);

        for (auto entry = launched.begin(); entry != launched.end();)
            entry = is_same_object(entry->first, entry->second) ? std::next(entry) : launched.erase(entry);
    }

    inline void refresh_sweep() {
        sweep.bullets.clear();
        sweep.throwables.clear();
        sweep.other_guns.clear();
        sweep.characters.clear();
        sweep.human_controllers = 0;

        sdk::UWorld* world = sdk::globals::world();
        if (!world) return;

        const sdk::APawn* mine = own_pawn();

        const sdk::TArray<sdk::AActor*> actors = world->level_actors();
        const std::int32_t total = actors.num();
        if (!actors.Data || total <= 0 || total > tune::sane_actor_cap) return;

        for (std::int32_t i = 0; i < total; ++i) {
            sdk::AActor* actor = sdk::mem::read<sdk::AActor*>(actors.Data, static_cast<std::uint32_t>(i) * sizeof(void*), nullptr);
            if (!actor) continue;

            const sdk::hw2::actor_kind kind = sdk::hw2::kind_of(actor);
            if (kind == sdk::hw2::actor_kind::other) continue;

            if (kind == sdk::hw2::actor_kind::player_controller) {
                ++sweep.human_controllers;
                continue;
            }

            if (kind == sdk::hw2::actor_kind::character) {
                if (actor != mine) sweep.characters.push_back(static_cast<sdk::APawn*>(actor));
                continue;
            }

            if (kind == sdk::hw2::actor_kind::weapon) {
                if (!mine || actor->Owner() != mine) sweep.other_guns.push_back(actor);
                continue;
            }

            const bool is_mine = mine && (actor->Instigator() == mine || actor->Owner() == mine);
            if (!is_mine) continue;

            if (kind == sdk::hw2::actor_kind::bullet) sweep.bullets.push_back(actor);
            else sweep.throwables.push_back({ actor, kind });
        }
    }

    [[nodiscard]] inline bool is_fire_rate_an_interval() {
        double highest = 0.0;
        for (const auto& [settings, original] : stats_originals)
            highest = std::max(highest, original.stats.fire_rate);

        return highest <= tune::fire_interval_ceiling;
    }

    [[nodiscard]] inline sdk::hw2::weapon_stats tuned_stats(const sdk::hw2::weapon_stats& original, bool is_interval) {
        const weapon_options& options = weapon_setup;
        sdk::hw2::weapon_stats tuned = original;

        if (options.is_fire_rate && options.fire_rate > 0.0f) {
            const double scale = is_interval ? 1.0 / options.fire_rate : options.fire_rate;
            tuned.fire_rate *= scale;
            tuned.burst_fire_rate *= scale;
        }

        if (options.is_recoil) {
            tuned.vertical_recoil_min *= options.recoil;
            tuned.vertical_recoil_max *= options.recoil;
            tuned.horizontal_recoil_min *= options.recoil;
            tuned.horizontal_recoil_max *= options.recoil;
        }

        if (options.is_damage) {
            tuned.damage *= options.damage;
            tuned.headshot *= options.headshot;
        }

        if (options.is_rapid_fire) tuned.is_pump_action = false;

        if (options.is_no_falloff) tuned.falloff_min = tune::no_falloff_floor;

        if (options.is_bullet_speed) tuned.bullet_velocity *= options.bullet_speed;

        if (options.hit_reg != keep_game) tuned.is_client_hit_reg = options.hit_reg == force_on;
        if (options.hit_scan != keep_game) tuned.is_hit_scan = options.hit_scan == force_on;

        if (aim_setup.is_silent && aim_status.is_open) {
            tuned.is_hit_scan = false;
            tuned.is_client_hit_reg = false;
        }

        if (options.is_pellets && original.is_shotgun) tuned.projectiles_per_shot = options.pellets;

        if (options.is_mag_size) tuned.ammo_per_mag = options.mag_size;

        return tuned;
    }

    [[nodiscard]] inline sdk::FLinearColor color_of(const float (&rgba)[4]) {
        return { rgba[0], rgba[1], rgba[2], rgba[3] };
    }

    [[nodiscard]] inline double paint_seconds() {
        using clock = std::chrono::steady_clock;
        static const clock::time_point first = clock::now();

        return std::chrono::duration<double>(clock::now() - first).count();
    }

    [[nodiscard]] inline sdk::FLinearColor hue_color(float hue, float alpha) {
        const float wrapped = (hue - std::floor(hue)) * 6.0f;
        const int sector = static_cast<int>(wrapped);
        const float ramp = wrapped - static_cast<float>(sector);

        switch (sector) {
        case 0: return { 1.0f, ramp, 0.0f, alpha };
        case 1: return { 1.0f - ramp, 1.0f, 0.0f, alpha };
        case 2: return { 0.0f, 1.0f, ramp, alpha };
        case 3: return { 0.0f, 1.0f - ramp, 1.0f, alpha };
        case 4: return { ramp, 0.0f, 1.0f, alpha };
        default: return { 1.0f, 0.0f, 1.0f - ramp, alpha };
        }
    }

    struct skin_colors {
        sdk::FLinearColor a;
        sdk::FLinearColor b;
    };

    [[nodiscard]] inline skin_colors wanted_colors() {
        const weapon_options& options = weapon_setup;
        if (!options.is_rgb) return { color_of(options.color_a), color_of(options.color_b) };

        const float hue = static_cast<float>(paint_seconds() * options.rgb_speed);
        const float split = options.is_rgb_split ? tune::rgb_split : 0.0f;

        return { hue_color(hue, options.color_a[3]), hue_color(hue + split, options.color_b[3]) };
    }

    [[nodiscard]] inline std::string stat_line(const char* label, double original, double live) {
        char text[128];
        std::snprintf(text, sizeof(text), "[ weapons ]   %s %.3f -> %.3f", label, original, live);

        return text;
    }

}
