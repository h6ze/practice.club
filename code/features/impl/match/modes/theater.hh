#pragma once
#include <atomic>
#include <chrono>
#include <cstdint>
#include <mutex>
#include <string>
#include <utility>
#include <vector>
#include <features/data/tune.hh>
#include <features/features.hh>
#include <sdk/core/access.hh>
#include <sdk/unreal/query/lookup.hh>
#include <sdk/hw2/match/objectives.hh>
#include <sdk/hw2/match/rules.hh>
#include <sdk/offsets.generated.hh>
#include <features/impl/combat/weapons/arsenal.hh>
#include <features/impl/match/host/lobby.hh>

namespace features::detail {

    inline std::mutex modes_lock;
    inline modes_snapshot latest_modes;
    inline std::atomic<bool> is_modes_pass_queued{ false };
    inline std::chrono::steady_clock::time_point modes_watched_until;
    inline std::chrono::steady_clock::time_point next_modes_refresh;
    inline constexpr std::chrono::milliseconds modes_refresh_every{ 500 };
    inline constexpr std::chrono::seconds modes_watch_window{ 1 };

    [[nodiscard]] inline sdk::AActor* picked_objective(std::uintptr_t id) {
        if (!id) return nullptr;

        for (sdk::AActor* objective : sdk::hw2::objectives())
            if (reinterpret_cast<std::uintptr_t>(objective) == id) return objective;

        return nullptr;
    }

    [[nodiscard]] inline sdk::AActor* picked_spawn(std::uintptr_t id) {
        if (!id) return nullptr;

        for (sdk::AActor* spawn : sdk::hw2::spawn_points())
            if (reinterpret_cast<std::uintptr_t>(spawn) == id) return spawn;

        return nullptr;
    }

    [[nodiscard]] inline sdk::UObject* mode_state_of(const char* class_name) {
        sdk::AGameStateBase* state = sdk::hw2::match_game_state();

        return sdk::lookup::derives_from(state, class_name) ? state : nullptr;
    }

    [[nodiscard]] inline sdk::UObject* picked_of_kind(sdk::hw2::objective_kind kind) {
        sdk::AActor* objective = picked_objective(modes_setup.objective);

        return objective && sdk::hw2::objective_kind_of(objective) == kind ? objective : nullptr;
    }

    [[nodiscard]] inline sdk::UObject* own_spectator() {
        sdk::APawn* pawn = own_pawn();

        return sdk::lookup::derives_from(pawn, "BP_SpectatorBase_C") ? pawn : nullptr;
    }

    [[nodiscard]] inline const char* objective_kind_name(sdk::hw2::objective_kind kind) {
        switch (kind) {
        case sdk::hw2::objective_kind::capture_point: return "capture point";
        case sdk::hw2::objective_kind::snd_site: return "bomb site";
        case sdk::hw2::objective_kind::rush_site: return "rush site";
        case sdk::hw2::objective_kind::other: return "objective";
        }

        return "objective";
    }

    [[nodiscard]] inline objective_entry describe_objective(sdk::AActor* objective) {
        namespace off = sdk::offsets;

        objective_entry entry;
        entry.id = reinterpret_cast<std::uintptr_t>(objective);

        const sdk::hw2::objective_kind kind = sdk::hw2::objective_kind_of(objective);
        entry.kind = static_cast<int>(kind);

        const std::string id = sdk::hw2::objective_id(objective).text();
        entry.label = std::string(objective_kind_name(kind)) + (id.empty() || id == "None" ? "" : " " + id);

        switch (kind) {
        case sdk::hw2::objective_kind::capture_point:
            entry.state = sdk::mem::read<std::uint8_t>(objective, off::hw2_capture_point::objetive_state);
            entry.team = sdk::mem::read<bool>(objective, off::hw2_capture_point::is_holder_team) ? 1 : 0;
            entry.points = sdk::mem::read<int>(objective, off::hw2_capture_point::points);
            break;
        case sdk::hw2::objective_kind::snd_site:
            entry.state = sdk::mem::read<std::uint8_t>(objective, off::hw2_snd_site::bomb_state);
            entry.team = sdk::mem::read<int>(objective, off::hw2_snd_site::team);
            break;
        case sdk::hw2::objective_kind::rush_site:
            entry.state = sdk::mem::read<std::uint8_t>(objective, off::hw2_rush_site::bomb_state);
            entry.team = sdk::mem::read<int>(objective, off::hw2_rush_site::team);
            entry.points = sdk::mem::read<int>(objective, off::hw2_rush_site::phase);
            break;
        case sdk::hw2::objective_kind::other:
            break;
        }

        return entry;
    }

    [[nodiscard]] inline modes_snapshot take_modes_snapshot() {
        namespace off = sdk::offsets;

        modes_snapshot fresh;
        fresh.mode = static_cast<int>(sdk::hw2::mode_of_match());

        for (sdk::AActor* objective : sdk::hw2::objectives()) fresh.objectives.push_back(describe_objective(objective));

        const sdk::APawn* mine = own_pawn();
        const sdk::FVector here = mine ? mine->origin() : sdk::FVector{};

        const std::vector<sdk::AActor*> spawns = sdk::hw2::spawn_points();
        for (std::size_t i = 0; i < spawns.size(); ++i) {
            const sdk::AActor* spawn = spawns[i];

            spawn_entry entry;
            entry.id = reinterpret_cast<std::uintptr_t>(spawn);
            entry.index = static_cast<int>(i);
            entry.team = sdk::mem::read<int>(spawn, off::hw2_player_spawn::team);
            entry.phase = sdk::mem::read<int>(spawn, off::hw2_player_spawn::phase);
            entry.is_active = sdk::mem::read<bool>(spawn, off::hw2_player_spawn::is_active);
            entry.is_claimed = sdk::mem::read<bool>(spawn, off::hw2_player_spawn::is_claimed);
            entry.distance = mine ? static_cast<float>((spawn->origin() - here).length() / tune::units_per_metre) : 0.0f;

            fresh.spawns.push_back(entry);
        }

        const sdk::AActor* bomb = sdk::hw2::snd_bomb();
        fresh.has_bomb = bomb != nullptr;

        const sdk::APawn* carrier = static_cast<const sdk::APawn*>(sdk::hw2::bomb_carrier(bomb));
        const sdk::APlayerState* holder = carrier ? carrier->PlayerState() : nullptr;
        if (holder) fresh.bomb_carrier = name_of(holder);

        return fresh;
    }

    [[nodiscard]] inline sdk::APawn* acting_pawn(bool is_by_picked, std::uintptr_t target, std::string& who) {
        if (!is_by_picked) {
            who = "you";
            return own_character();
        }

        sdk::APlayerState* member = chosen_member(target);
        if (!member) return nullptr;

        who = name_of(member);
        sdk::APawn* pawn = member->PawnPrivate();

        return pawn && sdk::hw2::kind_of(pawn) == sdk::hw2::actor_kind::character ? pawn : nullptr;
    }

    [[nodiscard]] inline sdk::AController* acting_controller(bool is_by_picked, std::uintptr_t target, std::string& who) {
        if (!is_by_picked) {
            who = "you";
            return own_controller();
        }

        sdk::APlayerState* member = chosen_member(target);
        if (!member) return nullptr;

        who = name_of(member);

        return sdk::hw2::controller_of(member);
    }

    inline void say_mode(bool is_called, const std::string& done, const char* function_name) {
        if (is_called) { logger::success("[ modes ] " + done); return; }

        logger::error(std::string("[ modes ] ") + function_name + " could not be called -> wrong mode, nothing picked, or read the call line above");
    }

}
