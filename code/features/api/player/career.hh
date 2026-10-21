#pragma once
#include <vector>

namespace features {

    struct mission_view {
        int id = 0;
        int progress = 0;
        int target = 0;
        int reward = 0;
        bool is_completed = false;
    };

    struct career_snapshot {
        bool has_cloud = false;
        bool is_authenticated = false;
        int cloud_level = 0;
        int cloud_xp = 0;
        int pending = 0;
        std::vector<mission_view> missions;
        int gates_open = 0;
    };

    struct career_options {
        int exp_amount = 1000;
        float score_amount = 100.0f;
        int score_reason = 0;

        int mission_index = -1;
        int won_mode = 0;
        int killed_weapon_type = 0;

        bool is_won = true;
        bool is_headshot = true;
        char kill_kind[32] = "Headshot";
        char stat_suffix[32] = "Kills";

        bool is_unlock_held = false;
        bool is_attachments_everywhere = false;
    };

    inline career_options career_setup;

    struct career_domain {
        void tick();
        void watch();
        [[nodiscard]] career_snapshot snapshot();

        void fetch_profile();

        void give_exp();
        void add_experience();
        void add_score();
        void level_up();
        void save_level();
        void load_level();

        void complete_missions();
        void save_missions();
        void mission_won();
        void mission_kill();

        void match_end();
        void record_kill();
        void local_kill();
        void bump_stat();

        void unlock_all();
        void relock_all();
    };

    inline career_domain career;

}
