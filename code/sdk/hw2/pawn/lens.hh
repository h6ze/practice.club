#pragma once
#include <sdk/unreal/engine.hh>

namespace sdk::hw2 {

    struct view_stats {
        double breathing_strength = 0.0;
        double breathing_yaw = 0.0;
        double breathing_pitch = 0.0;
        double tpp_arm_length = 0.0;
        float arm_length = 0.0f;
        float post_process_blend = 0.0f;
        FVector socket_offset;
        FVector target_offset;
        void* run_camera_shake = nullptr;
        bool is_breathing = false;
        bool is_hold_breath_allowed = false;
        bool is_arm_collision = false;
    };

    [[nodiscard]] UObject* camera_of(const APawn* pawn) noexcept;
    [[nodiscard]] UObject* spring_arm_of(const APawn* pawn) noexcept;
    [[nodiscard]] UObject* pawn_info_of(const APawn* pawn) noexcept;
    [[nodiscard]] UObject* view_settings_of(const APlayerController* controller) noexcept;

    [[nodiscard]] bool read_view(const APawn* pawn, view_stats& stats) noexcept;
    bool write_view(APawn* pawn, const view_stats& stats) noexcept;

    [[nodiscard]] float input_fov_of(const UObject* input_subsystem) noexcept;
    bool set_input_fov(UObject* input_subsystem, float fov) noexcept;

    [[nodiscard]] float camera_fov_of(const APawn* pawn) noexcept;
    [[nodiscard]] float manager_fov_of(const APlayerController* controller) noexcept;

    [[nodiscard]] float first_person_fov_of(const APawn* pawn) noexcept;
    [[nodiscard]] bool is_first_person_fov_on(const APawn* pawn) noexcept;
    [[nodiscard]] double current_fov_of(const APawn* pawn) noexcept;
    bool set_current_fov(APawn* pawn, double fov) noexcept;

    [[nodiscard]] float rendered_fov_of(const APlayerController* controller) noexcept;
    [[nodiscard]] double default_fov_of(const APawn* pawn) noexcept;
    bool set_default_fov(APawn* pawn, double fov) noexcept;

    [[nodiscard]] double settings_fov_of(const APlayerController* controller) noexcept;
    bool set_settings_fov(APlayerController* controller, double fov) noexcept;
    [[nodiscard]] bool is_third_person(const APlayerController* controller) noexcept;
    bool set_third_person(APlayerController* controller, bool is_tpp) noexcept;

    bool update_perspective(APawn* pawn);

    bool set_target_fov(APawn* pawn, double fov) noexcept;
    bool set_target_spread(APawn* pawn, double spread) noexcept;
    bool set_saturation(APawn* pawn, double saturation) noexcept;
    bool set_hold_breath(APawn* pawn, double alpha) noexcept;
    bool set_leaning(APawn* pawn, double leaning) noexcept;

    bool clear_view_recoil(APawn* pawn) noexcept;

    [[nodiscard]] double target_fov_of(const APawn* pawn) noexcept;
    [[nodiscard]] double target_spread_of(const APawn* pawn) noexcept;
    [[nodiscard]] double saturation_of(const APawn* pawn) noexcept;
    [[nodiscard]] double leaning_of(const APawn* pawn) noexcept;
    [[nodiscard]] double camera_leaning_of(const APawn* pawn) noexcept;

}
