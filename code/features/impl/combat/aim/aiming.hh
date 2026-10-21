#pragma once
#include <Windows.h>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <features/data/tune.hh>
#include <features/features.hh>
#include <sdk/core/access.hh>
#include <sdk/hw2/combat/combat.hh>
#include <sdk/globals.hh>
#include <sdk/hw2/hw2.hh>
#include <sdk/offsets.generated.hh>
#include <features/impl/combat/weapons/arsenal.hh>

namespace features::detail {

    inline constexpr double radians_per_degree = 3.14159265358979323846 / 180.0;

    struct guard_memory {
        sdk::hw2::guard_switches original;
        bool is_saved = false;
        bool is_written = false;

        sdk::hw2::guard_limits original_limits;
        bool is_limits_saved = false;
        bool is_limits_written = false;
    };

    struct aim_target {
        sdk::APawn* pawn = nullptr;
        sdk::FVector point;
        double angle = 0.0;
    };

    struct aim_view {
        sdk::FVector location;
        sdk::FRotator rotation;
        bool is_valid = false;
    };

    inline guard_memory guard_state;

    inline fire_cadence wallbang_cadence;

    inline void seed_guard_options(const sdk::hw2::guard_limits& from) {
        guard_setup.max_trace_offset = from.max_trace_offset;
        guard_setup.hit_leeway = from.hit_leeway;
        guard_setup.head_zone = from.head_zone;
        guard_setup.sight_leeway = from.sight_leeway;

        guard_setup.aim_refuse = from.aim_refuse;
        guard_setup.aim_score = from.aim_score;
        guard_setup.aim_suspect = from.aim_suspect;
        guard_setup.aim_recheck = from.aim_recheck;
        guard_setup.snap_degrees = from.snap_degrees;
        guard_setup.snap_window = from.snap_window;

        guard_setup.hits_per_pellet = from.hits_per_pellet;
        guard_setup.fire_rate_tolerance = from.fire_rate_tolerance;
        guard_setup.burst_shots = from.burst_shots;
        guard_setup.burst_seconds = from.burst_seconds;

        guard_setup.melee_leeway = from.melee_leeway;
        guard_setup.melee_interval = from.melee_interval;

        guard_setup.max_rewind = from.max_rewind;
        guard_setup.rewind_slack = from.rewind_slack;

        guard_setup.warn_score = from.warn_score;
        guard_setup.kick_score = from.kick_score;
        guard_setup.score_decay = from.score_decay;
        guard_setup.violation_gap = from.violation_gap;
        guard_setup.kick_delay = from.kick_delay;

        guard_setup.is_seeded = true;
    }

    [[nodiscard]] inline sdk::hw2::guard_limits wanted_limits() {
        sdk::hw2::guard_limits wanted;

        wanted.max_trace_offset = guard_setup.max_trace_offset;
        wanted.hit_leeway = guard_setup.hit_leeway;
        wanted.head_zone = guard_setup.head_zone;
        wanted.sight_leeway = guard_setup.sight_leeway;

        wanted.aim_refuse = guard_setup.aim_refuse;
        wanted.aim_score = guard_setup.aim_score;
        wanted.aim_suspect = guard_setup.aim_suspect;
        wanted.aim_recheck = guard_setup.aim_recheck;
        wanted.snap_degrees = guard_setup.snap_degrees;
        wanted.snap_window = guard_setup.snap_window;

        wanted.hits_per_pellet = guard_setup.hits_per_pellet;
        wanted.fire_rate_tolerance = guard_setup.fire_rate_tolerance;
        wanted.burst_shots = guard_setup.burst_shots;
        wanted.burst_seconds = guard_setup.burst_seconds;

        wanted.melee_leeway = guard_setup.melee_leeway;
        wanted.melee_interval = guard_setup.melee_interval;

        wanted.max_rewind = guard_setup.max_rewind;
        wanted.rewind_slack = guard_setup.rewind_slack;

        wanted.warn_score = guard_setup.warn_score;
        wanted.kick_score = guard_setup.kick_score;
        wanted.score_decay = guard_setup.score_decay;
        wanted.violation_gap = guard_setup.violation_gap;
        wanted.kick_delay = guard_setup.kick_delay;

        return wanted;
    }

    inline sdk::FName bone_names[std::size(tune::aim_bones)];

    inline void refresh_aim_status() {
        sdk::UWorld* world = sdk::globals::world();

        aim_status.is_host = world && world->AuthorityGameMode() != nullptr;
        aim_status.humans = sweep.human_controllers;
        aim_status.is_open = aim_status.is_host && sweep.human_controllers <= 1;
        aim_status.has_target = false;
    }

    [[nodiscard]] inline aim_view view_of(const sdk::APlayerController* controller) {
        aim_view eye;

        const sdk::AActor* manager = controller ? controller->PlayerCameraManager() : nullptr;
        if (!manager) return eye;

        const std::uint32_t pov = sdk::offsets::acamera_manager::camera_cache + sdk::offsets::view::pov;
        eye.location = sdk::mem::read<sdk::FVector>(manager, pov + sdk::offsets::view::location, sdk::FVector{});
        eye.rotation = sdk::mem::read<sdk::FRotator>(manager, pov + sdk::offsets::view::rotation, sdk::FRotator{});
        eye.is_valid = !eye.location.is_zero();

        return eye;
    }

    [[nodiscard]] inline double normalized_axis(double degrees) {
        double value = std::fmod(degrees + 180.0, 360.0);
        if (value < 0.0) value += 360.0;

        return value - 180.0;
    }

    [[nodiscard]] inline sdk::FVector forward_of(const sdk::FRotator& rotation) {
        const double pitch = rotation.Pitch * radians_per_degree;
        const double yaw = rotation.Yaw * radians_per_degree;

        return { std::cos(pitch) * std::cos(yaw), std::cos(pitch) * std::sin(yaw), std::sin(pitch) };
    }

    [[nodiscard]] inline sdk::FRotator rotation_to(const sdk::FVector& from, const sdk::FVector& to) {
        const sdk::FVector delta = to - from;
        const double flat = std::sqrt(delta.X * delta.X + delta.Y * delta.Y);

        return { std::atan2(delta.Z, flat) / radians_per_degree, std::atan2(delta.Y, delta.X) / radians_per_degree, 0.0 };
    }

    [[nodiscard]] inline double angle_to(const aim_view& eye, const sdk::FVector& point) {
        const sdk::FVector delta = point - eye.location;
        const double length = delta.length();
        if (length < 1.0) return 180.0;

        const sdk::FVector forward = forward_of(eye.rotation);
        const double cosine = std::clamp(forward.dot(delta) / length, -1.0, 1.0);

        return std::acos(cosine) / radians_per_degree;
    }

    [[nodiscard]] inline sdk::FVector aim_point_of(const sdk::APawn* pawn) {
        const int slot = std::clamp(aim_setup.bone_slot, 0, static_cast<int>(std::size(tune::aim_bones)) - 1);
        const tune::aim_bone& bone = tune::aim_bones[slot];

        const sdk::FVector origin = pawn->origin();

        sdk::FName& name = bone_names[slot];
        if (name.is_none()) name = sdk::hw2::make_name(bone.socket);

        sdk::UObject* mesh = sdk::mem::pointer<sdk::UObject>(pawn, sdk::offsets::acharacter::mesh);

        sdk::FVector socket;
        if (sdk::hw2::socket_location(mesh, name, socket) && socket.Z > origin.Z) return socket;

        return { origin.X, origin.Y, origin.Z + bone.fallback_lift };
    }

    [[nodiscard]] inline bool is_enemy(const sdk::APawn* pawn) {
        if (aim_setup.is_ignore_teams) return true;

        const sdk::APlayerState* mine = own_state();
        const sdk::APlayerState* theirs = pawn->PlayerState();

        const int own_team = mine ? sdk::hw2::team_of(mine) : -1;
        const int their_team = theirs ? sdk::hw2::team_of(theirs) : -1;

        return own_team < 0 || their_team < 0 || own_team != their_team;
    }

    [[nodiscard]] inline aim_target best_target(const aim_view& eye, float cone, bool is_visible_only) {
        aim_target best;

        sdk::APlayerController* controller = own_controller();
        if (!controller || !eye.is_valid) return best;

        const double reach = aim_setup.max_distance * tune::units_per_metre;

        for (sdk::APawn* pawn : sweep.characters) {
            if (sdk::hw2::is_dead(pawn) || !is_enemy(pawn)) continue;
            if ((pawn->origin() - eye.location).length() > reach) continue;

            const sdk::FVector point = aim_point_of(pawn);
            const double angle = angle_to(eye, point);
            if (angle > cone) continue;
            if (best.pawn && angle >= best.angle) continue;
            if (is_visible_only && !sdk::hw2::has_line_of_sight(controller, pawn, eye.location)) continue;

            best = { pawn, point, angle };
        }

        return best;
    }

    [[nodiscard]] inline bool is_aim_key_held() {
        const int slot = std::clamp(aim_setup.key_slot, 0, static_cast<int>(std::size(tune::aim_keys)) - 1);

        return (GetAsyncKeyState(tune::aim_keys[slot].code) & 0x8000) != 0;
    }

}
