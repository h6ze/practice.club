#pragma once

namespace features {

    struct view_options {
        bool is_fov = false;
        float fov = 110.0f;

        bool is_fixed_ads_fov = false;
        float ads_fov = 110.0f;

        bool is_no_sway = false;

        bool is_hold_breath = false;
        float hold_breath = 1.0f;

        bool is_no_recoil = false;
        bool is_no_spread = false;

        bool is_clean_screen = false;
        float saturation = 1.0f;
        bool is_no_run_shake = false;

        bool is_third_person = false;
        float arm_length = 200.0f;
        float side_shift = 60.0f;
        float pivot_rise = 20.0f;

        bool is_lean = false;
        float lean = 20.0f;
    };

    inline view_options view_setup;

    struct view_domain {
        void tick();

        void tune_view();
        void field_of_view();
        void settings();
        void steady();

        void report();
        void restore();

        void probe();
    };

    inline view_domain view;

}
