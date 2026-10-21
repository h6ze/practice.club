#pragma once
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <iterator>
#include <string>
#include <unordered_map>
#include <features/data/tune.hh>
#include <features/features.hh>
#include <sdk/hw2/pawn/motion.hh>
#include <sdk/offsets.generated.hh>
#include <client/bridge/dispatch.hh>
#include <client/bridge/natives.hh>
#include <features/impl/combat/aim/aiming.hh>
#include <features/impl/combat/weapons/arsenal.hh>

namespace features::detail {

    struct tracked_speed {
        float base = 0.0f;
        float written = 0.0f;
    };

    struct movement_original {
        std::int32_t index = -1;
        sdk::hw2::movement_stats stats;
        tracked_speed walk;
        tracked_speed crouch;
        tracked_speed fly;
        bool is_flying = false;
    };

    inline std::unordered_map<sdk::APawn*, movement_original> movement_originals;
    inline std::atomic<bool> is_movement_pass_queued{ false };

    struct spin_memory {
        sdk::APawn* pawn = nullptr;
        std::chrono::steady_clock::time_point last;
        double yaw = 0.0;
        bool is_moving = false;
        bool is_saved = false;
        bool was_yaw_from_controller = true;
        bool was_orient_to_movement = false;
        bool was_arm_on_control = false;
        bool was_arm_inheriting_yaw = true;
        bool was_camera_on_control = false;

        void forget() noexcept { pawn = nullptr; is_saved = false; last = {}; }
    };

    inline spin_memory spin_state;

    inline game::natives::thunk original_move_forward = nullptr;
    inline game::natives::thunk original_move_right = nullptr;
    inline game::natives::thunk original_actor_forward = nullptr;
    inline game::natives::thunk original_actor_right = nullptr;

    inline void exec_move_forward(void* context, void* stack, void* result) {
        spin_memory& memory = spin_state;

        const bool is_ours = memory.is_saved && context == memory.pawn;
        if (is_ours) memory.is_moving = true;

        original_move_forward(context, stack, result);

        if (is_ours) memory.is_moving = false;
    }

    inline void exec_move_right(void* context, void* stack, void* result) {
        spin_memory& memory = spin_state;

        const bool is_ours = memory.is_saved && context == memory.pawn;
        if (is_ours) memory.is_moving = true;

        original_move_right(context, stack, result);

        if (is_ours) memory.is_moving = false;
    }

    [[nodiscard]] inline bool camera_axis(const void* context, sdk::FVector& axis, bool is_right) {
        const spin_memory& memory = spin_state;
        if (!memory.is_moving || !memory.is_saved || context != memory.pawn) return false;

        const sdk::APlayerController* controller = own_controller();
        if (!controller) return false;

        const double yaw = (controller->ControlRotation().Yaw + (is_right ? 90.0 : 0.0)) * radians_per_degree;

        axis = { std::cos(yaw), std::sin(yaw), 0.0 };

        return true;
    }

    inline void exec_actor_forward(void* context, void* stack, void* result) {
        original_actor_forward(context, stack, result);

        sdk::FVector axis;
        if (result && camera_axis(context, axis, false)) *static_cast<sdk::FVector*>(result) = axis;
    }

    inline void exec_actor_right(void* context, void* stack, void* result) {
        original_actor_right(context, stack, result);

        sdk::FVector axis;
        if (result && camera_axis(context, axis, true)) *static_cast<sdk::FVector*>(result) = axis;
    }

    inline void take_movement_thunks(sdk::APawn* pawn) {
        if (original_move_forward) return;

        sdk::UClass* body = pawn ? pawn->klass() : nullptr;
        if (!body) return;

        sdk::UFunction* forward_move = body->find_function("OnMoveForward");
        sdk::UFunction* right_move = body->find_function("OnMoveRight");
        sdk::UFunction* forward = body->find_function("GetActorForwardVector");
        sdk::UFunction* right = body->find_function("GetActorRightVector");

        if (!forward_move || !right_move || !forward || !right) {
            logger::error("[ movement ] could not find all four movement functions -> wasd will follow the body");
            return;
        }

        original_actor_forward = game::natives::swap(forward, exec_actor_forward);
        original_actor_right = game::natives::swap(right, exec_actor_right);
        original_move_forward = game::natives::swap(forward_move, exec_move_forward);
        original_move_right = game::natives::swap(right_move, exec_move_right);

        if (original_move_forward && original_move_right && original_actor_forward && original_actor_right) {
            logger::success("[ movement ] movement thunks swapped, wasd follows the camera");
            return;
        }

        game::natives::restore_all();
        original_move_forward = nullptr;
        original_move_right = nullptr;
        original_actor_forward = nullptr;
        original_actor_right = nullptr;

        logger::error("[ movement ] only part of the movement thunks swapped -> all of them put back");
    }

    [[nodiscard]] inline double spin_step(spin_memory& memory, float degrees_a_second) noexcept {
        const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        const std::chrono::steady_clock::time_point previous = memory.last;

        memory.last = now;

        if (previous == std::chrono::steady_clock::time_point{}) return 0.0;

        const double elapsed = std::chrono::duration<double>(now - previous).count();
        if (elapsed <= 0.0 || elapsed > tune::spin_gap_ceiling) return 0.0;

        return elapsed * static_cast<double>(degrees_a_second);
    }


    inline movement_original* original_movement(sdk::APawn* pawn) {
        if (!pawn) return nullptr;

        const auto found = movement_originals.find(pawn);
        if (found != movement_originals.end() && is_same_object(pawn, found->second.index)) return &found->second;

        movement_original entry;
        entry.index = pawn->index();
        if (!sdk::hw2::read_movement(pawn, entry.stats)) return nullptr;

        entry.walk.base = sdk::hw2::max_walk_speed_of(pawn);
        entry.crouch.base = sdk::hw2::max_crouch_speed_of(pawn);
        entry.fly.base = sdk::hw2::max_fly_speed_of(pawn);

        return &(movement_originals[pawn] = entry);
    }

    inline void forget_stale_movement() {
        for (auto entry = movement_originals.begin(); entry != movement_originals.end();)
            entry = is_same_object(entry->first, entry->second.index) ? std::next(entry) : movement_originals.erase(entry);
    }

    [[nodiscard]] inline sdk::hw2::movement_stats tuned_movement(const sdk::hw2::movement_stats& original) {
        const movement_options& options = movement_setup;
        sdk::hw2::movement_stats tuned = original;

        if (options.is_acceleration) {
            tuned.max_acceleration *= options.acceleration;
            tuned.braking_deceleration_walking *= options.acceleration;
            tuned.ground_friction *= options.acceleration;
        }

        if (options.is_jump) {
            tuned.jump_z_velocity *= options.jump;
            tuned.jump_max_count = options.jumps;
        }

        if (options.is_gravity) tuned.gravity_scale *= options.gravity;
        if (options.is_air_control) tuned.air_control = options.air_control;
        if (options.is_step_height) tuned.max_step_height = options.step_height;
        if (options.is_steep_slopes) tuned.walkable_floor_angle = tune::steep_slope_angle;

        if (options.is_edge_guard) {
            tuned.is_walk_off_ledges = false;
            tuned.is_walk_off_ledges_crouching = false;
        }

        if (options.is_no_fall_damage) tuned.is_fall_damage = false;
        if (options.is_flat_ads_speed) tuned.ads_speed_extra = 0.0;
        if (options.is_no_correction) tuned.is_ignore_correction = true;

        return tuned;
    }

    [[nodiscard]] inline std::string stride_line(const char* label, double original, double live) {
        char text[128];
        std::snprintf(text, sizeof(text), "[ movement ]   %s %.3f -> %.3f", label, original, live);

        return text;
    }

    inline float scaled_speed(tracked_speed& speed, float live, bool is_on, float scale) {
        if (live != speed.written) speed.base = live;

        speed.written = is_on ? speed.base * scale : speed.base;

        return speed.written;
    }

}
