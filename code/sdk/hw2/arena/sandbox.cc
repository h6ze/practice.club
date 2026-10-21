#include "sandbox.hh"
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/core/container.hh>
#include <sdk/core/text/encoding.hh>
#include <sdk/offsets.generated.hh>
#include <sdk/unreal/query/lookup.hh>

namespace sdk::hw2::detail {

    struct held_default {
        UObject* object = nullptr;
        std::int32_t index = -1;
    };

    inline held_default dev_default;
    inline held_default bot_default;
    inline held_default streak_default;
    inline held_default mode_default;
    inline held_default streak_settings_default;
    inline held_default bot_library_default;

    inline std::vector<lookup::held> streak_components;

    inline lookup::held car;
    inline ULONGLONG next_car_search = 0;
    constexpr ULONGLONG car_search_every_ms = 1000;

    [[nodiscard]] inline UObject* default_of(held_default& held, const char* class_name) {
        if (held.object && objects::at(held.index) == held.object) return held.object;

        UClass* type = objects::find_class(class_name);
        held.object = type ? type->default_object() : nullptr;
        held.index = held.object ? held.object->index() : -1;

        return held.object;
    }

    inline constexpr std::uint32_t tier_stride = 0x60;

    [[nodiscard]] inline std::uint8_t* tier_at(int index) {
        const TArray<std::uint8_t> tiers = mem::read<TArray<std::uint8_t>>(
            default_of(bot_default, "HW2BotSettings"), offsets::hw2_bot_settings::tiers, TArray<std::uint8_t>{});
        if (!tiers.Data || index < 0 || index >= tiers.num()) return nullptr;

        return tiers.Data + static_cast<std::uint32_t>(index) * tier_stride;
    }

}

sdk::UObject* sdk::hw2::dev_settings() {
    return detail::default_of(detail::dev_default, "HW2FunnyModeSettings");
}

bool sdk::hw2::read_dev_mode(dev_mode& mode) noexcept {
    const UObject* settings = dev_settings();
    if (!settings) return false;

    namespace field = offsets::hw2_funny_settings;

    mode.is_enabled = mem::read<bool>(settings, field::is_funny_mode);
    mode.is_esp = mem::read<bool>(settings, field::is_esp);
    mode.is_esp_overlay = mem::read<bool>(settings, field::is_esp_overlay);
    mode.esp_color = mem::read<FLinearColor>(settings, field::esp_color, FLinearColor{});
    mode.esp_radius = mem::read<float>(settings, field::esp_radius);
    mode.esp_height = mem::read<float>(settings, field::esp_height);
    mode.esp_distance = mem::read<float>(settings, field::esp_distance);
    mode.team_size = mem::read<int>(settings, field::team_size);
    mode.max_players = mem::read<int>(settings, field::max_players);

    return true;
}

bool sdk::hw2::write_dev_mode(const dev_mode& mode) noexcept {
    UObject* settings = dev_settings();
    if (!settings) return false;

    namespace field = offsets::hw2_funny_settings;

    bool is_written = mem::write<bool>(settings, field::is_funny_mode, mode.is_enabled);
    is_written &= mem::write<bool>(settings, field::is_esp, mode.is_esp);
    is_written &= mem::write<bool>(settings, field::is_esp_overlay, mode.is_esp_overlay);
    is_written &= mem::write<FLinearColor>(settings, field::esp_color, mode.esp_color);
    is_written &= mem::write<float>(settings, field::esp_radius, mode.esp_radius);
    is_written &= mem::write<float>(settings, field::esp_height, mode.esp_height);
    is_written &= mem::write<float>(settings, field::esp_distance, mode.esp_distance);
    is_written &= mem::write<int>(settings, field::team_size, mode.team_size);
    is_written &= mem::write<int>(settings, field::max_players, mode.max_players);

    return is_written;
}

bool sdk::hw2::is_dev_mode_active() {
    call::invocation entry(detail::default_of(detail::mode_default, "HW2FunnyModeLibrary"), "IsFunnyModeActive");
    if (!entry.is_valid() || !entry.fire()) return false;

    return entry.get<bool>(0);
}

sdk::UObject* sdk::hw2::bot_settings() {
    return detail::default_of(detail::bot_default, "HW2BotSettings");
}

int sdk::hw2::bot_tier_count() noexcept {
    return mem::read<TArray<std::uint8_t>>(bot_settings(), offsets::hw2_bot_settings::tiers, TArray<std::uint8_t>{}).num();
}

std::string sdk::hw2::bot_tier_name(int index) {
    const std::uint8_t* tier = detail::tier_at(index);
    if (!tier) return std::string{};

    return narrow(mem::read<FString>(tier, 0, FString{}));
}

bool sdk::hw2::read_bot_tier(int index, bot_tier& tier) noexcept {
    const std::uint8_t* entry = detail::tier_at(index);
    if (!entry) return false;

    namespace field = offsets::hw2_bot_tier;

    tier.aim_turn_rate = mem::read<float>(entry, field::aim_turn_rate);
    tier.aim_reaction_delay = mem::read<float>(entry, field::aim_reaction_delay);
    tier.aim_error_initial = mem::read<float>(entry, field::aim_error_initial);
    tier.aim_error_settled = mem::read<float>(entry, field::aim_error_settled);
    tier.aim_settle_time = mem::read<float>(entry, field::aim_settle_time);
    tier.aim_fire_angle = mem::read<float>(entry, field::aim_fire_angle);
    tier.burst_duration = mem::read<float>(entry, field::burst_duration);
    tier.burst_rest = mem::read<float>(entry, field::burst_rest);
    tier.aim_latency = mem::read<float>(entry, field::aim_latency);
    tier.aim_predict_skill = mem::read<float>(entry, field::aim_predict_skill);
    tier.reaction_time = mem::read<float>(entry, field::reaction_time);
    tier.spread_multiplier = mem::read<float>(entry, field::spread_multiplier);
    tier.moving_spread_scale = mem::read<float>(entry, field::moving_spread_scale);
    tier.max_bots_per_target = mem::read<int>(entry, field::max_bots_per_target);
    tier.engage_range = mem::read<float>(entry, field::engage_range);
    tier.max_fire_range = mem::read<float>(entry, field::max_fire_range);
    tier.detect_time = mem::read<float>(entry, field::detect_time);
    tier.flinch_spread = mem::read<float>(entry, field::flinch_spread);
    tier.pursuit_scale = mem::read<float>(entry, field::pursuit_scale);

    return tier.aim_turn_rate > 0.0f && tier.engage_range > 0.0f;
}

bool sdk::hw2::write_bot_tier(int index, const bot_tier& tier) noexcept {
    std::uint8_t* entry = detail::tier_at(index);
    if (!entry) return false;

    namespace field = offsets::hw2_bot_tier;

    bool is_written = mem::write<float>(entry, field::aim_turn_rate, tier.aim_turn_rate);
    is_written &= mem::write<float>(entry, field::aim_reaction_delay, tier.aim_reaction_delay);
    is_written &= mem::write<float>(entry, field::aim_error_initial, tier.aim_error_initial);
    is_written &= mem::write<float>(entry, field::aim_error_settled, tier.aim_error_settled);
    is_written &= mem::write<float>(entry, field::aim_settle_time, tier.aim_settle_time);
    is_written &= mem::write<float>(entry, field::aim_fire_angle, tier.aim_fire_angle);
    is_written &= mem::write<float>(entry, field::burst_duration, tier.burst_duration);
    is_written &= mem::write<float>(entry, field::burst_rest, tier.burst_rest);
    is_written &= mem::write<float>(entry, field::aim_latency, tier.aim_latency);
    is_written &= mem::write<float>(entry, field::aim_predict_skill, tier.aim_predict_skill);
    is_written &= mem::write<float>(entry, field::reaction_time, tier.reaction_time);
    is_written &= mem::write<float>(entry, field::spread_multiplier, tier.spread_multiplier);
    is_written &= mem::write<float>(entry, field::moving_spread_scale, tier.moving_spread_scale);
    is_written &= mem::write<int>(entry, field::max_bots_per_target, tier.max_bots_per_target);
    is_written &= mem::write<float>(entry, field::engage_range, tier.engage_range);
    is_written &= mem::write<float>(entry, field::max_fire_range, tier.max_fire_range);
    is_written &= mem::write<float>(entry, field::detect_time, tier.detect_time);
    is_written &= mem::write<float>(entry, field::flinch_spread, tier.flinch_spread);
    is_written &= mem::write<float>(entry, field::pursuit_scale, tier.pursuit_scale);

    return is_written;
}

bool sdk::hw2::read_bot_brain(bot_brain& brain) noexcept {
    const UObject* settings = bot_settings();
    if (!settings) return false;

    namespace field = offsets::hw2_bot_settings;

    brain.aim_interp_speed = mem::read<float>(settings, field::aim_interp_speed);
    brain.aim_error_interval = mem::read<float>(settings, field::aim_error_interval);
    brain.aim_target_z_offset = mem::read<float>(settings, field::aim_target_z_offset);
    brain.hearing_radius = mem::read<float>(settings, field::hearing_radius);
    brain.memory_seconds = mem::read<float>(settings, field::memory_seconds);
    brain.is_perceived_aim = mem::read<bool>(settings, field::is_perceived_aim);
    brain.is_movement_spread = mem::read<bool>(settings, field::is_movement_spread);

    return brain.aim_interp_speed > 0.0f;
}

bool sdk::hw2::write_bot_brain(const bot_brain& brain) noexcept {
    UObject* settings = bot_settings();
    if (!settings) return false;

    namespace field = offsets::hw2_bot_settings;

    bool is_written = mem::write<float>(settings, field::aim_interp_speed, brain.aim_interp_speed);
    is_written &= mem::write<float>(settings, field::aim_error_interval, brain.aim_error_interval);
    is_written &= mem::write<float>(settings, field::aim_target_z_offset, brain.aim_target_z_offset);
    is_written &= mem::write<float>(settings, field::hearing_radius, brain.hearing_radius);
    is_written &= mem::write<float>(settings, field::memory_seconds, brain.memory_seconds);
    is_written &= mem::write<bool>(settings, field::is_perceived_aim, brain.is_perceived_aim);
    is_written &= mem::write<bool>(settings, field::is_movement_spread, brain.is_movement_spread);

    return is_written;
}

const char* sdk::hw2::killstreak_name(killstreak streak) noexcept {
    switch (streak) {
    case killstreak::snitch: return "snitch";
    case killstreak::homies: return "homies";
    case killstreak::suicide_bomber: return "suicide bomber";
    case killstreak::drive_by: return "drive by";
    }

    return "unknown";
}

bool sdk::hw2::activate_killstreak(AActor* context, killstreak streak) {
    call::invocation entry(detail::default_of(detail::streak_default, "HW2KillstreakLibrary"), "HW2KillstreakActivate");
    if (!entry.is_valid()) return false;

    namespace parm = offsets::params::killstreak_activate;

    entry.set<AActor*>(parm::context, context);
    entry.set<std::uint8_t>(parm::streak, static_cast<std::uint8_t>(streak));
    if (!entry.fire()) return false;

    return entry.get<bool>(parm::is_activated);
}

bool sdk::hw2::activate_killstreak_slot(AActor* context, int slot) {
    call::invocation entry(detail::default_of(detail::streak_default, "HW2KillstreakLibrary"), "HW2KillstreakActivateSlot");
    if (!entry.is_valid()) return false;

    namespace parm = offsets::params::killstreak_activate_slot;

    entry.set<AActor*>(parm::context, context);
    entry.set<int>(parm::slot, slot);
    if (!entry.fire()) return false;

    return entry.get<bool>(parm::is_activated);
}

bool sdk::hw2::place_killstreak(AActor* context, const FVector& location) {
    call::invocation entry(detail::default_of(detail::streak_default, "HW2KillstreakLibrary"), "HW2KillstreakPlace");
    if (!entry.is_valid()) return false;

    namespace parm = offsets::params::killstreak_place;

    entry.set<AActor*>(parm::context, context);
    entry.set<FVector>(parm::location, location);

    return entry.fire();
}

sdk::UObject* sdk::hw2::streak_settings() {
    return detail::default_of(detail::streak_settings_default, "HW2KillstreakSettings");
}

sdk::UObject* sdk::hw2::streak_component_of(std::initializer_list<const UObject*> owners) {
    std::vector<lookup::held>& known = detail::streak_components;
    known.erase(std::remove_if(known.begin(), known.end(), [](const lookup::held& slot) { return !lookup::is_live(slot); }), known.end());

    for (const lookup::held& slot : known) {
        const UObject* outer = slot.object->outer();
        for (const UObject* owner : owners)
            if (owner && outer == owner) return slot.object;
    }

    UObject* found = lookup::find_owned("HW2KillstreakComponent", owners);
    if (found) known.push_back({ found, found->index() });

    return found;
}

bool sdk::hw2::restore_killstreaks(UObject* component, int ready_mask) {
    return call::fire_with<int>(component, "HW2RestoreMigratedKillstreaks", offsets::params::restore_killstreaks::mask, ready_mask);
}

bool sdk::hw2::set_equipped_streaks(UObject* component, std::uint8_t mask) {
    return call::fire_with<std::uint8_t>(component, "ServerSetEquipped", offsets::params::set_equipped_streaks::mask, mask);
}

bool sdk::hw2::use_streak(UObject* component, killstreak streak) {
    return call::fire_with<std::uint8_t>(component, "ServerUse", offsets::params::use_streak::streak, static_cast<std::uint8_t>(streak));
}

sdk::UObject* sdk::hw2::old_streaks_of(const APlayerState* player_state) {
    UObject* component = mem::pointer<UObject>(player_state, offsets::hw2_player_state::old_streaks);

    return lookup::derives_from(component, "AC_KillStreak_C") ? component : nullptr;
}

bool sdk::hw2::spawn_cluster_strike(UObject* component, const FVector& location) {
    return call::fire_with<FVector>(component, "SpawnClusterStrike", offsets::params::spawn_cluster_strike::location, location);
}

bool sdk::hw2::set_kill_streak(UObject* component, int count) {
    return call::fire_with<int>(component, "SetKillStreak", offsets::params::set_kill_streak::count, count);
}

bool sdk::hw2::bot_on_damaged(AController* bot, APawn* shooter) {
    if (!bot || !shooter) return false;

    call::invocation entry(detail::default_of(detail::bot_library_default, "HW2BotLibrary"), "HW2BotOnDamaged");
    if (!entry.is_valid()) return false;

    entry.set<AController*>(offsets::params::bot_on_damaged::controller, bot);
    entry.set<APawn*>(offsets::params::bot_on_damaged::shooter, shooter);

    return entry.fire();
}

bool sdk::hw2::drop_spawn_protection(APawn* pawn) {
    return call::fire(mem::pointer<UObject>(pawn, offsets::hw2_character::health_component), "DisableSpawnProtection");
}

sdk::AActor* sdk::hw2::drive_by_car() {
    if (lookup::is_live(detail::car)) return static_cast<AActor*>(detail::car.object);

    const ULONGLONG now = GetTickCount64();
    if (now < detail::next_car_search) return nullptr;
    detail::next_car_search = now + detail::car_search_every_ms;

    UObject* found = objects::find_live_instance(objects::find_class("HW2DriveByCar"));
    detail::car = { found, found ? found->index() : -1 };

    return static_cast<AActor*>(found);
}

int sdk::hw2::set_summoned_team(int team) {
    int moved = 0;
    for (UObject* marker : lookup::live_instances("HW2SummonedBotMarker"))
        moved += mem::write<int>(marker, offsets::hw2_summoned_marker::team, team) ? 1 : 0;

    return moved;
}
