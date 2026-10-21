#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace features {

    struct objective_entry {
        std::uintptr_t id = 0;
        std::string label;
        int kind = 0;
        int state = 0;
        int team = 0;
        int points = 0;
    };

    struct spawn_entry {
        std::uintptr_t id = 0;
        int index = 0;
        int team = 0;
        int phase = 0;
        bool is_active = false;
        bool is_claimed = false;
        float distance = 0.0f;
    };

    struct modes_snapshot {
        int mode = 0;
        std::vector<objective_entry> objectives;
        std::vector<spawn_entry> spawns;
        bool has_bomb = false;
        std::string bomb_carrier;
    };

    struct modes_options {
        std::uintptr_t objective = 0;
        std::uintptr_t spawn = 0;

        int capture_state = 0;
        bool is_points_team = false;
        float points_score = 100.0f;
        int points_reason = 0;
        bool is_holder_team = false;
        int holder_point = 0;

        bool is_by_picked = false;

        int rush_phase = 1;
        int rush_team = 0;

        int spawn_team = 0;
        bool is_ffa_preview = false;

        float resume_clock = 600.0f;
        int resume_a = 50;
        int resume_b = 0;
    };

    inline modes_options modes_setup;

    struct modes_domain {
        void tick();
        void watch();
        [[nodiscard]] modes_snapshot snapshot();

        void capture();
        void secure();
        void recover();
        void give_points();
        void set_holder();

        void plant();
        void disarm();
        void explode();
        void defuse();

        void give_bomb();
        void drop_bomb();
        void reset_bomb();

        void reset_reinforcements();
        void rush_phase();
        void choose_site();
        void pick_sites();
        void force_spawn();
        void refresh_rosters();
        void check_ffa();

        void spawn_on(bool is_active);
        void spawn_here();
        void spawn_native();
        void preview_spawn();
        void respawn_me(bool is_force);

        void simulate_resume();
    };

    inline modes_domain modes;

}
