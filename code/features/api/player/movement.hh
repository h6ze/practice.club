#pragma once

namespace features {

    struct movement_options {
        bool is_speed = false;
        float speed = 1.5f;

        bool is_acceleration = false;
        float acceleration = 4.0f;

        bool is_jump = false;
        float jump = 1.5f;
        int jumps = 2;

        bool is_gravity = false;
        float gravity = 0.5f;

        bool is_air_control = false;
        float air_control = 1.0f;

        bool is_step_height = false;
        float step_height = 100.0f;

        bool is_steep_slopes = false;
        bool is_edge_guard = false;

        bool is_no_fall_damage = false;
        bool is_endless_sprint = false;
        bool is_flat_ads_speed = false;

        bool is_fly = false;
        float fly_speed = 2.0f;

        bool is_no_correction = false;

        bool is_spin = false;
        float spin_speed = 720.0f;
    };

    inline movement_options movement_setup;

    struct movement_domain {
        void tick();

        void tune_movement();
        void speeds();
        void flight();
        void character();
        void spin();

        void report();
        void restore();
    };

    inline movement_domain movement;

}
