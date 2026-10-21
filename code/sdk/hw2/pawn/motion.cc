#include "motion.hh"
#include <cmath>
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/offsets.generated.hh>

sdk::UObject* sdk::hw2::movement_of(const APawn* pawn) noexcept {
    return mem::pointer<UObject>(pawn, offsets::acharacter::character_movement);
}

bool sdk::hw2::read_movement(const APawn* pawn, movement_stats& stats) noexcept {
    const UObject* movement = movement_of(pawn);
    if (!movement) return false;

    namespace field = offsets::ucharacter_movement;

    stats.gravity_scale = mem::read<float>(movement, field::gravity_scale);
    stats.max_step_height = mem::read<float>(movement, field::max_step_height);
    stats.jump_z_velocity = mem::read<float>(movement, field::jump_z_velocity);
    stats.walkable_floor_angle = mem::read<float>(movement, field::walkable_floor_angle);
    stats.ground_friction = mem::read<float>(movement, field::ground_friction);
    stats.max_acceleration = mem::read<float>(movement, field::max_acceleration);
    stats.braking_deceleration_walking = mem::read<float>(movement, field::braking_deceleration_walking);
    stats.air_control = mem::read<float>(movement, field::air_control);
    stats.jump_max_count = mem::read<int>(pawn, offsets::acharacter::jump_max_count);
    stats.ads_speed_extra = mem::read<double>(pawn, offsets::hw2_character::ads_speed_extra);
    stats.is_fall_damage = mem::read<bool>(pawn, offsets::hw2_character::is_fall_damage);
    stats.is_walk_off_ledges = mem::read_bit(movement, field::walk_off_ledges, field::walk_off_ledges_bit);
    stats.is_walk_off_ledges_crouching = mem::read_bit(movement, field::walk_off_ledges_crouching, field::walk_off_ledges_crouching_bit);
    stats.is_ignore_correction = mem::read_bit(movement, field::ignore_correction, field::ignore_correction_bit);

    return stats.max_step_height > 0.0f && stats.max_acceleration > 0.0f;
}

bool sdk::hw2::write_movement(APawn* pawn, const movement_stats& stats) noexcept {
    UObject* movement = movement_of(pawn);
    if (!movement) return false;

    namespace field = offsets::ucharacter_movement;

    bool is_written = mem::write<float>(movement, field::gravity_scale, stats.gravity_scale);
    is_written &= mem::write<float>(movement, field::max_step_height, stats.max_step_height);
    is_written &= mem::write<float>(movement, field::jump_z_velocity, stats.jump_z_velocity);
    is_written &= mem::write<float>(movement, field::ground_friction, stats.ground_friction);
    is_written &= mem::write<float>(movement, field::max_acceleration, stats.max_acceleration);
    is_written &= mem::write<float>(movement, field::braking_deceleration_walking, stats.braking_deceleration_walking);
    is_written &= mem::write<float>(movement, field::air_control, stats.air_control);
    is_written &= mem::write<int>(pawn, offsets::acharacter::jump_max_count, stats.jump_max_count);
    is_written &= mem::write<double>(pawn, offsets::hw2_character::ads_speed_extra, stats.ads_speed_extra);
    is_written &= mem::write<bool>(pawn, offsets::hw2_character::is_fall_damage, stats.is_fall_damage);
    is_written &= mem::write_bit(movement, field::walk_off_ledges, field::walk_off_ledges_bit, stats.is_walk_off_ledges);
    is_written &= mem::write_bit(movement, field::walk_off_ledges_crouching, field::walk_off_ledges_crouching_bit, stats.is_walk_off_ledges_crouching);
    is_written &= mem::write_bit(movement, field::ignore_correction, field::ignore_correction_bit, stats.is_ignore_correction);

    is_written &= mem::write<float>(movement, field::walkable_floor_angle, stats.walkable_floor_angle);
    is_written &= mem::write<float>(movement, field::walkable_floor_z, std::cos(stats.walkable_floor_angle * 3.14159265358979f / 180.0f));

    return is_written;
}

float sdk::hw2::max_walk_speed_of(const APawn* pawn) noexcept {
    return mem::read<float>(movement_of(pawn), offsets::ucharacter_movement::max_walk_speed, 0.0f);
}

float sdk::hw2::max_crouch_speed_of(const APawn* pawn) noexcept {
    return mem::read<float>(movement_of(pawn), offsets::ucharacter_movement::max_walk_speed_crouched, 0.0f);
}

float sdk::hw2::max_fly_speed_of(const APawn* pawn) noexcept {
    return mem::read<float>(movement_of(pawn), offsets::ucharacter_movement::max_fly_speed, 0.0f);
}

bool sdk::hw2::set_max_walk_speed(APawn* pawn, float speed) noexcept {
    return mem::write<float>(movement_of(pawn), offsets::ucharacter_movement::max_walk_speed, speed);
}

bool sdk::hw2::set_max_crouch_speed(APawn* pawn, float speed) noexcept {
    return mem::write<float>(movement_of(pawn), offsets::ucharacter_movement::max_walk_speed_crouched, speed);
}

bool sdk::hw2::set_max_fly_speed(APawn* pawn, float speed) noexcept {
    return mem::write<float>(movement_of(pawn), offsets::ucharacter_movement::max_fly_speed, speed);
}

sdk::hw2::movement_mode sdk::hw2::movement_mode_of(const APawn* pawn) noexcept {
    return mem::read<movement_mode>(movement_of(pawn), offsets::ucharacter_movement::movement_mode, movement_mode::none);
}

const char* sdk::hw2::mode_name(movement_mode mode) noexcept {
    switch (mode) {
    case movement_mode::none: return "none";
    case movement_mode::walking: return "walking";
    case movement_mode::nav_walking: return "nav walking";
    case movement_mode::falling: return "falling";
    case movement_mode::swimming: return "swimming";
    case movement_mode::flying: return "flying";
    case movement_mode::custom: return "custom";
    }

    return "unknown";
}

bool sdk::hw2::set_movement_mode(APawn* pawn, movement_mode mode) noexcept {
    return mem::write<movement_mode>(movement_of(pawn), offsets::ucharacter_movement::movement_mode, mode);
}

bool sdk::hw2::is_cheat_flying(const APawn* pawn) noexcept {
    namespace field = offsets::ucharacter_movement;

    return mem::read_bit(movement_of(pawn), field::cheat_flying, field::cheat_flying_bit);
}

bool sdk::hw2::set_cheat_flying(APawn* pawn, bool is_flying) noexcept {
    namespace field = offsets::ucharacter_movement;

    return mem::write_bit(movement_of(pawn), field::cheat_flying, field::cheat_flying_bit, is_flying);
}

bool sdk::hw2::set_sprint_ready(APawn* pawn, bool is_ready) noexcept {
    bool is_written = mem::write<bool>(pawn, offsets::hw2_character::can_run, is_ready);
    is_written &= mem::write<bool>(pawn, offsets::hw2_character::can_tactical_sprint, is_ready);

    return is_written;
}

bool sdk::hw2::is_sprint_ready(const APawn* pawn) noexcept {
    return mem::read<bool>(pawn, offsets::hw2_character::can_run, false)
        && mem::read<bool>(pawn, offsets::hw2_character::can_tactical_sprint, false);
}

bool sdk::hw2::is_yaw_from_controller(const APawn* pawn) noexcept {
    namespace field = offsets::apawn;

    return mem::read_bit(pawn, field::use_controller_yaw, field::use_controller_yaw_bit);
}

bool sdk::hw2::set_yaw_from_controller(APawn* pawn, bool is_from_controller) noexcept {
    namespace field = offsets::apawn;

    return mem::write_bit(pawn, field::use_controller_yaw, field::use_controller_yaw_bit, is_from_controller);
}

bool sdk::hw2::is_orient_to_movement(const APawn* pawn) noexcept {
    namespace field = offsets::ucharacter_movement;

    return mem::read_bit(movement_of(pawn), field::orient_to_movement, field::orient_to_movement_bit);
}

bool sdk::hw2::set_orient_to_movement(APawn* pawn, bool is_orient) noexcept {
    namespace field = offsets::ucharacter_movement;

    return mem::write_bit(movement_of(pawn), field::orient_to_movement, field::orient_to_movement_bit, is_orient);
}

bool sdk::hw2::set_body_rotation(AActor* actor, const FRotator& rotation) {
    if (!actor) return false;

    call::invocation entry(actor, "K2_SetActorRotation");
    if (!entry.is_valid()) return false;

    namespace field = offsets::params::set_actor_rotation;
    entry.set<FRotator>(field::rotation, rotation);

    entry.set<bool>(field::is_teleport, true);

    return entry.fire() && entry.get<bool>(field::return_value);
}

bool sdk::hw2::is_camera_on_control(const UObject* camera) noexcept {
    namespace field = offsets::ucamera_component;

    return mem::read_bit(camera, field::use_pawn_control_rotation, field::use_pawn_control_rotation_bit);
}

bool sdk::hw2::set_camera_on_control(UObject* camera, bool is_on_control) noexcept {
    if (!camera) return false;

    namespace field = offsets::ucamera_component;

    return mem::write_bit(camera, field::use_pawn_control_rotation, field::use_pawn_control_rotation_bit, is_on_control);
}

bool sdk::hw2::is_arm_on_control(const UObject* spring_arm) noexcept {
    namespace field = offsets::uspring_arm;

    return mem::read_bit(spring_arm, field::use_pawn_control_rotation, field::use_pawn_control_rotation_bit);
}

bool sdk::hw2::is_arm_inheriting_yaw(const UObject* spring_arm) noexcept {
    namespace field = offsets::uspring_arm;

    return mem::read_bit(spring_arm, field::inherit_yaw, field::inherit_yaw_bit);
}

bool sdk::hw2::set_arm_flags(UObject* spring_arm, bool is_on_control, bool is_inheriting_yaw) noexcept {
    if (!spring_arm) return false;

    namespace field = offsets::uspring_arm;

    bool is_written = mem::write_bit(spring_arm, field::use_pawn_control_rotation, field::use_pawn_control_rotation_bit, is_on_control);
    is_written &= mem::write_bit(spring_arm, field::inherit_yaw, field::inherit_yaw_bit, is_inheriting_yaw);

    return is_written;
}
