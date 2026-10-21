#pragma once
#include <atomic>
#include <chrono>
#include <cstdint>
#include <iterator>
#include <map>
#include <mutex>
#include <string>
#include <utility>
#include <features/features.hh>
#include <sdk/core/access.hh>
#include <sdk/hw2/progression/ledger.hh>
#include <sdk/unreal/query/lookup.hh>
#include <sdk/offsets.generated.hh>
#include <client/diag/log/logger.hh>
#include <features/impl/progress.hh>

namespace features::detail {

    inline std::mutex career_lock;
    inline career_snapshot latest_career;
    inline std::atomic<bool> is_career_pass_queued{ false };
    inline std::chrono::steady_clock::time_point career_watched_until;
    inline std::chrono::steady_clock::time_point next_career_refresh;
    inline std::chrono::steady_clock::time_point next_gate_pass;
    inline constexpr std::chrono::seconds career_refresh_every{ 1 };
    inline constexpr std::chrono::seconds career_watch_window{ 1 };
    inline constexpr std::chrono::seconds gate_hold_every{ 10 };

    struct unlock_gate {
        const char* class_name;
        std::uint32_t offset;
        bool is_flag;
        int open_value;
    };

    inline constexpr unlock_gate unlock_gates[] = {
        { "PDA_WeaponInfo_C", sdk::offsets::hw2_weapon_info::unlock_level, false, 0 },
        { "PDA_SkinInfo_C", sdk::offsets::hw2_skin_info::unlock_kills, false, 0 },
        { "PDA_Operator_Info_C", sdk::offsets::hw2_operator_info::is_locked, true, 0 },
        { "PDA_Operator_Info_C", sdk::offsets::hw2_operator_info::level_to_unlock, false, 0 },
        { "PDA_Perk_Info_C", sdk::offsets::hw2_perk_info::unlock_level, false, 0 },
        { "PDA_FieldUpgrades_C", sdk::offsets::hw2_field_upgrade_info::unlock_level, false, 0 },
        { "PDA_LethalEquipment_C", sdk::offsets::hw2_lethal_info::unlock_level, false, 0 },
    };

    inline constexpr unlock_gate attachment_gate = { "PDA_WeaponInfo_C", sdk::offsets::hw2_weapon_info::is_can_use_attachments, true, 1 };

    struct gate_original {
        std::int32_t index = -1;
        int value = 0;
        bool is_flag = false;
    };

    inline std::map<std::pair<sdk::UObject*, std::uint32_t>, gate_original> gate_originals;

    [[nodiscard]] inline int read_gate(const sdk::UObject* asset, const unlock_gate& gate) {
        return gate.is_flag ? (sdk::mem::read<bool>(asset, gate.offset) ? 1 : 0) : sdk::mem::read<int>(asset, gate.offset);
    }

    inline bool write_gate(sdk::UObject* asset, std::uint32_t offset, bool is_flag, int value) {
        return is_flag ? sdk::mem::write<bool>(asset, offset, value != 0) : sdk::mem::write<int>(asset, offset, value);
    }

    [[nodiscard]] inline int open_gate(const unlock_gate& gate) {
        int opened = 0;

        for (sdk::UObject* asset : sdk::lookup::live_instances(gate.class_name)) {
            const int current = read_gate(asset, gate);
            if (current == gate.open_value) continue;

            const auto key = std::make_pair(asset, gate.offset);
            if (gate_originals.find(key) == gate_originals.end()) gate_originals[key] = { asset->index(), current, gate.is_flag };

            if (write_gate(asset, gate.offset, gate.is_flag, gate.open_value)) ++opened;
        }

        return opened;
    }

    [[nodiscard]] inline int open_gates(bool is_attachments_everywhere) {
        int opened = 0;
        for (const unlock_gate& gate : unlock_gates) opened += open_gate(gate);
        if (is_attachments_everywhere) opened += open_gate(attachment_gate);

        return opened;
    }

    [[nodiscard]] inline int close_gates() {
        int restored = 0;

        for (const auto& [key, original] : gate_originals) {
            if (sdk::objects::at(original.index) != key.first) continue;

            if (write_gate(key.first, key.second, original.is_flag, original.value)) ++restored;
        }

        gate_originals.clear();

        return restored;
    }

    struct live_slot {
        sdk::lookup::held held;
        std::chrono::steady_clock::time_point next_try;
    };

    inline live_slot save_level_slot;
    inline live_slot save_game_slot;
    inline live_slot save_streaks_slot;
    inline live_slot save_menu_slot;
    inline constexpr std::chrono::seconds save_search_every{ 3 };

    [[nodiscard]] inline sdk::UObject* live_object(live_slot& slot, const char* class_name) {
        if (sdk::lookup::is_live(slot.held)) return slot.held.object;

        const auto now = std::chrono::steady_clock::now();
        if (now < slot.next_try) return nullptr;
        slot.next_try = now + save_search_every;

        sdk::UObject* found = sdk::objects::find_live_instance(sdk::objects::find_class(class_name));
        slot.held = { found, found ? found->index() : -1 };

        return found;
    }

    [[nodiscard]] inline career_snapshot take_career_snapshot() {
        career_snapshot fresh;

        const sdk::hw2::cloud_status cloud = sdk::hw2::read_cloud(own_controller());
        fresh.has_cloud = cloud.is_found;
        fresh.is_authenticated = cloud.is_authenticated;
        fresh.cloud_level = cloud.level;
        fresh.cloud_xp = cloud.total_xp;
        fresh.pending = cloud.pending;

        for (const sdk::hw2::mission_entry& entry : sdk::hw2::missions(own_state()))
            fresh.missions.push_back({ entry.id, entry.progress, entry.target, entry.reward, entry.is_completed });

        fresh.gates_open = static_cast<int>(gate_originals.size());

        return fresh;
    }

    inline void say_career(bool is_called, const std::string& done, const char* function_name) {
        if (is_called) { logger::success("[ career ] " + done); return; }

        logger::error(std::string("[ career ] ") + function_name + " could not be called -> join a match, or read the call line above");
    }

}
