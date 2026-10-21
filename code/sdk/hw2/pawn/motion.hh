#pragma once
#include <cstdint>
#include <sdk/unreal/engine.hh>

namespace sdk::hw2 {

    enum class movement_mode : std::uint8_t {
        none = 0, walking = 1, nav_walking = 2, falling = 3, swimming = 4, flying = 5, custom = 6
    };

    struct movement_stats {
        float gravity_scale = 0.0f;
        float max_step_height = 0.0f;
        float jump_z_velocity = 0.0f;
        float walkable_floor_angle = 0.0f;
        float ground_friction = 0.0f;
        float max_acceleration = 0.0f;
        float braking_deceleration_walking = 0.0f;
        float air_control = 0.0f;
        int jump_max_count = 0;
        double ads_speed_extra = 0.0;
        bool is_fall_damage = false;
        bool is_walk_off_ledges = false;
        bool is_walk_off_ledges_crouching = false;
        bool is_ignore_correction = false;
    };

    [[nodiscard]] UObject* movement_of(const APawn* pawn) noexcept;

    [[nodiscard]] bool read_movement(const APawn* pawn, movement_stats& stats) noexcept;
    bool write_movement(APawn* pawn, const movement_stats& stats) noexcept;

    [[nodiscard]] float max_walk_speed_of(const APawn* pawn) noexcept;
    [[nodiscard]] float max_crouch_speed_of(const APawn* pawn) noexcept;
    [[nodiscard]] float max_fly_speed_of(const APawn* pawn) noexcept;
    bool set_max_walk_speed(APawn* pawn, float speed) noexcept;
    bool set_max_crouch_speed(APawn* pawn, float speed) noexcept;
    bool set_max_fly_speed(APawn* pawn, float speed) noexcept;

    [[nodiscard]] movement_mode movement_mode_of(const APawn* pawn) noexcept;
    [[nodiscard]] const char* mode_name(movement_mode mode) noexcept;
    bool set_movement_mode(APawn* pawn, movement_mode mode) noexcept;

    [[nodiscard]] bool is_cheat_flying(const APawn* pawn) noexcept;
    bool set_cheat_flying(APawn* pawn, bool is_flying) noexcept;

    bool set_sprint_ready(APawn* pawn, bool is_ready) noexcept;
    [[nodiscard]] bool is_sprint_ready(const APawn* pawn) noexcept;

    [[nodiscard]] bool is_yaw_from_controller(const APawn* pawn) noexcept;
    bool set_yaw_from_controller(APawn* pawn, bool is_from_controller) noexcept;
    [[nodiscard]] bool is_orient_to_movement(const APawn* pawn) noexcept;
    bool set_orient_to_movement(APawn* pawn, bool is_orient) noexcept;

    bool set_body_rotation(AActor* actor, const FRotator& rotation);

    [[nodiscard]] bool is_camera_on_control(const UObject* camera) noexcept;
    bool set_camera_on_control(UObject* camera, bool is_on_control) noexcept;

    [[nodiscard]] bool is_arm_on_control(const UObject* spring_arm) noexcept;
    [[nodiscard]] bool is_arm_inheriting_yaw(const UObject* spring_arm) noexcept;
    bool set_arm_flags(UObject* spring_arm, bool is_on_control, bool is_inheriting_yaw) noexcept;

}
