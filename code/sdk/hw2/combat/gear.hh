#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <sdk/unreal/engine.hh>

namespace sdk::hw2 {

    [[nodiscard]] UObject* inventory_of(const APawn* pawn) noexcept;
    [[nodiscard]] UObject* vitals_of(const APawn* pawn) noexcept;
    [[nodiscard]] UObject* interaction_of(const APawn* pawn) noexcept;
    [[nodiscard]] AActor* lethal_of(const APawn* pawn) noexcept;
    [[nodiscard]] UObject* loadout_of(const AController* controller);

    enum class attachment_slot : std::uint8_t { optic, muzzle, stock, magazine, accessory, underbarrel, canted_sight };
    inline constexpr int attachment_slots = 7;

    struct attachment_set {
        UClass* parts[attachment_slots] = {};
    };

    [[nodiscard]] UObject* parts_of(const AActor* weapon) noexcept;
    [[nodiscard]] AActor* part_in(const AActor* weapon, attachment_slot slot) noexcept;
    [[nodiscard]] attachment_set attachments_of(const AActor* weapon) noexcept;

    bool set_attachments(AActor* weapon, const attachment_set& parts);

    bool give_weapon(APawn* pawn, UClass* weapon_class, int ammo, const attachment_set& parts, bool is_full_mag);
    bool refill_ammo(APawn* pawn);
    bool add_lethal_ammo(APawn* pawn);
    bool drop_weapon(APawn* pawn);
    bool destroy_weapons(APawn* pawn);
    bool force_change_weapon(APawn* pawn, bool is_primary);

    [[nodiscard]] int fill_reserves(APawn* pawn, bool is_weapons, bool is_lethals) noexcept;

    bool set_firing_mode(AActor* weapon, std::uint8_t mode);
    bool cancel_bolt_cycle(AActor* weapon);
    bool set_mag_ammo(AActor* weapon, int ammo);
    bool set_stock_state(AActor* weapon, bool is_no_stock);

    bool loadout_weapon(AController* controller, UClass* weapon_class, bool is_primary);
    bool loadout_lethal(AController* controller, UClass* lethal_class);
    bool loadout_operator(AController* controller, int team, UObject* operator_info);
    bool set_perk(AController* controller, std::uint8_t perk);
    bool set_field_upgrade(AController* controller, std::uint8_t upgrade);

    bool heal(APawn* pawn, double amount);
    bool set_max_health(APawn* pawn, double max_health);
    bool damage(APawn* pawn, double amount);
    bool kill(APawn* pawn);

    bool use_class_skill(APawn* pawn);
    bool reset_skill(APawn* pawn);
    bool apply_perk(APawn* pawn);
    bool set_fire_enabled(APawn* pawn, bool is_enabled);
    bool force_uncrouch(APawn* pawn);

    [[nodiscard]] int detonate_claymores();
    [[nodiscard]] int explode_grenades();
    [[nodiscard]] int refill_ammo_boxes() noexcept;

    struct gear_entry {
        UObject* object = nullptr;
        std::string name;
    };

    [[nodiscard]] std::vector<gear_entry> loaded_classes(const char* base_class);
    [[nodiscard]] std::vector<gear_entry> operator_assets();

}
