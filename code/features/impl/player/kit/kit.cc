#include <features/features.hh>
#include <cstdio>
#include <string>
#include <utility>
#include <sdk/unreal/runtime/stage.hh>
#include <features/impl/helpers.hh>

namespace features {

    void kit_domain::tick() {
        if (!kit_setup.is_infinite_reserve && !kit_setup.is_infinite_lethals) return;
        if (detail::is_kit_pass_queued.exchange(true)) return;

        game::dispatch::post([]() {
            (void)sdk::hw2::fill_reserves(detail::own_character(), kit_setup.is_infinite_reserve, kit_setup.is_infinite_lethals);

            detail::is_kit_pass_queued = false;
        });
    }

    void kit_domain::refresh_catalog() {
        const auto now = std::chrono::steady_clock::now();
        if (now < detail::next_catalog_try) return;
        detail::next_catalog_try = now + detail::catalog_retry_every;

        game::dispatch::post([]() {
            kit_catalog fresh = detail::build_catalog();

            char line[160];
            std::snprintf(line, sizeof(line), "[ kit ] %zu weapons, %zu lethals, %zu operators, %zu damage types loaded",
                fresh.weapons.size(), fresh.lethals.size(), fresh.operators.size(), fresh.damage_types.size());
            logger::success(line);

            const std::lock_guard<std::mutex> guard(detail::catalog_lock);
            detail::published_catalog = std::move(fresh);
        });
    }

    kit_catalog kit_domain::catalog() {
        return detail::catalog_copy();
    }

    void kit_domain::give_weapon() {
        const kit_options chosen = kit_setup;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([chosen, target]() {
            detail::kit_subject subject;
            if (!detail::find_subject(chosen.is_on_picked, target, true, "giving a weapon", subject)) return;

            const kit_catalog list = detail::catalog_copy();
            sdk::UClass* weapon = detail::chosen_object<sdk::UClass>(list.weapons, chosen.weapon);
            if (!weapon) { logger::error("[ kit ] that weapon class is gone -> refresh the lists"); return; }

            sdk::hw2::attachment_set parts;
            if (chosen.is_with_parts)
                for (int slot = 0; slot < attachment_slot_count; ++slot)
                    parts.parts[slot] = detail::chosen_object<sdk::UClass>(list.attachments[slot], chosen.parts[slot]);

            detail::say_kit(sdk::hw2::give_weapon(subject.pawn, weapon, chosen.give_ammo, parts, chosen.is_full_mag),
                subject.who + " got " + list.weapons[static_cast<size_t>(chosen.weapon)].name, "Server_OnPickupWeapon");
        });
    }

    void kit_domain::refill_ammo() {
        const bool is_on_picked = kit_setup.is_on_picked;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([is_on_picked, target]() {
            detail::kit_subject subject;
            if (!detail::find_subject(is_on_picked, target, true, "refilling ammo", subject)) return;

            const bool is_refilled = sdk::hw2::refill_ammo(subject.pawn) && sdk::hw2::add_lethal_ammo(subject.pawn);
            detail::say_kit(is_refilled, subject.who + " refilled, guns and lethals", "RefillAmmo/AddLethalAmmo");
        });
    }

    void kit_domain::drop_weapon() {
        const bool is_on_picked = kit_setup.is_on_picked;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([is_on_picked, target]() {
            detail::kit_subject subject;
            if (!detail::find_subject(is_on_picked, target, false, "dropping a weapon", subject)) return;

            detail::say_kit(sdk::hw2::drop_weapon(subject.pawn), subject.who + " dropped the gun in hand", "Server_DropWeapon");
        });
    }

    void kit_domain::disarm() {
        const bool is_on_picked = kit_setup.is_on_picked;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([is_on_picked, target]() {
            detail::kit_subject subject;
            if (!detail::find_subject(is_on_picked, target, true, "disarming", subject)) return;

            detail::say_kit(sdk::hw2::destroy_weapons(subject.pawn), subject.who + " disarmed", "DestroyWeapons");
        });
    }

    void kit_domain::switch_weapon(bool is_primary) {
        const bool is_on_picked = kit_setup.is_on_picked;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([is_on_picked, target, is_primary]() {
            detail::kit_subject subject;
            if (!detail::find_subject(is_on_picked, target, false, "switching someone's weapon", subject)) return;

            detail::say_kit(sdk::hw2::force_change_weapon(subject.pawn, is_primary),
                subject.who + " switched to the " + (is_primary ? "primary" : "secondary"), "Client_ForceChangeWeapon");
        });
    }

    void kit_domain::set_firing_mode() {
        const int mode = kit_setup.firing_mode;

        game::dispatch::post([mode]() {
            sdk::AActor* weapon = detail::held_weapon_of(detail::own_character());
            if (!weapon) { logger::error("[ kit ] no gun in your hands"); return; }

            detail::say_kit(sdk::hw2::set_firing_mode(weapon, static_cast<std::uint8_t>(mode)), "firing mode set to " + std::to_string(mode), "SetFiringMode");
        });
    }

    void kit_domain::cancel_bolt() {
        game::dispatch::post([]() {
            sdk::AActor* weapon = detail::held_weapon_of(detail::own_character());
            if (!weapon) { logger::error("[ kit ] no gun in your hands"); return; }

            detail::say_kit(sdk::hw2::cancel_bolt_cycle(weapon), "bolt cycle cancelled", "CancelBoltCycle");
        });
    }

    void kit_domain::set_mag_ammo() {
        const int ammo = kit_setup.mag_ammo;

        game::dispatch::post([ammo]() {
            if (!detail::require_host("setting the magazine")) return;

            sdk::AActor* weapon = detail::held_weapon_of(detail::own_character());
            if (!weapon) { logger::error("[ kit ] no gun in your hands"); return; }

            detail::say_kit(sdk::hw2::set_mag_ammo(weapon, ammo), "magazine set to " + std::to_string(ammo), "SetMagAmmo");
        });
    }

    void kit_domain::set_stock(bool is_no_stock) {
        game::dispatch::post([is_no_stock]() {
            sdk::AActor* weapon = detail::held_weapon_of(detail::own_character());
            if (!weapon) { logger::error("[ kit ] no gun in your hands"); return; }

            detail::say_kit(sdk::hw2::set_stock_state(weapon, is_no_stock), is_no_stock ? "stock taken off" : "stock put back", "HW2_SetStockState");
        });
    }

    void kit_domain::apply_attachments() {
        const kit_options chosen = kit_setup;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([chosen, target]() {
            detail::kit_subject subject;
            if (!detail::find_subject(chosen.is_on_picked, target, true, "changing attachments", subject)) return;

            sdk::AActor* weapon = detail::held_weapon_of(subject.pawn);
            if (!weapon) { logger::error("[ kit ] " + subject.who + " has no gun in hand"); return; }

            const kit_catalog list = detail::catalog_copy();
            sdk::hw2::attachment_set parts = sdk::hw2::attachments_of(weapon);
            for (int slot = 0; slot < attachment_slot_count; ++slot) {
                if (chosen.parts[slot] == -1) continue;

                parts.parts[slot] = detail::chosen_object<sdk::UClass>(list.attachments[slot], chosen.parts[slot]);
            }

            detail::say_kit(sdk::hw2::set_attachments(weapon, parts), "attachments rebuilt on " + subject.whose + " gun", "SetAttachments/SpawnAttachments");
        });
    }

    void kit_domain::loadout_weapon(bool is_primary) {
        const kit_options chosen = kit_setup;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([chosen, target, is_primary]() {
            detail::kit_subject subject;
            if (!detail::find_subject(chosen.is_on_picked, target, false, "changing a loadout", subject)) return;

            const kit_catalog list = detail::catalog_copy();
            sdk::UClass* weapon = detail::chosen_object<sdk::UClass>(list.weapons, chosen.weapon);
            if (!weapon) { logger::error("[ kit ] that weapon class is gone -> refresh the lists"); return; }

            detail::say_kit(sdk::hw2::loadout_weapon(subject.controller, weapon, is_primary),
                subject.whose + " " + (is_primary ? "primary" : "secondary") + " is now " + list.weapons[static_cast<size_t>(chosen.weapon)].name,
                is_primary ? "Server_SetPrimaryWeapon" : "Server_SetSecondaryWeapon");
        });
    }

    void kit_domain::loadout_lethal() {
        const kit_options chosen = kit_setup;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([chosen, target]() {
            detail::kit_subject subject;
            if (!detail::find_subject(chosen.is_on_picked, target, false, "changing a lethal", subject)) return;

            const kit_catalog list = detail::catalog_copy();
            sdk::UClass* lethal = detail::chosen_object<sdk::UClass>(list.lethals, chosen.lethal);
            if (!lethal) { logger::error("[ kit ] that lethal class is gone -> refresh the lists"); return; }

            detail::say_kit(sdk::hw2::loadout_lethal(subject.controller, lethal),
                subject.whose + " lethal is now " + list.lethals[static_cast<size_t>(chosen.lethal)].name, "SetLethalEquipmentClass");
        });
    }

    void kit_domain::loadout_operator() {
        const kit_options chosen = kit_setup;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([chosen, target]() {
            detail::kit_subject subject;
            if (!detail::find_subject(chosen.is_on_picked, target, false, "changing a character", subject)) return;

            const kit_catalog list = detail::catalog_copy();
            sdk::UObject* operator_info = detail::chosen_object<sdk::UObject>(list.operators, chosen.operator_pick);
            if (!operator_info) { logger::error("[ kit ] that character asset is gone -> refresh the lists"); return; }

            detail::say_kit(sdk::hw2::loadout_operator(subject.controller, chosen.operator_team, operator_info),
                subject.who + " is now " + list.operators[static_cast<size_t>(chosen.operator_pick)].name + " for team " + std::to_string(chosen.operator_team),
                "Server_SetOperatorClass");
        });
    }

    void kit_domain::set_perk() {
        const kit_options chosen = kit_setup;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([chosen, target]() {
            detail::kit_subject subject;
            if (!detail::find_subject(chosen.is_on_picked, target, false, "changing a perk", subject)) return;

            detail::say_kit(sdk::hw2::set_perk(subject.controller, static_cast<std::uint8_t>(chosen.perk)),
                subject.whose + " perk set to " + std::to_string(chosen.perk) + " -> apply perk puts it on the body", "SetPerkType");
        });
    }

    void kit_domain::set_field_upgrade() {
        const kit_options chosen = kit_setup;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([chosen, target]() {
            detail::kit_subject subject;
            if (!detail::find_subject(chosen.is_on_picked, target, false, "changing a field upgrade", subject)) return;

            detail::say_kit(sdk::hw2::set_field_upgrade(subject.controller, static_cast<std::uint8_t>(chosen.field_upgrade)),
                subject.whose + " field upgrade set to " + std::to_string(chosen.field_upgrade), "SetFieldUpgrade");
        });
    }

    void kit_domain::heal() {
        const kit_options chosen = kit_setup;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([chosen, target]() {
            detail::kit_subject subject;
            if (!detail::find_subject(chosen.is_on_picked, target, true, "healing", subject)) return;

            detail::say_kit(sdk::hw2::heal(subject.pawn, chosen.heal_amount),
                subject.who + " healed by " + std::to_string(static_cast<int>(chosen.heal_amount)), "HealActor");
        });
    }

    void kit_domain::set_max_health() {
        const kit_options chosen = kit_setup;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([chosen, target]() {
            detail::kit_subject subject;
            if (!detail::find_subject(chosen.is_on_picked, target, true, "changing max health", subject)) return;

            detail::say_kit(sdk::hw2::set_max_health(subject.pawn, chosen.max_health),
                subject.whose + " max health set to " + std::to_string(static_cast<int>(chosen.max_health)), "SetMaxHealth");
        });
    }

    void kit_domain::damage() {
        const kit_options chosen = kit_setup;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([chosen, target]() {
            detail::kit_subject subject;
            if (!detail::find_subject(chosen.is_on_picked, target, true, "damaging", subject)) return;

            detail::say_kit(sdk::hw2::damage(subject.pawn, chosen.damage_amount),
                subject.who + " took " + std::to_string(static_cast<int>(chosen.damage_amount)), "DamageActor");
        });
    }

    void kit_domain::kill() {
        const bool is_on_picked = kit_setup.is_on_picked;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([is_on_picked, target]() {
            detail::kit_subject subject;
            if (!detail::find_subject(is_on_picked, target, true, "killing", subject)) return;

            detail::say_kit(sdk::hw2::kill(subject.pawn), subject.who + " killed", "Server_KillPawn");
        });
    }

    void kit_domain::use_skill() {
        game::dispatch::post([]() {
            sdk::APawn* pawn = detail::own_character();
            if (!pawn) { logger::error("[ kit ] no pawn -> spawn in first"); return; }

            detail::say_kit(sdk::hw2::use_class_skill(pawn), "class skill used", "UseClassSkill");
        });
    }

    void kit_domain::reset_skill() {
        game::dispatch::post([]() {
            sdk::APawn* pawn = detail::own_character();
            if (!pawn) { logger::error("[ kit ] no pawn -> spawn in first"); return; }

            detail::say_kit(sdk::hw2::reset_skill(pawn), "skill reset", "ResetSkill");
        });
    }

    void kit_domain::apply_perk() {
        game::dispatch::post([]() {
            sdk::APawn* pawn = detail::own_character();
            if (!pawn) { logger::error("[ kit ] no pawn -> spawn in first"); return; }

            detail::say_kit(sdk::hw2::apply_perk(pawn), "selected perk applied to your body", "ApplySelectedPerk");
        });
    }

    void kit_domain::set_fire(bool is_enabled) {
        const bool is_on_picked = kit_setup.is_on_picked;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([is_on_picked, target, is_enabled]() {
            detail::kit_subject subject;
            if (!detail::find_subject(is_on_picked, target, false, "stopping someone firing", subject)) return;

            detail::say_kit(sdk::hw2::set_fire_enabled(subject.pawn, is_enabled),
                std::string("firing ") + (is_enabled ? "allowed" : "blocked") + " for " + subject.who, is_enabled ? "EnableFire" : "DisableFire");
        });
    }

    void kit_domain::uncrouch() {
        const bool is_on_picked = kit_setup.is_on_picked;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([is_on_picked, target]() {
            detail::kit_subject subject;
            if (!detail::find_subject(is_on_picked, target, false, "standing someone up", subject)) return;

            detail::say_kit(sdk::hw2::force_uncrouch(subject.pawn), subject.who + " stood up", "ForceUncrouch");
        });
    }

    void kit_domain::detonate_claymores() {
        game::dispatch::post([]() {
            if (!detail::require_host("detonating claymores")) return;

            logger::success("[ kit ] " + std::to_string(sdk::hw2::detonate_claymores()) + " claymores set off");
        });
    }

    void kit_domain::explode_grenades() {
        game::dispatch::post([]() {
            if (!detail::require_host("exploding grenades")) return;

            logger::success("[ kit ] " + std::to_string(sdk::hw2::explode_grenades()) + " grenades set off");
        });
    }

    void kit_domain::refill_ammo_boxes() {
        game::dispatch::post([]() {
            if (!detail::require_host("refilling ammo boxes")) return;

            logger::success("[ kit ] " + std::to_string(sdk::hw2::refill_ammo_boxes()) + " ammo boxes usable again");
        });
    }

}
