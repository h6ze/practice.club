#pragma once

namespace features {

    struct dev_options {
        bool is_enabled = false;
        bool is_hold = false;

        bool is_esp = false;
        bool is_esp_overlay = false;
        float esp_color[4] = { 1.0f, 0.25f, 0.25f, 1.0f };
        float esp_radius = 6.0f;
        float esp_height = 40.0f;
        float esp_distance = 300.0f;

        bool is_lobby_size = false;
        int team_size = 12;
        int max_players = 24;
    };

    struct bot_options {
        int tier_slot = 0;
        bool is_hold = false;

        float aim_turn_rate = 0.0f;
        float aim_reaction_delay = 0.0f;
        float aim_error_initial = 0.0f;
        float aim_error_settled = 0.0f;
        float aim_settle_time = 0.0f;
        float aim_fire_angle = 0.0f;
        float burst_duration = 0.0f;
        float burst_rest = 0.0f;
        float aim_latency = 0.0f;
        float aim_predict_skill = 0.0f;
        float reaction_time = 0.0f;
        float spread_multiplier = 0.0f;
        float moving_spread_scale = 0.0f;
        int max_bots_per_target = 0;
        float engage_range = 0.0f;
        float max_fire_range = 0.0f;
        float detect_time = 0.0f;
        float flinch_spread = 0.0f;
        float pursuit_scale = 0.0f;

        float aim_interp_speed = 0.0f;
        float aim_error_interval = 0.0f;
        float aim_target_z_offset = 0.0f;
        float hearing_radius = 0.0f;
        float memory_seconds = 0.0f;
        bool is_perceived_aim = false;
        bool is_movement_spread = false;
    };

    struct streak_options {
        int streak_slot = 0;
        int loadout_slot = 0;
        bool is_place_ahead = true;
        float place_distance = 10.0f;

        int ready_mask = 0x0F;
        int equip_mask = 0x0F;

        int streak_count = 5;
        float uav_seconds = 30.0f;
        int summon_team = 0;
    };

    struct aggro_options {
        bool is_hunt = false;
        float interval = 2.0f;
        bool is_enemies_only = true;
    };

    inline aggro_options aggro_setup;

    inline dev_options dev_setup;

    inline bot_options bot_setup;

    inline streak_options streak_setup;

    struct arena_domain {
        void tick();

        void load_dev();
        void apply_dev();

        void load_bots();
        void apply_bots();

        void fire_streak();
        void fire_streak_slot();
        void place_streak();

        void grant_streaks(bool is_target);
        void equip_streaks();
        void use_streak();

        void cluster_strike();
        void set_streak_count();
        void team_uav();

        void drop_protection();
        void hunt_once();

        void summons_to_team();

        void report();
        void restore();
    };

    inline arena_domain arena;

}
