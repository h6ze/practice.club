#include "gear.hh"
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/core/container.hh>
#include <sdk/offsets.generated.hh>
#include <sdk/unreal/query/lookup.hh>

namespace sdk::hw2::detail {

    [[nodiscard]] inline std::uint32_t set_slot(attachment_slot slot) noexcept {
        namespace field = offsets::hw2_attachment_set;

        switch (slot) {
        case attachment_slot::optic: return field::optic;
        case attachment_slot::muzzle: return field::muzzle;
        case attachment_slot::stock: return field::stock;
        case attachment_slot::magazine: return field::magazine;
        case attachment_slot::accessory: return field::accessory;
        case attachment_slot::underbarrel: return field::underbarrel;
        case attachment_slot::canted_sight: return field::canted_sight;
        }

        return field::optic;
    }

    [[nodiscard]] inline std::uint32_t actor_slot(attachment_slot slot) noexcept {
        namespace field = offsets::hw2_weapon_parts;

        switch (slot) {
        case attachment_slot::optic: return field::optic;
        case attachment_slot::muzzle: return field::muzzle;
        case attachment_slot::stock: return field::stock;
        case attachment_slot::magazine: return field::magazine;
        case attachment_slot::accessory: return field::accessory;
        case attachment_slot::underbarrel: return field::underbarrel;
        case attachment_slot::canted_sight: return field::canted_sight;
        }

        return field::optic;
    }

    [[nodiscard]] inline bool is_compile_leftover(const std::string& name) {
        return name.rfind("SKEL_", 0) == 0 || name.rfind("REINST_", 0) == 0 || name.rfind("TRASHCLASS", 0) == 0;
    }

    [[nodiscard]] inline int top_up(void* inventory, std::uint32_t array_at, std::uint32_t stride, std::uint32_t quantity, std::uint32_t maximum) noexcept {
        const TArray<std::uint8_t> entries = mem::read<TArray<std::uint8_t>>(inventory, array_at, TArray<std::uint8_t>{});
        if (!entries.Data || entries.num() <= 0 || entries.num() > 64) return 0;

        int written = 0;
        for (std::int32_t i = 0; i < entries.num(); ++i) {
            std::uint8_t* entry = entries.Data + stride * static_cast<std::uint32_t>(i);

            const int most = mem::read<int>(entry, maximum, 0);
            if (most > 0 && mem::read<int>(entry, quantity, 0) < most && mem::write<int>(entry, quantity, most)) ++written;
        }

        return written;
    }

}

sdk::UObject* sdk::hw2::inventory_of(const APawn* pawn) noexcept {
    return mem::pointer<UObject>(pawn, offsets::hw2_character::inventory);
}

sdk::UObject* sdk::hw2::vitals_of(const APawn* pawn) noexcept {
    return mem::pointer<UObject>(pawn, offsets::hw2_character::health_component);
}

sdk::UObject* sdk::hw2::interaction_of(const APawn* pawn) noexcept {
    return mem::pointer<UObject>(pawn, offsets::hw2_character::interact_system);
}

sdk::AActor* sdk::hw2::lethal_of(const APawn* pawn) noexcept {
    return mem::pointer<AActor>(inventory_of(pawn), offsets::hw2_inventory_full::lethal_equipment);
}

sdk::UObject* sdk::hw2::loadout_of(const AController* controller) {
    UObject* loadout = mem::pointer<UObject>(controller, offsets::hw2_controller::loadout_component);

    return lookup::derives_from(loadout, "AC_Loadout_C") ? loadout : nullptr;
}

sdk::UObject* sdk::hw2::parts_of(const AActor* weapon) noexcept {
    return mem::pointer<UObject>(weapon, offsets::hw2_weapon_actor::ac_weapon_attachments);
}

sdk::AActor* sdk::hw2::part_in(const AActor* weapon, attachment_slot slot) noexcept {
    return mem::pointer<AActor>(parts_of(weapon), detail::actor_slot(slot));
}

sdk::hw2::attachment_set sdk::hw2::attachments_of(const AActor* weapon) noexcept {
    attachment_set parts;

    const UObject* component = parts_of(weapon);
    if (!component) return parts;

    for (int i = 0; i < attachment_slots; ++i) {
        const std::uint32_t at = offsets::hw2_weapon_parts::attachments + detail::set_slot(static_cast<attachment_slot>(i));
        parts.parts[i] = mem::pointer<UClass>(component, at);
    }

    return parts;
}

bool sdk::hw2::set_attachments(AActor* weapon, const attachment_set& parts) {
    UObject* component = parts_of(weapon);

    call::invocation entry(component, "SetAttachments");
    if (!entry.is_valid()) return false;

    for (int i = 0; i < attachment_slots; ++i)
        entry.set<UClass*>(offsets::params::set_attachments::attachments + detail::set_slot(static_cast<attachment_slot>(i)), parts.parts[i]);

    if (!entry.fire()) return false;

    return call::fire(component, "SpawnAttachments");
}

bool sdk::hw2::give_weapon(APawn* pawn, UClass* weapon_class, int ammo, const attachment_set& parts, bool is_full_mag) {
    if (!weapon_class) return false;

    call::invocation entry(pawn, "Server_OnPickupWeapon");
    if (!entry.is_valid()) return false;

    namespace parm = offsets::params::pickup_weapon;

    entry.set<UClass*>(parm::weapon_class, weapon_class);
    entry.set<int>(parm::ammo, ammo);
    for (int i = 0; i < attachment_slots; ++i)
        entry.set<UClass*>(parm::attachments + detail::set_slot(static_cast<attachment_slot>(i)), parts.parts[i]);
    entry.set<UObject*>(parm::skin, nullptr);
    entry.set<bool>(parm::is_full_mag, is_full_mag);

    return entry.fire();
}

bool sdk::hw2::refill_ammo(APawn* pawn) {
    return call::fire(inventory_of(pawn), "RefillAmmo");
}

bool sdk::hw2::add_lethal_ammo(APawn* pawn) {
    return call::fire(inventory_of(pawn), "AddLethalAmmo");
}

bool sdk::hw2::drop_weapon(APawn* pawn) {
    return call::fire(inventory_of(pawn), "Server_DropWeapon");
}

bool sdk::hw2::destroy_weapons(APawn* pawn) {
    return call::fire(inventory_of(pawn), "DestroyWeapons");
}

bool sdk::hw2::force_change_weapon(APawn* pawn, bool is_primary) {
    call::invocation entry(pawn, "Client_ForceChangeWeapon");
    if (!entry.is_valid()) return false;

    entry.set<bool>(offsets::params::force_change_weapon::is_primary, is_primary);
    entry.set<bool>(offsets::params::force_change_weapon::is_quick, true);

    return entry.fire();
}

int sdk::hw2::fill_reserves(APawn* pawn, bool is_weapons, bool is_lethals) noexcept {
    void* inventory = inventory_of(pawn);
    if (!inventory) return 0;

    int written = 0;

    if (is_weapons)
        written += detail::top_up(inventory, offsets::hw2_inventory_full::weapon_ammo, offsets::hw2_reserve_ammo_layout::byte_size,
            offsets::hw2_reserve_ammo::quantity, offsets::hw2_reserve_ammo::max_quantity);

    if (is_lethals)
        written += detail::top_up(inventory, offsets::hw2_inventory_full::lethal_ammo, offsets::hw2_lethal_ammo_layout::byte_size,
            offsets::hw2_lethal_ammo::quantity, offsets::hw2_lethal_ammo::max_quantity);

    return written;
}

bool sdk::hw2::set_firing_mode(AActor* weapon, std::uint8_t mode) {
    return call::fire_with<std::uint8_t>(weapon, "SetFiringMode", offsets::params::set_firing_mode::mode, mode);
}

bool sdk::hw2::cancel_bolt_cycle(AActor* weapon) {
    return call::fire(weapon, "CancelBoltCycle");
}

bool sdk::hw2::set_mag_ammo(AActor* weapon, int ammo) {
    return call::fire_with<int>(weapon, "SetMagAmmo", offsets::params::set_mag_ammo::ammo, ammo);
}

bool sdk::hw2::set_stock_state(AActor* weapon, bool is_no_stock) {
    return call::fire_with<bool>(weapon, "HW2_SetStockState", offsets::params::set_stock_state::is_no_stock, is_no_stock);
}

bool sdk::hw2::loadout_weapon(AController* controller, UClass* weapon_class, bool is_primary) {
    if (!weapon_class) return false;

    UObject* loadout = loadout_of(controller);
    if (is_primary) return call::fire_with<UClass*>(loadout, "Server_SetPrimaryWeapon", offsets::params::loadout_primary::weapon_class, weapon_class);

    return call::fire_with<UClass*>(loadout, "Server_SetSecondaryWeapon", offsets::params::loadout_secondary::weapon_class, weapon_class);
}

bool sdk::hw2::loadout_lethal(AController* controller, UClass* lethal_class) {
    if (!lethal_class) return false;

    return call::fire_with<UClass*>(loadout_of(controller), "SetLethalEquipmentClass", offsets::params::set_lethal_class::lethal_class, lethal_class);
}

bool sdk::hw2::loadout_operator(AController* controller, int team, UObject* operator_info) {
    if (!operator_info) return false;

    call::invocation entry(loadout_of(controller), "Server_SetOperatorClass");
    if (!entry.is_valid()) return false;

    entry.set<int>(offsets::params::loadout_operator::team, team);
    entry.set<UObject*>(offsets::params::loadout_operator::operator_info, operator_info);

    return entry.fire();
}

bool sdk::hw2::set_perk(AController* controller, std::uint8_t perk) {
    return call::fire_with<std::uint8_t>(loadout_of(controller), "SetPerkType", offsets::params::set_perk_type::perk, perk);
}

bool sdk::hw2::set_field_upgrade(AController* controller, std::uint8_t upgrade) {
    return call::fire_with<std::uint8_t>(loadout_of(controller), "SetFieldUpgrade", offsets::params::set_field_upgrade::upgrade, upgrade);
}

bool sdk::hw2::heal(APawn* pawn, double amount) {
    return call::fire_with<double>(vitals_of(pawn), "HealActor", offsets::params::heal_actor::amount, amount);
}

bool sdk::hw2::set_max_health(APawn* pawn, double max_health) {
    return call::fire_with<double>(vitals_of(pawn), "SetMaxHealth", offsets::params::set_max_health::max_health, max_health);
}

bool sdk::hw2::damage(APawn* pawn, double amount) {
    return call::fire_with<double>(vitals_of(pawn), "DamageActor", offsets::params::damage_actor::amount, amount);
}

bool sdk::hw2::kill(APawn* pawn) {
    return call::fire(vitals_of(pawn), "Server_KillPawn");
}

bool sdk::hw2::use_class_skill(APawn* pawn) {
    return call::fire(pawn, "UseClassSkill");
}

bool sdk::hw2::reset_skill(APawn* pawn) {
    return call::fire(pawn, "ResetSkill");
}

bool sdk::hw2::apply_perk(APawn* pawn) {
    return call::fire(pawn, "ApplySelectedPerk");
}

bool sdk::hw2::set_fire_enabled(APawn* pawn, bool is_enabled) {
    return call::fire(pawn, is_enabled ? "EnableFire" : "DisableFire");
}

bool sdk::hw2::force_uncrouch(APawn* pawn) {
    return call::fire(pawn, "ForceUncrouch");
}

int sdk::hw2::detonate_claymores() {
    int reached = 0;

    for (UObject* claymore : lookup::live_instances("BP_Claymore_C")) {
        AController* placer = mem::pointer<AController>(claymore, offsets::hw2_claymore::instigator_controller);
        if (call::fire_with<AController*>(claymore, "Explode", offsets::params::claymore_explode::instigator, placer)) ++reached;
    }

    return reached;
}

int sdk::hw2::explode_grenades() {
    int reached = 0;
    for (UObject* grenade : lookup::live_instances("BP_FragGrenade_C"))
        reached += call::fire(grenade, "ExplodeGrenade") ? 1 : 0;

    return reached;
}

int sdk::hw2::refill_ammo_boxes() noexcept {
    int reached = 0;

    for (UObject* box : lookup::live_instances("BP_SmallAmmoBox_C"))
        reached += mem::write<bool>(box, offsets::hw2_ammo_box::is_used, false) ? 1 : 0;

    for (UObject* box : lookup::live_instances("BP_SmallExplosiveAmmoBox_C"))
        reached += mem::write<bool>(box, offsets::hw2_explosive_box::is_used, false) ? 1 : 0;

    return reached;
}

std::vector<sdk::hw2::gear_entry> sdk::hw2::loaded_classes(const char* base_class) {
    std::vector<gear_entry> found;

    for (UClass* type : objects::subclasses_of(objects::find_class(base_class))) {
        std::string name = type->name();
        if (name.empty() || detail::is_compile_leftover(name)) continue;

        found.push_back({ type, std::move(name) });
    }

    return found;
}

std::vector<sdk::hw2::gear_entry> sdk::hw2::operator_assets() {
    std::vector<gear_entry> found;

    for (UObject* asset : lookup::live_instances("PDA_Operator_Info_C")) {
        std::string name = asset->name();
        if (!name.empty()) found.push_back({ asset, std::move(name) });
    }

    return found;
}
