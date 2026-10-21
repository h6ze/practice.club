#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <features/api/combat/weapons.hh>

namespace features {

    struct kit_choice {
        std::uintptr_t id = 0;
        std::int32_t index = -1;
        std::string name;
    };

    inline constexpr int attachment_slot_count = 7;

    struct kit_catalog {
        std::vector<kit_choice> weapons;
        std::vector<kit_choice> lethals;
        std::vector<kit_choice> operators;
        std::vector<kit_choice> damage_types;
        std::vector<kit_choice> attachments[attachment_slot_count];
    };

    struct kit_options {
        bool is_on_picked = false;

        int weapon = 0;
        int give_ammo = 300;
        bool is_full_mag = true;
        bool is_with_parts = false;
        int parts[attachment_slot_count] = { -1, -1, -1, -1, -1, -1, -1 };

        int lethal = 0;
        int operator_pick = 0;
        int operator_team = 0;
        int perk = 0;
        int field_upgrade = 0;

        int firing_mode = 0;
        int mag_ammo = 30;

        float heal_amount = 50.0f;
        float max_health = 200.0f;
        float damage_amount = 25.0f;

        bool is_infinite_reserve = false;
        bool is_infinite_lethals = false;
    };

    inline kit_options kit_setup;

    struct kit_domain {
        void tick();
        void refresh_catalog();
        [[nodiscard]] kit_catalog catalog();

        void give_weapon();
        void refill_ammo();
        void drop_weapon();
        void disarm();
        void switch_weapon(bool is_primary);

        void set_firing_mode();
        void cancel_bolt();
        void set_mag_ammo();
        void set_stock(bool is_no_stock);
        void apply_attachments();

        void loadout_weapon(bool is_primary);
        void loadout_lethal();
        void loadout_operator();
        void set_perk();
        void set_field_upgrade();

        void heal();
        void set_max_health();
        void damage();
        void kill();

        void use_skill();
        void reset_skill();
        void apply_perk();
        void set_fire(bool is_enabled);
        void uncrouch();

        void detonate_claymores();
        void explode_grenades();
        void refill_ammo_boxes();
    };

    inline kit_domain kit;

}
