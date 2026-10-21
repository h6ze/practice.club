#pragma once

namespace features {

    struct visuals_options {
        bool is_enabled = false;
        bool is_box = true;
        bool is_name = true;
        bool is_health = true;
        bool is_distance = true;
        bool is_snapline = false;
        bool is_head_dot = false;
        bool is_enemy_only = true;
        float max_distance = 300.0f;
    };

    inline visuals_options visuals_setup;

    struct visuals_domain {
        void boxes();
        void names();
        void health();
        void distance();
        void snaplines();
        void head_dots();
    };

    inline visuals_domain visuals;

}
