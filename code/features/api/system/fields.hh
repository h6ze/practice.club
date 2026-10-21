#pragma once
#include <cstdint>

namespace features {

    enum class field_kind : std::uint8_t { flag, bit, byte, whole, single, wide };

    inline constexpr std::uint32_t no_gate = 0xFFFFFFFFu;

    struct field {
        const char* label;
        std::uint32_t offset;
        field_kind kind;
        float low = 0.0f;
        float high = 1.0f;
        std::uint32_t bit = 0;

        std::uint32_t gate = no_gate;
        std::uint32_t gate_bit = 0;
    };

    struct field_state {
        bool is_held = false;
        double value = 0.0;
        double live = 0.0;
        double original = 0.0;
        bool is_saved = false;

        bool gate_original = false;
        bool is_gate_saved = false;

        bool is_present = true;
    };

    enum class board_target : std::uint8_t {
        match_settings, match_state, game_mode, lobby_instance,
        bot_settings, bot_weapon_profile, chosen_bot,
        streak_settings, streak_definitions, own_streaks, own_old_streaks, drive_by_car,
        held_weapon, held_weapon_data, held_magazine, held_optic,
        own_vitals, picked_vitals, own_body, own_interaction, own_lethal, own_loadout,
        frag_defaults, claymore_defaults, pickup_defaults, medkit_defaults, damage_type,
        picked_capture_point, picked_snd_site, picked_rush_site, snd_bomb,
        conquest_state, rush_state, snd_state, ffa_state, picked_spawn, own_spectator, host_migration,
        online_settings, own_progression, save_level, save_game, save_streaks, save_menu,
        cine_settings, replay_settings, voice_settings, voice_save, audio_output, voice_cues, own_voice,
        own_controller_options, input_settings, input_aim_gated, player_input, third_person,
        world_settings, screen_post, post_volume, level_fog, sky_light, sun_light,
        sky_atmosphere, volumetric_clouds, local_fog, wind_source,
    };

    struct field_board {
        const char* title;
        board_target target;
        const field* fields;
        int count;
        field_state* state;

        int element = 0;
        int element_count = 0;

        bool is_watched = false;

        bool is_found = false;
        const void* object = nullptr;
        const void* owner = nullptr;
        std::int32_t object_index = -1;
    };

    struct fields_domain {
        void tick();
        void release(field_board& board);
        void release_all();
    };

    inline fields_domain fields;

}
