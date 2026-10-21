#pragma once
#include <atomic>
#include <chrono>
#include <cstdint>
#include <unordered_map>
#include <features/data/tune.hh>
#include <features/features.hh>
#include <sdk/unreal/view/camera.hh>
#include <sdk/hw2/match/rules.hh>
#include <sdk/hw2/arena/sandbox.hh>
#include <features/impl/combat/aim/aiming.hh>
#include <features/impl/combat/weapons/arsenal.hh>
#include <features/impl/match/host/lobby.hh>

namespace features::detail {

    inline std::chrono::steady_clock::time_point next_hunt;

    [[nodiscard]] inline sdk::UObject* own_streaks_now() {
        sdk::APlayerController* controller = own_controller();
        if (!controller) return nullptr;

        return sdk::hw2::streak_component_of({ controller, controller->PlayerState(), controller->Pawn() });
    }

    [[nodiscard]] inline bool streak_point(const sdk::APawn* pawn, sdk::FVector& where) {
        where = pawn->origin();
        if (!streak_setup.is_place_ahead) return true;

        const game::camera::view& eye = game::camera::current();
        if (!eye.is_valid) return false;

        const sdk::FVector ahead = forward_of(eye.rotation);
        const double reach = static_cast<double>(streak_setup.place_distance) * tune::units_per_metre;
        where = { eye.location.X + ahead.X * reach, eye.location.Y + ahead.Y * reach, eye.location.Z + ahead.Z * reach };

        return true;
    }

    [[nodiscard]] inline int hunt_with_bots(std::uintptr_t prey_id, bool is_enemies_only) {
        sdk::APlayerState* prey = lobby_member(prey_id);
        sdk::APawn* body = prey ? prey->PawnPrivate() : nullptr;
        if (!body || sdk::hw2::is_dead(body)) return -1;

        const sdk::AGameStateBase* state = sdk::hw2::match_game_state();
        if (!state) return -1;

        const int prey_team = sdk::hw2::team_of(prey);
        const sdk::TArray<sdk::APlayerState*> players = state->PlayerArray();
        if (players.num() <= 0 || players.num() > lobby_cap) return -1;

        int told = 0;
        for (std::int32_t i = 0; i < players.num(); ++i) {
            const sdk::APlayerState* member = players.at(i);
            if (!member || member == prey || !sdk::hw2::is_bot(member)) continue;
            if (is_enemies_only && sdk::hw2::team_of(member) == prey_team) continue;

            if (sdk::hw2::bot_on_damaged(sdk::hw2::controller_of(member), body)) ++told;
        }

        return told;
    }

    inline sdk::hw2::dev_mode original_dev;
    inline bool is_dev_saved = false;

    inline sdk::hw2::bot_brain original_brain;
    inline bool is_brain_saved = false;

    inline std::unordered_map<int, sdk::hw2::bot_tier> original_tiers;
    inline std::atomic<bool> is_arena_pass_queued{ false };

    inline const sdk::hw2::dev_mode* saved_dev() {
        if (is_dev_saved) return &original_dev;

        is_dev_saved = sdk::hw2::read_dev_mode(original_dev);

        return is_dev_saved ? &original_dev : nullptr;
    }

    inline const sdk::hw2::bot_brain* saved_brain() {
        if (is_brain_saved) return &original_brain;

        is_brain_saved = sdk::hw2::read_bot_brain(original_brain);

        return is_brain_saved ? &original_brain : nullptr;
    }

    inline const sdk::hw2::bot_tier* saved_tier(int index) {
        const auto found = original_tiers.find(index);
        if (found != original_tiers.end()) return &found->second;

        sdk::hw2::bot_tier tier;
        if (!sdk::hw2::read_bot_tier(index, tier)) return nullptr;

        return &(original_tiers[index] = tier);
    }

    [[nodiscard]] inline sdk::hw2::dev_mode dev_from_options() {
        const dev_options& options = dev_setup;
        sdk::hw2::dev_mode mode;

        mode.is_enabled = options.is_enabled;
        mode.is_esp = options.is_esp;
        mode.is_esp_overlay = options.is_esp_overlay;
        mode.esp_color = { options.esp_color[0], options.esp_color[1], options.esp_color[2], options.esp_color[3] };
        mode.esp_radius = options.esp_radius;
        mode.esp_height = options.esp_height;
        mode.esp_distance = options.esp_distance;

        const sdk::hw2::dev_mode* original = saved_dev();
        mode.team_size = options.is_lobby_size ? options.team_size : (original ? original->team_size : 0);
        mode.max_players = options.is_lobby_size ? options.max_players : (original ? original->max_players : 0);

        return mode;
    }

    inline void dev_to_options(const sdk::hw2::dev_mode& mode) {
        dev_options& options = dev_setup;

        options.is_enabled = mode.is_enabled;
        options.is_esp = mode.is_esp;
        options.is_esp_overlay = mode.is_esp_overlay;
        options.esp_color[0] = mode.esp_color.R;
        options.esp_color[1] = mode.esp_color.G;
        options.esp_color[2] = mode.esp_color.B;
        options.esp_color[3] = mode.esp_color.A;
        options.esp_radius = mode.esp_radius;
        options.esp_height = mode.esp_height;
        options.esp_distance = mode.esp_distance;
        options.team_size = mode.team_size;
        options.max_players = mode.max_players;
    }

    [[nodiscard]] inline sdk::hw2::bot_tier tier_from_options() {
        const bot_options& options = bot_setup;
        sdk::hw2::bot_tier tier;

        tier.aim_turn_rate = options.aim_turn_rate;
        tier.aim_reaction_delay = options.aim_reaction_delay;
        tier.aim_error_initial = options.aim_error_initial;
        tier.aim_error_settled = options.aim_error_settled;
        tier.aim_settle_time = options.aim_settle_time;
        tier.aim_fire_angle = options.aim_fire_angle;
        tier.burst_duration = options.burst_duration;
        tier.burst_rest = options.burst_rest;
        tier.aim_latency = options.aim_latency;
        tier.aim_predict_skill = options.aim_predict_skill;
        tier.reaction_time = options.reaction_time;
        tier.spread_multiplier = options.spread_multiplier;
        tier.moving_spread_scale = options.moving_spread_scale;
        tier.max_bots_per_target = options.max_bots_per_target;
        tier.engage_range = options.engage_range;
        tier.max_fire_range = options.max_fire_range;
        tier.detect_time = options.detect_time;
        tier.flinch_spread = options.flinch_spread;
        tier.pursuit_scale = options.pursuit_scale;

        return tier;
    }

    inline void tier_to_options(const sdk::hw2::bot_tier& tier) {
        bot_options& options = bot_setup;

        options.aim_turn_rate = tier.aim_turn_rate;
        options.aim_reaction_delay = tier.aim_reaction_delay;
        options.aim_error_initial = tier.aim_error_initial;
        options.aim_error_settled = tier.aim_error_settled;
        options.aim_settle_time = tier.aim_settle_time;
        options.aim_fire_angle = tier.aim_fire_angle;
        options.burst_duration = tier.burst_duration;
        options.burst_rest = tier.burst_rest;
        options.aim_latency = tier.aim_latency;
        options.aim_predict_skill = tier.aim_predict_skill;
        options.reaction_time = tier.reaction_time;
        options.spread_multiplier = tier.spread_multiplier;
        options.moving_spread_scale = tier.moving_spread_scale;
        options.max_bots_per_target = tier.max_bots_per_target;
        options.engage_range = tier.engage_range;
        options.max_fire_range = tier.max_fire_range;
        options.detect_time = tier.detect_time;
        options.flinch_spread = tier.flinch_spread;
        options.pursuit_scale = tier.pursuit_scale;
    }

    [[nodiscard]] inline sdk::hw2::bot_brain brain_from_options() {
        const bot_options& options = bot_setup;
        sdk::hw2::bot_brain brain;

        brain.aim_interp_speed = options.aim_interp_speed;
        brain.aim_error_interval = options.aim_error_interval;
        brain.aim_target_z_offset = options.aim_target_z_offset;
        brain.hearing_radius = options.hearing_radius;
        brain.memory_seconds = options.memory_seconds;
        brain.is_perceived_aim = options.is_perceived_aim;
        brain.is_movement_spread = options.is_movement_spread;

        return brain;
    }

    inline void brain_to_options(const sdk::hw2::bot_brain& brain) {
        bot_options& options = bot_setup;

        options.aim_interp_speed = brain.aim_interp_speed;
        options.aim_error_interval = brain.aim_error_interval;
        options.aim_target_z_offset = brain.aim_target_z_offset;
        options.hearing_radius = brain.hearing_radius;
        options.memory_seconds = brain.memory_seconds;
        options.is_perceived_aim = brain.is_perceived_aim;
        options.is_movement_spread = brain.is_movement_spread;
    }

}
