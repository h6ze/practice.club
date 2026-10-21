#include "ledger.hh"
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/core/container.hh>
#include <sdk/offsets.generated.hh>
#include <sdk/unreal/query/lookup.hh>
#include <sdk/unreal/runtime/strings.hh>

namespace sdk::hw2::detail {

    inline lookup::held online_settings_default;

    constexpr std::int32_t mission_cap = 256;

    [[nodiscard]] inline UObject* cloud_sync_of(const APlayerController* controller) {
        UObject* sync = mem::pointer<UObject>(controller, offsets::hw2_controller::cloud_sync);

        return lookup::derives_from(sync, "HW2CloudSyncComponent") ? sync : nullptr;
    }

    [[nodiscard]] inline UObject* state_info_of(const APlayerState* player_state) {
        return mem::pointer<UObject>(player_state, offsets::hw2_player_state::state_info);
    }

    template <class T> [[nodiscard]] inline T get_only(UObject* object, const char* function_name, std::uint32_t offset) {
        call::invocation entry(object, function_name);
        if (!entry.is_valid() || !entry.fire()) return T{};

        return entry.get<T>(offset);
    }

    [[nodiscard]] inline bool fire_text(UObject* object, const char* function_name, std::uint32_t offset, const char* text) {
        if (!object || !text || !*text) return false;

        const FString value = strings::make(text);
        if (!value.Data) return false;

        return call::fire_with<FString>(object, function_name, offset, value);
    }

}

sdk::UObject* sdk::hw2::online_settings() {
    return lookup::class_default(detail::online_settings_default, "HW2OnlineSettings");
}

sdk::hw2::cloud_status sdk::hw2::read_cloud(const APlayerController* controller) {
    cloud_status status;

    UObject* sync = detail::cloud_sync_of(controller);
    if (!sync) return status;

    status.is_found = true;
    status.is_authenticated = detail::get_only<bool>(sync, "IsAuthenticated", offsets::params::cloud_authenticated::return_value);
    status.level = detail::get_only<int>(sync, "GetCloudLevel", offsets::params::cloud_level::return_value);
    status.total_xp = detail::get_only<int>(sync, "GetCloudTotalXp", offsets::params::cloud_total_xp::return_value);
    status.pending = detail::get_only<int>(sync, "GetPendingReportCount", offsets::params::cloud_pending::return_value);

    return status;
}

bool sdk::hw2::fetch_profile(APlayerController* controller) {
    return call::fire(detail::cloud_sync_of(controller), "FetchProfile");
}

bool sdk::hw2::give_exp(APlayerState* player_state, int amount) {
    if (!lookup::derives_from(player_state, "BP_PlayerState_C")) return false;

    return call::fire_with<int>(player_state, "GiveExp", offsets::params::give_exp::amount, amount);
}

bool sdk::hw2::add_experience(APlayerState* player_state, int amount) {
    return call::fire_with<int>(detail::state_info_of(player_state), "AddExperience", offsets::params::add_experience::amount, amount);
}

bool sdk::hw2::add_score(APlayerState* player_state, double score, std::uint8_t reason) {
    if (!lookup::derives_from(player_state, "BP_PlayerState_C")) return false;

    call::invocation entry(player_state, "AddScoreToPlayer");
    if (!entry.is_valid()) return false;

    entry.set<double>(offsets::params::add_score::score, score);
    entry.set<std::uint8_t>(offsets::params::add_score::reason, reason);

    return entry.fire();
}

bool sdk::hw2::increase_level(APlayerState* player_state) {
    return call::fire(detail::state_info_of(player_state), "IncreaseLevel");
}

bool sdk::hw2::save_level(APlayerState* player_state) {
    return call::fire(detail::state_info_of(player_state), "SaveLevel_Exp");
}

bool sdk::hw2::load_level(APlayerState* player_state) {
    return call::fire(detail::state_info_of(player_state), "Load_Level_Exp");
}

sdk::UObject* sdk::hw2::missions_of(const APlayerState* player_state) {
    UObject* missions = mem::pointer<UObject>(player_state, offsets::hw2_player_state::missions);

    return lookup::derives_from(missions, "AC_Missions_C") ? missions : nullptr;
}

std::vector<sdk::hw2::mission_entry> sdk::hw2::missions(const APlayerState* player_state) {
    std::vector<mission_entry> found;

    const UObject* component = missions_of(player_state);
    const TArray<std::uint8_t> list = mem::read<TArray<std::uint8_t>>(component, offsets::hw2_mission_set::missions, TArray<std::uint8_t>{});
    if (!list.Data || list.num() <= 0 || list.num() > detail::mission_cap) return found;

    for (std::int32_t i = 0; i < list.num(); ++i) {
        const std::uint8_t* item = list.Data + offsets::hw2_mission_layout::byte_size * static_cast<std::uint32_t>(i);
        const UObject* info = mem::pointer<UObject>(item, offsets::hw2_mission_entry::info);

        mission_entry entry;
        entry.progress = mem::read<int>(item, offsets::hw2_mission_entry::progress);
        entry.is_completed = mem::read<bool>(item, offsets::hw2_mission_entry::is_completed);
        entry.id = mem::read<int>(info, offsets::hw2_mission_info::id);
        entry.target = mem::read<int>(info, offsets::hw2_mission_info::target);
        entry.reward = mem::read<int>(info, offsets::hw2_mission_info::exp_reward);

        found.push_back(entry);
    }

    return found;
}

int sdk::hw2::complete_missions(APlayerState* player_state, int only_index) {
    const UObject* component = missions_of(player_state);
    const TArray<std::uint8_t> list = mem::read<TArray<std::uint8_t>>(component, offsets::hw2_mission_set::missions, TArray<std::uint8_t>{});
    if (!list.Data || list.num() <= 0 || list.num() > detail::mission_cap) return 0;

    int completed = 0;
    for (std::int32_t i = 0; i < list.num(); ++i) {
        if (only_index >= 0 && i != only_index) continue;

        std::uint8_t* item = list.Data + offsets::hw2_mission_layout::byte_size * static_cast<std::uint32_t>(i);
        const UObject* info = mem::pointer<UObject>(item, offsets::hw2_mission_entry::info);
        if (!info) continue;

        const int target = mem::read<int>(info, offsets::hw2_mission_info::target);
        const bool is_written = mem::write<int>(item, offsets::hw2_mission_entry::progress, target)
            && mem::write<bool>(item, offsets::hw2_mission_entry::is_completed, true);

        if (is_written) ++completed;
    }

    return completed;
}

bool sdk::hw2::save_missions(APlayerState* player_state) {
    return call::fire(missions_of(player_state), "SaveProgress");
}

bool sdk::hw2::missions_game_won(APlayerState* player_state, std::uint8_t mode) {
    return call::fire_with<std::uint8_t>(missions_of(player_state), "GameWon", offsets::params::missions_game_won::mode, mode);
}

bool sdk::hw2::missions_player_killed(APlayerState* player_state, std::uint8_t weapon_type) {
    return call::fire_with<std::uint8_t>(missions_of(player_state), "PlayerKilled", offsets::params::missions_player_killed::weapon_type, weapon_type);
}

sdk::UObject* sdk::hw2::progression_of(const APlayerController* controller) {
    UObject* progression = mem::pointer<UObject>(controller, offsets::hw2_controller::progression_component);

    return lookup::derives_from(progression, "AC_Progression_C") ? progression : nullptr;
}

bool sdk::hw2::notify_match_end(APlayerController* controller, bool is_won) {
    return call::fire_with<bool>(progression_of(controller), "NotifyMatchEnd", offsets::params::notify_match_end::is_won, is_won);
}

bool sdk::hw2::record_kill(APlayerController* controller, bool is_headshot) {
    return call::fire_with<bool>(progression_of(controller), "RecordKill", offsets::params::record_kill::is_headshot, is_headshot);
}

bool sdk::hw2::notify_local_kill(APlayerController* controller, const char* kind) {
    return detail::fire_text(progression_of(controller), "NotifyLocalKill", offsets::params::notify_local_kill::kind, kind);
}

bool sdk::hw2::bump_weapon_stat(APlayerController* controller, const char* suffix) {
    return detail::fire_text(progression_of(controller), "BumpWeaponStat", offsets::params::bump_weapon_stat::suffix, suffix);
}
