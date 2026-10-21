#pragma once
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <string>
#include <utility>
#include <vector>
#include <features/features.hh>
#include <sdk/hw2/combat/gear.hh>
#include <sdk/hw2/hw2.hh>
#include <sdk/hw2/match/rules.hh>
#include <sdk/hw2/combat/weapon.hh>
#include <client/diag/log/logger.hh>
#include <features/impl/combat/weapons/arsenal.hh>
#include <features/impl/match/host/lobby.hh>

namespace features::detail {

    inline std::mutex catalog_lock;
    inline kit_catalog published_catalog;
    inline std::atomic<bool> is_kit_pass_queued{ false };
    inline std::chrono::steady_clock::time_point next_catalog_try;
    inline constexpr std::chrono::seconds catalog_retry_every{ 5 };

    inline constexpr const char* attachment_bases[attachment_slot_count] = {
        "BP_Base_Optics_C", "BP_Base_Muzzle_C", "BP_Base_Stock_C", "BP_Base_Magazine_C",
        "BP_Base_Accessory_C", "BP_Base_Underbarrel_C", "BP_CantedSight_Base_C",
    };

    [[nodiscard]] inline std::string plain_name(std::string name) {
        for (const char* prefix : { "BP_", "Bp_", "DT_", "PDA_" }) {
            if (name.rfind(prefix, 0) != 0) continue;

            name.erase(0, std::strlen(prefix));
            break;
        }

        if (name.size() > 2 && name.compare(name.size() - 2, 2, "_C") == 0) name.erase(name.size() - 2);

        return name;
    }

    [[nodiscard]] inline std::vector<kit_choice> to_choices(const std::vector<sdk::hw2::gear_entry>& entries) {
        std::vector<kit_choice> choices;

        for (const sdk::hw2::gear_entry& entry : entries) {
            if (entry.name.find("Base") != std::string::npos) continue;

            choices.push_back({ reinterpret_cast<std::uintptr_t>(entry.object), entry.object->index(), plain_name(entry.name) });
        }

        std::sort(choices.begin(), choices.end(), [](const kit_choice& a, const kit_choice& b) { return a.name < b.name; });

        return choices;
    }

    [[nodiscard]] inline kit_catalog build_catalog() {
        kit_catalog fresh;
        fresh.weapons = to_choices(sdk::hw2::loaded_classes("BP_BaseWeapon_C"));
        fresh.lethals = to_choices(sdk::hw2::loaded_classes("BP_BaseLethalEquipment_C"));
        fresh.operators = to_choices(sdk::hw2::operator_assets());
        fresh.damage_types = to_choices(sdk::hw2::loaded_classes("DT_BaseDamage_C"));

        for (int slot = 0; slot < attachment_slot_count; ++slot)
            fresh.attachments[slot] = to_choices(sdk::hw2::loaded_classes(attachment_bases[slot]));

        return fresh;
    }

    template <class T> [[nodiscard]] inline T* chosen_object(const std::vector<kit_choice>& list, int pick) {
        if (pick < 0 || pick >= static_cast<int>(list.size())) return nullptr;

        const kit_choice& choice = list[static_cast<size_t>(pick)];
        sdk::UObject* object = sdk::objects::at(choice.index);

        return reinterpret_cast<std::uintptr_t>(object) == choice.id ? static_cast<T*>(object) : nullptr;
    }

    [[nodiscard]] inline kit_catalog catalog_copy() {
        const std::lock_guard<std::mutex> guard(catalog_lock);

        return published_catalog;
    }

    [[nodiscard]] inline sdk::UObject* damage_type_default(int element, int& count) {
        const std::lock_guard<std::mutex> guard(catalog_lock);

        count = static_cast<int>(published_catalog.damage_types.size());
        sdk::UClass* type = chosen_object<sdk::UClass>(published_catalog.damage_types, element);

        return type ? type->default_object() : nullptr;
    }

    struct kit_subject {
        sdk::APawn* pawn = nullptr;
        sdk::AController* controller = nullptr;
        std::string who;

        std::string whose;
    };

    [[nodiscard]] inline bool find_subject(bool is_on_picked, std::uintptr_t target, bool is_server_side, const char* what, kit_subject& subject) {
        if ((is_on_picked || is_server_side) && !require_host(what)) return false;

        if (!is_on_picked) {
            subject.pawn = own_character();
            subject.controller = own_controller();
            subject.who = "you";
            subject.whose = "your";

            if (!subject.pawn) logger::error("[ kit ] no pawn -> spawn in first");

            return subject.pawn != nullptr;
        }

        sdk::APlayerState* member = chosen_member(target);
        if (!member) return false;

        subject.who = name_of(member);
        subject.whose = subject.who + "'s";
        subject.controller = sdk::hw2::controller_of(member);
        subject.pawn = member->PawnPrivate();

        if (!subject.pawn || sdk::hw2::kind_of(subject.pawn) != sdk::hw2::actor_kind::character) {
            logger::error("[ kit ] " + subject.who + " is not alive");
            return false;
        }

        return true;
    }

    [[nodiscard]] inline sdk::AActor* held_weapon_of(const sdk::APawn* pawn) {
        return sdk::hw2::weapon_of(pawn, sdk::hw2::weapon_slot::current);
    }

    inline void say_kit(bool is_called, const std::string& done, const char* function_name) {
        if (is_called) { logger::success("[ kit ] " + done); return; }

        logger::error(std::string("[ kit ] ") + function_name + " could not be called -> read the call line above");
    }

}
