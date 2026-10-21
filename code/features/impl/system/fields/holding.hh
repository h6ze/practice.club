#pragma once
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <features/data/boards.hh>
#include <features/features.hh>
#include <sdk/core/access.hh>
#include <sdk/core/container.hh>
#include <sdk/hw2/combat/gear.hh>
#include <sdk/unreal/query/lookup.hh>
#include <sdk/hw2/match/rules.hh>
#include <sdk/hw2/arena/sandbox.hh>
#include <sdk/hw2/combat/weapon.hh>
#include <features/impl/combat/weapons/arsenal.hh>
#include <features/impl/match/host/lobby.hh>
#include <features/impl/player/kit/outfit.hh>
#include <features/impl/match/network/airwaves.hh>
#include <features/impl/player/view/optics.hh>
#include <features/impl/progress.hh>
#include <features/impl/player/progression/records.hh>
#include <features/impl/world/scenery/scenery.hh>
#include <features/impl/match/modes/theater.hh>

namespace features::detail {

    inline std::atomic<bool> is_fields_pass_queued{ false };

    struct board_place {
        sdk::UObject* owner = nullptr;
        void* base = nullptr;
        std::uint32_t span = 0;
        int count = 0;
    };

    inline constexpr std::uint32_t whole_object = 0xFFFFFFFFu;
    inline constexpr std::int32_t array_cap = 256;

    inline sdk::lookup::held own_streak_slot;
    inline std::chrono::steady_clock::time_point next_streak_search;
    inline constexpr std::chrono::seconds streak_search_every{ 2 };

    [[nodiscard]] inline board_place object_place(sdk::UObject* object) {
        board_place place;
        place.owner = object;
        place.base = object;
        place.span = object ? whole_object : 0;

        return place;
    }

    [[nodiscard]] inline board_place array_place(sdk::UObject* owner, std::uint32_t offset, std::uint32_t stride, int element, bool is_one_element) {
        const sdk::TArray<std::uint8_t> items = sdk::mem::read<sdk::TArray<std::uint8_t>>(owner, offset, sdk::TArray<std::uint8_t>{});
        if (!owner || !items.Data || items.num() <= 0 || items.num() > array_cap) return {};

        board_place place;
        place.owner = owner;
        place.count = items.num();

        if (!is_one_element) {
            place.base = items.Data;
            place.span = stride * static_cast<std::uint32_t>(items.num());
            return place;
        }

        const int chosen = std::clamp(element, 0, items.num() - 1);
        place.base = items.Data + stride * static_cast<std::uint32_t>(chosen);
        place.span = stride;

        return place;
    }

    [[nodiscard]] inline sdk::UObject* own_streak_component() {
        if (sdk::lookup::is_live(own_streak_slot)) return own_streak_slot.object;

        if (!own_character()) return nullptr;

        const auto now = std::chrono::steady_clock::now();
        if (now < next_streak_search) return nullptr;
        next_streak_search = now + streak_search_every;

        sdk::APlayerController* controller = own_controller();
        if (!controller) return nullptr;

        sdk::UObject* found = sdk::hw2::streak_component_of({ controller, controller->PlayerState(), controller->Pawn() });
        own_streak_slot = { found, found ? found->index() : -1 };

        return found;
    }

    inline sdk::lookup::held frag_default_slot;
    inline sdk::lookup::held claymore_default_slot;
    inline sdk::lookup::held pickup_default_slot;
    inline sdk::lookup::held medkit_default_slot;

    [[nodiscard]] inline sdk::UObject* held_part(sdk::hw2::attachment_slot slot, const char* class_name) {
        sdk::AActor* part = sdk::hw2::part_in(held_weapon_of(own_character()), slot);

        return sdk::lookup::derives_from(part, class_name) ? part : nullptr;
    }

    [[nodiscard]] inline sdk::UObject* picked_vitals() {
        const sdk::APlayerState* member = lobby_member(host_setup.target);
        const sdk::APawn* pawn = member ? member->PawnPrivate() : nullptr;
        if (!pawn || sdk::hw2::kind_of(pawn) != sdk::hw2::actor_kind::character) return nullptr;

        return sdk::hw2::vitals_of(pawn);
    }

    [[nodiscard]] inline sdk::UObject* chosen_bot_controller() {
        const sdk::APlayerState* member = lobby_member(host_setup.target);
        sdk::AController* controller = member ? sdk::hw2::controller_of(member) : nullptr;

        return sdk::lookup::derives_from(controller, "BP_AI_PlayerController_C") ? controller : nullptr;
    }

    [[nodiscard]] inline board_place actor_place(const field_board& board, const char* class_name) {
        int count = 0;
        board_place place = object_place(sdk::scene::actor_of(class_name, board.element, count));
        place.count = count;

        return place;
    }

    [[nodiscard]] inline board_place component_place(const field_board& board, const char* class_name, std::uint32_t component_offset) {
        int count = 0;
        board_place place = object_place(sdk::scene::component_of(class_name, component_offset, board.element, count));
        place.count = count;

        return place;
    }

    [[nodiscard]] inline board_place place_of(const field_board& board) {
        namespace off = sdk::offsets;

        switch (board.target) {
        case board_target::match_settings: return object_place(sdk::hw2::match_component(sdk::hw2::match_part::match_settings));
        case board_target::match_state: return object_place(sdk::hw2::match_component(sdk::hw2::match_part::match_state));
        case board_target::game_mode: return object_place(sdk::hw2::game_mode());
        case board_target::lobby_instance: return object_place(sdk::hw2::lobby_instance());
        case board_target::bot_settings: return object_place(sdk::hw2::bot_settings());
        case board_target::bot_weapon_profile:
            return array_place(sdk::hw2::bot_settings(), off::hw2_bot_config::weapon_profiles, off::hw2_bot_weapon_profile::byte_size, board.element, true);
        case board_target::chosen_bot: return object_place(chosen_bot_controller());
        case board_target::streak_settings: return object_place(sdk::hw2::streak_settings());
        case board_target::streak_definitions:
            return array_place(sdk::hw2::streak_settings(), off::hw2_streak_config::killstreaks, off::hw2_streak_definition::byte_size, 0, false);
        case board_target::own_streaks: return object_place(own_streak_component());
        case board_target::own_old_streaks: return object_place(sdk::hw2::old_streaks_of(own_state()));
        case board_target::drive_by_car: return object_place(sdk::hw2::drive_by_car());
        case board_target::held_weapon: return object_place(held_weapon_of(own_character()));
        case board_target::held_weapon_data: return object_place(sdk::hw2::settings_of(held_weapon_of(own_character())));
        case board_target::held_magazine: return object_place(held_part(sdk::hw2::attachment_slot::magazine, "BP_Base_Magazine_C"));
        case board_target::held_optic: return object_place(held_part(sdk::hw2::attachment_slot::optic, "BP_Base_Optics_C"));
        case board_target::own_vitals: return object_place(sdk::hw2::vitals_of(own_character()));
        case board_target::picked_vitals: return object_place(picked_vitals());
        case board_target::own_body: return object_place(own_character());
        case board_target::own_interaction: return object_place(sdk::hw2::interaction_of(own_character()));
        case board_target::own_lethal: return object_place(sdk::hw2::lethal_of(own_character()));
        case board_target::own_loadout: return object_place(sdk::hw2::loadout_of(own_controller()));
        case board_target::frag_defaults: return object_place(sdk::lookup::class_default(frag_default_slot, "BP_FragGrenade_C"));
        case board_target::claymore_defaults: return object_place(sdk::lookup::class_default(claymore_default_slot, "BP_Claymore_C"));
        case board_target::pickup_defaults: return object_place(sdk::lookup::class_default(pickup_default_slot, "BP_PickupWeapon_C"));
        case board_target::medkit_defaults: return object_place(sdk::lookup::class_default(medkit_default_slot, "BP_Medkit_C"));
        case board_target::damage_type: {
            int count = 0;
            board_place place = object_place(damage_type_default(board.element, count));
            place.count = count;
            return place;
        }
        case board_target::picked_capture_point: return object_place(picked_of_kind(sdk::hw2::objective_kind::capture_point));
        case board_target::picked_snd_site: return object_place(picked_of_kind(sdk::hw2::objective_kind::snd_site));
        case board_target::picked_rush_site: return object_place(picked_of_kind(sdk::hw2::objective_kind::rush_site));
        case board_target::snd_bomb: return object_place(sdk::hw2::snd_bomb());
        case board_target::conquest_state: return object_place(mode_state_of("BP_Conquest_GS_C"));
        case board_target::rush_state: return object_place(mode_state_of("BP_Rush_GS_C"));
        case board_target::snd_state: return object_place(mode_state_of("BP_SearchAndDestroy_GS_C"));
        case board_target::ffa_state: return object_place(mode_state_of("BP_FreeForAll_GS_C"));
        case board_target::picked_spawn: return object_place(picked_spawn(modes_setup.spawn));
        case board_target::own_spectator: return object_place(own_spectator());
        case board_target::host_migration: return object_place(sdk::hw2::match_component(sdk::hw2::match_part::host_migration));
        case board_target::online_settings: return object_place(sdk::hw2::online_settings());
        case board_target::own_progression: return object_place(sdk::hw2::progression_of(own_controller()));
        case board_target::save_level: return object_place(live_object(save_level_slot, "BP_FPS_SaveLevelAndExp_C"));
        case board_target::save_game: return object_place(live_object(save_game_slot, "BP_FPS_SaveGame_C"));
        case board_target::save_streaks: return object_place(live_object(save_streaks_slot, "HW2KillstreakLoadoutSave"));
        case board_target::save_menu: return object_place(live_object(save_menu_slot, "HW2MenuPrefsSaveGame"));
        case board_target::cine_settings: return object_place(sdk::hw2::cine_settings());
        case board_target::replay_settings: return object_place(sdk::hw2::replay_settings());
        case board_target::voice_settings: return object_place(sdk::hw2::voice_settings());
        case board_target::voice_save: return object_place(sdk::hw2::voice_save());
        case board_target::audio_output: return object_place(sdk::hw2::audio_output_settings());
        case board_target::voice_cues: return object_place(sdk::hw2::voice_cue_settings());
        case board_target::own_voice: return object_place(sdk::hw2::voice_of(own_character()));
        case board_target::own_controller_options: return object_place(sdk::hw2::view_settings_of(own_controller()));
        case board_target::input_settings: return object_place(sdk::hw2::input_settings());
        case board_target::input_aim_gated: return object_place(aim_status.is_open ? sdk::hw2::input_settings() : nullptr);
        case board_target::player_input: return object_place(input_subsystem());
        case board_target::third_person: return object_place(sdk::hw2::third_person_settings());
        case board_target::world_settings: return object_place(sdk::scene::settings());
        case board_target::screen_post: return object_place(own_camera());
        case board_target::post_volume: return actor_place(board, "PostProcessVolume");
        case board_target::level_fog: return component_place(board, "ExponentialHeightFog", off::aexponential_height_fog::component);
        case board_target::sky_light: return component_place(board, "SkyLight", off::asky_light::light_component);
        case board_target::sun_light: return component_place(board, "DirectionalLight", off::alight::light_component);
        case board_target::sky_atmosphere: return component_place(board, "SkyAtmosphere", off::asky_atmosphere::sky_atmosphere_component);
        case board_target::volumetric_clouds: return component_place(board, "VolumetricCloud", off::avolumetric_cloud::volumetric_cloud_component);
        case board_target::local_fog: return component_place(board, "LocalFogVolume", off::alocal_fog_volume::local_fog_volume_volume);
        case board_target::wind_source: return component_place(board, "WindDirectionalSource", off::awind_source::component);
        }

        return {};
    }

    [[nodiscard]] inline std::uint32_t width_of(field_kind kind) {
        switch (kind) {
        case field_kind::flag:
        case field_kind::bit:
        case field_kind::byte: return 1;
        case field_kind::whole:
        case field_kind::single: return 4;
        case field_kind::wide: return 8;
        }

        return 8;
    }

    [[nodiscard]] inline double read_field(const void* base, const field& entry) {
        switch (entry.kind) {
        case field_kind::flag: return sdk::mem::read<bool>(base, entry.offset) ? 1.0 : 0.0;
        case field_kind::bit: return sdk::mem::read_bit(base, entry.offset, entry.bit) ? 1.0 : 0.0;
        case field_kind::byte: return static_cast<double>(sdk::mem::read<std::uint8_t>(base, entry.offset));
        case field_kind::whole: return static_cast<double>(sdk::mem::read<std::int32_t>(base, entry.offset));
        case field_kind::single: return static_cast<double>(sdk::mem::read<float>(base, entry.offset));
        case field_kind::wide: return sdk::mem::read<double>(base, entry.offset);
        }

        return 0.0;
    }

    inline bool write_field(void* base, const field& entry, double value) {
        switch (entry.kind) {
        case field_kind::flag: return sdk::mem::write<bool>(base, entry.offset, value != 0.0);
        case field_kind::bit: return sdk::mem::write_bit(base, entry.offset, entry.bit, value != 0.0);
        case field_kind::byte: return sdk::mem::write<std::uint8_t>(base, entry.offset, static_cast<std::uint8_t>(std::lround(value)));
        case field_kind::whole: return sdk::mem::write<std::int32_t>(base, entry.offset, static_cast<std::int32_t>(std::lround(value)));
        case field_kind::single: return sdk::mem::write<float>(base, entry.offset, static_cast<float>(value));
        case field_kind::wide: return sdk::mem::write<double>(base, entry.offset, value);
        }

        return false;
    }

    inline void restore_gate(void* base, const field& entry, field_state& state) {
        if (!state.is_gate_saved) return;

        if (entry.gate != no_gate) sdk::mem::write_bit(base, entry.gate, entry.gate_bit, state.gate_original);

        state.is_gate_saved = false;
    }

    inline void release_place(field_board& board) {
        const bool is_alive = board.owner && board.object_index >= 0 && sdk::objects::at(board.object_index) == board.owner;

        for (int i = 0; i < board.count; ++i) {
            field_state& state = board.state[i];
            if (state.is_saved && is_alive) write_field(const_cast<void*>(board.object), board.fields[i], state.original);
            if (is_alive) restore_gate(const_cast<void*>(board.object), board.fields[i], state);

            state.is_saved = false;
            state.is_gate_saved = false;
        }
    }

    [[nodiscard]] inline bool is_idle(const field_board& board) {
        if (board.is_watched) return false;

        for (int i = 0; i < board.count; ++i)
            if (board.state[i].is_held || board.state[i].is_saved || board.state[i].is_gate_saved) return false;

        return true;
    }

    inline void sync_board(field_board& board) {
        const board_place place = place_of(board);
        board.is_found = place.base != nullptr;
        board.element_count = place.count;

        const std::int32_t index = place.owner ? place.owner->index() : -1;
        if (place.base != board.object || place.owner != board.owner || index != board.object_index) {
            release_place(board);

            board.object = place.base;
            board.owner = place.owner;
            board.object_index = index;
        }

        if (!place.base) return;

        for (int i = 0; i < board.count; ++i) {
            const field& entry = board.fields[i];
            field_state& state = board.state[i];

            state.is_present = entry.offset + width_of(entry.kind) <= place.span
                && (entry.gate == no_gate || entry.gate < place.span);
            if (!state.is_present) continue;

            double live = read_field(place.base, entry);

            if (state.is_held) {
                if (!state.is_saved) {
                    state.original = live;
                    state.is_saved = true;
                }

                if (!state.is_gate_saved && entry.gate != no_gate) {
                    state.gate_original = sdk::mem::read_bit(place.base, entry.gate, entry.gate_bit);
                    state.is_gate_saved = true;
                }

                if (live != state.value && write_field(place.base, entry, state.value)) live = state.value;
            } else {
                if (state.is_saved) {
                    if (write_field(place.base, entry, state.original)) live = state.original;
                    state.is_saved = false;
                }

                restore_gate(place.base, entry, state);
            }

            state.live = live;
        }

        for (int i = 0; i < board.count; ++i) {
            const field& entry = board.fields[i];
            const field_state& state = board.state[i];
            if (!state.is_held || !state.is_present || entry.gate == no_gate) continue;

            sdk::mem::write_bit(place.base, entry.gate, entry.gate_bit, true);
        }
    }

}
