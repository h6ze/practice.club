#pragma once

namespace features {

    struct progression_options {
        int level = 100;
        int experience = 50000;
        char stat_key[64] = "Kills";
        int stat_value = 1000;
    };

    inline progression_options progression_setup;

    struct progression_domain {
        void set_level(int level);
        void max_level();
        void reset_level();
        void grant_experience(int amount);
        void fill_level();

        void apply_unlocks();
        void save();
        void load();
        void report_unlocks();

        void set_stat(const char* key, int value);
        void add_stat(const char* key, int amount);

        void list_stats();
        void raise_every_stat(int value);
        void max_everything();

        void list_weapons();
        void unlock_every_weapon_stat(int value);
    };

    inline progression_domain progression;

}
