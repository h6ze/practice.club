#include "lens.hh"
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/offsets.generated.hh>

sdk::UObject* sdk::hw2::camera_of(const APawn* pawn) noexcept {
    return mem::pointer<UObject>(pawn, offsets::hw2_character::camera);
}

sdk::UObject* sdk::hw2::spring_arm_of(const APawn* pawn) noexcept {
    return mem::pointer<UObject>(pawn, offsets::hw2_character::spring_arm);
}

sdk::UObject* sdk::hw2::pawn_info_of(const APawn* pawn) noexcept {
    return mem::pointer<UObject>(pawn, offsets::hw2_character::pawn_info);
}

sdk::UObject* sdk::hw2::view_settings_of(const APlayerController* controller) noexcept {
    return mem::pointer<UObject>(controller, offsets::hw2_controller::controller_settings);
}

bool sdk::hw2::read_view(const APawn* pawn, view_stats& stats) noexcept {
    const UObject* camera = camera_of(pawn);
    const UObject* arm = spring_arm_of(pawn);
    if (!camera || !arm) return false;

    namespace field = offsets::hw2_character;

    stats.breathing_strength = mem::read<double>(pawn, field::breathing_strength);
    stats.breathing_yaw = mem::read<double>(pawn, field::breathing_yaw);
    stats.breathing_pitch = mem::read<double>(pawn, field::breathing_pitch);
    stats.tpp_arm_length = mem::read<double>(pawn, field::tpp_arm_length);
    stats.run_camera_shake = mem::read<void*>(pawn, field::run_camera_shake);
    stats.is_breathing = mem::read<bool>(pawn, field::is_breathing);
    stats.is_hold_breath_allowed = mem::read<bool>(pawn, field::can_hold_breath);

    stats.post_process_blend = mem::read<float>(camera, offsets::ucamera_component::post_process_blend);

    namespace arm_field = offsets::uspring_arm;

    stats.arm_length = mem::read<float>(arm, arm_field::target_arm_length);
    stats.socket_offset = mem::read<FVector>(arm, arm_field::socket_offset);
    stats.target_offset = mem::read<FVector>(arm, arm_field::target_offset);
    stats.is_arm_collision = mem::read_bit(arm, arm_field::do_collision_test, arm_field::do_collision_test_bit);

    return true;
}

bool sdk::hw2::write_view(APawn* pawn, const view_stats& stats) noexcept {
    UObject* camera = camera_of(pawn);
    UObject* arm = spring_arm_of(pawn);
    if (!camera || !arm) return false;

    namespace field = offsets::hw2_character;

    bool is_written = mem::write<double>(pawn, field::breathing_strength, stats.breathing_strength);
    is_written &= mem::write<double>(pawn, field::breathing_yaw, stats.breathing_yaw);
    is_written &= mem::write<double>(pawn, field::breathing_pitch, stats.breathing_pitch);
    is_written &= mem::write<double>(pawn, field::tpp_arm_length, stats.tpp_arm_length);
    is_written &= mem::write<void*>(pawn, field::run_camera_shake, stats.run_camera_shake);
    is_written &= mem::write<bool>(pawn, field::is_breathing, stats.is_breathing);
    is_written &= mem::write<bool>(pawn, field::can_hold_breath, stats.is_hold_breath_allowed);

    is_written &= mem::write<float>(camera, offsets::ucamera_component::post_process_blend, stats.post_process_blend);

    namespace arm_field = offsets::uspring_arm;

    is_written &= mem::write<float>(arm, arm_field::target_arm_length, stats.arm_length);
    is_written &= mem::write<FVector>(arm, arm_field::socket_offset, stats.socket_offset);
    is_written &= mem::write<FVector>(arm, arm_field::target_offset, stats.target_offset);
    is_written &= mem::write_bit(arm, arm_field::do_collision_test, arm_field::do_collision_test_bit, stats.is_arm_collision);

    return is_written;
}

float sdk::hw2::camera_fov_of(const APawn* pawn) noexcept {
    return mem::read<float>(camera_of(pawn), offsets::ucamera_component::field_of_view, 0.0f);
}

float sdk::hw2::input_fov_of(const UObject* input_subsystem) noexcept {
    return mem::read<float>(input_subsystem, offsets::hw2_player_input::field_of_view, 0.0f);
}

bool sdk::hw2::set_input_fov(UObject* input_subsystem, float fov) noexcept {
    return mem::write<float>(input_subsystem, offsets::hw2_player_input::field_of_view, fov);
}

float sdk::hw2::first_person_fov_of(const APawn* pawn) noexcept {
    return mem::read<float>(camera_of(pawn), offsets::ucamera_component::first_person_fov, 0.0f);
}

bool sdk::hw2::is_first_person_fov_on(const APawn* pawn) noexcept {
    namespace field = offsets::ucamera_component;

    return mem::read_bit(camera_of(pawn), field::enable_first_person_fov, field::enable_first_person_fov_bit);
}

float sdk::hw2::manager_fov_of(const APlayerController* controller) noexcept {
    const AActor* manager = controller ? controller->PlayerCameraManager() : nullptr;

    return mem::read<float>(manager, offsets::acamera_manager::default_fov, 0.0f);
}

double sdk::hw2::current_fov_of(const APawn* pawn) noexcept {
    return mem::read<double>(pawn, offsets::hw2_character::current_fov, 0.0);
}

bool sdk::hw2::set_current_fov(APawn* pawn, double fov) noexcept {
    return mem::write<double>(pawn, offsets::hw2_character::current_fov, fov);
}

float sdk::hw2::rendered_fov_of(const APlayerController* controller) noexcept {
    const AActor* manager = controller ? controller->PlayerCameraManager() : nullptr;
    const std::uint32_t pov = offsets::acamera_manager::camera_cache + offsets::view::pov;

    return mem::read<float>(manager, pov + offsets::view::fov, 0.0f);
}

double sdk::hw2::default_fov_of(const APawn* pawn) noexcept {
    return mem::read<double>(pawn, offsets::hw2_character::default_fov, 0.0);
}

bool sdk::hw2::set_default_fov(APawn* pawn, double fov) noexcept {
    return mem::write<double>(pawn, offsets::hw2_character::default_fov, fov);
}

double sdk::hw2::settings_fov_of(const APlayerController* controller) noexcept {
    return mem::read<double>(view_settings_of(controller), offsets::hw2_controller_settings::field_of_view, 0.0);
}

bool sdk::hw2::set_settings_fov(APlayerController* controller, double fov) noexcept {
    return mem::write<double>(view_settings_of(controller), offsets::hw2_controller_settings::field_of_view, fov);
}

bool sdk::hw2::is_third_person(const APlayerController* controller) noexcept {
    return mem::read<bool>(view_settings_of(controller), offsets::hw2_controller_settings::use_tpp, false);
}

bool sdk::hw2::set_third_person(APlayerController* controller, bool is_tpp) noexcept {
    return mem::write<bool>(view_settings_of(controller), offsets::hw2_controller_settings::use_tpp, is_tpp);
}

bool sdk::hw2::update_perspective(APawn* pawn) {
    call::invocation entry(pawn, "Update Perspective");

    return entry.is_valid() && entry.fire();
}

bool sdk::hw2::set_target_fov(APawn* pawn, double fov) noexcept {
    return mem::write<double>(pawn, offsets::hw2_character::target_fov, fov);
}

bool sdk::hw2::set_target_spread(APawn* pawn, double spread) noexcept {
    return mem::write<double>(pawn, offsets::hw2_character::target_spread, spread);
}

bool sdk::hw2::set_saturation(APawn* pawn, double saturation) noexcept {
    return mem::write<double>(pawn, offsets::hw2_character::saturation, saturation);
}

bool sdk::hw2::set_hold_breath(APawn* pawn, double alpha) noexcept {
    return mem::write<double>(pawn, offsets::hw2_character::hold_breath_alpha, alpha);
}

bool sdk::hw2::set_leaning(APawn* pawn, double leaning) noexcept {
    bool is_written = mem::write<double>(pawn_info_of(pawn), offsets::hw2_pawn_info::leaning, leaning);
    is_written &= mem::write<double>(pawn, offsets::hw2_character::camera_leaning, leaning);

    return is_written;
}

bool sdk::hw2::clear_view_recoil(APawn* pawn) noexcept {
    bool is_written = mem::write<double>(pawn, offsets::hw2_character::pitch_acum, 0.0);
    is_written &= mem::write<double>(pawn, offsets::hw2_character::yaw_acum, 0.0);

    return is_written;
}

double sdk::hw2::target_fov_of(const APawn* pawn) noexcept {
    return mem::read<double>(pawn, offsets::hw2_character::target_fov, 0.0);
}

double sdk::hw2::target_spread_of(const APawn* pawn) noexcept {
    return mem::read<double>(pawn, offsets::hw2_character::target_spread, 0.0);
}

double sdk::hw2::saturation_of(const APawn* pawn) noexcept {
    return mem::read<double>(pawn, offsets::hw2_character::saturation, 0.0);
}

double sdk::hw2::leaning_of(const APawn* pawn) noexcept {
    return mem::read<double>(pawn_info_of(pawn), offsets::hw2_pawn_info::leaning, 0.0);
}

double sdk::hw2::camera_leaning_of(const APawn* pawn) noexcept {
    return mem::read<double>(pawn, offsets::hw2_character::camera_leaning, 0.0);
}
