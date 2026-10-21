#include "combat.hh"
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/offsets.generated.hh>
#include <sdk/unreal/runtime/strings.hh>

sdk::UObject* sdk::hw2::guard_settings() {
    UClass* type = objects::find_class("HW2ServerGuardSettings");

    return type ? type->default_object() : nullptr;
}

bool sdk::hw2::read_guard(guard_switches& switches) {
    const UObject* settings = guard_settings();
    if (!settings) return false;

    namespace field = offsets::hw2_guard_settings;

    switches.is_enabled = mem::read<bool>(settings, field::is_enabled);
    switches.is_enforce = mem::read<bool>(settings, field::is_enforce);
    switches.is_kick = mem::read<bool>(settings, field::is_kick);
    switches.is_check_shots = mem::read<bool>(settings, field::is_check_shots);
    switches.is_check_sight = mem::read<bool>(settings, field::is_check_sight);
    switches.is_check_movement = mem::read<bool>(settings, field::is_check_movement);

    return true;
}

bool sdk::hw2::write_guard(const guard_switches& switches) {
    UObject* settings = guard_settings();
    if (!settings) return false;

    namespace field = offsets::hw2_guard_settings;

    bool is_written = mem::write<bool>(settings, field::is_enabled, switches.is_enabled);
    is_written &= mem::write<bool>(settings, field::is_enforce, switches.is_enforce);
    is_written &= mem::write<bool>(settings, field::is_kick, switches.is_kick);
    is_written &= mem::write<bool>(settings, field::is_check_shots, switches.is_check_shots);
    is_written &= mem::write<bool>(settings, field::is_check_sight, switches.is_check_sight);
    is_written &= mem::write<bool>(settings, field::is_check_movement, switches.is_check_movement);

    return is_written;
}

bool sdk::hw2::read_limits(guard_limits& limits) {
    const UObject* settings = guard_settings();
    if (!settings) return false;

    namespace field = offsets::hw2_guard_settings;

    limits.max_trace_offset = mem::read<float>(settings, field::max_trace_offset);
    limits.hit_leeway = mem::read<float>(settings, field::hit_leeway);
    limits.head_zone = mem::read<float>(settings, field::head_zone);
    limits.sight_leeway = mem::read<float>(settings, field::sight_leeway);

    limits.aim_refuse = mem::read<float>(settings, field::aim_refuse);
    limits.aim_score = mem::read<float>(settings, field::aim_score);
    limits.aim_suspect = mem::read<float>(settings, field::aim_suspect);
    limits.aim_recheck = mem::read<float>(settings, field::aim_recheck);
    limits.snap_degrees = mem::read<float>(settings, field::snap_degrees);
    limits.snap_window = mem::read<float>(settings, field::snap_window);

    limits.hits_per_pellet = mem::read<float>(settings, field::hits_per_pellet);
    limits.fire_rate_tolerance = mem::read<float>(settings, field::fire_rate_tolerance);
    limits.burst_shots = mem::read<float>(settings, field::burst_shots);
    limits.burst_seconds = mem::read<float>(settings, field::burst_seconds);

    limits.melee_leeway = mem::read<float>(settings, field::melee_leeway);
    limits.melee_interval = mem::read<float>(settings, field::melee_interval);

    limits.max_rewind = mem::read<float>(settings, field::max_rewind);
    limits.rewind_slack = mem::read<float>(settings, field::rewind_slack);

    limits.warn_score = mem::read<float>(settings, field::warn_score);
    limits.kick_score = mem::read<float>(settings, field::kick_score);
    limits.score_decay = mem::read<float>(settings, field::score_decay);
    limits.violation_gap = mem::read<float>(settings, field::violation_gap);
    limits.kick_delay = mem::read<float>(settings, field::kick_delay);

    return true;
}

bool sdk::hw2::write_limits(const guard_limits& limits) {
    UObject* settings = guard_settings();
    if (!settings) return false;

    namespace field = offsets::hw2_guard_settings;

    bool is_written = mem::write<float>(settings, field::max_trace_offset, limits.max_trace_offset);
    is_written &= mem::write<float>(settings, field::hit_leeway, limits.hit_leeway);
    is_written &= mem::write<float>(settings, field::head_zone, limits.head_zone);
    is_written &= mem::write<float>(settings, field::sight_leeway, limits.sight_leeway);

    is_written &= mem::write<float>(settings, field::aim_refuse, limits.aim_refuse);
    is_written &= mem::write<float>(settings, field::aim_score, limits.aim_score);
    is_written &= mem::write<float>(settings, field::aim_suspect, limits.aim_suspect);
    is_written &= mem::write<float>(settings, field::aim_recheck, limits.aim_recheck);
    is_written &= mem::write<float>(settings, field::snap_degrees, limits.snap_degrees);
    is_written &= mem::write<float>(settings, field::snap_window, limits.snap_window);

    is_written &= mem::write<float>(settings, field::hits_per_pellet, limits.hits_per_pellet);
    is_written &= mem::write<float>(settings, field::fire_rate_tolerance, limits.fire_rate_tolerance);
    is_written &= mem::write<float>(settings, field::burst_shots, limits.burst_shots);
    is_written &= mem::write<float>(settings, field::burst_seconds, limits.burst_seconds);

    is_written &= mem::write<float>(settings, field::melee_leeway, limits.melee_leeway);
    is_written &= mem::write<float>(settings, field::melee_interval, limits.melee_interval);

    is_written &= mem::write<float>(settings, field::max_rewind, limits.max_rewind);
    is_written &= mem::write<float>(settings, field::rewind_slack, limits.rewind_slack);

    is_written &= mem::write<float>(settings, field::warn_score, limits.warn_score);
    is_written &= mem::write<float>(settings, field::kick_score, limits.kick_score);
    is_written &= mem::write<float>(settings, field::score_decay, limits.score_decay);
    is_written &= mem::write<float>(settings, field::violation_gap, limits.violation_gap);
    is_written &= mem::write<float>(settings, field::kick_delay, limits.kick_delay);

    return is_written;
}

bool sdk::hw2::set_control_rotation(AController* controller, const FRotator& rotation) noexcept {
    return mem::write<FRotator>(controller, offsets::acontroller::control_rotation, rotation);
}

sdk::FName sdk::hw2::make_name(const char* text) {
    UClass* type = objects::find_class("KismetStringLibrary");
    UObject* library = type ? type->default_object() : nullptr;
    if (!library) return FName{};

    call::invocation entry(library, "Conv_StringToName");
    if (!entry.is_valid()) return FName{};

    const FString value = strings::make(text);
    if (!value.Data) return FName{};

    entry.set<FString>(offsets::params::string_to_name::in_string, value);
    if (!entry.fire()) return FName{};

    return entry.get<FName>(offsets::params::string_to_name::return_value);
}

bool sdk::hw2::socket_location(UObject* mesh, const FName& socket, FVector& location) {
    if (!mesh || socket.is_none()) return false;

    call::invocation entry(mesh, "GetSocketLocation");
    if (!entry.is_valid()) return false;

    entry.set<FName>(offsets::params::socket_location::socket_name, socket);
    if (!entry.fire()) return false;

    location = entry.get<FVector>(offsets::params::socket_location::return_value);

    return !location.is_zero();
}

bool sdk::hw2::has_line_of_sight(AController* controller, const AActor* other, const FVector& view_point) {
    if (!controller || !other) return false;

    call::invocation entry(controller, "LineOfSightTo");
    if (!entry.is_valid()) return false;

    entry.set<const AActor*>(offsets::params::line_of_sight::other, other);
    entry.set<FVector>(offsets::params::line_of_sight::view_point, view_point);
    entry.set<bool>(offsets::params::line_of_sight::is_alternate, false);
    if (!entry.fire()) return false;

    return entry.get<bool>(offsets::params::line_of_sight::return_value);
}
