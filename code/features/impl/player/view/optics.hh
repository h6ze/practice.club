#pragma once
#include <atomic>
#include <cstdint>
#include <cstdio>
#include <iterator>
#include <string>
#include <unordered_map>
#include <features/features.hh>
#include <sdk/hw2/pawn/lens.hh>
#include <features/impl/combat/weapons/arsenal.hh>

namespace features::detail {

    struct tracked_fov {
        double base = 0.0;
        double written = 0.0;
    };

    struct view_original {
        std::int32_t index = -1;
        sdk::hw2::view_stats stats;
        tracked_fov default_fov;
        tracked_fov current_fov;
    };

    struct view_settings_original {
        std::int32_t index = -1;
        tracked_fov fov;
        bool is_tpp = false;
        bool is_tpp_forced = false;
    };

    inline std::unordered_map<sdk::APawn*, view_original> view_originals;
    inline std::unordered_map<sdk::UObject*, view_settings_original> view_settings_originals;
    inline std::atomic<bool> is_view_pass_queued{ false };

    inline view_original* original_view(sdk::APawn* pawn) {
        if (!pawn) return nullptr;

        const auto found = view_originals.find(pawn);
        if (found != view_originals.end() && is_same_object(pawn, found->second.index)) return &found->second;

        view_original entry;
        entry.index = pawn->index();
        if (!sdk::hw2::read_view(pawn, entry.stats)) return nullptr;

        entry.default_fov.base = sdk::hw2::default_fov_of(pawn);

        return &(view_originals[pawn] = entry);
    }

    inline view_settings_original* original_view_settings(sdk::UObject* settings) {
        if (!settings) return nullptr;

        const auto found = view_settings_originals.find(settings);
        if (found != view_settings_originals.end() && is_same_object(settings, found->second.index)) return &found->second;

        view_settings_original entry;
        entry.index = settings->index();
        entry.fov.base = sdk::mem::read<double>(settings, sdk::offsets::hw2_controller_settings::field_of_view, 0.0);
        entry.is_tpp = sdk::mem::read<bool>(settings, sdk::offsets::hw2_controller_settings::use_tpp, false);

        return &(view_settings_originals[settings] = entry);
    }

    inline tracked_fov held_input_fov;

    inline void forget_stale_view() {
        for (auto entry = view_originals.begin(); entry != view_originals.end();)
            entry = is_same_object(entry->first, entry->second.index) ? std::next(entry) : view_originals.erase(entry);

        for (auto entry = view_settings_originals.begin(); entry != view_settings_originals.end();)
            entry = is_same_object(entry->first, entry->second.index) ? std::next(entry) : view_settings_originals.erase(entry);
    }

    [[nodiscard]] inline sdk::hw2::view_stats tuned_view(const sdk::hw2::view_stats& original) {
        const view_options& options = view_setup;
        sdk::hw2::view_stats tuned = original;

        if (options.is_no_sway) {
            tuned.is_breathing = false;
            tuned.breathing_strength = 0.0;
            tuned.breathing_yaw = 0.0;
            tuned.breathing_pitch = 0.0;
        }

        if (options.is_hold_breath) tuned.is_hold_breath_allowed = true;
        if (options.is_clean_screen) tuned.post_process_blend = 0.0f;
        if (options.is_no_run_shake) tuned.run_camera_shake = nullptr;

        if (options.is_third_person) {
            tuned.tpp_arm_length = options.arm_length;
            tuned.arm_length = options.arm_length;

            tuned.socket_offset = { 0.0, options.side_shift, 0.0 };
            tuned.target_offset = { 0.0, 0.0, options.pivot_rise };
            tuned.is_arm_collision = false;
        }

        return tuned;
    }

    [[nodiscard]] inline std::string optics_line(const char* label, double original, double live) {
        char text[128];
        std::snprintf(text, sizeof(text), "[ view ]   %s %.3f -> %.3f", label, original, live);

        return text;
    }

    inline sdk::UObject* held_input_subsystem = nullptr;
    inline std::int32_t held_input_index = -1;
    inline int input_lookup_wait = 0;

    [[nodiscard]] inline sdk::UObject* input_subsystem() {
        if (is_same_object(held_input_subsystem, held_input_index)) return held_input_subsystem;
        if (input_lookup_wait > 0) { --input_lookup_wait; return nullptr; }

        const sdk::UClass* type = sdk::objects::find_class("HW2PlayerInputSubsystem");
        held_input_subsystem = type ? sdk::objects::find_live_instance(type) : nullptr;
        held_input_index = held_input_subsystem ? held_input_subsystem->index() : -1;

        if (!held_input_subsystem) input_lookup_wait = 120;

        return held_input_subsystem;
    }

    [[nodiscard]] inline bool is_in_image(std::uintptr_t address, std::uintptr_t base) {
        return base && address >= base && address < base + sdk::offsets::image_size;
    }

    [[nodiscard]] inline std::string rva_line(const char* label, std::uintptr_t address, std::uintptr_t base) {
        char text[192];
        std::snprintf(text, sizeof(text), "[ view ]   %s 0x%016llX rva 0x%08llX", label,
            static_cast<unsigned long long>(address),
            static_cast<unsigned long long>(address >= base ? address - base : 0));

        return text;
    }

    [[nodiscard]] inline std::string slot_label(std::uint32_t vtable_at, std::uint32_t slot) {
        char text[64];
        std::snprintf(text, sizeof(text), "+0x%02X slot %u", vtable_at, slot);

        return text;
    }

    [[nodiscard]] inline std::string optics_value(const char* label, double value) {
        char text[128];
        std::snprintf(text, sizeof(text), "[ view ]   %s %.3f", label, value);

        return text;
    }

    inline double held_fov(tracked_fov& fov, double live, bool is_on, double wanted) {
        if (live != fov.written) fov.base = live;

        fov.written = is_on ? wanted : fov.base;

        return fov.written;
    }

}
