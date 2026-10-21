#pragma once
#include <sdk/core/math.hh>
#include <sdk/core/text/name.hh>
#include <sdk/unreal/engine.hh>

namespace sdk::hw2 {

    struct guard_switches {
        bool is_enabled = false;
        bool is_enforce = false;
        bool is_kick = false;
        bool is_check_shots = false;
        bool is_check_sight = false;
        bool is_check_movement = false;
    };

    struct guard_limits {
        float max_trace_offset = 0.0f;
        float hit_leeway = 0.0f;
        float head_zone = 0.0f;
        float sight_leeway = 0.0f;

        float aim_refuse = 0.0f;
        float aim_score = 0.0f;
        float aim_suspect = 0.0f;
        float aim_recheck = 0.0f;
        float snap_degrees = 0.0f;
        float snap_window = 0.0f;

        float hits_per_pellet = 0.0f;
        float fire_rate_tolerance = 0.0f;
        float burst_shots = 0.0f;
        float burst_seconds = 0.0f;

        float melee_leeway = 0.0f;
        float melee_interval = 0.0f;

        float max_rewind = 0.0f;
        float rewind_slack = 0.0f;

        float warn_score = 0.0f;
        float kick_score = 0.0f;
        float score_decay = 0.0f;
        float violation_gap = 0.0f;
        float kick_delay = 0.0f;
    };

    [[nodiscard]] UObject* guard_settings();
    [[nodiscard]] bool read_guard(guard_switches& switches);
    bool write_guard(const guard_switches& switches);
    [[nodiscard]] bool read_limits(guard_limits& limits);
    bool write_limits(const guard_limits& limits);

    bool set_control_rotation(AController* controller, const FRotator& rotation) noexcept;

    [[nodiscard]] FName make_name(const char* text);
    [[nodiscard]] bool socket_location(UObject* mesh, const FName& socket, FVector& location);
    [[nodiscard]] bool has_line_of_sight(AController* controller, const AActor* other, const FVector& view_point);

}
