#pragma once

namespace features {

    struct aim_options {
        bool is_guard_off = false;

        bool is_aimbot = false;
        int key_slot = 0;
        float fov = 15.0f;
        float smooth = 4.0f;

        bool is_aimbot_circle = true;
        float aimbot_circle[4] = { 0.45f, 0.53f, 0.98f, 0.85f };

        bool is_silent = false;
        float silent_fov = 30.0f;

        bool is_silent_circle = true;
        float silent_circle[4] = { 0.91f, 0.78f, 0.42f, 0.85f };

        bool is_wallbang = false;
        float wallbang_fov = 30.0f;
        float wallbang_rate = 8.0f;
        float wallbang_push = 60.0f;

        bool is_bullet_tp = false;
        float bullet_tp_fov = 60.0f;
        bool is_bullet_tp_hit = true;

        int bone_slot = 0;
        float max_distance = 300.0f;
        bool is_visible_only = true;
        bool is_ignore_teams = false;
    };

    struct aim_state {
        bool is_host = false;
        int humans = 0;
        bool is_open = false;
        bool has_target = false;
    };

    inline aim_options aim_setup;

    inline aim_state aim_status;

    struct guard_options {
        bool is_enabled = false;
        bool is_seeded = false;

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

    inline guard_options guard_setup;

    struct aim_domain {
        void guard();
        void limits();
        void aimbot();
        void silent();
        void wallbang();
        void teleport();

        void circles();
    };

    inline aim_domain aim;

}
