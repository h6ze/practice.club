#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace features {

    struct lobby_entry {
        std::uintptr_t id = 0;
        std::string name;
        int team = -1;
        int kills = 0;
        int deaths = 0;
        int assists = 0;
        double score = 0.0;
        bool is_bot = false;
        bool is_local = false;
        bool is_alive = false;
    };

    struct match_snapshot {
        bool is_host = false;
        bool has_match = false;
        int team_a = 0;
        int team_b = 0;
        int rounds_a = 0;
        int rounds_b = 0;
        int winner = 0;
        int match_state = 0;
        int round_state = 0;
        float clock = 0.0f;
        double time_to_start = 0.0;
        std::vector<lobby_entry> players;
    };

    struct host_options {
        std::uintptr_t target = 0;

        int team_a_points = 0;
        int team_b_points = 0;
        int team = 0;
        int match_state = 0;
        int round_state = 0;

        char new_name[32] = "";
        int kills = 0;
        int deaths = 0;
        int assists = 0;
        float score = 0.0f;

        int bots_a = 1;
        int bots_b = 1;
        int bots_ffa = 1;

        char travel_level[64] = "";
        char match_mode[32] = "";
    };

    inline host_options host_setup;

    struct host_domain {
        void tick();
        [[nodiscard]] match_snapshot snapshot();

        void set_points(int side);
        void add_point();
        void add_round();
        void set_winner();
        void end_round();
        void end_game();
        void reset_scores();
        void flip_rounds();
        void set_match_state();
        void set_round_state();
        void start_clock();
        void time_out();
        void apply_lobby_size();

        void restart_match();
        void start_match();
        void end_match();
        void travel();
        void create_match();

        void respawn_target();
        void respawn_bot();
        void remove_bot();
        void move_target();
        void check_target_team();
        void rename_target();
        void set_target_stats();

        void switch_own_team();
        void flip_teams();
        void balance_teams();

        void add_bots();
        void add_bots_ffa();
        void remove_one_bot();
        void remove_all_bots();

        void report();
    };

    inline host_domain host;

}
