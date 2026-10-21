#pragma once
#include <features/api/common.hh>

namespace features {

    struct weapon_options {
        bool is_fire_rate = false;
        float fire_rate = 1.5f;

        bool is_rapid_fire = false;

        bool is_auto_fire = false;
        float auto_fire_rate = 10.0f;
        float auto_fire_spread = 0.0f;

        bool is_recoil = false;
        float recoil = 0.0f;

        bool is_damage = false;
        float damage = 1.5f;
        float headshot = 1.5f;
        bool is_no_falloff = false;

        bool is_bot_damage = false;
        float bot_damage = 0.5f;

        bool is_bullet_speed = false;
        float bullet_speed = 2.0f;
        bool is_no_drop = false;

        int hit_reg = keep_game;
        int hit_scan = keep_game;

        bool is_pellets = false;
        int pellets = 12;

        bool is_infinite_ammo = false;
        bool is_mag_size = false;
        int mag_size = 60;

        bool is_recolor = false;
        float color_a[4] = { 0.85f, 0.18f, 0.24f, 1.0f };
        float color_b[4] = { 0.08f, 0.08f, 0.09f, 1.0f };

        bool is_rgb = false;
        float rgb_speed = 0.35f;
        bool is_rgb_split = true;
    };

    struct throwable_options {
        bool is_enabled = false;
        float speed = 1.5f;
        float gravity = 1.0f;
        float bounce = 1.0f;
    };

    inline weapon_options weapon_setup;

    inline throwable_options throwable_setup;

    struct weapons_domain {
        void tick();

        void tune_stats();
        void rechamber();
        void auto_fire();
        void bot_damage();
        void ammo();
        void recolor();
        void bullet_drop();
        void throwables();

        void report();
        void restore();
    };

    inline weapons_domain weapons;

}
