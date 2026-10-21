#pragma once
#include <cstdint>

namespace sdk::offsets {

    inline constexpr char dump_tag[] = "5.8.3-58210709+++UE5+Release-5.8-HW2";
    inline constexpr std::uint32_t image_size = 0x0BD2F000;

    namespace global {
        inline constexpr std::uintptr_t gobjects = 0x0AFF0A00;
        inline constexpr std::uintptr_t gnames = 0x0AF229C0;
        inline constexpr std::uintptr_t gworld = 0x0B073630;
        inline constexpr std::uintptr_t append_string = 0x014E1370;
        inline constexpr std::uintptr_t process_event = 0x016B48D0;
        inline constexpr std::uint32_t process_event_index = 0x0000004A;
    }

    namespace object_array {
        inline constexpr std::uint32_t objects = 0x00;
        inline constexpr std::uint32_t num = 0x08;
        inline constexpr std::uint32_t max = 0x0C;
        inline constexpr std::uint32_t chunks = 0x10;
        inline constexpr std::uint32_t item_stride = 0x18;
        inline constexpr std::uint32_t item_object = 0x08;
        inline constexpr std::uint32_t per_chunk = 0x10000;
    }

    namespace view {
        inline constexpr std::uint32_t pov = 0x10;
        inline constexpr std::uint32_t location = 0x00;
        inline constexpr std::uint32_t rotation = 0x18;
        inline constexpr std::uint32_t fov = 0x30;
    }

    namespace params {
        namespace server_fire_bullet {
            inline constexpr std::uint32_t spawn_location = 0x0;
            inline constexpr std::uint32_t bullet_velocity = 0x18;
            inline constexpr std::uint32_t instigator = 0x30;
            inline constexpr std::uint32_t spawn_rotation = 0x38;
            inline constexpr std::uint32_t spread = 0x50;
        }
        namespace server_fire_instant {
            inline constexpr std::uint32_t trace_start = 0x0;
            inline constexpr std::uint32_t forward = 0x18;
            inline constexpr std::uint32_t instigator = 0x30;
            inline constexpr std::uint32_t spread = 0x38;
        }
        namespace add_movement_input {
            inline constexpr std::uint32_t direction = 0x0;
            inline constexpr std::uint32_t scale = 0x18;
            inline constexpr std::uint32_t is_force = 0x1C;
        }
        namespace set_actor_rotation {
            inline constexpr std::uint32_t rotation = 0x0;
            inline constexpr std::uint32_t is_teleport = 0x18;
            inline constexpr std::uint32_t return_value = 0x19;
        }
        namespace move_bullet {
            inline constexpr std::uint32_t new_location = 0x0;
            inline constexpr std::uint32_t is_blocking_hit = 0x18;
        }
        namespace line_trace_info {
            inline constexpr std::uint32_t trace_start = 0x0;
            inline constexpr std::uint32_t forward = 0x18;
        }
        namespace spawn_bullet_info {
            inline constexpr std::uint32_t spawn_location = 0x0;
            inline constexpr std::uint32_t velocity = 0x18;
            inline constexpr std::uint32_t spawn_rotation = 0x30;
        }
        namespace check_unlocks_for_level {
            inline constexpr std::uint32_t new_level = 0x0;
        }
        namespace is_weapon_unlocked {
            inline constexpr std::uint32_t unlock_level = 0x0;
            inline constexpr std::uint32_t is_unlocked = 0x4;
        }
        namespace raise_stat_to {
            inline constexpr std::uint32_t key = 0x0;
            inline constexpr std::uint32_t value = 0x10;
        }
        namespace add_stat {
            inline constexpr std::uint32_t key = 0x0;
            inline constexpr std::uint32_t amount = 0x10;
        }
        namespace set_level {
            inline constexpr std::uint32_t level = 0x0;
        }
        namespace set_experience {
            inline constexpr std::uint32_t experience = 0x0;
        }
        namespace get_stat {
            inline constexpr std::uint32_t key = 0x0;
            inline constexpr std::uint32_t value = 0x10;
        }
        namespace enumerator_name {
            inline constexpr std::uint32_t enum_object = 0x0;
            inline constexpr std::uint32_t value = 0x8;
            inline constexpr std::uint32_t return_value = 0x10;
        }
        namespace conv_int_to_string {
            inline constexpr std::uint32_t in_int = 0x0;
            inline constexpr std::uint32_t return_value = 0x8;
        }
        namespace concat_str_str {
            inline constexpr std::uint32_t a = 0x0;
            inline constexpr std::uint32_t b = 0x10;
            inline constexpr std::uint32_t return_value = 0x20;
        }
        namespace apply_skin_colors {
            inline constexpr std::uint32_t target_mesh = 0x0;
            inline constexpr std::uint32_t color_a = 0x8;
            inline constexpr std::uint32_t color_b = 0x18;
        }
        namespace socket_location {
            inline constexpr std::uint32_t socket_name = 0x0;
            inline constexpr std::uint32_t return_value = 0x8;
        }
        namespace string_to_name {
            inline constexpr std::uint32_t in_string = 0x0;
            inline constexpr std::uint32_t return_value = 0x10;
        }
        namespace killstreak_activate {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t streak = 0x8;
            inline constexpr std::uint32_t is_activated = 0x9;
        }
        namespace killstreak_activate_slot {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t slot = 0x8;
            inline constexpr std::uint32_t is_activated = 0xC;
        }
        namespace killstreak_place {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t location = 0x8;
        }
        namespace line_of_sight {
            inline constexpr std::uint32_t other = 0x0;
            inline constexpr std::uint32_t view_point = 0x8;
            inline constexpr std::uint32_t is_alternate = 0x20;
            inline constexpr std::uint32_t return_value = 0x21;
        }
        namespace set_team_a_points {
            inline constexpr std::uint32_t points = 0x0;
        }
        namespace set_team_b_points {
            inline constexpr std::uint32_t points = 0x0;
        }
        namespace add_points {
            inline constexpr std::uint32_t team = 0x0;
        }
        namespace add_rounds_won {
            inline constexpr std::uint32_t team = 0x0;
            inline constexpr std::uint32_t is_game_over = 0x4;
        }
        namespace set_winner_team {
            inline constexpr std::uint32_t winner = 0x0;
        }
        namespace set_match_state {
            inline constexpr std::uint32_t state = 0x0;
        }
        namespace set_round_state {
            inline constexpr std::uint32_t state = 0x0;
        }
        namespace end_round {
            inline constexpr std::uint32_t winner = 0x0;
        }
        namespace apply_funny_match_settings {
            inline constexpr std::uint32_t match_settings = 0x0;
        }
        namespace server_travel_to_map {
            inline constexpr std::uint32_t level = 0x0;
        }
        namespace create_new_match {
            inline constexpr std::uint32_t game_mode = 0x0;
        }
        namespace restart_player {
            inline constexpr std::uint32_t new_player = 0x0;
        }
        namespace change_name {
            inline constexpr std::uint32_t controller = 0x0;
            inline constexpr std::uint32_t new_name = 0x8;
            inline constexpr std::uint32_t is_name_change = 0x18;
        }
        namespace team_set {
            inline constexpr std::uint32_t team = 0x0;
        }
        namespace controller_set_team {
            inline constexpr std::uint32_t team = 0x0;
        }
        namespace can_join_team {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t player = 0x8;
            inline constexpr std::uint32_t team = 0x10;
            inline constexpr std::uint32_t return_value = 0x14;
        }
        namespace create_bots {
            inline constexpr std::uint32_t team_a = 0x0;
            inline constexpr std::uint32_t team_b = 0x4;
        }
        namespace create_bots_ffa {
            inline constexpr std::uint32_t count = 0x0;
        }
        namespace remove_bot {
            inline constexpr std::uint32_t player_state = 0x0;
        }
        namespace respawn_bot {
            inline constexpr std::uint32_t controller = 0x0;
        }
        namespace remove_one_bot {
            inline constexpr std::uint32_t team = 0x0;
        }
        namespace set_player_score {
            inline constexpr std::uint32_t score = 0x0;
        }
        namespace set_kills {
            inline constexpr std::uint32_t kills = 0x0;
        }
        namespace set_deaths {
            inline constexpr std::uint32_t deaths = 0x0;
        }
        namespace set_assists {
            inline constexpr std::uint32_t assists = 0x0;
        }
        namespace restore_killstreaks {
            inline constexpr std::uint32_t mask = 0x0;
        }
        namespace set_equipped_streaks {
            inline constexpr std::uint32_t mask = 0x0;
        }
        namespace use_streak {
            inline constexpr std::uint32_t streak = 0x0;
        }
        namespace spawn_cluster_strike {
            inline constexpr std::uint32_t location = 0x0;
        }
        namespace set_kill_streak {
            inline constexpr std::uint32_t count = 0x0;
        }
        namespace activate_uav {
            inline constexpr std::uint32_t team = 0x0;
            inline constexpr std::uint32_t instigator = 0x8;
            inline constexpr std::uint32_t seconds = 0x10;
        }
        namespace bot_on_damaged {
            inline constexpr std::uint32_t controller = 0x0;
            inline constexpr std::uint32_t shooter = 0x8;
        }
        namespace pickup_weapon {
            inline constexpr std::uint32_t weapon_class = 0x0;
            inline constexpr std::uint32_t ammo = 0x8;
            inline constexpr std::uint32_t attachments = 0x10;
            inline constexpr std::uint32_t skin = 0x48;
            inline constexpr std::uint32_t is_full_mag = 0x50;
        }
        namespace heal_player {
            inline constexpr std::uint32_t amount = 0x0;
            inline constexpr std::uint32_t instigator = 0x8;
        }
        namespace force_change_weapon {
            inline constexpr std::uint32_t is_primary = 0x0;
            inline constexpr std::uint32_t is_quick = 0x1;
        }
        namespace set_firing_mode {
            inline constexpr std::uint32_t mode = 0x0;
        }
        namespace set_mag_ammo {
            inline constexpr std::uint32_t ammo = 0x0;
        }
        namespace set_stock_state {
            inline constexpr std::uint32_t is_no_stock = 0x0;
        }
        namespace loadout_primary {
            inline constexpr std::uint32_t weapon_class = 0x0;
        }
        namespace loadout_secondary {
            inline constexpr std::uint32_t weapon_class = 0x0;
        }
        namespace loadout_operator {
            inline constexpr std::uint32_t team = 0x0;
            inline constexpr std::uint32_t operator_info = 0x8;
        }
        namespace set_perk_type {
            inline constexpr std::uint32_t perk = 0x0;
        }
        namespace set_field_upgrade {
            inline constexpr std::uint32_t upgrade = 0x0;
        }
        namespace set_lethal_class {
            inline constexpr std::uint32_t lethal_class = 0x0;
        }
        namespace set_attachments {
            inline constexpr std::uint32_t attachments = 0x0;
        }
        namespace heal_actor {
            inline constexpr std::uint32_t amount = 0x0;
        }
        namespace set_max_health {
            inline constexpr std::uint32_t max_health = 0x0;
        }
        namespace damage_actor {
            inline constexpr std::uint32_t amount = 0x0;
        }
        namespace claymore_explode {
            inline constexpr std::uint32_t instigator = 0x0;
        }
        namespace capture_point {
            inline constexpr std::uint32_t state = 0x0;
        }
        namespace give_objective_points {
            inline constexpr std::uint32_t is_team = 0x0;
            inline constexpr std::uint32_t score = 0x8;
            inline constexpr std::uint32_t reason = 0x10;
        }
        namespace set_point_holder {
            inline constexpr std::uint32_t holder_team = 0x0;
            inline constexpr std::uint32_t point = 0x1;
        }
        namespace snd_activate_bomb {
            inline constexpr std::uint32_t pawn = 0x0;
        }
        namespace snd_deactivate_bomb {
            inline constexpr std::uint32_t pawn = 0x0;
        }
        namespace rush_activate_bomb {
            inline constexpr std::uint32_t pawn = 0x0;
        }
        namespace rush_deactivate_bomb {
            inline constexpr std::uint32_t pawn = 0x0;
        }
        namespace attach_bomb {
            inline constexpr std::uint32_t character = 0x0;
        }
        namespace rush_phase_spawns {
            inline constexpr std::uint32_t phase = 0x0;
            inline constexpr std::uint32_t team = 0x4;
        }
        namespace spawn_at_point {
            inline constexpr std::uint32_t spawn = 0x0;
            inline constexpr std::uint32_t controller = 0x8;
            inline constexpr std::uint32_t team = 0x10;
        }
        namespace spawn_with_team {
            inline constexpr std::uint32_t controller = 0x0;
        }
        namespace set_spawn_active {
            inline constexpr std::uint32_t is_active = 0x0;
        }
        namespace spawn_player_pawn {
            inline constexpr std::uint32_t controller = 0x0;
            inline constexpr std::uint32_t spawn_point = 0x8;
            inline constexpr std::uint32_t pawn_class = 0x10;
        }
        namespace choose_spawn {
            inline constexpr std::uint32_t spawn_system = 0x0;
            inline constexpr std::uint32_t team = 0x8;
            inline constexpr std::uint32_t is_ffa = 0xC;
            inline constexpr std::uint32_t for_player = 0x10;
            inline constexpr std::uint32_t return_value = 0x18;
        }
        namespace simulate_resume {
            inline constexpr std::uint32_t clock = 0x0;
            inline constexpr std::uint32_t team_a = 0x4;
            inline constexpr std::uint32_t team_b = 0x8;
        }
        namespace controller_spawn {
            inline constexpr std::uint32_t is_force = 0x0;
        }
        namespace give_exp {
            inline constexpr std::uint32_t amount = 0x0;
        }
        namespace add_score {
            inline constexpr std::uint32_t score = 0x0;
            inline constexpr std::uint32_t reason = 0x8;
        }
        namespace add_experience {
            inline constexpr std::uint32_t amount = 0x0;
        }
        namespace missions_game_won {
            inline constexpr std::uint32_t mode = 0x0;
        }
        namespace missions_player_killed {
            inline constexpr std::uint32_t weapon_type = 0x0;
        }
        namespace notify_match_end {
            inline constexpr std::uint32_t is_won = 0x0;
        }
        namespace record_kill {
            inline constexpr std::uint32_t is_headshot = 0x0;
        }
        namespace notify_local_kill {
            inline constexpr std::uint32_t kind = 0x0;
        }
        namespace bump_weapon_stat {
            inline constexpr std::uint32_t suffix = 0x0;
        }
        namespace cloud_level {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace cloud_total_xp {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace cloud_pending {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace cloud_authenticated {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace string_to_text {
            inline constexpr std::uint32_t in_string = 0x0;
            inline constexpr std::uint32_t return_value = 0x10;
        }
        namespace send_message_all {
            inline constexpr std::uint32_t message = 0x0;
            inline constexpr std::uint32_t is_reliable = 0x10;
        }
        namespace send_message_team {
            inline constexpr std::uint32_t team_0 = 0x0;
            inline constexpr std::uint32_t team_1 = 0x10;
            inline constexpr std::uint32_t is_reliable = 0x20;
        }
        namespace show_objective_message {
            inline constexpr std::uint32_t text = 0x0;
        }
        namespace kick_player {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t controller = 0x8;
            inline constexpr std::uint32_t reason = 0x10;
            inline constexpr std::uint32_t return_value = 0x20;
        }
        namespace ban_player {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t controller = 0x8;
            inline constexpr std::uint32_t reason = 0x10;
            inline constexpr std::uint32_t return_value = 0x20;
        }
        namespace update_session {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t extra_settings = 0x8;
            inline constexpr std::uint32_t public_connections = 0x18;
            inline constexpr std::uint32_t private_connections = 0x1C;
            inline constexpr std::uint32_t is_lan = 0x20;
            inline constexpr std::uint32_t is_allow_invites = 0x21;
            inline constexpr std::uint32_t is_join_in_progress = 0x22;
            inline constexpr std::uint32_t is_refresh = 0x23;
            inline constexpr std::uint32_t is_dedicated = 0x24;
            inline constexpr std::uint32_t is_advertise = 0x25;
            inline constexpr std::uint32_t is_join_presence = 0x26;
            inline constexpr std::uint32_t is_join_friends_only = 0x27;
            inline constexpr std::uint32_t return_value = 0x28;
        }
        namespace browser_open {
            inline constexpr std::uint32_t controller = 0x0;
            inline constexpr std::uint32_t return_value = 0x8;
        }
        namespace browser_refresh {
            inline constexpr std::uint32_t is_quiet = 0x0;
        }
        namespace friends_get {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t return_value = 0x8;
        }
        namespace join_friend {
            inline constexpr std::uint32_t index = 0x0;
            inline constexpr std::uint32_t return_value = 0x4;
        }
        namespace invite_friend {
            inline constexpr std::uint32_t index = 0x0;
            inline constexpr std::uint32_t return_value = 0x4;
        }
        namespace invite_get {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t return_value = 0x8;
        }
        namespace has_pending_invite {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace pending_inviter {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace leave_match {
            inline constexpr std::uint32_t is_to_desktop = 0x0;
        }
        namespace migration_phase {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace migration_successor {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace announce_leaving {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace report_json {
            inline constexpr std::uint32_t match_id = 0x0;
            inline constexpr std::uint32_t return_value = 0x10;
        }
        namespace reset_voice {
            inline constexpr std::uint32_t context = 0x0;
        }
        namespace set_aim_assist {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t is_enabled = 0x8;
        }
        namespace set_input_fov {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t fov = 0x8;
        }
        namespace set_vibration {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t is_enabled = 0x8;
        }
        namespace reset_controller {
            inline constexpr std::uint32_t context = 0x0;
        }
        namespace try_voice {
            inline constexpr std::uint32_t event_id = 0x0;
        }
        namespace cine_god_mode {
            inline constexpr std::uint32_t is_enabled = 0x0;
        }
        namespace cine_is_god_mode {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace cine_is_recording {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace cine_seconds {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace cine_status {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace replay_record {
            inline constexpr std::uint32_t name = 0x0;
            inline constexpr std::uint32_t return_value = 0x10;
        }
        namespace replay_play {
            inline constexpr std::uint32_t name = 0x0;
            inline constexpr std::uint32_t start = 0x10;
            inline constexpr std::uint32_t return_value = 0x14;
        }
        namespace replay_highlight {
            inline constexpr std::uint32_t label = 0x0;
            inline constexpr std::uint32_t return_value = 0x10;
        }
        namespace replay_jump {
            inline constexpr std::uint32_t direction = 0x0;
            inline constexpr std::uint32_t return_value = 0x4;
        }
        namespace replay_follow {
            inline constexpr std::uint32_t name = 0x0;
            inline constexpr std::uint32_t return_value = 0x10;
        }
        namespace replay_list {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace replay_status {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace replay_is_recording {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace replay_is_playing {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace replay_seek_to {
            inline constexpr std::uint32_t seconds = 0x0;
        }
        namespace replay_seek {
            inline constexpr std::uint32_t delta = 0x0;
        }
        namespace replay_speed {
            inline constexpr std::uint32_t speed = 0x0;
        }
        namespace set_visibility {
            inline constexpr std::uint32_t is_visible = 0x0;
            inline constexpr std::uint32_t is_propagated = 0x1;
        }
        namespace set_light_intensity {
            inline constexpr std::uint32_t intensity = 0x0;
        }
        namespace set_cast_shadows {
            inline constexpr std::uint32_t is_casting = 0x0;
        }
        namespace set_global_time_dilation {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t time_dilation = 0x8;
        }
        namespace get_global_time_dilation {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t return_value = 0x8;
        }
        namespace console_command {
            inline constexpr std::uint32_t context = 0x0;
            inline constexpr std::uint32_t command = 0x8;
            inline constexpr std::uint32_t specific_player = 0x18;
        }
        namespace cvar_float {
            inline constexpr std::uint32_t variable_name = 0x0;
            inline constexpr std::uint32_t return_value = 0x10;
        }
        namespace cvar_int {
            inline constexpr std::uint32_t variable_name = 0x0;
            inline constexpr std::uint32_t return_value = 0x10;
        }
        namespace cvar_bool {
            inline constexpr std::uint32_t variable_name = 0x0;
            inline constexpr std::uint32_t return_value = 0x10;
        }
        namespace get_user_settings {
            inline constexpr std::uint32_t return_value = 0x0;
        }
        namespace user_quality {
            inline constexpr std::uint32_t value = 0x0;
        }
        namespace user_resolution_scale {
            inline constexpr std::uint32_t scale = 0x0;
        }
        namespace user_frame_limit {
            inline constexpr std::uint32_t limit = 0x0;
        }
        namespace user_vsync {
            inline constexpr std::uint32_t is_enabled = 0x0;
        }
        namespace user_apply {
            inline constexpr std::uint32_t is_command_line_checked = 0x0;
        }
        namespace enable_path_tracing {
            inline constexpr std::uint32_t is_enabled = 0x0;
        }
        namespace psos_remaining {
            inline constexpr std::uint32_t return_value = 0x0;
        }
    }

    namespace uobject {
        inline constexpr std::uint32_t flags = 0x8;
        inline constexpr std::uint32_t index = 0xC;
        inline constexpr std::uint32_t klass = 0x10;
        inline constexpr std::uint32_t name = 0x18;
        inline constexpr std::uint32_t outer = 0x20;
    }

    namespace ufunction {
        inline constexpr std::uint32_t exec_function = 0xD8;
    }

    namespace ufield {
        inline constexpr std::uint32_t next = 0x28;
    }

    namespace ustruct {
        inline constexpr std::uint32_t super = 0x40;
        inline constexpr std::uint32_t children = 0x48;
        inline constexpr std::uint32_t size = 0x58;
    }

    namespace uclass {
        inline constexpr std::uint32_t cast_flags = 0xE0;
        inline constexpr std::uint32_t default_object = 0x118;
    }

    namespace uworld {
        inline constexpr std::uint32_t persistent_level = 0x30;
        inline constexpr std::uint32_t net_driver = 0x38;
        inline constexpr std::uint32_t demo_net_driver = 0x140;
        inline constexpr std::uint32_t authority_game_mode = 0x1A8;
        inline constexpr std::uint32_t game_state = 0x1B0;
        inline constexpr std::uint32_t owning_game_instance = 0x228;
    }

    namespace ugame_instance {
        inline constexpr std::uint32_t local_players = 0x38;
    }

    namespace uplayer {
        inline constexpr std::uint32_t player_controller = 0x30;
    }

    namespace acontroller {
        inline constexpr std::uint32_t player_state = 0x2B0;
        inline constexpr std::uint32_t state_name = 0x2E0;
        inline constexpr std::uint32_t pawn = 0x2E8;
        inline constexpr std::uint32_t control_rotation = 0x320;
    }

    namespace apawn {
        inline constexpr std::uint32_t player_state = 0x2C8;
        inline constexpr std::uint32_t controller = 0x2D8;
        inline constexpr std::uint32_t use_controller_yaw = 0x2B0;
        inline constexpr std::uint32_t use_controller_yaw_bit = 0x1;
    }

    namespace unet_driver {
        inline constexpr std::uint32_t server_connection = 0x100;
        inline constexpr std::uint32_t client_connections = 0x108;
        inline constexpr std::uint32_t net_driver_name = 0x218;
    }

    namespace agame_state {
        inline constexpr std::uint32_t player_array = 0x2C0;
    }

    namespace aactor {
        inline constexpr std::uint32_t root_component = 0x1B8;
        inline constexpr std::uint32_t owner = 0x158;
        inline constexpr std::uint32_t instigator = 0x1A0;
    }

    namespace ulevel {
        inline constexpr std::uint32_t actors = 0xA0;
        inline constexpr std::uint32_t world_settings = 0x2B8;
    }

    namespace uprojectile_movement {
        inline constexpr std::uint32_t velocity = 0xD8;
        inline constexpr std::uint32_t gravity_scale = 0x158;
        inline constexpr std::uint32_t bounciness = 0x160;
    }

    namespace uscene_component {
        inline constexpr std::uint32_t relative_location = 0x148;
        inline constexpr std::uint32_t relative_rotation = 0x160;
        inline constexpr std::uint32_t visible = 0x1A8;
        inline constexpr std::uint32_t visible_bit = 0x5;
    }

    namespace acharacter {
        inline constexpr std::uint32_t mesh = 0x328;
        inline constexpr std::uint32_t character_movement = 0x330;
        inline constexpr std::uint32_t jump_max_count = 0x484;
    }

    namespace ucharacter_movement {
        inline constexpr std::uint32_t gravity_scale = 0x1A8;
        inline constexpr std::uint32_t max_step_height = 0x1AC;
        inline constexpr std::uint32_t jump_z_velocity = 0x1B0;
        inline constexpr std::uint32_t walkable_floor_angle = 0x1D4;
        inline constexpr std::uint32_t walkable_floor_z = 0x1D8;
        inline constexpr std::uint32_t movement_mode = 0x241;
        inline constexpr std::uint32_t ground_friction = 0x244;
        inline constexpr std::uint32_t max_walk_speed = 0x288;
        inline constexpr std::uint32_t max_walk_speed_crouched = 0x28C;
        inline constexpr std::uint32_t max_fly_speed = 0x294;
        inline constexpr std::uint32_t max_acceleration = 0x29C;
        inline constexpr std::uint32_t braking_deceleration_walking = 0x2B0;
        inline constexpr std::uint32_t air_control = 0x2C0;
        inline constexpr std::uint32_t default_land_movement_mode = 0x558;
        inline constexpr std::uint32_t walk_off_ledges = 0x2F9;
        inline constexpr std::uint32_t walk_off_ledges_bit = 0x6;
        inline constexpr std::uint32_t walk_off_ledges_crouching = 0x2F9;
        inline constexpr std::uint32_t walk_off_ledges_crouching_bit = 0x7;
        inline constexpr std::uint32_t ignore_correction = 0x579;
        inline constexpr std::uint32_t ignore_correction_bit = 0x1;
        inline constexpr std::uint32_t orient_to_movement = 0x2F8;
        inline constexpr std::uint32_t orient_to_movement_bit = 0x4;
        inline constexpr std::uint32_t cheat_flying = 0x579;
        inline constexpr std::uint32_t cheat_flying_bit = 0x5;
    }

    namespace aplayer_state {
        inline constexpr std::uint32_t pawn_private = 0x320;
        inline constexpr std::uint32_t player_name = 0x340;
        inline constexpr std::uint32_t is_bot = 0x2B2;
        inline constexpr std::uint32_t is_bot_bit = 0x3;
    }

    namespace aplayer_controller {
        inline constexpr std::uint32_t camera_manager = 0x360;
    }

    namespace acamera_manager {
        inline constexpr std::uint32_t camera_cache = 0x15D0;
        inline constexpr std::uint32_t default_fov = 0x2C0;
    }

    namespace hw2_player_input {
        inline constexpr std::uint32_t sensitivity = 0x30;
        inline constexpr std::uint32_t ads_sensitivity = 0x34;
        inline constexpr std::uint32_t scope_sensitivity = 0x38;
        inline constexpr std::uint32_t field_of_view = 0x40;
    }

    namespace ucamera_component {
        inline constexpr std::uint32_t field_of_view = 0x250;
        inline constexpr std::uint32_t first_person_fov = 0x254;
        inline constexpr std::uint32_t post_process_blend = 0x300;
        inline constexpr std::uint32_t post_process_settings = 0x330;
        inline constexpr std::uint32_t enable_first_person_fov = 0x292;
        inline constexpr std::uint32_t enable_first_person_fov_bit = 0x2;
        inline constexpr std::uint32_t use_pawn_control_rotation = 0x292;
        inline constexpr std::uint32_t use_pawn_control_rotation_bit = 0x1;
    }

    namespace uspring_arm {
        inline constexpr std::uint32_t target_arm_length = 0x250;
        inline constexpr std::uint32_t socket_offset = 0x258;
        inline constexpr std::uint32_t target_offset = 0x270;
        inline constexpr std::uint32_t do_collision_test = 0x290;
        inline constexpr std::uint32_t do_collision_test_bit = 0x0;
        inline constexpr std::uint32_t use_pawn_control_rotation = 0x290;
        inline constexpr std::uint32_t use_pawn_control_rotation_bit = 0x1;
        inline constexpr std::uint32_t inherit_yaw = 0x290;
        inline constexpr std::uint32_t inherit_yaw_bit = 0x3;
    }

    namespace hw2_player_state {
        inline constexpr std::uint32_t state_info = 0x378;
        inline constexpr std::uint32_t team_component = 0x380;
        inline constexpr std::uint32_t old_streaks = 0x370;
        inline constexpr std::uint32_t missions = 0x368;
    }

    namespace hw2_state_info {
        inline constexpr std::uint32_t kills = 0xC8;
        inline constexpr std::uint32_t deaths = 0xD0;
        inline constexpr std::uint32_t level = 0x124;
        inline constexpr std::uint32_t experience = 0x120;
        inline constexpr std::uint32_t experience_to_level = 0x128;
        inline constexpr std::uint32_t max_level = 0x154;
    }

    namespace hw2_controller {
        inline constexpr std::uint32_t progression_component = 0x750;
        inline constexpr std::uint32_t loadout_component = 0x780;
        inline constexpr std::uint32_t controller_settings = 0x778;
        inline constexpr std::uint32_t cloud_sync = 0x748;
    }

    namespace hw2_controller_settings {
        inline constexpr std::uint32_t field_of_view = 0x208;
        inline constexpr std::uint32_t use_tpp = 0xC8;
    }

    namespace hw2_pawn_info {
        inline constexpr std::uint32_t leaning = 0x150;
    }

    namespace hw2_progression {
        inline constexpr std::uint32_t stats = 0xC8;
        inline constexpr std::uint32_t pending_unlocks = 0x190;
        inline constexpr std::uint32_t is_loaded = 0x1A0;
    }

    namespace hw2_team {
        inline constexpr std::uint32_t team = 0xC8;
    }

    namespace hw2_character {
        inline constexpr std::uint32_t health_component = 0x6C0;
        inline constexpr std::uint32_t inventory = 0x698;
        inline constexpr std::uint32_t is_fall_damage = 0x7E4;
        inline constexpr std::uint32_t can_run = 0x710;
        inline constexpr std::uint32_t wants_to_run = 0x729;
        inline constexpr std::uint32_t can_tactical_sprint = 0x940;
        inline constexpr std::uint32_t ads_speed_extra = 0x978;
        inline constexpr std::uint32_t pawn_info = 0x6A0;
        inline constexpr std::uint32_t camera = 0x6B0;
        inline constexpr std::uint32_t spring_arm = 0x6B8;
        inline constexpr std::uint32_t pitch_acum = 0x700;
        inline constexpr std::uint32_t yaw_acum = 0x708;
        inline constexpr std::uint32_t default_fov = 0x718;
        inline constexpr std::uint32_t current_fov = 0x720;
        inline constexpr std::uint32_t target_fov = 0x770;
        inline constexpr std::uint32_t target_spread = 0x778;
        inline constexpr std::uint32_t saturation = 0x788;
        inline constexpr std::uint32_t tpp_arm_length = 0x7A0;
        inline constexpr std::uint32_t hold_breath_alpha = 0x800;
        inline constexpr std::uint32_t can_hold_breath = 0x820;
        inline constexpr std::uint32_t breathing_strength = 0x840;
        inline constexpr std::uint32_t is_breathing = 0x848;
        inline constexpr std::uint32_t breathing_yaw = 0x850;
        inline constexpr std::uint32_t breathing_pitch = 0x858;
        inline constexpr std::uint32_t camera_leaning = 0x918;
        inline constexpr std::uint32_t run_camera_shake = 0x948;
        inline constexpr std::uint32_t interact_system = 0x690;
        inline constexpr std::uint32_t melee_range = 0x740;
        inline constexpr std::uint32_t can_melee = 0x748;
        inline constexpr std::uint32_t ability_cooldown = 0x790;
        inline constexpr std::uint32_t can_use_skill = 0x798;
        inline constexpr std::uint32_t can_shoot = 0x6F8;
        inline constexpr std::uint32_t wants_to_fire = 0x860;
        inline constexpr std::uint32_t fire_enabled = 0x862;
        inline constexpr std::uint32_t field_upgrade = 0x958;
        inline constexpr std::uint32_t generic_voice = 0x678;
    }

    namespace hw2_inventory {
        inline constexpr std::uint32_t primary = 0xC8;
        inline constexpr std::uint32_t secondary = 0xD0;
        inline constexpr std::uint32_t current = 0xE8;
    }

    namespace hw2_weapon {
        inline constexpr std::uint32_t ammo_per_mag = 0x2D0;
        inline constexpr std::uint32_t current_ammo = 0x2D4;
        inline constexpr std::uint32_t settings = 0x300;
        inline constexpr std::uint32_t mesh_fpp = 0x2B8;
        inline constexpr std::uint32_t mesh_tpp = 0x2C0;
        inline constexpr std::uint32_t bot_damage = 0x318;
        inline constexpr std::uint32_t skin_color_a = 0x370;
        inline constexpr std::uint32_t skin_color_b = 0x380;
        inline constexpr std::uint32_t is_needs_pump = 0x2F0;
        inline constexpr std::uint32_t is_bolt_cycling = 0x314;
    }

    namespace hw2_weapon_settings {
        inline constexpr std::uint32_t damage = 0x28;
        inline constexpr std::uint32_t fire_rate = 0x30;
        inline constexpr std::uint32_t burst_fire_rate = 0x90;
        inline constexpr std::uint32_t range = 0x38;
        inline constexpr std::uint32_t ammo_per_mag = 0x40;
        inline constexpr std::uint32_t is_hit_scan = 0x44;
        inline constexpr std::uint32_t is_shotgun = 0x45;
        inline constexpr std::uint32_t projectiles_per_shot = 0x48;
        inline constexpr std::uint32_t headshot = 0x88;
        inline constexpr std::uint32_t is_client_hit_reg = 0xB0;
        inline constexpr std::uint32_t vertical_recoil_min = 0xD0;
        inline constexpr std::uint32_t vertical_recoil_max = 0xD8;
        inline constexpr std::uint32_t horizontal_recoil_min = 0xE0;
        inline constexpr std::uint32_t horizontal_recoil_max = 0xE8;
        inline constexpr std::uint32_t bullet_velocity = 0xF8;
        inline constexpr std::uint32_t falloff_start = 0x180;
        inline constexpr std::uint32_t falloff_end = 0x188;
        inline constexpr std::uint32_t falloff_min = 0x190;
        inline constexpr std::uint32_t is_pump_action = 0x138;
    }

    namespace hw2_guard_settings {
        inline constexpr std::uint32_t is_enabled = 0x38;
        inline constexpr std::uint32_t is_enforce = 0x39;
        inline constexpr std::uint32_t is_kick = 0x3A;
        inline constexpr std::uint32_t is_check_shots = 0x5C;
        inline constexpr std::uint32_t is_check_sight = 0x6C;
        inline constexpr std::uint32_t is_check_movement = 0xC8;
        inline constexpr std::uint32_t max_trace_offset = 0x60;
        inline constexpr std::uint32_t hit_leeway = 0x64;
        inline constexpr std::uint32_t head_zone = 0x68;
        inline constexpr std::uint32_t sight_leeway = 0x70;
        inline constexpr std::uint32_t aim_refuse = 0x74;
        inline constexpr std::uint32_t aim_score = 0x78;
        inline constexpr std::uint32_t aim_suspect = 0x7C;
        inline constexpr std::uint32_t aim_recheck = 0x80;
        inline constexpr std::uint32_t snap_degrees = 0x84;
        inline constexpr std::uint32_t snap_window = 0x88;
        inline constexpr std::uint32_t hits_per_pellet = 0x8C;
        inline constexpr std::uint32_t fire_rate_tolerance = 0x90;
        inline constexpr std::uint32_t burst_shots = 0x94;
        inline constexpr std::uint32_t burst_seconds = 0x98;
        inline constexpr std::uint32_t melee_leeway = 0x9C;
        inline constexpr std::uint32_t melee_interval = 0xA0;
        inline constexpr std::uint32_t max_rewind = 0x54;
        inline constexpr std::uint32_t rewind_slack = 0x58;
        inline constexpr std::uint32_t warn_score = 0x3C;
        inline constexpr std::uint32_t kick_score = 0x40;
        inline constexpr std::uint32_t score_decay = 0x44;
        inline constexpr std::uint32_t violation_gap = 0x48;
        inline constexpr std::uint32_t kick_delay = 0x4C;
    }

    namespace hw2_bullet {
        inline constexpr std::uint32_t velocity = 0x2B8;
        inline constexpr std::uint32_t z_velocity = 0x2E8;
        inline constexpr std::uint32_t start_location = 0x2D0;
    }

    namespace hw2_throwable {
        inline constexpr std::uint32_t frag_movement = 0x2C8;
        inline constexpr std::uint32_t medkit_movement = 0x2B0;
        inline constexpr std::uint32_t ammo_box_movement = 0x2B0;
        inline constexpr std::uint32_t explosive_box_movement = 0x2B0;
    }

    namespace hw2_funny_settings {
        inline constexpr std::uint32_t is_funny_mode = 0x38;
        inline constexpr std::uint32_t is_esp = 0x39;
        inline constexpr std::uint32_t is_esp_overlay = 0x3A;
        inline constexpr std::uint32_t esp_color = 0x3C;
        inline constexpr std::uint32_t esp_radius = 0x4C;
        inline constexpr std::uint32_t esp_height = 0x50;
        inline constexpr std::uint32_t esp_distance = 0x54;
        inline constexpr std::uint32_t team_size = 0x58;
        inline constexpr std::uint32_t max_players = 0x5C;
    }

    namespace hw2_bot_settings {
        inline constexpr std::uint32_t tiers = 0x38;
        inline constexpr std::uint32_t aim_interp_speed = 0x48;
        inline constexpr std::uint32_t aim_error_interval = 0x4C;
        inline constexpr std::uint32_t aim_target_z_offset = 0x50;
        inline constexpr std::uint32_t is_perceived_aim = 0x54;
        inline constexpr std::uint32_t is_movement_spread = 0x55;
        inline constexpr std::uint32_t hearing_radius = 0xB8;
        inline constexpr std::uint32_t memory_seconds = 0x98;
    }

    namespace hw2_bot_tier {
        inline constexpr std::uint32_t aim_turn_rate = 0x10;
        inline constexpr std::uint32_t aim_reaction_delay = 0x14;
        inline constexpr std::uint32_t aim_error_initial = 0x18;
        inline constexpr std::uint32_t aim_error_settled = 0x1C;
        inline constexpr std::uint32_t aim_settle_time = 0x20;
        inline constexpr std::uint32_t aim_fire_angle = 0x24;
        inline constexpr std::uint32_t burst_duration = 0x28;
        inline constexpr std::uint32_t burst_rest = 0x2C;
        inline constexpr std::uint32_t aim_latency = 0x30;
        inline constexpr std::uint32_t aim_predict_skill = 0x34;
        inline constexpr std::uint32_t reaction_time = 0x38;
        inline constexpr std::uint32_t spread_multiplier = 0x3C;
        inline constexpr std::uint32_t moving_spread_scale = 0x40;
        inline constexpr std::uint32_t max_bots_per_target = 0x44;
        inline constexpr std::uint32_t engage_range = 0x48;
        inline constexpr std::uint32_t max_fire_range = 0x4C;
        inline constexpr std::uint32_t detect_time = 0x50;
        inline constexpr std::uint32_t flinch_spread = 0x54;
        inline constexpr std::uint32_t pursuit_scale = 0x58;
    }

    namespace hw2_health {
        inline constexpr std::uint32_t health = 0xC8;
        inline constexpr std::uint32_t max_health = 0xD0;
        inline constexpr std::uint32_t is_dead = 0xF8;
    }

    namespace hw2_game_state {
        inline constexpr std::uint32_t host_migration = 0x328;
        inline constexpr std::uint32_t match_report = 0x330;
        inline constexpr std::uint32_t match_settings = 0x338;
        inline constexpr std::uint32_t bot_manager = 0x340;
        inline constexpr std::uint32_t match_state_system = 0x348;
        inline constexpr std::uint32_t spawn_system = 0x350;
        inline constexpr std::uint32_t objectives = 0x360;
        inline constexpr std::uint32_t bots_to_remove = 0x438;
    }

    namespace hw2_match_state {
        inline constexpr std::uint32_t match_state = 0xC8;
        inline constexpr std::uint32_t round_state = 0xC9;
        inline constexpr std::uint32_t time_left_to_start = 0x118;
        inline constexpr std::uint32_t winner_team = 0x120;
        inline constexpr std::uint32_t team_a_points = 0x138;
        inline constexpr std::uint32_t team_b_points = 0x13C;
        inline constexpr std::uint32_t rounds_won_a = 0x148;
        inline constexpr std::uint32_t rounds_won_b = 0x14C;
        inline constexpr std::uint32_t match_time = 0x178;
        inline constexpr std::uint32_t pre_match_time = 0x17C;
        inline constexpr std::uint32_t post_match_time = 0x198;
    }

    namespace hw2_match_settings {
        inline constexpr std::uint32_t allow_respawn = 0xC0;
        inline constexpr std::uint32_t allow_friendly_fire = 0xC1;
        inline constexpr std::uint32_t bots_team_a = 0xC4;
        inline constexpr std::uint32_t bots_team_b = 0xC8;
        inline constexpr std::uint32_t ai_difficulty = 0xCC;
        inline constexpr std::uint32_t friendly_fire_multiplier = 0xD0;
        inline constexpr std::uint32_t allow_bots = 0xD8;
        inline constexpr std::uint32_t points_to_win = 0xDC;
        inline constexpr std::uint32_t rounds_to_win = 0xE0;
        inline constexpr std::uint32_t allow_change_team = 0xE4;
        inline constexpr std::uint32_t pre_match_time = 0xE8;
        inline constexpr std::uint32_t post_round_time = 0xF0;
        inline constexpr std::uint32_t round_time_limit = 0xF8;
        inline constexpr std::uint32_t game_mode = 0x100;
        inline constexpr std::uint32_t match_with_time_limit = 0x102;
        inline constexpr std::uint32_t post_match_time = 0x108;
        inline constexpr std::uint32_t max_players = 0x110;
    }

    namespace hw2_game_instance {
        inline constexpr std::uint32_t max_players = 0x1D8;
        inline constexpr std::uint32_t allow_bots = 0x1DC;
        inline constexpr std::uint32_t allow_friendly_fire = 0x1DD;
        inline constexpr std::uint32_t team_a_bots = 0x1E0;
        inline constexpr std::uint32_t team_b_bots = 0x1E4;
        inline constexpr std::uint32_t points_to_win = 0x1E8;
        inline constexpr std::uint32_t ai_difficulty = 0x1EC;
        inline constexpr std::uint32_t round_time_limit = 0x1F0;
        inline constexpr std::uint32_t use_custom_settings = 0x1F8;
        inline constexpr std::uint32_t apply_mode_defaults = 0x1F9;
        inline constexpr std::uint32_t rounds_to_win = 0x1FC;
    }

    namespace agame_mode {
        inline constexpr std::uint32_t min_respawn_delay = 0x358;
        inline constexpr std::uint32_t start_as_spectators = 0x328;
        inline constexpr std::uint32_t start_as_spectators_bit = 0x1;
        inline constexpr std::uint32_t pauseable = 0x328;
        inline constexpr std::uint32_t pauseable_bit = 0x2;
        inline constexpr std::uint32_t delayed_start = 0x348;
        inline constexpr std::uint32_t delayed_start_bit = 0x0;
    }

    namespace hw2_reserve_ammo {
        inline constexpr std::uint32_t quantity = 0x4;
        inline constexpr std::uint32_t max_quantity = 0x8;
    }

    namespace hw2_lethal_ammo {
        inline constexpr std::uint32_t quantity = 0x4;
        inline constexpr std::uint32_t max_quantity = 0x8;
    }

    namespace hw2_attachment_set {
        inline constexpr std::uint32_t optic = 0x0;
        inline constexpr std::uint32_t muzzle = 0x8;
        inline constexpr std::uint32_t stock = 0x10;
        inline constexpr std::uint32_t magazine = 0x18;
        inline constexpr std::uint32_t accessory = 0x20;
        inline constexpr std::uint32_t underbarrel = 0x28;
        inline constexpr std::uint32_t canted_sight = 0x30;
    }

    namespace hw2_mission_entry {
        inline constexpr std::uint32_t info = 0x0;
        inline constexpr std::uint32_t progress = 0x8;
        inline constexpr std::uint32_t is_completed = 0xC;
    }

    namespace hw2_scoreboard {
        inline constexpr std::uint32_t assist = 0xCC;
        inline constexpr std::uint32_t player_score = 0xE8;
        inline constexpr std::uint32_t killing_spree = 0x398;
    }

    namespace hw2_bot_config {
        inline constexpr std::uint32_t tiers = 0x38;
        inline constexpr std::uint32_t aim_interp_speed = 0x48;
        inline constexpr std::uint32_t aim_error_interval = 0x4C;
        inline constexpr std::uint32_t aim_target_z_offset = 0x50;
        inline constexpr std::uint32_t is_perceived_position_aim = 0x54;
        inline constexpr std::uint32_t is_movement_spread = 0x55;
        inline constexpr std::uint32_t is_fair_roaming = 0x56;
        inline constexpr std::uint32_t is_anti_pile_on = 0x57;
        inline constexpr std::uint32_t is_anti_pile_on_humans_only = 0x58;
        inline constexpr std::uint32_t pile_on_distance_penalty = 0x5C;
        inline constexpr std::uint32_t sticky_target_distance = 0x60;
        inline constexpr std::uint32_t attacker_preference_seconds = 0x64;
        inline constexpr std::uint32_t is_threat_memory = 0x68;
        inline constexpr std::uint32_t hold_min_seconds = 0x6C;
        inline constexpr std::uint32_t hold_max_seconds = 0x70;
        inline constexpr std::uint32_t pursue_lead_seconds = 0x74;
        inline constexpr std::uint32_t pursue_lead_max = 0x78;
        inline constexpr std::uint32_t pursue_max_seconds = 0x7C;
        inline constexpr std::uint32_t pursue_max_distance = 0x80;
        inline constexpr std::uint32_t pursue_clear_range = 0x84;
        inline constexpr std::uint32_t search_point_count = 0x88;
        inline constexpr std::uint32_t search_radius = 0x8C;
        inline constexpr std::uint32_t search_point_seconds = 0x90;
        inline constexpr std::uint32_t search_max_seconds = 0x94;
        inline constexpr std::uint32_t memory_max_seconds = 0x98;
        inline constexpr std::uint32_t memory_refresh_radius = 0x9C;
        inline constexpr std::uint32_t max_memory_refreshes = 0xA0;
        inline constexpr std::uint32_t objective_leash_radius = 0xA4;
        inline constexpr std::uint32_t objective_pursue_slack = 0xA8;
        inline constexpr std::uint32_t is_alerts = 0xAC;
        inline constexpr std::uint32_t damage_alert_seconds = 0xB0;
        inline constexpr std::uint32_t hearing_alert_seconds = 0xB4;
        inline constexpr std::uint32_t hearing_alert_radius = 0xB8;
        inline constexpr std::uint32_t hearing_alert_cooldown = 0xBC;
        inline constexpr std::uint32_t attention_turn_scale = 0xC0;
        inline constexpr std::uint32_t is_investigate_noise = 0xC4;
        inline constexpr std::uint32_t investigate_min_distance = 0xC8;
        inline constexpr std::uint32_t investigate_max_distance = 0xCC;
        inline constexpr std::uint32_t investigate_cooldown = 0xD0;
        inline constexpr std::uint32_t is_damage_reaction = 0xD4;
        inline constexpr std::uint32_t damage_hold_min_seconds = 0xD8;
        inline constexpr std::uint32_t damage_hold_max_seconds = 0xDC;
        inline constexpr std::uint32_t damage_hit_window_seconds = 0xE0;
        inline constexpr std::uint32_t flank_turn_seconds = 0xE4;
        inline constexpr std::uint32_t flank_switch_hits = 0xE8;
        inline constexpr std::uint32_t is_reload_movement = 0xEC;
        inline constexpr std::uint32_t reload_move_min_distance = 0xF0;
        inline constexpr std::uint32_t reload_move_max_distance = 0xF4;
        inline constexpr std::uint32_t reload_move_candidates = 0xF8;
        inline constexpr std::uint32_t reload_stall_seconds = 0xFC;
        inline constexpr std::uint32_t tactical_reload_fraction = 0x100;
        inline constexpr std::uint32_t tactical_reload_calm_seconds = 0x104;
        inline constexpr std::uint32_t is_combat_strafe = 0x108;
        inline constexpr std::uint32_t strafe_idle_seconds = 0x10C;
        inline constexpr std::uint32_t strafe_min_distance = 0x110;
        inline constexpr std::uint32_t strafe_max_distance = 0x114;
        inline constexpr std::uint32_t strafe_interval_min = 0x118;
        inline constexpr std::uint32_t strafe_interval_max = 0x11C;
        inline constexpr std::uint32_t is_objective_first = 0x120;
        inline constexpr std::uint32_t is_fire_on_move = 0x121;
        inline constexpr std::uint32_t move_fire_interval = 0x124;
        inline constexpr std::uint32_t is_shoot_hostile_vehicles = 0x128;
        inline constexpr std::uint32_t hostile_vehicle_range = 0x12C;
        inline constexpr std::uint32_t hostile_vehicle_burst_min = 0x130;
        inline constexpr std::uint32_t hostile_vehicle_burst_max = 0x134;
        inline constexpr std::uint32_t hostile_vehicle_pause_min = 0x138;
        inline constexpr std::uint32_t hostile_vehicle_pause_max = 0x13C;
        inline constexpr std::uint32_t hostile_vehicle_aim_tolerance = 0x140;
        inline constexpr std::uint32_t engage_min_seconds = 0x144;
        inline constexpr std::uint32_t disengage_scale = 0x148;
        inline constexpr std::uint32_t engage_when_shot_seconds = 0x14C;
        inline constexpr std::uint32_t carrier_engage_radius = 0x150;
        inline constexpr std::uint32_t carrier_path_check_distance = 0x154;
        inline constexpr std::uint32_t carrier_path_block_radius = 0x158;
        inline constexpr std::uint32_t carrier_stall_seconds = 0x15C;
        inline constexpr std::uint32_t carrier_sprint_threat_radius = 0x160;
        inline constexpr std::uint32_t escort_engage_radius = 0x164;
        inline constexpr std::uint32_t capturer_engage_radius = 0x168;
        inline constexpr std::uint32_t capture_circle_margin = 0x16C;
        inline constexpr std::uint32_t defender_post_radius = 0x170;
        inline constexpr std::uint32_t defender_leash_radius = 0x174;
        inline constexpr std::uint32_t interactor_engage_radius = 0x178;
        inline constexpr std::uint32_t interactor_arrive_radius = 0x17C;
        inline constexpr std::uint32_t is_retrieve_dropped_bags = 0x180;
        inline constexpr std::uint32_t retrievers_per_bag = 0x184;
        inline constexpr std::uint32_t retriever_engage_radius = 0x188;
        inline constexpr std::uint32_t bag_home_radius = 0x18C;
        inline constexpr std::uint32_t is_carrier_reload_on_the_move = 0x190;
        inline constexpr std::uint32_t is_combat_stances = 0x191;
        inline constexpr std::uint32_t cover_search_radius = 0x194;
        inline constexpr std::uint32_t retreat_search_radius = 0x198;
        inline constexpr std::uint32_t cover_candidates = 0x19C;
        inline constexpr std::uint32_t cover_max_traces = 0x1A0;
        inline constexpr std::uint32_t cover_queries_per_team_per_second = 0x1A4;
        inline constexpr std::uint32_t cover_min_threat_distance = 0x1A8;
        inline constexpr std::uint32_t cover_max_advance = 0x1AC;
        inline constexpr std::uint32_t cover_claim_radius = 0x1B0;
        inline constexpr std::uint32_t cover_max_path_factor = 0x1B4;
        inline constexpr std::uint32_t is_crouch_in_half_cover = 0x1B8;
        inline constexpr std::uint32_t cover_hide_max_seconds = 0x1BC;
        inline constexpr std::uint32_t cover_hide_min_seconds = 0x1C0;
        inline constexpr std::uint32_t peek_min_seconds = 0x1C4;
        inline constexpr std::uint32_t peek_max_seconds = 0x1C8;
        inline constexpr std::uint32_t peek_damage_to_hide = 0x1CC;
        inline constexpr std::uint32_t peeks_before_pursuit = 0x1D0;
        inline constexpr std::uint32_t cover_standoff_max_seconds = 0x1D4;
        inline constexpr std::uint32_t stance_eval_min_seconds = 0x1D8;
        inline constexpr std::uint32_t stance_eval_max_seconds = 0x1DC;
        inline constexpr std::uint32_t retreat_health_min = 0x1E0;
        inline constexpr std::uint32_t retreat_health_max = 0x1E4;
        inline constexpr std::uint32_t retreat_recover_health = 0x1E8;
        inline constexpr std::uint32_t retreat_max_seconds = 0x1EC;
        inline constexpr std::uint32_t retreat_cooldown_seconds = 0x1F0;
        inline constexpr std::uint32_t is_heal_before_roaming = 0x1F4;
        inline constexpr std::uint32_t retreat_cornered_radius = 0x1F8;
        inline constexpr std::uint32_t push_damage_dealt = 0x1FC;
        inline constexpr std::uint32_t push_aggression_min = 0x200;
        inline constexpr std::uint32_t push_aggressive_chance = 0x204;
        inline constexpr std::uint32_t cover_reload_fraction = 0x208;
        inline constexpr std::uint32_t peek_low_mag_fraction = 0x20C;
        inline constexpr std::uint32_t objective_cover_slack = 0x210;
        inline constexpr std::uint32_t objective_standoff_scale = 0x214;
        inline constexpr std::uint32_t hold_circle_margin = 0x218;
        inline constexpr std::uint32_t defender_hold_radius = 0x21C;
        inline constexpr std::uint32_t is_team_coordinator = 0x220;
        inline constexpr std::uint32_t coordinator_interval = 0x224;
        inline constexpr std::uint32_t assignment_min_seconds = 0x228;
        inline constexpr std::uint32_t assignment_sticky_bonus = 0x22C;
        inline constexpr std::uint32_t personality_cost_scale = 0x230;
        inline constexpr std::uint32_t human_slot_radius = 0x234;
        inline constexpr std::uint32_t redirect_distance = 0x238;
        inline constexpr std::uint32_t conquest_defender_share = 0x23C;
        inline constexpr std::uint32_t conquest_threat_defenders = 0x240;
        inline constexpr std::uint32_t conquest_split_share = 0x244;
        inline constexpr std::uint32_t conquest_post_radius = 0x248;
        inline constexpr std::uint32_t conquest_post_swap_min_seconds = 0x24C;
        inline constexpr std::uint32_t conquest_post_swap_max_seconds = 0x250;
        inline constexpr std::uint32_t conquest_post_angle = 0x254;
        inline constexpr std::uint32_t ctf_interceptors = 0x258;
        inline constexpr std::uint32_t ctf_intercept_radius = 0x25C;
        inline constexpr std::uint32_t ctf_escort_lead_distance = 0x260;
        inline constexpr std::uint32_t ctf_escort_cover_distance = 0x264;
        inline constexpr std::uint32_t ctf_home_defender_min_team = 0x268;
        inline constexpr std::uint32_t kc_max_collect_distance = 0x26C;
        inline constexpr std::uint32_t lane_count = 0x270;
        inline constexpr std::uint32_t lane_roam_chance = 0x274;
        inline constexpr std::uint32_t lane_width_share = 0x278;
        inline constexpr std::uint32_t is_callouts = 0x27C;
        inline constexpr std::uint32_t callout_delay_min = 0x280;
        inline constexpr std::uint32_t callout_delay_max = 0x284;
        inline constexpr std::uint32_t callout_recipients = 0x288;
        inline constexpr std::uint32_t callout_radius = 0x28C;
        inline constexpr std::uint32_t callout_error = 0x290;
        inline constexpr std::uint32_t callout_cooldown = 0x294;
        inline constexpr std::uint32_t is_personalities = 0x298;
        inline constexpr std::uint32_t aggression_min = 0x29C;
        inline constexpr std::uint32_t aggression_max = 0x2A0;
        inline constexpr std::uint32_t patience_min = 0x2A4;
        inline constexpr std::uint32_t patience_max = 0x2A8;
        inline constexpr std::uint32_t leash_min = 0x2AC;
        inline constexpr std::uint32_t leash_max = 0x2B0;
        inline constexpr std::uint32_t retreat_bias_range = 0x2B4;
        inline constexpr std::uint32_t reaction_scale_min = 0x2B8;
        inline constexpr std::uint32_t reaction_scale_max = 0x2BC;
        inline constexpr std::uint32_t is_tier_pursuit_tilt = 0x2C0;
        inline constexpr std::uint32_t is_gradual_detection = 0x2C1;
        inline constexpr std::uint32_t detect_focus_half_angle = 0x2C4;
        inline constexpr std::uint32_t detect_peripheral_factor = 0x2C8;
        inline constexpr std::uint32_t detect_near_distance = 0x2CC;
        inline constexpr std::uint32_t detect_near_factor = 0x2D0;
        inline constexpr std::uint32_t detect_reference_distance = 0x2D4;
        inline constexpr std::uint32_t detect_far_distance = 0x2D8;
        inline constexpr std::uint32_t detect_far_factor = 0x2DC;
        inline constexpr std::uint32_t detect_moving_factor = 0x2E0;
        inline constexpr std::uint32_t detect_moving_speed = 0x2E4;
        inline constexpr std::uint32_t detect_crouch_factor = 0x2E8;
        inline constexpr std::uint32_t detect_alert_factor = 0x2EC;
        inline constexpr std::uint32_t awareness_keep_seconds = 0x2F0;
        inline constexpr std::uint32_t awareness_decay_seconds = 0x2F4;
        inline constexpr std::uint32_t is_flinch = 0x2F8;
        inline constexpr std::uint32_t flinch_seconds = 0x2FC;
        inline constexpr std::uint32_t is_bot_voice = 0x300;
        inline constexpr std::uint32_t voice_spotted_event_id = 0x304;
        inline constexpr std::uint32_t voice_retreat_event_id = 0x308;
        inline constexpr std::uint32_t voice_push_event_id = 0x30C;
        inline constexpr std::uint32_t voice_min_gap_seconds = 0x310;
        inline constexpr std::uint32_t voice_team_gap_seconds = 0x314;
        inline constexpr std::uint32_t is_face_off_recovery = 0x318;
        inline constexpr std::uint32_t face_off_radius = 0x31C;
        inline constexpr std::uint32_t face_off_speed = 0x320;
        inline constexpr std::uint32_t face_off_seconds = 0x324;
        inline constexpr std::uint32_t stuck_yield_seconds = 0x328;
        inline constexpr std::uint32_t yield_step_min = 0x32C;
        inline constexpr std::uint32_t yield_step_max = 0x330;
        inline constexpr std::uint32_t stuck_reroute_seconds = 0x334;
        inline constexpr std::uint32_t reroute_offset_min = 0x338;
        inline constexpr std::uint32_t reroute_offset_max = 0x33C;
        inline constexpr std::uint32_t post_min_spacing = 0x340;
        inline constexpr std::uint32_t is_active_defence = 0x344;
        inline constexpr std::uint32_t is_watch_points = 0x345;
        inline constexpr std::uint32_t is_focal_sanity = 0x346;
        inline constexpr std::uint32_t focal_sanity_tolerance = 0x348;
        inline constexpr std::uint32_t defend_activity_weights = 0x34C;
        inline constexpr std::uint32_t defend_hold_min_seconds = 0x360;
        inline constexpr std::uint32_t defend_hold_max_seconds = 0x364;
        inline constexpr std::uint32_t defend_shift_min_distance = 0x368;
        inline constexpr std::uint32_t defend_shift_max_distance = 0x36C;
        inline constexpr std::uint32_t defend_crouch_min_seconds = 0x370;
        inline constexpr std::uint32_t defend_crouch_max_seconds = 0x374;
        inline constexpr std::uint32_t defend_reposition_min = 0x378;
        inline constexpr std::uint32_t defend_reposition_max = 0x37C;
        inline constexpr std::uint32_t defend_clear_share_min = 0x380;
        inline constexpr std::uint32_t defend_clear_share_max = 0x384;
        inline constexpr std::uint32_t approach_length = 0x388;
        inline constexpr std::uint32_t approaches_max = 0x38C;
        inline constexpr std::uint32_t approach_merge_degrees = 0x390;
        inline constexpr std::uint32_t danger_seconds = 0x394;
        inline constexpr std::uint32_t seen_post_avoid_seconds = 0x398;
        inline constexpr std::uint32_t defend_post_candidates = 0x39C;
        inline constexpr std::uint32_t defend_post_trace_budget = 0x3A0;
        inline constexpr std::uint32_t defend_posts_per_slot = 0x3A4;
        inline constexpr std::uint32_t defend_occupant_leash_scale = 0x3A8;
        inline constexpr std::uint32_t site_defend_radius = 0x3AC;
        inline constexpr std::uint32_t is_advantage_stance = 0x3B0;
        inline constexpr std::uint32_t mode_aggression_bias = 0x3B4;
        inline constexpr std::uint32_t advantage_push_above = 0x3CC;
        inline constexpr std::uint32_t advantage_cover_below = 0x3D0;
        inline constexpr std::uint32_t peek_hit_extend_seconds = 0x3D4;
        inline constexpr std::uint32_t is_purpose_sprint = 0x3D8;
        inline constexpr std::uint32_t chaos_gunfire_roam_chance = 0x3DC;
        inline constexpr std::uint32_t is_weapon_archetypes = 0x3E0;
        inline constexpr std::uint32_t weapon_profiles = 0x3E8;
        inline constexpr std::uint32_t weapon_archetype_overrides = 0x3F8;
        inline constexpr std::uint32_t is_sidearm_swap = 0x448;
        inline constexpr std::uint32_t sidearm_reload_seconds_threshold = 0x44C;
        inline constexpr std::uint32_t sidearm_max_range = 0x450;
        inline constexpr std::uint32_t sidearm_cover_radius = 0x454;
        inline constexpr std::uint32_t sidearm_fight_seen_seconds = 0x458;
        inline constexpr std::uint32_t sidearm_return_seconds = 0x45C;
        inline constexpr std::uint32_t is_shotgun_interrupt_reload = 0x460;
        inline constexpr std::uint32_t shotgun_interrupt_shells = 0x464;
        inline constexpr std::uint32_t dry_melee_range = 0x468;
        inline constexpr std::uint32_t is_give_bots_sidearm = 0x46C;
        inline constexpr std::uint32_t bot_sidearm_classes = 0x470;
        inline constexpr std::uint32_t sidearm_swap_seconds = 0x480;
        inline constexpr std::uint32_t force_bot_primary = 0x488;
        inline constexpr std::uint32_t is_sight_ignores_friendlies = 0x498;
        inline constexpr std::uint32_t investigate_contact_chance = 0x49C;
        inline constexpr std::uint32_t contact_lifetime = 0x4A0;
        inline constexpr std::uint32_t noise_error_fraction = 0x4A4;
        inline constexpr std::uint32_t noise_error_max = 0x4A8;
        inline constexpr std::uint32_t damage_direction_error_degrees = 0x4AC;
        inline constexpr std::uint32_t roam_min_distance = 0x4B0;
        inline constexpr std::uint32_t roam_max_distance = 0x4B4;
        inline constexpr std::uint32_t roam_claim_radius = 0x4B8;
        inline constexpr std::uint32_t roam_point_class_prefixes = 0x4C0;
        inline constexpr std::uint32_t is_smart_spawns = 0x4D0;
        inline constexpr std::uint32_t spawn_enemy_hard_radius = 0x4D4;
        inline constexpr std::uint32_t spawn_safe_distance = 0x4D8;
        inline constexpr std::uint32_t spawn_sight_check_radius = 0x4DC;
        inline constexpr std::uint32_t spawn_sight_penalty = 0x4E0;
        inline constexpr std::uint32_t spawn_reuse_seconds = 0x4E4;
        inline constexpr std::uint32_t spawn_reuse_penalty = 0x4E8;
        inline constexpr std::uint32_t spawn_danger_seconds = 0x4EC;
        inline constexpr std::uint32_t spawn_danger_radius = 0x4F0;
        inline constexpr std::uint32_t spawn_danger_penalty = 0x4F4;
        inline constexpr std::uint32_t spawn_pick_margin = 0x4F8;
        inline constexpr std::uint32_t is_end_spawn_protection_on_attack = 0x4FC;
        inline constexpr std::uint32_t spawn_protection_seconds = 0x500;
        inline constexpr std::uint32_t is_glass_see_through = 0x504;
        inline constexpr std::uint32_t is_glass_shoot_through = 0x505;
        inline constexpr std::uint32_t glass_sight_recheck_seconds = 0x508;
        inline constexpr std::uint32_t glass_sight_max_distance = 0x50C;
        inline constexpr std::uint32_t is_sn_d_director = 0x510;
        inline constexpr std::uint32_t is_sn_d_observe_only = 0x511;
        inline constexpr std::uint32_t sn_d_weight_default = 0x514;
        inline constexpr std::uint32_t sn_d_weight_split = 0x518;
        inline constexpr std::uint32_t sn_d_weight_fake = 0x51C;
        inline constexpr std::uint32_t sn_d_weight_rush = 0x520;
        inline constexpr std::uint32_t sn_d_stage_hold_min = 0x524;
        inline constexpr std::uint32_t sn_d_stage_hold_max = 0x528;
        inline constexpr std::uint32_t sn_d_stall_seconds = 0x52C;
        inline constexpr std::uint32_t sn_d_advance_engage_scale = 0x530;
        inline constexpr std::uint32_t sn_d_stage_gather_share = 0x534;
        inline constexpr std::uint32_t sn_d_fake_hold_min = 0x538;
        inline constexpr std::uint32_t sn_d_fake_hold_max = 0x53C;
        inline constexpr std::uint32_t sn_d_late_round_seconds = 0x540;
        inline constexpr std::uint32_t sn_d_contested_distance = 0x544;
        inline constexpr std::uint32_t sn_d_careful_tail = 0x548;
        inline constexpr std::uint32_t sn_d_corner_slow_seconds = 0x54C;
        inline constexpr std::uint32_t sn_d_attacker_aggression_bias = 0x550;
        inline constexpr std::uint32_t sn_d_holder_aggression_bias = 0x554;
        inline constexpr std::uint32_t sn_d_corner_min_open = 0x558;
        inline constexpr std::uint32_t sn_d_corner_pause_open = 0x55C;
        inline constexpr std::uint32_t sn_d_corner_pause_min = 0x560;
        inline constexpr std::uint32_t sn_d_corner_pause_max = 0x564;
        inline constexpr std::uint32_t sn_d_follow_spacing = 0x568;
        inline constexpr std::uint32_t sn_d_trade_radius = 0x56C;
        inline constexpr std::uint32_t sn_d_lurker_chance = 0x570;
        inline constexpr std::uint32_t sn_d_forward_chance = 0x574;
        inline constexpr std::uint32_t sn_d_forward_seconds_min = 0x578;
        inline constexpr std::uint32_t sn_d_forward_seconds_max = 0x57C;
        inline constexpr std::uint32_t sn_d_push_chance = 0x580;
        inline constexpr std::uint32_t sn_d_push_start_min = 0x584;
        inline constexpr std::uint32_t sn_d_push_start_max = 0x588;
        inline constexpr std::uint32_t sn_d_push_seconds = 0x58C;
        inline constexpr std::uint32_t sn_d_second_pusher_chance = 0x590;
        inline constexpr std::uint32_t sn_d_push_share_min = 0x594;
        inline constexpr std::uint32_t sn_d_push_share_max = 0x598;
        inline constexpr std::uint32_t sn_d_push_max_distance = 0x59C;
        inline constexpr std::uint32_t sn_d_rotate_danger = 0x5A0;
        inline constexpr std::uint32_t sn_d_relocate_min = 0x5A4;
        inline constexpr std::uint32_t sn_d_relocate_max = 0x5A8;
        inline constexpr std::uint32_t sn_d_shift_min = 0x5AC;
        inline constexpr std::uint32_t sn_d_shift_max = 0x5B0;
        inline constexpr std::uint32_t sn_d_retake_gather_max = 0x5B4;
        inline constexpr std::uint32_t sn_d_interact_seconds = 0x5B8;
        inline constexpr std::uint32_t sn_d_hold_leash = 0x5BC;
        inline constexpr std::uint32_t sn_d_move_leash = 0x5C0;
        inline constexpr std::uint32_t sn_d_push_leash = 0x5C4;
        inline constexpr std::uint32_t is_telemetry = 0x5C8;
        inline constexpr std::uint32_t is_auto_dump_stats_on_world_end = 0x5C9;
        inline constexpr std::uint32_t contact_gap_seconds = 0x5CC;
        inline constexpr std::uint32_t first_shot_window_seconds = 0x5D0;
        inline constexpr std::uint32_t pile_on_window_seconds = 0x5D4;
        inline constexpr std::uint32_t byte_size = 0x5D8;
    }

    namespace hw2_bot_weapon_profile {
        inline constexpr std::uint32_t archetype = 0x0;
        inline constexpr std::uint32_t band_min = 0x4;
        inline constexpr std::uint32_t band_ideal = 0x8;
        inline constexpr std::uint32_t band_max = 0xC;
        inline constexpr std::uint32_t engage_range_scale = 0x10;
        inline constexpr std::uint32_t push_bias = 0x14;
        inline constexpr std::uint32_t is_close_out_of_band = 0x18;
        inline constexpr std::uint32_t peek_scale = 0x1C;
        inline constexpr std::uint32_t hide_scale = 0x20;
        inline constexpr std::uint32_t strafe_scale = 0x24;
        inline constexpr std::uint32_t retreat_health_bias = 0x28;
        inline constexpr std::uint32_t fire_angle_scale = 0x2C;
        inline constexpr std::uint32_t burst_rest_scale = 0x30;
        inline constexpr std::uint32_t vantage_weight = 0x34;
        inline constexpr std::uint32_t is_relocate_after_kill = 0x38;
        inline constexpr std::uint32_t is_aim_while_holding = 0x39;
        inline constexpr std::uint32_t sidearm_chance_min = 0x3C;
        inline constexpr std::uint32_t sidearm_chance_max = 0x40;
        inline constexpr std::uint32_t sidearm_mag_fraction = 0x44;
        inline constexpr std::uint32_t seed_reload_seconds = 0x48;
        inline constexpr std::uint32_t hold_fire_beyond_band = 0x4C;
        inline constexpr std::uint32_t close_sidearm_range = 0x50;
        inline constexpr std::uint32_t byte_size = 0x54;
    }

    namespace hw2_bot_defend_weights {
        inline constexpr std::uint32_t hold_angle = 0x0;
        inline constexpr std::uint32_t shift = 0x4;
        inline constexpr std::uint32_t crouch_watch = 0x8;
        inline constexpr std::uint32_t reposition = 0xC;
        inline constexpr std::uint32_t clear_angle = 0x10;
        inline constexpr std::uint32_t byte_size = 0x14;
    }

    namespace hw2_bot_mode_bias {
        inline constexpr std::uint32_t chaos = 0x0;
        inline constexpr std::uint32_t gang_bang = 0x4;
        inline constexpr std::uint32_t chain_snatch = 0x8;
        inline constexpr std::uint32_t turf_war = 0xC;
        inline constexpr std::uint32_t hit_a_lick = 0x10;
        inline constexpr std::uint32_t destroy_the_block = 0x14;
        inline constexpr std::uint32_t byte_size = 0x18;
    }

    namespace hw2_bot_controller {
        inline constexpr std::uint32_t uber_graph_frame = 0x3C8;
        inline constexpr std::uint32_t ac_kill_feed = 0x3D0;
        inline constexpr std::uint32_t ai_perception = 0x3D8;
        inline constexpr std::uint32_t percived_actor = 0x3E0;
        inline constexpr std::uint32_t enemy = 0x3E8;
        inline constexpr std::uint32_t is_on_sight_key = 0x3F0;
        inline constexpr std::uint32_t blackboard_key_enemy = 0x3F8;
        inline constexpr std::uint32_t enemy_last_position_key = 0x400;
        inline constexpr std::uint32_t reset_ai_target_handle = 0x408;
        inline constexpr std::uint32_t ai_difficulty = 0x410;
        inline constexpr std::uint32_t respawn_timer = 0x418;
        inline constexpr std::uint32_t aim_acquire_time = 0x420;
        inline constexpr std::uint32_t aim_last_seen_time = 0x428;
        inline constexpr std::uint32_t aim_err_yaw = 0x430;
        inline constexpr std::uint32_t aim_err_pitch = 0x438;
        inline constexpr std::uint32_t aim_err_goal_yaw = 0x440;
        inline constexpr std::uint32_t aim_err_goal_pitch = 0x448;
        inline constexpr std::uint32_t aim_next_error_time = 0x450;
        inline constexpr std::uint32_t burst_until = 0x458;
        inline constexpr std::uint32_t burst_rest_until = 0x460;
        inline constexpr std::uint32_t aim_turn_rate = 0x468;
        inline constexpr std::uint32_t aim_interp_speed = 0x470;
        inline constexpr std::uint32_t aim_reaction_delay = 0x478;
        inline constexpr std::uint32_t aim_error_initial = 0x480;
        inline constexpr std::uint32_t aim_error_settled = 0x488;
        inline constexpr std::uint32_t aim_settle_time = 0x490;
        inline constexpr std::uint32_t aim_error_interval = 0x498;
        inline constexpr std::uint32_t aim_fire_angle = 0x4A0;
        inline constexpr std::uint32_t aim_target_z_offset = 0x4A8;
        inline constexpr std::uint32_t burst_duration = 0x4B0;
        inline constexpr std::uint32_t burst_rest = 0x4B8;
        inline constexpr std::uint32_t is_aim_settled = 0x4C0;
        inline constexpr std::uint32_t is_aim_overriding = 0x4C1;
        inline constexpr std::uint32_t aim_rotation = 0x4C8;
        inline constexpr std::uint32_t aim_proxy = 0x4E0;
        inline constexpr std::uint32_t aim_target_actor = 0x4E8;
        inline constexpr std::uint32_t patrol_focus_target = 0x4F0;
        inline constexpr std::uint32_t patrol_focus_current = 0x508;
        inline constexpr std::uint32_t is_patrol_focus_active = 0x520;
        inline constexpr std::uint32_t patrol_focus_until = 0x528;
        inline constexpr std::uint32_t watchdog_last_location = 0x530;
        inline constexpr std::uint32_t watchdog_check_accum = 0x548;
        inline constexpr std::uint32_t watchdog_idle_seconds = 0x550;
        inline constexpr std::uint32_t watchdog_interaction_seconds = 0x558;
        inline constexpr std::uint32_t watchdog_recovery_count = 0x560;
        inline constexpr std::uint32_t watchdog_last_fallback = 0x568;
        inline constexpr std::uint32_t watchdog_last_moved_distance = 0x580;
        inline constexpr std::uint32_t is_watchdog_recovering = 0x588;
        inline constexpr std::uint32_t is_bot_traits_initialized_ue = 0x589;
        inline constexpr std::uint32_t bot_trait_seed_ue = 0x58C;
        inline constexpr std::uint32_t bot_role_index_ue = 0x590;
        inline constexpr std::uint32_t bot_lane_degrees_ue = 0x598;
        inline constexpr std::uint32_t bot_aggression_ue = 0x5A0;
        inline constexpr std::uint32_t bot_roster_scan_index_ue = 0x5A8;
        inline constexpr std::uint32_t bot_last_intent_reason_ue = 0x5B0;
        inline constexpr std::uint32_t bot_intent_change_count_ue = 0x5C0;
        inline constexpr std::uint32_t bot_intent_invalidation_count_ue = 0x5C4;
        inline constexpr std::uint32_t bot_replan_request_count_ue = 0x5C8;
        inline constexpr std::uint32_t bot_lifecycle_reset_count_ue = 0x5CC;
        inline constexpr std::uint32_t ammo_deadlock_seconds_ue = 0x5D0;
        inline constexpr std::uint32_t byte_size = 0x5D8;
    }

    namespace hw2_streak_config {
        inline constexpr std::uint32_t is_enabled = 0x38;
        inline constexpr std::uint32_t killstreaks = 0x40;
        inline constexpr std::uint32_t is_free_killstreaks_for_testing = 0x50;
        inline constexpr std::uint32_t max_equipped = 0x54;
        inline constexpr std::uint32_t slot_input_actions = 0x58;
        inline constexpr std::uint32_t is_gamepad_picker = 0x68;
        inline constexpr std::uint32_t picker_tap_seconds = 0x6C;
        inline constexpr std::uint32_t picker_timeout_seconds = 0x70;
        inline constexpr std::uint32_t picker_input_priority = 0x74;
        inline constexpr std::uint32_t is_keep_earned_on_death = 0x78;
        inline constexpr std::uint32_t is_bots_use_killstreaks = 0x79;
        inline constexpr std::uint32_t is_bot_random_loadout = 0x7A;
        inline constexpr std::uint32_t bot_use_delay_min = 0x7C;
        inline constexpr std::uint32_t bot_use_delay_max = 0x80;
        inline constexpr std::uint32_t bot_fight_grace_seconds = 0x84;
        inline constexpr std::uint32_t bot_max_wait_seconds = 0x88;
        inline constexpr std::uint32_t is_bot_free_killstreaks_for_testing = 0x8C;
        inline constexpr std::uint32_t max_placement_distance = 0x90;
        inline constexpr std::uint32_t nav_projection_extent = 0x94;
        inline constexpr std::uint32_t is_require_playable_nav = 0x98;
        inline constexpr std::uint32_t off_nav_remove_seconds = 0x9C;
        inline constexpr std::uint32_t is_phone_call = 0xA0;
        inline constexpr std::uint32_t phone_call_seconds = 0xA4;
        inline constexpr std::uint32_t phone_equip_timeout = 0xA8;
        inline constexpr std::uint32_t phone_mesh = 0xB0;
        inline constexpr std::uint32_t phone_screen_slot = 0xD8;
        inline constexpr std::uint32_t phone_screens = 0xE0;
        inline constexpr std::uint32_t phone_screen_generic = 0xF0;
        inline constexpr std::uint32_t phone_fpp_transform = 0x120;
        inline constexpr std::uint32_t phone_tpp_transform = 0x180;
        inline constexpr std::uint32_t phone_call_sound = 0x1E0;
        inline constexpr std::uint32_t phone_weapon_class = 0x208;
        inline constexpr std::uint32_t is_arrive_in_front = 0x230;
        inline constexpr std::uint32_t front_distance = 0x234;
        inline constexpr std::uint32_t front_min_distance = 0x238;
        inline constexpr std::uint32_t front_max_distance = 0x23C;
        inline constexpr std::uint32_t front_max_angle = 0x240;
        inline constexpr std::uint32_t behind_distance = 0x244;
        inline constexpr std::uint32_t behind_min_distance = 0x248;
        inline constexpr std::uint32_t behind_max_distance = 0x24C;
        inline constexpr std::uint32_t behind_min_angle = 0x250;
        inline constexpr std::uint32_t behind_max_path_ratio = 0x254;
        inline constexpr std::uint32_t homie_count = 0x258;
        inline constexpr std::uint32_t homie_weapon_class = 0x260;
        inline constexpr std::uint32_t homie_name_format = 0x288;
        inline constexpr std::uint32_t homies_kill_feed_damage_type = 0x298;
        inline constexpr std::uint32_t homie_spacing = 0x2C0;
        inline constexpr std::uint32_t homie_max_life_seconds = 0x2C4;
        inline constexpr std::uint32_t bomber_name_format = 0x2C8;
        inline constexpr std::uint32_t bomber_pawn_class_team0 = 0x2D8;
        inline constexpr std::uint32_t bomber_pawn_class_team1 = 0x300;
        inline constexpr std::uint32_t bomber_hold_weapon_class = 0x328;
        inline constexpr std::uint32_t bomber_hold_montage = 0x350;
        inline constexpr std::uint32_t bomber_hold_time = 0x378;
        inline constexpr std::uint32_t detonate_distance = 0x37C;
        inline constexpr std::uint32_t fuse_seconds = 0x380;
        inline constexpr std::uint32_t max_life_seconds = 0x384;
        inline constexpr std::uint32_t is_detonate_on_death = 0x388;
        inline constexpr std::uint32_t blast_base_damage = 0x38C;
        inline constexpr std::uint32_t blast_minimum_damage = 0x390;
        inline constexpr std::uint32_t blast_inner_radius = 0x394;
        inline constexpr std::uint32_t blast_outer_radius = 0x398;
        inline constexpr std::uint32_t blast_damage_type = 0x3A0;
        inline constexpr std::uint32_t blast_effect = 0x3C8;
        inline constexpr std::uint32_t blast_effect_scale = 0x3F0;
        inline constexpr std::uint32_t blast_sounds = 0x3F8;
        inline constexpr std::uint32_t arm_sound = 0x408;
        inline constexpr std::uint32_t beep_interval = 0x430;
        inline constexpr std::uint32_t beep_near_interval = 0x434;
        inline constexpr std::uint32_t beep_far_distance = 0x438;
        inline constexpr std::uint32_t armed_beep_interval = 0x43C;
        inline constexpr std::uint32_t blast_camera_shake = 0x440;
        inline constexpr std::uint32_t blast_decal = 0x468;
        inline constexpr std::uint32_t c4_mesh = 0x490;
        inline constexpr std::uint32_t c4_material = 0x4B8;
        inline constexpr std::uint32_t c4_scale = 0x4E0;
        inline constexpr std::uint32_t c4_offset = 0x4E8;
        inline constexpr std::uint32_t drive_by_rails = 0x500;
        inline constexpr std::uint32_t drive_by_health = 0x510;
        inline constexpr std::uint32_t drive_by_stall_seconds_min = 0x514;
        inline constexpr std::uint32_t drive_by_stall_seconds_max = 0x518;
        inline constexpr std::uint32_t drive_by_speed = 0x51C;
        inline constexpr std::uint32_t drive_by_brake_distance = 0x520;
        inline constexpr std::uint32_t drive_by_patrol_speed = 0x524;
        inline constexpr std::uint32_t drive_by_patrol_half_length = 0x528;
        inline constexpr std::uint32_t drive_by_u_turn_radius = 0x52C;
        inline constexpr std::uint32_t is_drive_by_avoidance = 0x530;
        inline constexpr std::uint32_t is_drive_by_open_doors = 0x531;
        inline constexpr std::uint32_t drive_by_door_class_prefix = 0x538;
        inline constexpr std::uint32_t drive_by_door_radius = 0x548;
        inline constexpr std::uint32_t is_drive_by_knock_down_fences = 0x54C;
        inline constexpr std::uint32_t drive_by_knock_down_meshes = 0x550;
        inline constexpr std::uint32_t drive_by_avoid_max_offset = 0x560;
        inline constexpr std::uint32_t drive_by_avoid_slope = 0x564;
        inline constexpr std::uint32_t drive_by_avoid_margin = 0x568;
        inline constexpr std::uint32_t drive_by_destroy_score = 0x56C;
        inline constexpr std::uint32_t drive_by_wreck_seconds = 0x570;
        inline constexpr std::uint32_t drive_by_wreck_blast_damage = 0x574;
        inline constexpr std::uint32_t drive_by_wreck_blast_minimum_damage = 0x578;
        inline constexpr std::uint32_t drive_by_wreck_blast_inner_radius = 0x57C;
        inline constexpr std::uint32_t drive_by_wreck_blast_outer_radius = 0x580;
        inline constexpr std::uint32_t drive_by_wreck_damage_type = 0x588;
        inline constexpr std::uint32_t drive_by_car_mesh = 0x5B0;
        inline constexpr std::uint32_t drive_by_paint_slot = 0x5D8;
        inline constexpr std::uint32_t drive_by_paint_material = 0x5E0;
        inline constexpr std::uint32_t drive_by_paint_team0 = 0x608;
        inline constexpr std::uint32_t drive_by_paint_team1 = 0x618;
        inline constexpr std::uint32_t drive_by_glass_slot = 0x628;
        inline constexpr std::uint32_t drive_by_glass_opacity = 0x62C;
        inline constexpr std::uint32_t drive_by_glass_tint = 0x630;
        inline constexpr std::uint32_t drive_by_paint_other = 0x640;
        inline constexpr std::uint32_t drive_by_tag_height = 0x650;
        inline constexpr std::uint32_t drive_by_tag_range = 0x654;
        inline constexpr std::uint32_t drive_by_tag_aim_range = 0x658;
        inline constexpr std::uint32_t drive_by_tag_aim_degrees = 0x65C;
        inline constexpr std::uint32_t drive_by_wheel_radius = 0x660;
        inline constexpr std::uint32_t drive_by_body_box_center = 0x668;
        inline constexpr std::uint32_t drive_by_body_box_extent = 0x680;
        inline constexpr std::uint32_t drive_by_cabin_box_center = 0x698;
        inline constexpr std::uint32_t drive_by_cabin_box_extent = 0x6B0;
        inline constexpr std::uint32_t drive_by_music = 0x6C8;
        inline constexpr std::uint32_t drive_by_music_volume = 0x6D8;
        inline constexpr std::uint32_t drive_by_music_start_fraction = 0x6DC;
        inline constexpr std::uint32_t drive_by_music_inner_radius = 0x6E0;
        inline constexpr std::uint32_t drive_by_music_falloff = 0x6E4;
        inline constexpr std::uint32_t drive_by_music_eq = 0x6E8;
        inline constexpr std::uint32_t drive_by_music_drive = 0x6F8;
        inline constexpr std::uint32_t drive_by_music_drive_output_db = 0x6FC;
        inline constexpr std::uint32_t is_drive_by_music_rattle = 0x700;
        inline constexpr std::uint32_t drive_by_music_rattle = 0x708;
        inline constexpr std::uint32_t drive_by_music_crush = 0x720;
        inline constexpr std::uint32_t drive_by_music_speaker = 0x730;
        inline constexpr std::uint32_t drive_by_music_post_eq = 0x740;
        inline constexpr std::uint32_t drive_by_music_reverb_seconds = 0x750;
        inline constexpr std::uint32_t drive_by_music_reverb_wet_db = 0x754;
        inline constexpr std::uint32_t drive_by_music_reverb_dry_db = 0x758;
        inline constexpr std::uint32_t drive_by_music_low_pass_hz = 0x75C;
        inline constexpr std::uint32_t drive_by_music_min_track_seconds = 0x760;
        inline constexpr std::uint32_t drive_by_engine_sound = 0x768;
        inline constexpr std::uint32_t drive_by_engine_volume = 0x790;
        inline constexpr std::uint32_t drive_by_wreck_fire = 0x798;
        inline constexpr std::uint32_t drive_by_crew_team0 = 0x7C0;
        inline constexpr std::uint32_t drive_by_crew_team1 = 0x7D0;
        inline constexpr std::uint32_t drive_by_seats = 0x7E0;
        inline constexpr std::uint32_t drive_by_crew_materials = 0x7F0;
        inline constexpr std::uint32_t drive_by_crew_base_anim = 0x800;
        inline constexpr std::uint32_t drive_by_gun_mesh = 0x828;
        inline constexpr std::uint32_t drive_by_gun_part_mesh = 0x850;
        inline constexpr std::uint32_t drive_by_gun_part_socket = 0x878;
        inline constexpr std::uint32_t drive_by_gun_hand_offset = 0x880;
        inline constexpr std::uint32_t drive_by_gun_roll = 0x8E0;
        inline constexpr std::uint32_t drive_by_window_sill_height = 0x8E4;
        inline constexpr std::uint32_t drive_by_lean = 0x8E8;
        inline constexpr std::uint32_t drive_by_muzzle_flash = 0x8F0;
        inline constexpr std::uint32_t drive_by_fire_sound = 0x918;
        inline constexpr std::uint32_t drive_by_tracer = 0x940;
        inline constexpr std::uint32_t drive_by_impact = 0x968;
        inline constexpr std::uint32_t drive_by_casing = 0x990;
        inline constexpr std::uint32_t drive_by_bullet_hole_decal = 0x9B8;
        inline constexpr std::uint32_t drive_by_impact_sound = 0x9E0;
        inline constexpr std::uint32_t drive_by_bullet_hole_seconds = 0xA08;
        inline constexpr std::uint32_t drive_by_impact_cull_distance = 0xA0C;
        inline constexpr std::uint32_t drive_by_casing_cull_distance = 0xA10;
        inline constexpr std::uint32_t drive_by_crew_groom_keep = 0xA18;
        inline constexpr std::uint32_t is_drive_by_crew_cast_shadows = 0xA28;
        inline constexpr std::uint32_t drive_by_crew_min_lod = 0xA2C;
        inline constexpr std::uint32_t drive_by_crew_face_min_lod = 0xA30;
        inline constexpr std::uint32_t drive_by_damage = 0xA34;
        inline constexpr std::uint32_t drive_by_headshot_multiplier = 0xA38;
        inline constexpr std::uint32_t drive_by_damage_type = 0xA40;
        inline constexpr std::uint32_t drive_by_range = 0xA68;
        inline constexpr std::uint32_t drive_by_arc_half_angle = 0xA6C;
        inline constexpr std::uint32_t drive_by_fire_interval = 0xA70;
        inline constexpr std::uint32_t drive_by_burst_min = 0xA74;
        inline constexpr std::uint32_t drive_by_burst_max = 0xA78;
        inline constexpr std::uint32_t drive_by_burst_pause_min = 0xA7C;
        inline constexpr std::uint32_t drive_by_burst_pause_max = 0xA80;
        inline constexpr std::uint32_t drive_by_magazine = 0xA84;
        inline constexpr std::uint32_t drive_by_reload_seconds = 0xA88;
        inline constexpr std::uint32_t drive_by_reaction_seconds = 0xA8C;
        inline constexpr std::uint32_t drive_by_moving_target_spread = 0xA90;
        inline constexpr std::uint32_t drive_by_car_moving_spread = 0xA94;
        inline constexpr std::uint32_t drive_by_aim_wander = 0xA98;
        inline constexpr std::uint32_t drive_by_spread = 0xA9C;
        inline constexpr std::uint32_t drive_by_spread_fresh = 0xAA0;
        inline constexpr std::uint32_t drive_by_settle_seconds = 0xAA4;
        inline constexpr std::uint32_t drive_by_head_chance = 0xAA8;
        inline constexpr std::uint32_t summon_nametag_color = 0xAAC;
        inline constexpr std::uint32_t hud_margin = 0xAC0;
        inline constexpr std::uint32_t ready_sound = 0xAD0;
        inline constexpr std::uint32_t byte_size = 0xB00;
    }

    namespace hw2_streak_definition {
        inline constexpr std::uint32_t display_name = 0x0;
        inline constexpr std::uint32_t kills_required = 0x10;
        inline constexpr std::uint32_t icon = 0x18;
        inline constexpr std::uint32_t description = 0x40;
        inline constexpr std::uint32_t byte_size = 0x50;
    }

    namespace hw2_streak_component {
        inline constexpr std::uint32_t ready_mask = 0xC0;
        inline constexpr std::uint32_t equipped_mask = 0xC1;
        inline constexpr std::uint32_t is_team_snitch_up = 0xC2;
        inline constexpr std::uint32_t minimap_class = 0xE0;
        inline constexpr std::uint32_t hud = 0x148;
        inline constexpr std::uint32_t picker_context = 0x1A0;
        inline constexpr std::uint32_t byte_size = 0x1A8;
    }

    namespace hw2_drive_by_car {
        inline constexpr std::uint32_t rail_points = 0x2A8;
        inline constexpr std::uint32_t stall_distance = 0x2B8;
        inline constexpr std::uint32_t patrol_half_length = 0x2BC;
        inline constexpr std::uint32_t patrol_speed = 0x2C0;
        inline constexpr std::uint32_t patrol_side = 0x2C4;
        inline constexpr std::uint32_t patrol_half_laps = 0x2C8;
        inline constexpr std::uint32_t rail_flags = 0x2CC;
        inline constexpr std::uint32_t travel_half = 0x2D0;
        inline constexpr std::uint32_t u_turn_r = 0x2D4;
        inline constexpr std::uint32_t avoid_a = 0x2D8;
        inline constexpr std::uint32_t avoid_b = 0x2E8;
        inline constexpr std::uint32_t start_time = 0x2F8;
        inline constexpr std::uint32_t stall_seconds = 0x300;
        inline constexpr std::uint32_t team = 0x304;
        inline constexpr std::uint32_t health = 0x308;
        inline constexpr std::uint32_t wreck_time = 0x310;
        inline constexpr std::uint32_t targets = 0x318;
        inline constexpr std::uint32_t reload_mask = 0x328;
        inline constexpr std::uint32_t body_box = 0x330;
        inline constexpr std::uint32_t cabin_box = 0x338;
        inline constexpr std::uint32_t car_mesh = 0x340;
        inline constexpr std::uint32_t paint_mid = 0x348;
        inline constexpr std::uint32_t music = 0x350;
        inline constexpr std::uint32_t engine = 0x358;
        inline constexpr std::uint32_t current_song = 0x370;
        inline constexpr std::uint32_t glass_mid = 0x378;
        inline constexpr std::uint32_t tag = 0x380;
        inline constexpr std::uint32_t music_chain = 0x390;
        inline constexpr std::uint32_t fire_light = 0x3C0;
        inline constexpr std::uint32_t crew_components = 0x3C8;
        inline constexpr std::uint32_t byte_size = 0x4B0;
    }

    namespace hw2_summoned_marker {
        inline constexpr std::uint32_t kind = 0xC0;
        inline constexpr std::uint32_t team = 0xC4;
        inline constexpr std::uint32_t target_distance = 0xC8;
        inline constexpr std::uint32_t c4 = 0xD0;
        inline constexpr std::uint32_t byte_size = 0xF0;
    }

    namespace hw2_old_streaks {
        inline constexpr std::uint32_t uber_graph_frame = 0xC0;
        inline constexpr std::uint32_t uav_used = 0xC8;
        inline constexpr std::uint32_t current_kill_streak = 0xD8;
        inline constexpr std::uint32_t kill_streak_updated = 0xE0;
        inline constexpr std::uint32_t is_can_use_uav = 0xF0;
        inline constexpr std::uint32_t kill_streak_widget = 0xF8;
        inline constexpr std::uint32_t kill_streak_widget_ref = 0x120;
        inline constexpr std::uint32_t uav_actor_class = 0x128;
        inline constexpr std::uint32_t uav_time = 0x150;
        inline constexpr std::uint32_t cluster_strike_class = 0x158;
        inline constexpr std::uint32_t is_can_use_cluster_strike = 0x180;
        inline constexpr std::uint32_t cluster_strike_used = 0x188;
        inline constexpr std::uint32_t cluster_strike_cool_down = 0x198;
        inline constexpr std::uint32_t is_killstreaks_enabled = 0x19C;
        inline constexpr std::uint32_t byte_size = 0x1A0;
    }

    namespace hw2_weapon_actor {
        inline constexpr std::uint32_t uber_graph_frame = 0x2A8;
        inline constexpr std::uint32_t ac_weapon_attachments = 0x2B0;
        inline constexpr std::uint32_t mesh_fpp = 0x2B8;
        inline constexpr std::uint32_t mesh_tpp = 0x2C0;
        inline constexpr std::uint32_t scene = 0x2C8;
        inline constexpr std::uint32_t ammo_per_mag = 0x2D0;
        inline constexpr std::uint32_t current_ammo = 0x2D4;
        inline constexpr std::uint32_t pick_up_weapon_ammo = 0x2D8;
        inline constexpr std::uint32_t is_start_with_full_mag = 0x2DC;
        inline constexpr std::uint32_t firing_mode = 0x2DD;
        inline constexpr std::uint32_t ammo_changed = 0x2E0;
        inline constexpr std::uint32_t is_needs_pump = 0x2F0;
        inline constexpr std::uint32_t animation_data = 0x2F8;
        inline constexpr std::uint32_t settings_data = 0x300;
        inline constexpr std::uint32_t sniper_scope_ref = 0x308;
        inline constexpr std::uint32_t material_index = 0x310;
        inline constexpr std::uint32_t is_bolt_cycling = 0x314;
        inline constexpr std::uint32_t bot_damage_multiplier = 0x318;
        inline constexpr std::uint32_t last_pawn_hit_distance = 0x320;
        inline constexpr std::uint32_t last_pawn_hit_time = 0x328;
        inline constexpr std::uint32_t skin_mirror_slots = 0x330;
        inline constexpr std::uint32_t skin_extra_skin_materials = 0x340;
        inline constexpr std::uint32_t skin_extra_part_materials = 0x350;
        inline constexpr std::uint32_t skin_extra_mesh_assets = 0x360;
        inline constexpr std::uint32_t hw2_skin_color_a = 0x370;
        inline constexpr std::uint32_t hw2_skin_color_b = 0x380;
        inline constexpr std::uint32_t hw2_skin_source = 0x390;
        inline constexpr std::uint32_t hw2_b_no_stock = 0x398;
        inline constexpr std::uint32_t hw2_stock_mesh = 0x3A0;
        inline constexpr std::uint32_t hw2_no_stock_mesh = 0x3A8;
        inline constexpr std::uint32_t last_pawn_hit_aiming = 0x3B0;
        inline constexpr std::uint32_t byte_size = 0x3B8;
    }

    namespace hw2_weapon_data {
        inline constexpr std::uint32_t damage = 0x28;
        inline constexpr std::uint32_t fire_rate = 0x30;
        inline constexpr std::uint32_t weapon_range = 0x38;
        inline constexpr std::uint32_t ammo_per_mag = 0x40;
        inline constexpr std::uint32_t is_hit_scan_bullets = 0x44;
        inline constexpr std::uint32_t is_shotgun = 0x45;
        inline constexpr std::uint32_t projectiles_per_shot = 0x48;
        inline constexpr std::uint32_t damage_type = 0x50;
        inline constexpr std::uint32_t melee_damage_type = 0x58;
        inline constexpr std::uint32_t firing_modes = 0x60;
        inline constexpr std::uint32_t bullets_per_burst = 0x70;
        inline constexpr std::uint32_t weapon_name = 0x74;
        inline constexpr std::uint32_t aim_fov = 0x78;
        inline constexpr std::uint32_t aiming_interpolation_speed = 0x80;
        inline constexpr std::uint32_t headshot_multiplier = 0x88;
        inline constexpr std::uint32_t burst_fire_rate = 0x90;
        inline constexpr std::uint32_t weapon_type = 0x98;
        inline constexpr std::uint32_t is_hide_crosshair_in_tpp = 0x99;
        inline constexpr std::uint32_t noise_range = 0xA0;
        inline constexpr std::uint32_t noise_loudness = 0xA8;
        inline constexpr std::uint32_t is_use_client_side_hit_reg = 0xB0;
        inline constexpr std::uint32_t crosshair_widget = 0xB8;
        inline constexpr std::uint32_t bullet_spread = 0xC0;
        inline constexpr std::uint32_t aiming_bullet_spread = 0xC8;
        inline constexpr std::uint32_t vertical_recoil_min = 0xD0;
        inline constexpr std::uint32_t vertical_recoil_max = 0xD8;
        inline constexpr std::uint32_t horizontal_recoil_min = 0xE0;
        inline constexpr std::uint32_t horizontal_recoil_max = 0xE8;
        inline constexpr std::uint32_t recoil_interpolation_speed = 0xF0;
        inline constexpr std::uint32_t bullet_velocity = 0xF8;
        inline constexpr std::uint32_t ammo_type = 0x100;
        inline constexpr std::uint32_t is_uses_silencer = 0x101;
        inline constexpr std::uint32_t weapon_icon = 0x108;
        inline constexpr std::uint32_t bullet_case = 0x110;
        inline constexpr std::uint32_t zoom_in_sound = 0x118;
        inline constexpr std::uint32_t dry_fire = 0x120;
        inline constexpr std::uint32_t muzzle_flash = 0x128;
        inline constexpr std::uint32_t muzzle_flash_with_suppresor = 0x130;
        inline constexpr std::uint32_t is_pump_action = 0x138;
        inline constexpr std::uint32_t fpp_fire_sound = 0x140;
        inline constexpr std::uint32_t tpp_fire_sound = 0x148;
        inline constexpr std::uint32_t bullet_trace = 0x150;
        inline constexpr std::uint32_t uses_ammo = 0x158;
        inline constexpr std::uint32_t is_can_aim = 0x159;
        inline constexpr std::uint32_t aiming_bullet_spread_while_falling = 0x160;
        inline constexpr std::uint32_t bullet_spread_crouched = 0x168;
        inline constexpr std::uint32_t movement_spread_multiplier = 0x170;
        inline constexpr std::uint32_t bullet_impact = 0x178;
        inline constexpr std::uint32_t damage_falloff_start_distance = 0x180;
        inline constexpr std::uint32_t damage_falloff_end_distance = 0x188;
        inline constexpr std::uint32_t damage_falloff_min_multiplier = 0x190;
        inline constexpr std::uint32_t f_pp_fire_sound_suppressed = 0x198;
        inline constexpr std::uint32_t t_pp_fire_sound_suppressed = 0x1A0;
        inline constexpr std::uint32_t byte_size = 0x1A8;
    }

    namespace hw2_inventory_full {
        inline constexpr std::uint32_t uber_graph_frame = 0xC0;
        inline constexpr std::uint32_t primary_weapon = 0xC8;
        inline constexpr std::uint32_t secondary_weapon = 0xD0;
        inline constexpr std::uint32_t on_weapon_equipped = 0xD8;
        inline constexpr std::uint32_t current_weapon = 0xE8;
        inline constexpr std::uint32_t lethal_equipment = 0xF0;
        inline constexpr std::uint32_t weapon_ammo = 0xF8;
        inline constexpr std::uint32_t update_ammo = 0x108;
        inline constexpr std::uint32_t lethal_ammo = 0x118;
        inline constexpr std::uint32_t update_lethal = 0x128;
        inline constexpr std::uint32_t firing_mode_changed = 0x138;
        inline constexpr std::uint32_t current_crosshair_widget = 0x148;
        inline constexpr std::uint32_t previous_weapon = 0x150;
        inline constexpr std::uint32_t primary_weapon_skin = 0x158;
        inline constexpr std::uint32_t secondary_weapon_skin = 0x160;
        inline constexpr std::uint32_t laser_pointer = 0x168;
        inline constexpr std::uint32_t is_using_primary = 0x170;
        inline constexpr std::uint32_t primary_skin_color_a = 0x174;
        inline constexpr std::uint32_t primary_skin_color_b = 0x184;
        inline constexpr std::uint32_t secondary_skin_color_a = 0x194;
        inline constexpr std::uint32_t secondary_skin_color_b = 0x1A4;
        inline constexpr std::uint32_t hw2_pickup_skin_color_a = 0x1B4;
        inline constexpr std::uint32_t hw2_pickup_skin_color_b = 0x1C4;
        inline constexpr std::uint32_t hw2_spare_mag_granted = 0x1D8;
        inline constexpr std::uint32_t byte_size = 0x1E8;
    }

    namespace hw2_loadout {
        inline constexpr std::uint32_t uber_graph_frame = 0xC0;
        inline constexpr std::uint32_t selected_loadout_index = 0xC8;
        inline constexpr std::uint32_t is_editing_primary_weapon = 0xCC;
        inline constexpr std::uint32_t preview_loadout_changed = 0xD0;
        inline constexpr std::uint32_t max_loadouts = 0xE0;
        inline constexpr std::uint32_t player_loadouts = 0xE8;
        inline constexpr std::uint32_t current_loadout = 0xF8;
        inline constexpr std::uint32_t default_loadout = 0x198;
        inline constexpr std::uint32_t field_upgrade = 0x238;
        inline constexpr std::uint32_t preview_loadout = 0x240;
        inline constexpr std::uint32_t operator_class_a = 0x2E0;
        inline constexpr std::uint32_t operator_class_b = 0x2E8;
        inline constexpr std::uint32_t preview_operator_mesh_a = 0x2F0;
        inline constexpr std::uint32_t preview_operator_changed = 0x2F8;
        inline constexpr std::uint32_t preview_operator_mesh_b = 0x308;
        inline constexpr std::uint32_t operator_class_changed = 0x310;
        inline constexpr std::uint32_t laser_pointer = 0x320;
        inline constexpr std::uint32_t laser_pointer_class = 0x328;
        inline constexpr std::uint32_t is_weapon_accessory_active = 0x330;
        inline constexpr std::uint32_t loadout_skin_colors = 0x338;
        inline constexpr std::uint32_t current_primary_skin_color_a = 0x348;
        inline constexpr std::uint32_t current_primary_skin_color_b = 0x358;
        inline constexpr std::uint32_t current_secondary_skin_color_a = 0x368;
        inline constexpr std::uint32_t current_secondary_skin_color_b = 0x378;
        inline constexpr std::uint32_t preview_skin_color_a = 0x388;
        inline constexpr std::uint32_t preview_skin_color_b = 0x398;
        inline constexpr std::uint32_t byte_size = 0x3A8;
    }

    namespace hw2_vitals {
        inline constexpr std::uint32_t uber_graph_frame = 0xC0;
        inline constexpr std::uint32_t health = 0xC8;
        inline constexpr std::uint32_t max_health = 0xD0;
        inline constexpr std::uint32_t on_health_changed = 0xD8;
        inline constexpr std::uint32_t on_player_dead = 0xE8;
        inline constexpr std::uint32_t is_dead = 0xF8;
        inline constexpr std::uint32_t is_health_regen_enabled = 0xF9;
        inline constexpr std::uint32_t health_regen_initial_delay = 0x100;
        inline constexpr std::uint32_t start_regen_timer_handle = 0x108;
        inline constexpr std::uint32_t health_regen_timer = 0x110;
        inline constexpr std::uint32_t regen_tick_frecuency = 0x118;
        inline constexpr std::uint32_t health_per_tick = 0x120;
        inline constexpr std::uint32_t old_health_value = 0x128;
        inline constexpr std::uint32_t is_spawn_protected = 0x130;
        inline constexpr std::uint32_t spawn_protection_duration = 0x138;
        inline constexpr std::uint32_t byte_size = 0x140;
    }

    namespace hw2_lethal_equipment {
        inline constexpr std::uint32_t uber_graph_frame = 0x2A8;
        inline constexpr std::uint32_t fpp = 0x2B0;
        inline constexpr std::uint32_t tpp = 0x2B8;
        inline constexpr std::uint32_t default_scene_root = 0x2C0;
        inline constexpr std::uint32_t fpp_use_explosive = 0x2C8;
        inline constexpr std::uint32_t tpp_use_explosive = 0x2D0;
        inline constexpr std::uint32_t explosive_to_spawn = 0x2D8;
        inline constexpr std::uint32_t ui_icon = 0x2E0;
        inline constexpr std::uint32_t is_has_delayed_throw = 0x2E8;
        inline constexpr std::uint32_t time_to_explode = 0x2F0;
        inline constexpr std::uint32_t lethal_type = 0x2F8;
        inline constexpr std::uint32_t is_has_to_be_armed = 0x2F9;
        inline constexpr std::uint32_t equip_lethal_montage = 0x300;
        inline constexpr std::uint32_t equip_lethal_anim = 0x308;
        inline constexpr std::uint32_t byte_size = 0x310;
    }

    namespace hw2_frag {
        inline constexpr std::uint32_t uber_graph_frame = 0x2A8;
        inline constexpr std::uint32_t child_actor = 0x2B0;
        inline constexpr std::uint32_t mesh = 0x2B8;
        inline constexpr std::uint32_t sphere = 0x2C0;
        inline constexpr std::uint32_t projectile_movement = 0x2C8;
        inline constexpr std::uint32_t health_component = 0x2D0;
        inline constexpr std::uint32_t is_exploded = 0x2D8;
        inline constexpr std::uint32_t time_to_explode = 0x2E0;
        inline constexpr std::uint32_t pawn_velocity = 0x2E8;
        inline constexpr std::uint32_t radius = 0x2F0;
        inline constexpr std::uint32_t explosion_emitter = 0x2F8;
        inline constexpr std::uint32_t explosion_cue = 0x300;
        inline constexpr std::uint32_t explosion_shake = 0x308;
        inline constexpr std::uint32_t grenade_bounce_cue = 0x310;
        inline constexpr std::uint32_t byte_size = 0x318;
    }

    namespace hw2_claymore {
        inline constexpr std::uint32_t uber_graph_frame = 0x2A8;
        inline constexpr std::uint32_t static_mesh2 = 0x2B0;
        inline constexpr std::uint32_t static_mesh1 = 0x2B8;
        inline constexpr std::uint32_t child_actor = 0x2C0;
        inline constexpr std::uint32_t box = 0x2C8;
        inline constexpr std::uint32_t arrow = 0x2D0;
        inline constexpr std::uint32_t mesh = 0x2D8;
        inline constexpr std::uint32_t bp_health_component = 0x2E0;
        inline constexpr std::uint32_t radius = 0x2E8;
        inline constexpr std::uint32_t team = 0x2F0;
        inline constexpr std::uint32_t is_destroyed = 0x2F4;
        inline constexpr std::uint32_t instigator_controller = 0x2F8;
        inline constexpr std::uint32_t byte_size = 0x300;
    }

    namespace hw2_pickup_weapon {
        inline constexpr std::uint32_t uber_graph_frame = 0x2A8;
        inline constexpr std::uint32_t mesh = 0x2B0;
        inline constexpr std::uint32_t weapon_mesh = 0x2B8;
        inline constexpr std::uint32_t check_velocity_timer_handle = 0x2C0;
        inline constexpr std::uint32_t static_mesh = 0x2C8;
        inline constexpr std::uint32_t weapon_class = 0x2D0;
        inline constexpr std::uint32_t ammo = 0x2D8;
        inline constexpr std::uint32_t description = 0x2E0;
        inline constexpr std::uint32_t optic = 0x2F0;
        inline constexpr std::uint32_t magazine = 0x2F8;
        inline constexpr std::uint32_t stock = 0x300;
        inline constexpr std::uint32_t accessory = 0x308;
        inline constexpr std::uint32_t muzzle = 0x310;
        inline constexpr std::uint32_t underbarrel = 0x318;
        inline constexpr std::uint32_t canted_sight = 0x320;
        inline constexpr std::uint32_t default_attachments = 0x328;
        inline constexpr std::uint32_t initial_weapon_attachments = 0x360;
        inline constexpr std::uint32_t weapon_skin = 0x398;
        inline constexpr std::uint32_t is_full_mag = 0x3A0;
        inline constexpr std::uint32_t life_span = 0x3A8;
        inline constexpr std::uint32_t material_index = 0x3B0;
        inline constexpr std::uint32_t skin_color_a = 0x3B4;
        inline constexpr std::uint32_t skin_color_b = 0x3C4;
        inline constexpr std::uint32_t byte_size = 0x3D8;
    }

    namespace hw2_ammo_box {
        inline constexpr std::uint32_t uber_graph_frame = 0x2A8;
        inline constexpr std::uint32_t projectile_movement = 0x2B0;
        inline constexpr std::uint32_t scene = 0x2B8;
        inline constexpr std::uint32_t static_mesh = 0x2C0;
        inline constexpr std::uint32_t widget_actor = 0x2C8;
        inline constexpr std::uint32_t influence_sphere = 0x2D0;
        inline constexpr std::uint32_t is_active = 0x2D8;
        inline constexpr std::uint32_t check_velocity_timer_handle = 0x2E0;
        inline constexpr std::uint32_t is_used = 0x2E8;
        inline constexpr std::uint32_t byte_size = 0x2F0;
    }

    namespace hw2_medkit {
        inline constexpr std::uint32_t uber_graph_frame = 0x2A8;
        inline constexpr std::uint32_t projectile_movement = 0x2B0;
        inline constexpr std::uint32_t scene = 0x2B8;
        inline constexpr std::uint32_t static_mesh = 0x2C0;
        inline constexpr std::uint32_t widget_actor = 0x2C8;
        inline constexpr std::uint32_t influence_sphere = 0x2D0;
        inline constexpr std::uint32_t is_active = 0x2D8;
        inline constexpr std::uint32_t check_velocity_timer_handle = 0x2E0;
        inline constexpr std::uint32_t team = 0x2E8;
        inline constexpr std::uint32_t byte_size = 0x2F0;
    }

    namespace hw2_interaction {
        inline constexpr std::uint32_t uber_graph_frame = 0xC0;
        inline constexpr std::uint32_t interact_range = 0xC8;
        inline constexpr std::uint32_t current_interactable = 0xD0;
        inline constexpr std::uint32_t previous_interactable = 0xD8;
        inline constexpr std::uint32_t is_wants_to_interact = 0xE0;
        inline constexpr std::uint32_t check_for_interactable_timer_handle = 0xE8;
        inline constexpr std::uint32_t interacting_timer_handle = 0xF0;
        inline constexpr std::uint32_t is_interacting = 0xF8;
        inline constexpr std::uint32_t wb_interact_info = 0x100;
        inline constexpr std::uint32_t byte_size = 0x108;
    }

    namespace hw2_weapon_parts {
        inline constexpr std::uint32_t uber_graph_frame = 0xC0;
        inline constexpr std::uint32_t optic = 0xC8;
        inline constexpr std::uint32_t magazine = 0xD0;
        inline constexpr std::uint32_t stock = 0xD8;
        inline constexpr std::uint32_t accessory = 0xE0;
        inline constexpr std::uint32_t muzzle = 0xE8;
        inline constexpr std::uint32_t underbarrel = 0xF0;
        inline constexpr std::uint32_t weapon_fpp_mesh = 0xF8;
        inline constexpr std::uint32_t weapon_tpp_mesh = 0x100;
        inline constexpr std::uint32_t on_attachments_created = 0x108;
        inline constexpr std::uint32_t on_rep_attachment = 0x118;
        inline constexpr std::uint32_t attachments = 0x128;
        inline constexpr std::uint32_t default_attachments = 0x160;
        inline constexpr std::uint32_t canted_sight = 0x198;
        inline constexpr std::uint32_t byte_size = 0x1A0;
    }

    namespace hw2_magazine {
        inline constexpr std::uint32_t uber_graph_frame_bp_base_magazine_c = 0x2D8;
        inline constexpr std::uint32_t ammo_per_mag = 0x2E0;
        inline constexpr std::uint32_t mag_tactical_reload = 0x2E8;
        inline constexpr std::uint32_t mag_reload = 0x2F0;
        inline constexpr std::uint32_t tactical_reload = 0x2F8;
        inline constexpr std::uint32_t reload = 0x300;
        inline constexpr std::uint32_t am_fpp_tactical_reload_g1 = 0x308;
        inline constexpr std::uint32_t am_fpp_reload_g1 = 0x310;
        inline constexpr std::uint32_t am_tpp_tactical_reload_g1 = 0x318;
        inline constexpr std::uint32_t am_fpp_tactical_reload_g2 = 0x320;
        inline constexpr std::uint32_t am_fpp_reload_g2 = 0x328;
        inline constexpr std::uint32_t am_tpp_tactical_reload_g2 = 0x330;
        inline constexpr std::uint32_t byte_size = 0x338;
    }

    namespace hw2_optic {
        inline constexpr std::uint32_t aim_fov = 0x2D8;
        inline constexpr std::uint32_t byte_size = 0x2E0;
    }

    namespace hw2_damage_type {
        inline constexpr std::uint32_t weapon_name = 0x40;
        inline constexpr std::uint32_t is_can_headshot = 0x50;
        inline constexpr std::uint32_t kill_feed_bush = 0x60;
        inline constexpr std::uint32_t killedby_brush = 0x110;
        inline constexpr std::uint32_t hw2_ragdoll_launch_speed = 0x1C0;
        inline constexpr std::uint32_t hw2_ragdoll_lift_speed = 0x1C8;
        inline constexpr std::uint32_t byte_size = 0x1D0;
    }

    namespace hw2_operators_list {
        inline constexpr std::uint32_t operators = 0x28;
        inline constexpr std::uint32_t byte_size = 0x38;
    }

    namespace hw2_explosive_box {
        inline constexpr std::uint32_t uber_graph_frame = 0x2A8;
        inline constexpr std::uint32_t projectile_movement = 0x2B0;
        inline constexpr std::uint32_t scene = 0x2B8;
        inline constexpr std::uint32_t static_mesh = 0x2C0;
        inline constexpr std::uint32_t widget_actor = 0x2C8;
        inline constexpr std::uint32_t influence_sphere = 0x2D0;
        inline constexpr std::uint32_t is_active = 0x2D8;
        inline constexpr std::uint32_t check_velocity_timer_handle = 0x2E0;
        inline constexpr std::uint32_t is_used = 0x2E8;
        inline constexpr std::uint32_t byte_size = 0x2F0;
    }

    namespace hw2_reserve_ammo_layout {
        inline constexpr std::uint32_t ammo_type_5_1_cd642_d04_c3_bf1_f857_d9_ebbf2_f2_ef4_f5 = 0x0;
        inline constexpr std::uint32_t quantity_4_50296_d3443367_e8_fa683_faa68_e169687 = 0x4;
        inline constexpr std::uint32_t max_quantity_8_546_ea24_a4_ae28730_ef32_c0869_d82333_d = 0x8;
        inline constexpr std::uint32_t byte_size = 0xC;
    }

    namespace hw2_lethal_ammo_layout {
        inline constexpr std::uint32_t lethal_ammo_type_3_bcc14_ec64_c00310196_f0359459_ecaaff = 0x0;
        inline constexpr std::uint32_t quantity_6_f9_eb107_a4_f84_b89_ab44_dac88_dae78_f2_b = 0x4;
        inline constexpr std::uint32_t max_quantity_8_220_bf7_bc4814_e8_d7_bc71_ba994_b905318 = 0x8;
        inline constexpr std::uint32_t byte_size = 0xC;
    }

    namespace hw2_objective_base {
        inline constexpr std::uint32_t default_scene_root = 0x2A8;
        inline constexpr std::uint32_t objective_marker_icon = 0x2B0;
        inline constexpr std::uint32_t update_objective = 0x2B8;
        inline constexpr std::uint32_t objective_map_marker = 0x2C8;
        inline constexpr std::uint32_t id = 0x2D0;
        inline constexpr std::uint32_t byte_size = 0x2D8;
    }

    namespace hw2_capture_point {
        inline constexpr std::uint32_t uber_graph_frame = 0x2D8;
        inline constexpr std::uint32_t widget = 0x2E0;
        inline constexpr std::uint32_t flag_01 = 0x2E8;
        inline constexpr std::uint32_t decal = 0x2F0;
        inline constexpr std::uint32_t sphere = 0x2F8;
        inline constexpr std::uint32_t team_a_players = 0x300;
        inline constexpr std::uint32_t team_b_players = 0x304;
        inline constexpr std::uint32_t is_holder_team = 0x308;
        inline constexpr std::uint32_t point_id = 0x309;
        inline constexpr std::uint32_t game_state_ref = 0x310;
        inline constexpr std::uint32_t objetive_state = 0x318;
        inline constexpr std::uint32_t points_to_capture = 0x31C;
        inline constexpr std::uint32_t team_a_player_list = 0x320;
        inline constexpr std::uint32_t team_b_player_list = 0x330;
        inline constexpr std::uint32_t last_flag_state = 0x340;
        inline constexpr std::uint32_t points = 0x344;
        inline constexpr std::uint32_t conquest_progress_bar = 0x348;
        inline constexpr std::uint32_t match_state = 0x350;
        inline constexpr std::uint32_t byte_size = 0x358;
    }

    namespace hw2_capture_info {
        inline constexpr std::uint32_t state_2_81_fa77_cc4_ae111_f84_f0149_b1_b1443871 = 0x0;
        inline constexpr std::uint32_t progress_5_5_ba01_f4449811550_da999_b9902_bb9_cb3 = 0x4;
        inline constexpr std::uint32_t team_8_e6593_da3446_e94917_ae03_da63906_dee5 = 0x8;
        inline constexpr std::uint32_t byte_size = 0xC;
    }

    namespace hw2_snd_site {
        inline constexpr std::uint32_t uber_graph_frame = 0x2D8;
        inline constexpr std::uint32_t bomb_led = 0x2E0;
        inline constexpr std::uint32_t planted_bomb = 0x2E8;
        inline constexpr std::uint32_t destroyed_mesh = 0x2F0;
        inline constexpr std::uint32_t widget = 0x2F8;
        inline constexpr std::uint32_t bomb_mesh = 0x300;
        inline constexpr std::uint32_t bomb_timer_handle = 0x308;
        inline constexpr std::uint32_t bomb_sound_timer = 0x310;
        inline constexpr std::uint32_t bomb_state = 0x318;
        inline constexpr std::uint32_t phase = 0x31C;
        inline constexpr std::uint32_t bomb_time_to_explode = 0x320;
        inline constexpr std::uint32_t is_is_about_to_explode = 0x328;
        inline constexpr std::uint32_t team = 0x32C;
        inline constexpr std::uint32_t byte_size = 0x330;
    }

    namespace hw2_rush_site {
        inline constexpr std::uint32_t uber_graph_frame = 0x2D8;
        inline constexpr std::uint32_t point_light = 0x2E0;
        inline constexpr std::uint32_t widget = 0x2E8;
        inline constexpr std::uint32_t destroyed_mesh = 0x2F0;
        inline constexpr std::uint32_t bomb_mesh = 0x2F8;
        inline constexpr std::uint32_t rush_objective_time_line_new_track_0_ad5_b816_b4_a74_c103_d5_cbd98_eb74_f6247 = 0x300;
        inline constexpr std::uint32_t rush_objective_time_line_direction_ad5_b816_b4_a74_c103_d5_cbd98_eb74_f6247 = 0x304;
        inline constexpr std::uint32_t rush_objective_time_line = 0x308;
        inline constexpr std::uint32_t bomb_timer_handle = 0x310;
        inline constexpr std::uint32_t bomb_sound_timer = 0x318;
        inline constexpr std::uint32_t bomb_state = 0x320;
        inline constexpr std::uint32_t phase = 0x324;
        inline constexpr std::uint32_t bomb_time_to_explode = 0x328;
        inline constexpr std::uint32_t is_is_about_to_explode = 0x330;
        inline constexpr std::uint32_t team = 0x334;
        inline constexpr std::uint32_t byte_size = 0x338;
    }

    namespace hw2_snd_bomb {
        inline constexpr std::uint32_t uber_graph_frame = 0x2A8;
        inline constexpr std::uint32_t screen_mesh = 0x2B0;
        inline constexpr std::uint32_t sphere = 0x2B8;
        inline constexpr std::uint32_t widget = 0x2C0;
        inline constexpr std::uint32_t static_mesh = 0x2C8;
        inline constexpr std::uint32_t default_scene_root = 0x2D0;
        inline constexpr std::uint32_t is_bomb_taken = 0x2D8;
        inline constexpr std::uint32_t is_active = 0x2D9;
        inline constexpr std::uint32_t character = 0x2E0;
        inline constexpr std::uint32_t team = 0x2E8;
        inline constexpr std::uint32_t carrier = 0x2F0;
        inline constexpr std::uint32_t bomb_icon = 0x2F8;
        inline constexpr std::uint32_t last_carrier = 0x300;
        inline constexpr std::uint32_t byte_size = 0x308;
    }

    namespace hw2_conquest_state {
        inline constexpr std::uint32_t uber_graph_frame_bp_conquest_gs_c = 0x440;
        inline constexpr std::uint32_t point_a_holder = 0x448;
        inline constexpr std::uint32_t point_b_holder = 0x449;
        inline constexpr std::uint32_t point_c_holder = 0x44A;
        inline constexpr std::uint32_t point_a_info = 0x44C;
        inline constexpr std::uint32_t point_b_info = 0x458;
        inline constexpr std::uint32_t point_c_info = 0x464;
        inline constexpr std::uint32_t points_to_capture = 0x470;
        inline constexpr std::uint32_t points_to_capture_array = 0x478;
        inline constexpr std::uint32_t byte_size = 0x488;
    }

    namespace hw2_rush_state {
        inline constexpr std::uint32_t uber_graph_frame_bp_rush_gs_c = 0x440;
        inline constexpr std::uint32_t reinforcements = 0x448;
        inline constexpr std::uint32_t max_reinforcements = 0x44C;
        inline constexpr std::uint32_t bomb_ref = 0x450;
        inline constexpr std::uint32_t phase = 0x460;
        inline constexpr std::uint32_t final_phase = 0x464;
        inline constexpr std::uint32_t is_time_out = 0x468;
        inline constexpr std::uint32_t rush_update_reinforcements = 0x470;
        inline constexpr std::uint32_t byte_size = 0x480;
    }

    namespace hw2_snd_state {
        inline constexpr std::uint32_t uber_graph_frame_bp_search_and_destroy_gs_c = 0x440;
        inline constexpr std::uint32_t is_show_round_results = 0x448;
        inline constexpr std::uint32_t attacker_team = 0x450;
        inline constexpr std::uint32_t defender_team = 0x460;
        inline constexpr std::uint32_t attacker_team_updated = 0x470;
        inline constexpr std::uint32_t defender_team_updated = 0x480;
        inline constexpr std::uint32_t bomb = 0x490;
        inline constexpr std::uint32_t round_roster_ready = 0x498;
        inline constexpr std::uint32_t attack_site = 0x4A0;
        inline constexpr std::uint32_t defend_majority_site = 0x4A8;
        inline constexpr std::uint32_t attack_site_locked = 0x4B0;
        inline constexpr std::uint32_t plantable_sites = 0x4B8;
        inline constexpr std::uint32_t hw2_objective_shown = 0x4C8;
        inline constexpr std::uint32_t byte_size = 0x4D0;
    }

    namespace hw2_ffa_state {
        inline constexpr std::uint32_t uber_graph_frame_bp_free_for_all_gs_c = 0x440;
        inline constexpr std::uint32_t onest_player = 0x448;
        inline constexpr std::uint32_t onest_player_kills = 0x450;
        inline constexpr std::uint32_t twond_player = 0x458;
        inline constexpr std::uint32_t update_first_player = 0x460;
        inline constexpr std::uint32_t update_second_player = 0x470;
        inline constexpr std::uint32_t twond_player_kills = 0x480;
        inline constexpr std::uint32_t update_first_player_kills = 0x488;
        inline constexpr std::uint32_t update_second_player_kills = 0x498;
        inline constexpr std::uint32_t kills = 0x4A8;
        inline constexpr std::uint32_t byte_size = 0x4B0;
    }

    namespace hw2_spawn_system {
        inline constexpr std::uint32_t uber_graph_frame = 0xC0;
        inline constexpr std::uint32_t on_player_spawned = 0xC8;
        inline constexpr std::uint32_t spawns = 0xD8;
        inline constexpr std::uint32_t team0 = 0xE8;
        inline constexpr std::uint32_t team1 = 0xF8;
        inline constexpr std::uint32_t byte_size = 0x108;
    }

    namespace hw2_player_spawn {
        inline constexpr std::uint32_t capsule_collision = 0x2D8;
        inline constexpr std::uint32_t team = 0x2E0;
        inline constexpr std::uint32_t is_claimed = 0x2E4;
        inline constexpr std::uint32_t is_active = 0x2E5;
        inline constexpr std::uint32_t phase = 0x2E8;
        inline constexpr std::uint32_t byte_size = 0x2F0;
    }

    namespace hw2_spectator {
        inline constexpr std::uint32_t uber_graph_frame = 0x350;
        inline constexpr std::uint32_t spring_arm = 0x358;
        inline constexpr std::uint32_t camera = 0x360;
        inline constexpr std::uint32_t is_can_respawn = 0x368;
        inline constexpr std::uint32_t wb_spectator = 0x370;
        inline constexpr std::uint32_t current_spectate_target = 0x378;
        inline constexpr std::uint32_t current_spectate_health = 0x380;
        inline constexpr std::uint32_t teammate_spectate_candidates = 0x388;
        inline constexpr std::uint32_t enemy_spectate_candidates = 0x398;
        inline constexpr std::uint32_t is_has_unresolved_teammate_state = 0x3A8;
        inline constexpr std::uint32_t spectating_team = 0x3AC;
        inline constexpr std::uint32_t is_spectating_team_initialized = 0x3B0;
        inline constexpr std::uint32_t is_bomb_site_focused = 0x3B1;
        inline constexpr std::uint32_t byte_size = 0x3B8;
    }

    namespace hw2_operator_info {
        inline constexpr std::uint32_t operator_name = 0x28;
        inline constexpr std::uint32_t operator_icon = 0x30;
        inline constexpr std::uint32_t operator_class = 0x58;
        inline constexpr std::uint32_t team = 0x80;
        inline constexpr std::uint32_t skeletal_mesh = 0x88;
        inline constexpr std::uint32_t is_locked = 0xB0;
        inline constexpr std::uint32_t level_to_unlock = 0xB4;
        inline constexpr std::uint32_t is_use_for_bots = 0xB8;
        inline constexpr std::uint32_t byte_size = 0xC0;
    }

    namespace hw2_migration {
        inline constexpr std::uint32_t snapshot_interval_seconds = 0xC0;
        inline constexpr std::uint32_t resume_delay_seconds = 0xC4;
        inline constexpr std::uint32_t stats_interval_seconds = 0xC8;
        inline constexpr std::uint32_t reconcile_window_seconds = 0xCC;
        inline constexpr std::uint32_t host_silence_seconds = 0xD0;
        inline constexpr std::uint32_t host_silence_check_seconds = 0xD4;
        inline constexpr std::uint32_t host_silence_arm_delay_seconds = 0xD8;
        inline constexpr std::uint32_t snapshot = 0xE0;
        inline constexpr std::uint32_t is_migration_pending = 0x1D0;
        inline constexpr std::uint32_t stats_snapshot = 0x1D8;
        inline constexpr std::uint32_t byte_size = 0x3D8;
    }

    namespace hw2_progression_full {
        inline constexpr std::uint32_t uber_graph_frame = 0xC0;
        inline constexpr std::uint32_t stats = 0xC8;
        inline constexpr std::uint32_t slot_name = 0x118;
        inline constexpr std::uint32_t attachment_challenges = 0x128;
        inline constexpr std::uint32_t longshot_distances = 0x138;
        inline constexpr std::uint32_t point_blank_distance = 0x188;
        inline constexpr std::uint32_t pending_unlocks = 0x190;
        inline constexpr std::uint32_t is_loaded = 0x1A0;
        inline constexpr std::uint32_t on_progression_changed = 0x1A8;
        inline constexpr std::uint32_t is_demo_mode = 0x1B8;
        inline constexpr std::uint32_t byte_size = 0x1C0;
    }

    namespace hw2_mission_set {
        inline constexpr std::uint32_t uber_graph_frame = 0xC0;
        inline constexpr std::uint32_t missions = 0xC8;
        inline constexpr std::uint32_t slot_name = 0xD8;
        inline constexpr std::uint32_t byte_size = 0xE8;
    }

    namespace hw2_mission_layout {
        inline constexpr std::uint32_t mision_info_2_6_a274_e4_c4609_cb463017_a5_b1_f19_a2_f0_f = 0x0;
        inline constexpr std::uint32_t current_progress_5_21647_abd4_dab519_e8_c558382_d987_cad9 = 0x8;
        inline constexpr std::uint32_t is_completed_7_7_cd6_e3_f84_d1_f18501_b50_d5_b5_e48103_c6 = 0xC;
        inline constexpr std::uint32_t byte_size = 0x10;
    }

    namespace hw2_mission_info {
        inline constexpr std::uint32_t id = 0x28;
        inline constexpr std::uint32_t description_start = 0x30;
        inline constexpr std::uint32_t target = 0x40;
        inline constexpr std::uint32_t description_end = 0x48;
        inline constexpr std::uint32_t exp_reward = 0x58;
        inline constexpr std::uint32_t is_needs_wins = 0x5C;
        inline constexpr std::uint32_t is_needs_kills = 0x5D;
        inline constexpr std::uint32_t is_need_specific_weapon = 0x5E;
        inline constexpr std::uint32_t weapon_needed = 0x5F;
        inline constexpr std::uint32_t is_needs_specific_game_mode = 0x60;
        inline constexpr std::uint32_t game_mode_needed = 0x61;
        inline constexpr std::uint32_t byte_size = 0x68;
    }

    namespace hw2_online_settings {
        inline constexpr std::uint32_t is_enable_cloud_progression = 0x38;
        inline constexpr std::uint32_t api_base_url = 0x40;
        inline constexpr std::uint32_t steam_identity = 0x50;
        inline constexpr std::uint32_t http_timeout_seconds = 0x60;
        inline constexpr std::uint32_t is_upload_crash_reports = 0x64;
        inline constexpr std::uint32_t is_upload_crash_logs = 0x65;
        inline constexpr std::uint32_t is_upload_network_logs = 0x66;
        inline constexpr std::uint32_t is_show_crash_notice = 0x67;
        inline constexpr std::uint32_t profile_put_debounce_seconds = 0x68;
        inline constexpr std::uint32_t reauth_margin_seconds = 0x6C;
        inline constexpr std::uint32_t retry_backoff_min_seconds = 0x70;
        inline constexpr std::uint32_t retry_backoff_max_seconds = 0x74;
        inline constexpr std::uint32_t is_show_cached_cloud_level = 0x78;
        inline constexpr std::uint32_t is_sync_choices_to_cloud = 0x79;
        inline constexpr std::uint32_t is_restore_choices_from_cloud = 0x7A;
        inline constexpr std::uint32_t loadout_strip_grace_seconds = 0x7C;
        inline constexpr std::uint32_t is_sync_loadout_state_to_server = 0x80;
        inline constexpr std::uint32_t loadout_sync_interval_seconds = 0x84;
        inline constexpr std::uint32_t is_server_kill_stats = 0x88;
        inline constexpr std::uint32_t kill_aim_grace_seconds = 0x8C;
        inline constexpr std::uint32_t is_retire_legacy_missions = 0x90;
        inline constexpr std::uint32_t is_restore_missions_from_cloud = 0x91;
        inline constexpr std::uint32_t is_prompt_before_joining_invite = 0x92;
        inline constexpr std::uint32_t is_allow_inviting_offline_friends = 0x93;
        inline constexpr std::uint32_t invite_accept_key = 0x94;
        inline constexpr std::uint32_t invite_decline_key = 0x9C;
        inline constexpr std::uint32_t is_hide_join_game_when_empty = 0xA4;
        inline constexpr std::uint32_t server_probe_interval_seconds = 0xA8;
        inline constexpr std::uint32_t server_probe_max_results = 0xAC;
        inline constexpr std::uint32_t server_browser_max_results = 0xB0;
        inline constexpr std::uint32_t is_use_matchmaker = 0xB4;
        inline constexpr std::uint32_t matchmaker_heartbeat_seconds = 0xB8;
        inline constexpr std::uint32_t is_predict_in_game_ping = 0xBC;
        inline constexpr std::uint32_t ping_host_frame_factor = 0xC0;
        inline constexpr std::uint32_t ping_local_frame_factor = 0xC4;
        inline constexpr std::uint32_t is_live_lobby_refresh = 0xC8;
        inline constexpr std::uint32_t live_refresh_visible_seconds = 0xCC;
        inline constexpr std::uint32_t live_refresh_offscreen_seconds = 0xD0;
        inline constexpr std::uint32_t live_refresh_max_requests_per_second = 0xD4;
        inline constexpr std::uint32_t is_measure_server_ping = 0xD8;
        inline constexpr std::uint32_t ping_probe_interval_seconds = 0xDC;
        inline constexpr std::uint32_t ping_probe_give_up_seconds = 0xE0;
        inline constexpr std::uint32_t ping_probe_max_hosts = 0xE4;
        inline constexpr std::uint32_t ping_probe_max_replies_per_peer_per_second = 0xE8;
        inline constexpr std::uint32_t quick_play_preferred_ping_ms = 0xEC;
        inline constexpr std::uint32_t quick_play_max_ping_ms = 0xF0;
        inline constexpr std::uint32_t quick_play_min_open_slots = 0xF4;
        inline constexpr std::uint32_t quick_play_failed_lobby_seconds = 0xF8;
        inline constexpr std::uint32_t quick_play_full_lobby_seconds = 0xFC;
        inline constexpr std::uint32_t quick_play_join_budget_seconds = 0x100;
        inline constexpr std::uint32_t version_check_timeout_seconds = 0x104;
        inline constexpr std::uint32_t version_gate_reuse_seconds = 0x108;
        inline constexpr std::uint32_t version_recheck_interval_seconds = 0x10C;
        inline constexpr std::uint32_t version_popup_maps = 0x110;
        inline constexpr std::uint32_t steam_library_url = 0x120;
        inline constexpr std::uint32_t steam_store_fallback_url = 0x130;
        inline constexpr std::uint32_t steam_app_id = 0x140;
        inline constexpr std::uint32_t is_quit_after_opening_steam = 0x150;
        inline constexpr std::uint32_t quit_delay_after_opening_steam = 0x154;
        inline constexpr std::uint32_t is_enable_reports = 0x158;
        inline constexpr std::uint32_t is_enforce_bans_as_host = 0x159;
        inline constexpr std::uint32_t host_ban_check_delay_seconds = 0x15C;
        inline constexpr std::uint32_t host_ban_recheck_seconds = 0x160;
        inline constexpr std::uint32_t ban_appeal_url = 0x168;
        inline constexpr std::uint32_t is_use_dev_steam_id = 0x178;
        inline constexpr std::uint32_t dev_steam_id = 0x180;
        inline constexpr std::uint32_t is_verbose_http_logging = 0x190;
        inline constexpr std::uint32_t byte_size = 0x198;
    }

    namespace hw2_weapon_info {
        inline constexpr std::uint32_t weapon_name = 0x28;
        inline constexpr std::uint32_t icon = 0x30;
        inline constexpr std::uint32_t weapon_bp = 0x58;
        inline constexpr std::uint32_t weapon_skins = 0x80;
        inline constexpr std::uint32_t weapon_stats = 0x90;
        inline constexpr std::uint32_t weapon_mesh = 0xC0;
        inline constexpr std::uint32_t default_attachments = 0xE8;
        inline constexpr std::uint32_t weapon_type = 0x120;
        inline constexpr std::uint32_t is_can_use_attachments = 0x121;
        inline constexpr std::uint32_t picatiny = 0x128;
        inline constexpr std::uint32_t unlock_level = 0x150;
        inline constexpr std::uint32_t skin_mirror_slots = 0x158;
        inline constexpr std::uint32_t skin_extra_skin_materials = 0x168;
        inline constexpr std::uint32_t skin_extra_part_materials = 0x178;
        inline constexpr std::uint32_t skin_extra_mesh_assets = 0x188;
        inline constexpr std::uint32_t t_pp_hand_offset = 0x1A0;
        inline constexpr std::uint32_t t_pp_menu_pose = 0x200;
        inline constexpr std::uint32_t hw2_stock_mesh = 0x208;
        inline constexpr std::uint32_t hw2_no_stock_mesh = 0x210;
        inline constexpr std::uint32_t hw2_no_stock_attachments = 0x218;
        inline constexpr std::uint32_t byte_size = 0x230;
    }

    namespace hw2_skin_info {
        inline constexpr std::uint32_t skin_name = 0x28;
        inline constexpr std::uint32_t icon = 0x30;
        inline constexpr std::uint32_t material = 0x58;
        inline constexpr std::uint32_t material_index = 0x80;
        inline constexpr std::uint32_t unlock_kills = 0x84;
        inline constexpr std::uint32_t is_supports_custom_colors = 0x88;
        inline constexpr std::uint32_t default_color_primary = 0x8C;
        inline constexpr std::uint32_t default_color_secondary = 0x9C;
        inline constexpr std::uint32_t byte_size = 0xB0;
    }

    namespace hw2_perk_info {
        inline constexpr std::uint32_t perk_name = 0x28;
        inline constexpr std::uint32_t perk_icon = 0x30;
        inline constexpr std::uint32_t perk_type = 0x58;
        inline constexpr std::uint32_t unlock_level = 0x5C;
        inline constexpr std::uint32_t byte_size = 0x60;
    }

    namespace hw2_field_upgrade_info {
        inline constexpr std::uint32_t icon = 0x28;
        inline constexpr std::uint32_t name_0 = 0x50;
        inline constexpr std::uint32_t field_upgrade_type = 0x58;
        inline constexpr std::uint32_t unlock_level = 0x5C;
        inline constexpr std::uint32_t byte_size = 0x60;
    }

    namespace hw2_lethal_info {
        inline constexpr std::uint32_t lethal_type = 0x28;
        inline constexpr std::uint32_t icon = 0x30;
        inline constexpr std::uint32_t lethal_bp = 0x58;
        inline constexpr std::uint32_t lethal_mesh = 0x80;
        inline constexpr std::uint32_t unlock_level = 0xA8;
        inline constexpr std::uint32_t byte_size = 0xB0;
    }

    namespace hw2_save_level {
        inline constexpr std::uint32_t level = 0x28;
        inline constexpr std::uint32_t experience = 0x2C;
        inline constexpr std::uint32_t byte_size = 0x30;
    }

    namespace hw2_save_game {
        inline constexpr std::uint32_t uber_graph_frame = 0x28;
        inline constexpr std::uint32_t player_settings = 0x30;
        inline constexpr std::uint32_t loadouts = 0xC0;
        inline constexpr std::uint32_t operator_class_alpha = 0xD0;
        inline constexpr std::uint32_t operator_class_beta = 0xD8;
        inline constexpr std::uint32_t kill_streak_accessory = 0xE0;
        inline constexpr std::uint32_t is_toggle_aim = 0xE8;
        inline constexpr std::uint32_t is_toggle_aim_sniper = 0xE9;
        inline constexpr std::uint32_t field_upgrade = 0xEA;
        inline constexpr std::uint32_t selected_loadout_index = 0xEC;
        inline constexpr std::uint32_t controller_sensitivity = 0xF0;
        inline constexpr std::uint32_t controller_ads_sensitivity = 0xF8;
        inline constexpr std::uint32_t controller_scope_sensitivity = 0x100;
        inline constexpr std::uint32_t is_controller_vibration = 0x108;
        inline constexpr std::uint32_t is_controller_aim_assist = 0x109;
        inline constexpr std::uint32_t loadout_skin_colors = 0x110;
        inline constexpr std::uint32_t hw2_field_of_view = 0x120;
        inline constexpr std::uint32_t byte_size = 0x128;
    }

    namespace hw2_save_streaks {
        inline constexpr std::uint32_t equipped_mask = 0x28;
        inline constexpr std::uint32_t byte_size = 0x30;
    }

    namespace hw2_save_menu {
        inline constexpr std::uint32_t favorite_loadout_index = 0x28;
        inline constexpr std::uint32_t preview_operator_team = 0x2C;
        inline constexpr std::uint32_t version = 0x30;
        inline constexpr std::uint32_t byte_size = 0x38;
    }

    namespace hw2_cine_settings {
        inline constexpr std::uint32_t is_hotkeys_enabled = 0x38;
        inline constexpr std::uint32_t is_hotkeys_work_while_paused = 0x39;
        inline constexpr std::uint32_t record_key = 0x40;
        inline constexpr std::uint32_t tik_tok_record_key = 0x58;
        inline constexpr std::uint32_t tik_tok_high_res_record_key = 0x70;
        inline constexpr std::uint32_t is_tik_tok_high_res_record_key_needs_shift = 0x88;
        inline constexpr std::uint32_t drop_camera_key = 0x90;
        inline constexpr std::uint32_t record_camera_key = 0xA8;
        inline constexpr std::uint32_t cycle_camera_key = 0xC0;
        inline constexpr std::uint32_t screenshot_key = 0xD8;
        inline constexpr std::uint32_t god_mode_key = 0xF0;
        inline constexpr std::uint32_t god_mode_tap_window = 0x108;
        inline constexpr std::uint32_t frame_rate = 0x10C;
        inline constexpr std::uint32_t capture_width = 0x110;
        inline constexpr std::uint32_t capture_height = 0x114;
        inline constexpr std::uint32_t tik_tok_capture_width = 0x118;
        inline constexpr std::uint32_t tik_tok_capture_height = 0x11C;
        inline constexpr std::uint32_t tik_tok_high_res_capture_width = 0x120;
        inline constexpr std::uint32_t tik_tok_high_res_capture_height = 0x124;
        inline constexpr std::uint32_t tik_tok_high_res_bitrate_mbps = 0x128;
        inline constexpr std::uint32_t tik_tok_high_res_max_bitrate_mbps = 0x12C;
        inline constexpr std::uint32_t tik_tok_high_res_game_screen_percentage = 0x130;
        inline constexpr std::uint32_t is_tik_tok_high_res_locked_frame_rate = 0x134;
        inline constexpr std::uint32_t is_tik_tok_high_res_high_fidelity_lighting = 0x135;
        inline constexpr std::uint32_t is_tik_tok_circular_scope = 0x136;
        inline constexpr std::uint32_t tik_tok_scope_widget_class = 0x138;
        inline constexpr std::uint32_t tik_tok_scope_image_name = 0x158;
        inline constexpr std::uint32_t tik_tok_scope_texture = 0x160;
        inline constexpr std::uint32_t tik_tok_scope_width_fraction = 0x180;
        inline constexpr std::uint32_t camera_capture_width = 0x184;
        inline constexpr std::uint32_t camera_capture_height = 0x188;
        inline constexpr std::uint32_t camera_supersample = 0x18C;
        inline constexpr std::uint32_t is_sync_groom_hair = 0x190;
        inline constexpr std::uint32_t encoder = 0x191;
        inline constexpr std::uint32_t quality = 0x194;
        inline constexpr std::uint32_t is_cap_frame_rate_while_recording = 0x198;
        inline constexpr std::uint32_t is_locked_frame_rate = 0x199;
        inline constexpr std::uint32_t is_camera_temporal_aa = 0x19A;
        inline constexpr std::uint32_t camera_global_illumination = 0x19B;
        inline constexpr std::uint32_t is_camera_cinematic_quality = 0x19C;
        inline constexpr std::uint32_t camera_exposure = 0x19D;
        inline constexpr std::uint32_t camera_exposure_bias = 0x1A0;
        inline constexpr std::uint32_t camera_exposure_speed_up = 0x1A4;
        inline constexpr std::uint32_t camera_exposure_speed_down = 0x1A8;
        inline constexpr std::uint32_t is_camera_high_fidelity_lighting = 0x1AC;
        inline constexpr std::uint32_t is_camera_depth_of_field = 0x1AD;
        inline constexpr std::uint32_t is_camera_motion_blur = 0x1AE;
        inline constexpr std::uint32_t camera_motion_blur_amount = 0x1B0;
        inline constexpr std::uint32_t camera_motion_blur_max = 0x1B4;
        inline constexpr std::uint32_t is_record_audio = 0x1B8;
        inline constexpr std::uint32_t audio_bitrate_kbps = 0x1BC;
        inline constexpr std::uint32_t is_offline_audio_for_locked_takes = 0x1C0;
        inline constexpr std::uint32_t is_keep_locked_take_wav = 0x1C1;
        inline constexpr std::uint32_t offline_audio_buffer_frames = 0x1C4;
        inline constexpr std::uint32_t is_hide_ui = 0x1C8;
        inline constexpr std::uint32_t visible_widget_class_names = 0x1D0;
        inline constexpr std::uint32_t drop_camera_type = 0x1E0;
        inline constexpr std::uint32_t drop_camera_folder = 0x1E4;
        inline constexpr std::uint32_t screenshot_width = 0x1EC;
        inline constexpr std::uint32_t screenshot_height = 0x1F0;
        inline constexpr std::uint32_t is_screenshot_match_viewport_aspect = 0x1F4;
        inline constexpr std::uint32_t is_screenshot_ultra_quality = 0x1F5;
        inline constexpr std::uint32_t screenshot_convergence_frames = 0x1F8;
        inline constexpr std::uint32_t screenshot_warm_up_frames = 0x1FC;
        inline constexpr std::uint32_t is_screenshot_freeze_world = 0x200;
        inline constexpr std::uint32_t is_screenshot_flush_texture_streaming = 0x201;
        inline constexpr std::uint32_t is_screenshot_unpause_for_capture = 0x202;
        inline constexpr std::uint32_t screenshot_pause_policy = 0x203;
        inline constexpr std::uint32_t screenshot_visible_widgets = 0x208;
        inline constexpr std::uint32_t screenshot_directory = 0x218;
        inline constexpr std::uint32_t output_directory = 0x228;
        inline constexpr std::uint32_t f_fmpeg_path = 0x238;
        inline constexpr std::uint32_t is_keep_intermediate_files = 0x248;
        inline constexpr std::uint32_t byte_size = 0x250;
    }

    namespace hw2_replay_settings {
        inline constexpr std::uint32_t is_auto_record_matches = 0x38;
        inline constexpr std::uint32_t max_retained_replays = 0x3C;
        inline constexpr std::uint32_t never_record_maps = 0x40;
        inline constexpr std::uint32_t is_hotkeys_enabled = 0x50;
        inline constexpr std::uint32_t record_key = 0x58;
        inline constexpr std::uint32_t highlight_key = 0x70;
        inline constexpr std::uint32_t camera_speed = 0x88;
        inline constexpr std::uint32_t camera_boost_multiplier = 0x8C;
        inline constexpr std::uint32_t seek_step_seconds = 0x90;
        inline constexpr std::uint32_t is_show_playback_readout = 0x94;
        inline constexpr std::uint32_t control_bar_toggle_key = 0x98;
        inline constexpr std::uint32_t control_bar_inactive_opacity = 0xB0;
        inline constexpr std::uint32_t grade_panel_toggle_key = 0xB8;
        inline constexpr std::uint32_t is_restore_last_grade = 0xD0;
        inline constexpr std::uint32_t roster_panel_toggle_key = 0xD8;
        inline constexpr std::uint32_t follow_mode_key = 0xF0;
        inline constexpr std::uint32_t unfollow_key = 0x108;
        inline constexpr std::uint32_t follow_pan_key = 0x120;
        inline constexpr std::uint32_t follow_pan_depth_key = 0x138;
        inline constexpr std::uint32_t follow_pan_speed = 0x150;
        inline constexpr std::uint32_t is_invert_follow_pan = 0x154;
        inline constexpr std::uint32_t follow_distance = 0x158;
        inline constexpr std::uint32_t min_follow_distance = 0x15C;
        inline constexpr std::uint32_t max_follow_distance = 0x160;
        inline constexpr std::uint32_t follow_distance_step = 0x164;
        inline constexpr std::uint32_t follow_focus_height = 0x168;
        inline constexpr std::uint32_t follow_smooth_time = 0x16C;
        inline constexpr std::uint32_t chase_pitch = 0x170;
        inline constexpr std::uint32_t is_follow_smooth_by_default = 0x174;
        inline constexpr std::uint32_t is_follow_avoid_geometry = 0x175;
        inline constexpr std::uint32_t is_flying_breaks_follow = 0x176;
        inline constexpr std::uint32_t tactile_movement_time = 0x178;
        inline constexpr std::uint32_t smooth_movement_time = 0x17C;
        inline constexpr std::uint32_t look_smoothing_time = 0x180;
        inline constexpr std::uint32_t is_smooth_movement_by_default = 0x184;
        inline constexpr std::uint32_t is_smooth_look_by_default = 0x185;
        inline constexpr std::uint32_t smooth_movement_key = 0x188;
        inline constexpr std::uint32_t smooth_look_key = 0x1A0;
        inline constexpr std::uint32_t speed_adjust_key = 0x1B8;
        inline constexpr std::uint32_t camera_speed_step = 0x1D0;
        inline constexpr std::uint32_t min_camera_speed = 0x1D4;
        inline constexpr std::uint32_t max_camera_speed = 0x1D8;
        inline constexpr std::uint32_t zoom_step_scale = 0x1DC;
        inline constexpr std::uint32_t sequence_frame_rate = 0x1E0;
        inline constexpr std::uint32_t byte_size = 0x1E8;
    }

    namespace hw2_replay_file {
        inline constexpr std::uint32_t name = 0x0;
        inline constexpr std::uint32_t recorded = 0x10;
        inline constexpr std::uint32_t size_bytes = 0x18;
        inline constexpr std::uint32_t byte_size = 0x20;
    }

    namespace hw2_voice_settings {
        inline constexpr std::uint32_t is_voice_chat_allowed = 0x38;
        inline constexpr std::uint32_t push_to_talk_action = 0x40;
        inline constexpr std::uint32_t push_to_talk_context = 0x68;
        inline constexpr std::uint32_t fallback_push_to_talk_key = 0x90;
        inline constexpr std::uint32_t volume_sound_mix = 0xA8;
        inline constexpr std::uint32_t voice_sound_class = 0xD0;
        inline constexpr std::uint32_t push_to_talk_gate_threshold = 0xF8;
        inline constexpr std::uint32_t open_mic_threshold_scale = 0xFC;
        inline constexpr std::uint32_t max_mic_gain = 0x100;
        inline constexpr std::uint32_t is_default_voice_chat_enabled = 0x104;
        inline constexpr std::uint32_t default_voice_mode = 0x105;
        inline constexpr std::uint32_t default_voice_channel = 0x106;
        inline constexpr std::uint32_t default_voice_volume = 0x108;
        inline constexpr std::uint32_t default_mic_volume = 0x10C;
        inline constexpr std::uint32_t default_open_mic_threshold = 0x110;
        inline constexpr std::uint32_t speaker_icon = 0x118;
        inline constexpr std::uint32_t talkers_margin = 0x140;
        inline constexpr std::uint32_t max_talkers_shown = 0x150;
        inline constexpr std::uint32_t is_show_local_talker = 0x154;
        inline constexpr std::uint32_t talkers_z_order = 0x158;
        inline constexpr std::uint32_t talking_hold_seconds = 0x15C;
        inline constexpr std::uint32_t byte_size = 0x160;
    }

    namespace hw2_voice_save {
        inline constexpr std::uint32_t version = 0x28;
        inline constexpr std::uint32_t is_enabled = 0x2C;
        inline constexpr std::uint32_t mode = 0x2D;
        inline constexpr std::uint32_t channel = 0x2E;
        inline constexpr std::uint32_t input_device = 0x30;
        inline constexpr std::uint32_t voice_volume = 0x40;
        inline constexpr std::uint32_t mic_volume = 0x44;
        inline constexpr std::uint32_t open_mic_threshold = 0x48;
        inline constexpr std::uint32_t byte_size = 0x50;
    }

    namespace hw2_voice_system {
        inline constexpr std::uint32_t saved_object = 0x50;
        inline constexpr std::uint32_t push_to_talk_action = 0x160;
        inline constexpr std::uint32_t talkers_widget = 0x408;
        inline constexpr std::uint32_t speaker_icon = 0x418;
        inline constexpr std::uint32_t settings_rows = 0x420;
        inline constexpr std::uint32_t byte_size = 0x478;
    }

    namespace hw2_audio_output {
        inline constexpr std::uint32_t is_manage_output_device = 0x38;
        inline constexpr std::uint32_t is_recover_from_null_device = 0x39;
        inline constexpr std::uint32_t null_recovery_delay_seconds = 0x3C;
        inline constexpr std::uint32_t swap_grace_seconds = 0x40;
        inline constexpr std::uint32_t poll_interval_seconds = 0x44;
        inline constexpr std::uint32_t is_auto_audio_backend = 0x48;
        inline constexpr std::uint32_t is_show_audio_mode_row = 0x49;
        inline constexpr std::uint32_t is_na_n_guard = 0x4A;
        inline constexpr std::uint32_t signal_report_seconds = 0x4C;
        inline constexpr std::uint32_t max_label_length = 0x50;
        inline constexpr std::uint32_t byte_size = 0x58;
    }

    namespace hw2_friends {
        inline constexpr std::uint32_t on_friends_refreshed = 0x30;
        inline constexpr std::uint32_t party_actions = 0xE8;
        inline constexpr std::uint32_t friends = 0x100;
        inline constexpr std::uint32_t list_widget = 0x120;
        inline constexpr std::uint32_t menu_list_widget = 0x128;
        inline constexpr std::uint32_t invite_screen = 0x130;
        inline constexpr std::uint32_t row_widgets = 0x148;
        inline constexpr std::uint32_t row_handlers = 0x158;
        inline constexpr std::uint32_t debug_server_rows = 0x280;
        inline constexpr std::uint32_t byte_size = 0x2A0;
    }

    namespace hw2_friend_entry {
        inline constexpr std::uint32_t display_name = 0x0;
        inline constexpr std::uint32_t status = 0x10;
        inline constexpr std::uint32_t status_text = 0x18;
        inline constexpr std::uint32_t is_joinable = 0x28;
        inline constexpr std::uint32_t friend_index = 0x2C;
        inline constexpr std::uint32_t session_id = 0x30;
        inline constexpr std::uint32_t byte_size = 0x40;
    }

    namespace hw2_input_settings {
        inline constexpr std::uint32_t base_yaw_rate = 0x38;
        inline constexpr std::uint32_t base_pitch_rate = 0x3C;
        inline constexpr std::uint32_t inner_dead_zone = 0x40;
        inline constexpr std::uint32_t outer_dead_zone = 0x44;
        inline constexpr std::uint32_t response_exponent = 0x48;
        inline constexpr std::uint32_t acceleration_multiplier = 0x4C;
        inline constexpr std::uint32_t acceleration_start_delay = 0x50;
        inline constexpr std::uint32_t acceleration_ramp_time = 0x54;
        inline constexpr std::uint32_t acceleration_engage_threshold = 0x58;
        inline constexpr std::uint32_t stick_device_activation = 0x5C;
        inline constexpr std::uint32_t is_scale_stick_with_zoom = 0x60;
        inline constexpr std::uint32_t default_sensitivity = 0x64;
        inline constexpr std::uint32_t default_ads_sensitivity = 0x68;
        inline constexpr std::uint32_t default_scope_sensitivity = 0x6C;
        inline constexpr std::uint32_t is_default_vibration = 0x70;
        inline constexpr std::uint32_t is_default_aim_assist = 0x71;
        inline constexpr std::uint32_t default_field_of_view = 0x74;
        inline constexpr std::uint32_t min_field_of_view = 0x78;
        inline constexpr std::uint32_t max_field_of_view = 0x7C;
        inline constexpr std::uint32_t is_weapon_field_of_view_follows = 0x80;
        inline constexpr std::uint32_t is_hide_first_person_legs_at_low_quality = 0x81;
        inline constexpr std::uint32_t hide_first_person_legs_at_or_below_view_distance_quality = 0x84;
        inline constexpr std::uint32_t first_person_leg_components = 0x88;
        inline constexpr std::uint32_t is_hide_pawn_until_weapon_ready = 0x98;
        inline constexpr std::uint32_t pawn_weapon_ready_timeout_seconds = 0x9C;
        inline constexpr std::uint32_t is_restore_stranded_pawn_view = 0xA0;
        inline constexpr std::uint32_t stranded_pawn_view_grace_seconds = 0xA4;
        inline constexpr std::uint32_t unacknowledged_pawn_view_grace_seconds = 0xA8;
        inline constexpr std::uint32_t is_aim_assist_allowed = 0xAC;
        inline constexpr std::uint32_t max_target_distance = 0xB0;
        inline constexpr std::uint32_t rotation_cone_degrees = 0xB4;
        inline constexpr std::uint32_t slowdown_cone_degrees = 0xB8;
        inline constexpr std::uint32_t slowdown_scale = 0xBC;
        inline constexpr std::uint32_t rotation_degrees_per_second = 0xC0;
        inline constexpr std::uint32_t rotation_falloff_exponent = 0xC4;
        inline constexpr std::uint32_t rotation_min_motion = 0xC8;
        inline constexpr std::uint32_t rotation_reference_speed = 0xCC;
        inline constexpr std::uint32_t target_height_fraction = 0xD0;
        inline constexpr std::uint32_t is_require_line_of_sight = 0xD4;
        inline constexpr std::uint32_t global_rumble_scale = 0xD8;
        inline constexpr std::uint32_t fire_large_intensity = 0xDC;
        inline constexpr std::uint32_t fire_small_intensity = 0xE0;
        inline constexpr std::uint32_t fire_duration = 0xE4;
        inline constexpr std::uint32_t fire_heavy_large_intensity = 0xE8;
        inline constexpr std::uint32_t fire_heavy_small_intensity = 0xEC;
        inline constexpr std::uint32_t fire_heavy_duration = 0xF0;
        inline constexpr std::uint32_t damage_large_intensity = 0xF4;
        inline constexpr std::uint32_t damage_small_intensity = 0xF8;
        inline constexpr std::uint32_t damage_duration = 0xFC;
        inline constexpr std::uint32_t damage_full_strength_fraction = 0x100;
        inline constexpr std::uint32_t damage_minimum_scale = 0x104;
        inline constexpr std::uint32_t explosion_large_intensity = 0x108;
        inline constexpr std::uint32_t explosion_small_intensity = 0x10C;
        inline constexpr std::uint32_t explosion_duration = 0x110;
        inline constexpr std::uint32_t death_large_intensity = 0x114;
        inline constexpr std::uint32_t death_small_intensity = 0x118;
        inline constexpr std::uint32_t death_duration = 0x11C;
        inline constexpr std::uint32_t hitmarker_small_intensity = 0x120;
        inline constexpr std::uint32_t hitmarker_duration = 0x124;
        inline constexpr std::uint32_t rebindable_mapping_contexts = 0x128;
        inline constexpr std::uint32_t mutually_exclusive_mapping_contexts = 0x138;
        inline constexpr std::uint32_t hidden_keybind_rows = 0x148;
        inline constexpr std::uint32_t reserved_keys = 0x158;
        inline constexpr std::uint32_t hidden_gamepad_keybind_rows = 0x168;
        inline constexpr std::uint32_t reserved_gamepad_keys = 0x178;
        inline constexpr std::uint32_t legacy_settings_save_slot = 0x188;
        inline constexpr std::uint32_t keybind_notice_seconds = 0x198;
        inline constexpr std::uint32_t byte_size = 0x1A0;
    }

    namespace hw2_input_system {
        inline constexpr std::uint32_t sensitivity = 0x30;
        inline constexpr std::uint32_t ads_sensitivity = 0x34;
        inline constexpr std::uint32_t scope_sensitivity = 0x38;
        inline constexpr std::uint32_t is_vibration_enabled = 0x3C;
        inline constexpr std::uint32_t is_aim_assist_enabled = 0x3D;
        inline constexpr std::uint32_t field_of_view = 0x40;
        inline constexpr std::uint32_t byte_size = 0x78;
    }

    namespace hw2_third_person {
        inline constexpr std::uint32_t is_enabled = 0x38;
        inline constexpr std::uint32_t pivot_height = 0x3C;
        inline constexpr std::uint32_t pivot_height_smoothing_speed = 0x40;
        inline constexpr std::uint32_t hip_distance = 0x44;
        inline constexpr std::uint32_t hip_shoulder_offset = 0x48;
        inline constexpr std::uint32_t hip_height = 0x4C;
        inline constexpr std::uint32_t aim_distance = 0x50;
        inline constexpr std::uint32_t aim_shoulder_offset = 0x54;
        inline constexpr std::uint32_t aim_height = 0x58;
        inline constexpr std::uint32_t look_up_distance_scale = 0x5C;
        inline constexpr std::uint32_t aim_smoothing_time = 0x60;
        inline constexpr std::uint32_t shoulder_swap_smoothing_time = 0x64;
        inline constexpr std::uint32_t is_remember_shoulder_side = 0x68;
        inline constexpr std::uint32_t min_ads_field_of_view_ratio = 0x6C;
        inline constexpr std::uint32_t is_scope_from_eye = 0x70;
        inline constexpr std::uint32_t probe_radius = 0x74;
        inline constexpr std::uint32_t probe_channel = 0x78;
        inline constexpr std::uint32_t collision_return_smoothing_time = 0x7C;
        inline constexpr std::uint32_t is_auto_shoulder_swap = 0x80;
        inline constexpr std::uint32_t auto_swap_blocked_fraction = 0x84;
        inline constexpr std::uint32_t auto_swap_other_side_fraction = 0x88;
        inline constexpr std::uint32_t auto_swap_return_fraction = 0x8C;
        inline constexpr std::uint32_t auto_swap_hold_seconds = 0x90;
        inline constexpr std::uint32_t is_hide_character_when_close = 0x94;
        inline constexpr std::uint32_t hide_distance = 0x98;
        inline constexpr std::uint32_t show_distance = 0x9C;
        inline constexpr std::uint32_t is_cancel_inspect_in_third_person = 0xA0;
        inline constexpr std::uint32_t is_show_shoulder_hint = 0xA1;
        inline constexpr std::uint32_t shoulder_hint_action = 0xA8;
        inline constexpr std::uint32_t shoulder_hint_margin = 0xD0;
        inline constexpr std::uint32_t shoulder_hint_display_seconds = 0xE0;
        inline constexpr std::uint32_t shoulder_hint_opacity = 0xE4;
        inline constexpr std::uint32_t shoulder_hint_fade_time = 0xE8;
        inline constexpr std::uint32_t byte_size = 0xF0;
    }

    namespace hw2_voice_cues {
        inline constexpr std::uint32_t is_enabled = 0x38;
        inline constexpr std::uint32_t volume = 0x3C;
        inline constexpr std::uint32_t pitch = 0x40;
        inline constexpr std::uint32_t default_voice = 0x44;
        inline constexpr std::uint32_t attenuation = 0x50;
        inline constexpr std::uint32_t is_claim_generic_voice = 0x78;
        inline constexpr std::uint32_t spawn_line_delay = 0x7C;
        inline constexpr std::uint32_t post_match_delay = 0x80;
        inline constexpr std::uint32_t round_result_delay = 0x84;
        inline constexpr std::uint32_t is_generic_round_start_lines = 0x88;
        inline constexpr std::uint32_t is_round_start_lines = 0x89;
        inline constexpr std::uint32_t is_round_result_lines = 0x8A;
        inline constexpr std::uint32_t round_start_line_every = 0x8C;
        inline constexpr std::uint32_t round_result_line_every = 0x90;
        inline constexpr std::uint32_t is_generic_result_on_deciding_round = 0x94;
        inline constexpr std::uint32_t lead_hold_seconds = 0x98;
        inline constexpr std::uint32_t line_gap = 0x9C;
        inline constexpr std::uint32_t queue_stale_seconds = 0xA0;
        inline constexpr std::uint32_t sounds = 0xA8;
        inline constexpr std::uint32_t byte_size = 0xB8;
    }

    namespace hw2_generic_voice {
        inline constexpr std::uint32_t uber_graph_frame = 0xC0;
        inline constexpr std::uint32_t enabled = 0xC8;
        inline constexpr std::uint32_t volume = 0xD0;
        inline constexpr std::uint32_t global_cooldown = 0xD8;
        inline constexpr std::uint32_t next_voice_time = 0xE0;
        inline constexpr std::uint32_t next_attempt_time = 0xE8;
        inline constexpr std::uint32_t current_variant = 0xF0;
        inline constexpr std::uint32_t pending_intro = 0xF4;
        inline constexpr std::uint32_t intro_consumed = 0xF5;
        inline constexpr std::uint32_t result_consumed = 0xF6;
        inline constexpr std::uint32_t last_event = 0xF8;
        inline constexpr std::uint32_t last_index = 0xFC;
        inline constexpr std::uint32_t spot_ready_time = 0x100;
        inline constexpr std::uint32_t debug_force_play = 0x108;
        inline constexpr std::uint32_t played_count = 0x10C;
        inline constexpr std::uint32_t event_chances = 0x110;
        inline constexpr std::uint32_t event_cooldowns = 0x120;
        inline constexpr std::uint32_t next_event_times = 0x130;
        inline constexpr std::uint32_t event_offsets = 0x140;
        inline constexpr std::uint32_t event_counts = 0x150;
        inline constexpr std::uint32_t last_indices = 0x160;
        inline constexpr std::uint32_t voice_profile = 0x170;
        inline constexpr std::uint32_t active_voice = 0x178;
        inline constexpr std::uint32_t current_pawn = 0x180;
        inline constexpr std::uint32_t last_spotted_pawn = 0x188;
        inline constexpr std::uint32_t selected_sound = 0x190;
        inline constexpr std::uint32_t event_priority = 0x198;
        inline constexpr std::uint32_t silenced = 0x1A8;
        inline constexpr std::uint32_t byte_size = 0x1B0;
    }

    namespace hw2_controller_options {
        inline constexpr std::uint32_t uber_graph_frame = 0xC0;
        inline constexpr std::uint32_t is_use_tpp = 0xC8;
        inline constexpr std::uint32_t is_vertical_axis_inverted = 0xC9;
        inline constexpr std::uint32_t is_horizontal_axis_inverted = 0xCA;
        inline constexpr std::uint32_t is_show_fps = 0xCB;
        inline constexpr std::uint32_t ui_volume = 0xD0;
        inline constexpr std::uint32_t ambient_volume = 0xD8;
        inline constexpr std::uint32_t characters_volume = 0xE0;
        inline constexpr std::uint32_t master_volume = 0xE8;
        inline constexpr std::uint32_t music_volume = 0xF0;
        inline constexpr std::uint32_t mouse_sensitivity = 0xF8;
        inline constexpr std::uint32_t aim_sensitivity = 0x100;
        inline constexpr std::uint32_t perspective_changed = 0x108;
        inline constexpr std::uint32_t settings_changed = 0x118;
        inline constexpr std::uint32_t save_slot_name = 0x128;
        inline constexpr std::uint32_t is_show_latency = 0x138;
        inline constexpr std::uint32_t is_toggle_run = 0x139;
        inline constexpr std::uint32_t is_toggle_crouch = 0x13A;
        inline constexpr std::uint32_t is_toggle_aim = 0x13B;
        inline constexpr std::uint32_t input_key_map = 0x140;
        inline constexpr std::uint32_t firing_modes_used = 0x190;
        inline constexpr std::uint32_t is_toggle_aim_sniper = 0x1E0;
        inline constexpr std::uint32_t controller_sensitivity = 0x1E8;
        inline constexpr std::uint32_t controller_ads_sensitivity = 0x1F0;
        inline constexpr std::uint32_t controller_scope_sensitivity = 0x1F8;
        inline constexpr std::uint32_t is_controller_vibration = 0x200;
        inline constexpr std::uint32_t is_controller_aim_assist = 0x201;
        inline constexpr std::uint32_t hw2_field_of_view = 0x208;
        inline constexpr std::uint32_t byte_size = 0x210;
    }

    namespace aworld_settings {
        inline constexpr std::uint32_t visibility_cell_size = 0x2B0;
        inline constexpr std::uint32_t visibility_aggressiveness = 0x2B4;
        inline constexpr std::uint32_t is_precompute_visibility = 0x2B5;
        inline constexpr std::uint32_t is_precompute_visibility_bit = 0x0;
        inline constexpr std::uint32_t is_place_cells_only_along_camera_tracks = 0x2B5;
        inline constexpr std::uint32_t is_place_cells_only_along_camera_tracks_bit = 0x1;
        inline constexpr std::uint32_t is_enable_world_bounds_checks = 0x2B5;
        inline constexpr std::uint32_t is_enable_world_bounds_checks_bit = 0x2;
        inline constexpr std::uint32_t is_enable_navigation_system = 0x2B5;
        inline constexpr std::uint32_t is_enable_navigation_system_bit = 0x3;
        inline constexpr std::uint32_t is_enable_ai_system = 0x2B5;
        inline constexpr std::uint32_t is_enable_ai_system_bit = 0x4;
        inline constexpr std::uint32_t is_use_automatic_ugc_navigation = 0x2B5;
        inline constexpr std::uint32_t is_use_automatic_ugc_navigation_bit = 0x5;
        inline constexpr std::uint32_t is_enable_world_composition = 0x2B5;
        inline constexpr std::uint32_t is_enable_world_composition_bit = 0x6;
        inline constexpr std::uint32_t is_use_client_side_level_streaming_volumes = 0x2B5;
        inline constexpr std::uint32_t is_use_client_side_level_streaming_volumes_bit = 0x7;
        inline constexpr std::uint32_t is_enable_world_origin_rebasing = 0x2B6;
        inline constexpr std::uint32_t is_enable_world_origin_rebasing_bit = 0x0;
        inline constexpr std::uint32_t is_world_gravity_set = 0x2B6;
        inline constexpr std::uint32_t is_world_gravity_set_bit = 0x1;
        inline constexpr std::uint32_t is_global_gravity_set = 0x2B6;
        inline constexpr std::uint32_t is_global_gravity_set_bit = 0x2;
        inline constexpr std::uint32_t is_minimize_bsp_sections = 0x2B6;
        inline constexpr std::uint32_t is_minimize_bsp_sections_bit = 0x3;
        inline constexpr std::uint32_t is_force_no_precomputed_lighting = 0x2B6;
        inline constexpr std::uint32_t is_force_no_precomputed_lighting_bit = 0x4;
        inline constexpr std::uint32_t is_force_volumetric_lightmaps_only = 0x2B6;
        inline constexpr std::uint32_t is_force_volumetric_lightmaps_only_bit = 0x5;
        inline constexpr std::uint32_t is_high_priority_loading = 0x2B6;
        inline constexpr std::uint32_t is_high_priority_loading_bit = 0x6;
        inline constexpr std::uint32_t is_high_priority_loading_local = 0x2B6;
        inline constexpr std::uint32_t is_high_priority_loading_local_bit = 0x7;
        inline constexpr std::uint32_t is_override_default_broadphase_settings = 0x2B7;
        inline constexpr std::uint32_t is_override_default_broadphase_settings_bit = 0x0;
        inline constexpr std::uint32_t is_generate_single_cluster_for_level = 0x2B7;
        inline constexpr std::uint32_t is_generate_single_cluster_for_level_bit = 0x1;
        inline constexpr std::uint32_t is_allow_time_dilation = 0x2B7;
        inline constexpr std::uint32_t is_allow_time_dilation_bit = 0x2;
        inline constexpr std::uint32_t is_reuse_address_and_port = 0x2B7;
        inline constexpr std::uint32_t is_reuse_address_and_port_bit = 0x3;
        inline constexpr std::uint32_t ai_system_class = 0x2B8;
        inline constexpr std::uint32_t level_instance_pivot_offset = 0x2E0;
        inline constexpr std::uint32_t navigation_system_config = 0x2F8;
        inline constexpr std::uint32_t navigation_system_config_override = 0x300;
        inline constexpr std::uint32_t world_partition = 0x308;
        inline constexpr std::uint32_t base_navmesh_data_layers = 0x310;
        inline constexpr std::uint32_t world_to_meters = 0x320;
        inline constexpr std::uint32_t kill_z = 0x324;
        inline constexpr std::uint32_t kill_z_damage_type = 0x328;
        inline constexpr std::uint32_t world_gravity_z = 0x330;
        inline constexpr std::uint32_t global_gravity_z = 0x334;
        inline constexpr std::uint32_t default_physics_volume_class = 0x338;
        inline constexpr std::uint32_t physics_collision_handler_class = 0x340;
        inline constexpr std::uint32_t default_game_mode = 0x348;
        inline constexpr std::uint32_t game_network_manager_class = 0x350;
        inline constexpr std::uint32_t packed_light_and_shadow_map_texture_size = 0x358;
        inline constexpr std::uint32_t default_color_scale = 0x360;
        inline constexpr std::uint32_t default_max_distance_field_occlusion_distance = 0x378;
        inline constexpr std::uint32_t global_distance_field_view_distance = 0x37C;
        inline constexpr std::uint32_t dynamic_indirect_shadows_self_shadowing_intensity = 0x380;
        inline constexpr std::uint32_t volumetric_lightmap_loading_range = 0x384;
        inline constexpr std::uint32_t nanite_settings = 0x388;
        inline constexpr std::uint32_t default_reverb_settings = 0x390;
        inline constexpr std::uint32_t default_ambient_zone_settings = 0x3B0;
        inline constexpr std::uint32_t default_base_sound_mix = 0x3D8;
        inline constexpr std::uint32_t time_dilation = 0x3E0;
        inline constexpr std::uint32_t cinematic_time_dilation = 0x3E4;
        inline constexpr std::uint32_t demo_play_time_dilation = 0x3E8;
        inline constexpr std::uint32_t min_global_time_dilation = 0x3EC;
        inline constexpr std::uint32_t max_global_time_dilation = 0x3F0;
        inline constexpr std::uint32_t min_cinematic_time_dilation = 0x3F4;
        inline constexpr std::uint32_t max_cinematic_time_dilation = 0x3F8;
        inline constexpr std::uint32_t min_undilated_frame_time = 0x3FC;
        inline constexpr std::uint32_t max_undilated_frame_time = 0x400;
        inline constexpr std::uint32_t broadphase_settings = 0x408;
        inline constexpr std::uint32_t replication_viewers = 0x488;
        inline constexpr std::uint32_t asset_user_data = 0x498;
        inline constexpr std::uint32_t pauser_player_state = 0x4A8;
        inline constexpr std::uint32_t max_number_of_bookmarks = 0x4B0;
        inline constexpr std::uint32_t default_bookmark_class = 0x4B8;
        inline constexpr std::uint32_t bookmark_array = 0x4C0;
        inline constexpr std::uint32_t last_bookmark_class = 0x4D0;
        inline constexpr std::uint32_t byte_size = 0x4D8;
    }

    namespace post_process_settings {
        inline constexpr std::uint32_t is_override_temperature_type = 0x0;
        inline constexpr std::uint32_t is_override_temperature_type_bit = 0x0;
        inline constexpr std::uint32_t is_override_white_temp = 0x0;
        inline constexpr std::uint32_t is_override_white_temp_bit = 0x1;
        inline constexpr std::uint32_t is_override_white_tint = 0x0;
        inline constexpr std::uint32_t is_override_white_tint_bit = 0x2;
        inline constexpr std::uint32_t is_override_color_saturation = 0x0;
        inline constexpr std::uint32_t is_override_color_saturation_bit = 0x3;
        inline constexpr std::uint32_t is_override_color_contrast = 0x0;
        inline constexpr std::uint32_t is_override_color_contrast_bit = 0x4;
        inline constexpr std::uint32_t is_override_color_gamma = 0x0;
        inline constexpr std::uint32_t is_override_color_gamma_bit = 0x5;
        inline constexpr std::uint32_t is_override_color_gain = 0x0;
        inline constexpr std::uint32_t is_override_color_gain_bit = 0x6;
        inline constexpr std::uint32_t is_override_color_offset = 0x0;
        inline constexpr std::uint32_t is_override_color_offset_bit = 0x7;
        inline constexpr std::uint32_t is_override_color_saturation_shadows = 0x1;
        inline constexpr std::uint32_t is_override_color_saturation_shadows_bit = 0x0;
        inline constexpr std::uint32_t is_override_color_contrast_shadows = 0x1;
        inline constexpr std::uint32_t is_override_color_contrast_shadows_bit = 0x1;
        inline constexpr std::uint32_t is_override_color_gamma_shadows = 0x1;
        inline constexpr std::uint32_t is_override_color_gamma_shadows_bit = 0x2;
        inline constexpr std::uint32_t is_override_color_gain_shadows = 0x1;
        inline constexpr std::uint32_t is_override_color_gain_shadows_bit = 0x3;
        inline constexpr std::uint32_t is_override_color_offset_shadows = 0x1;
        inline constexpr std::uint32_t is_override_color_offset_shadows_bit = 0x4;
        inline constexpr std::uint32_t is_override_color_saturation_midtones = 0x1;
        inline constexpr std::uint32_t is_override_color_saturation_midtones_bit = 0x5;
        inline constexpr std::uint32_t is_override_color_contrast_midtones = 0x1;
        inline constexpr std::uint32_t is_override_color_contrast_midtones_bit = 0x6;
        inline constexpr std::uint32_t is_override_color_gamma_midtones = 0x1;
        inline constexpr std::uint32_t is_override_color_gamma_midtones_bit = 0x7;
        inline constexpr std::uint32_t is_override_color_gain_midtones = 0x2;
        inline constexpr std::uint32_t is_override_color_gain_midtones_bit = 0x0;
        inline constexpr std::uint32_t is_override_color_offset_midtones = 0x2;
        inline constexpr std::uint32_t is_override_color_offset_midtones_bit = 0x1;
        inline constexpr std::uint32_t is_override_color_saturation_highlights = 0x2;
        inline constexpr std::uint32_t is_override_color_saturation_highlights_bit = 0x2;
        inline constexpr std::uint32_t is_override_color_contrast_highlights = 0x2;
        inline constexpr std::uint32_t is_override_color_contrast_highlights_bit = 0x3;
        inline constexpr std::uint32_t is_override_color_gamma_highlights = 0x2;
        inline constexpr std::uint32_t is_override_color_gamma_highlights_bit = 0x4;
        inline constexpr std::uint32_t is_override_color_gain_highlights = 0x2;
        inline constexpr std::uint32_t is_override_color_gain_highlights_bit = 0x5;
        inline constexpr std::uint32_t is_override_color_offset_highlights = 0x2;
        inline constexpr std::uint32_t is_override_color_offset_highlights_bit = 0x6;
        inline constexpr std::uint32_t is_override_color_correction_shadows_max = 0x2;
        inline constexpr std::uint32_t is_override_color_correction_shadows_max_bit = 0x7;
        inline constexpr std::uint32_t is_override_color_correction_highlights_min = 0x3;
        inline constexpr std::uint32_t is_override_color_correction_highlights_min_bit = 0x0;
        inline constexpr std::uint32_t is_override_color_correction_highlights_max = 0x3;
        inline constexpr std::uint32_t is_override_color_correction_highlights_max_bit = 0x1;
        inline constexpr std::uint32_t is_override_blue_correction = 0x3;
        inline constexpr std::uint32_t is_override_blue_correction_bit = 0x2;
        inline constexpr std::uint32_t is_override_expand_gamut = 0x3;
        inline constexpr std::uint32_t is_override_expand_gamut_bit = 0x3;
        inline constexpr std::uint32_t is_override_tone_curve_amount = 0x3;
        inline constexpr std::uint32_t is_override_tone_curve_amount_bit = 0x4;
        inline constexpr std::uint32_t is_override_tonemapping_method = 0x3;
        inline constexpr std::uint32_t is_override_tonemapping_method_bit = 0x5;
        inline constexpr std::uint32_t is_override_film_slope = 0x3;
        inline constexpr std::uint32_t is_override_film_slope_bit = 0x6;
        inline constexpr std::uint32_t is_override_film_toe = 0x3;
        inline constexpr std::uint32_t is_override_film_toe_bit = 0x7;
        inline constexpr std::uint32_t is_override_film_shoulder = 0x4;
        inline constexpr std::uint32_t is_override_film_shoulder_bit = 0x0;
        inline constexpr std::uint32_t is_override_film_black_clip = 0x4;
        inline constexpr std::uint32_t is_override_film_black_clip_bit = 0x1;
        inline constexpr std::uint32_t is_override_film_white_clip = 0x4;
        inline constexpr std::uint32_t is_override_film_white_clip_bit = 0x2;
        inline constexpr std::uint32_t is_override_scene_color_tint = 0x4;
        inline constexpr std::uint32_t is_override_scene_color_tint_bit = 0x3;
        inline constexpr std::uint32_t is_override_scene_fringe_intensity = 0x4;
        inline constexpr std::uint32_t is_override_scene_fringe_intensity_bit = 0x4;
        inline constexpr std::uint32_t is_override_chromatic_aberration_start_offset = 0x4;
        inline constexpr std::uint32_t is_override_chromatic_aberration_start_offset_bit = 0x5;
        inline constexpr std::uint32_t is_override_b_mega_lights = 0x4;
        inline constexpr std::uint32_t is_override_b_mega_lights_bit = 0x6;
        inline constexpr std::uint32_t is_override_mega_lights_front_layer_translucency = 0x4;
        inline constexpr std::uint32_t is_override_mega_lights_front_layer_translucency_bit = 0x7;
        inline constexpr std::uint32_t is_override_ambient_cubemap_tint = 0x5;
        inline constexpr std::uint32_t is_override_ambient_cubemap_tint_bit = 0x0;
        inline constexpr std::uint32_t is_override_ambient_cubemap_intensity = 0x5;
        inline constexpr std::uint32_t is_override_ambient_cubemap_intensity_bit = 0x1;
        inline constexpr std::uint32_t is_override_bloom_method = 0x5;
        inline constexpr std::uint32_t is_override_bloom_method_bit = 0x2;
        inline constexpr std::uint32_t is_override_bloom_intensity = 0x5;
        inline constexpr std::uint32_t is_override_bloom_intensity_bit = 0x3;
        inline constexpr std::uint32_t is_override_bloom_gaussian_intensity = 0x5;
        inline constexpr std::uint32_t is_override_bloom_gaussian_intensity_bit = 0x4;
        inline constexpr std::uint32_t is_override_bloom_threshold = 0x5;
        inline constexpr std::uint32_t is_override_bloom_threshold_bit = 0x5;
        inline constexpr std::uint32_t is_override_bloom1_tint = 0x5;
        inline constexpr std::uint32_t is_override_bloom1_tint_bit = 0x6;
        inline constexpr std::uint32_t is_override_bloom1_size = 0x5;
        inline constexpr std::uint32_t is_override_bloom1_size_bit = 0x7;
        inline constexpr std::uint32_t is_override_bloom2_size = 0x6;
        inline constexpr std::uint32_t is_override_bloom2_size_bit = 0x0;
        inline constexpr std::uint32_t is_override_bloom2_tint = 0x6;
        inline constexpr std::uint32_t is_override_bloom2_tint_bit = 0x1;
        inline constexpr std::uint32_t is_override_bloom3_tint = 0x6;
        inline constexpr std::uint32_t is_override_bloom3_tint_bit = 0x2;
        inline constexpr std::uint32_t is_override_bloom3_size = 0x6;
        inline constexpr std::uint32_t is_override_bloom3_size_bit = 0x3;
        inline constexpr std::uint32_t is_override_bloom4_tint = 0x6;
        inline constexpr std::uint32_t is_override_bloom4_tint_bit = 0x4;
        inline constexpr std::uint32_t is_override_bloom4_size = 0x6;
        inline constexpr std::uint32_t is_override_bloom4_size_bit = 0x5;
        inline constexpr std::uint32_t is_override_bloom5_tint = 0x6;
        inline constexpr std::uint32_t is_override_bloom5_tint_bit = 0x6;
        inline constexpr std::uint32_t is_override_bloom5_size = 0x6;
        inline constexpr std::uint32_t is_override_bloom5_size_bit = 0x7;
        inline constexpr std::uint32_t is_override_bloom6_tint = 0x7;
        inline constexpr std::uint32_t is_override_bloom6_tint_bit = 0x0;
        inline constexpr std::uint32_t is_override_bloom6_size = 0x7;
        inline constexpr std::uint32_t is_override_bloom6_size_bit = 0x1;
        inline constexpr std::uint32_t is_override_bloom_size_scale = 0x7;
        inline constexpr std::uint32_t is_override_bloom_size_scale_bit = 0x2;
        inline constexpr std::uint32_t is_override_bloom_convolution_intensity = 0x7;
        inline constexpr std::uint32_t is_override_bloom_convolution_intensity_bit = 0x3;
        inline constexpr std::uint32_t is_override_bloom_convolution_texture = 0x7;
        inline constexpr std::uint32_t is_override_bloom_convolution_texture_bit = 0x4;
        inline constexpr std::uint32_t is_override_bloom_convolution_scatter_dispersion = 0x7;
        inline constexpr std::uint32_t is_override_bloom_convolution_scatter_dispersion_bit = 0x5;
        inline constexpr std::uint32_t is_override_bloom_convolution_size = 0x7;
        inline constexpr std::uint32_t is_override_bloom_convolution_size_bit = 0x6;
        inline constexpr std::uint32_t is_override_bloom_convolution_center_uv = 0x7;
        inline constexpr std::uint32_t is_override_bloom_convolution_center_uv_bit = 0x7;
        inline constexpr std::uint32_t is_override_bloom_convolution_pre_filter = 0x8;
        inline constexpr std::uint32_t is_override_bloom_convolution_pre_filter_bit = 0x0;
        inline constexpr std::uint32_t is_override_bloom_convolution_pre_filter_min = 0x8;
        inline constexpr std::uint32_t is_override_bloom_convolution_pre_filter_min_bit = 0x1;
        inline constexpr std::uint32_t is_override_bloom_convolution_pre_filter_max = 0x8;
        inline constexpr std::uint32_t is_override_bloom_convolution_pre_filter_max_bit = 0x2;
        inline constexpr std::uint32_t is_override_bloom_convolution_pre_filter_mult = 0x8;
        inline constexpr std::uint32_t is_override_bloom_convolution_pre_filter_mult_bit = 0x3;
        inline constexpr std::uint32_t is_override_bloom_convolution_buffer_scale = 0x8;
        inline constexpr std::uint32_t is_override_bloom_convolution_buffer_scale_bit = 0x4;
        inline constexpr std::uint32_t is_override_bloom_dirt_mask_intensity = 0x8;
        inline constexpr std::uint32_t is_override_bloom_dirt_mask_intensity_bit = 0x5;
        inline constexpr std::uint32_t is_override_bloom_dirt_mask_tint = 0x8;
        inline constexpr std::uint32_t is_override_bloom_dirt_mask_tint_bit = 0x6;
        inline constexpr std::uint32_t is_override_bloom_dirt_mask = 0x8;
        inline constexpr std::uint32_t is_override_bloom_dirt_mask_bit = 0x7;
        inline constexpr std::uint32_t is_override_camera_shutter_speed = 0x9;
        inline constexpr std::uint32_t is_override_camera_shutter_speed_bit = 0x0;
        inline constexpr std::uint32_t is_override_camera_iso = 0x9;
        inline constexpr std::uint32_t is_override_camera_iso_bit = 0x1;
        inline constexpr std::uint32_t is_override_auto_exposure_method = 0x9;
        inline constexpr std::uint32_t is_override_auto_exposure_method_bit = 0x2;
        inline constexpr std::uint32_t is_override_auto_exposure_low_percent = 0x9;
        inline constexpr std::uint32_t is_override_auto_exposure_low_percent_bit = 0x3;
        inline constexpr std::uint32_t is_override_auto_exposure_high_percent = 0x9;
        inline constexpr std::uint32_t is_override_auto_exposure_high_percent_bit = 0x4;
        inline constexpr std::uint32_t is_override_auto_exposure_min_brightness = 0x9;
        inline constexpr std::uint32_t is_override_auto_exposure_min_brightness_bit = 0x5;
        inline constexpr std::uint32_t is_override_auto_exposure_max_brightness = 0x9;
        inline constexpr std::uint32_t is_override_auto_exposure_max_brightness_bit = 0x6;
        inline constexpr std::uint32_t is_override_auto_exposure_calibration_constant = 0x9;
        inline constexpr std::uint32_t is_override_auto_exposure_calibration_constant_bit = 0x7;
        inline constexpr std::uint32_t is_override_auto_exposure_speed_up = 0xA;
        inline constexpr std::uint32_t is_override_auto_exposure_speed_up_bit = 0x0;
        inline constexpr std::uint32_t is_override_auto_exposure_speed_down = 0xA;
        inline constexpr std::uint32_t is_override_auto_exposure_speed_down_bit = 0x1;
        inline constexpr std::uint32_t is_override_auto_exposure_bias = 0xA;
        inline constexpr std::uint32_t is_override_auto_exposure_bias_bit = 0x2;
        inline constexpr std::uint32_t is_override_auto_exposure_bias_curve = 0xA;
        inline constexpr std::uint32_t is_override_auto_exposure_bias_curve_bit = 0x3;
        inline constexpr std::uint32_t is_override_auto_exposure_meter_mask = 0xA;
        inline constexpr std::uint32_t is_override_auto_exposure_meter_mask_bit = 0x4;
        inline constexpr std::uint32_t is_override_auto_exposure_apply_physical_camera_exposure = 0xA;
        inline constexpr std::uint32_t is_override_auto_exposure_apply_physical_camera_exposure_bit = 0x5;
        inline constexpr std::uint32_t is_override_histogram_log_min = 0xA;
        inline constexpr std::uint32_t is_override_histogram_log_min_bit = 0x6;
        inline constexpr std::uint32_t is_override_histogram_log_max = 0xA;
        inline constexpr std::uint32_t is_override_histogram_log_max_bit = 0x7;
        inline constexpr std::uint32_t is_override_local_exposure_method = 0xB;
        inline constexpr std::uint32_t is_override_local_exposure_method_bit = 0x0;
        inline constexpr std::uint32_t is_override_local_exposure_contrast_scale = 0xB;
        inline constexpr std::uint32_t is_override_local_exposure_contrast_scale_bit = 0x1;
        inline constexpr std::uint32_t is_override_local_exposure_highlight_contrast_scale = 0xB;
        inline constexpr std::uint32_t is_override_local_exposure_highlight_contrast_scale_bit = 0x2;
        inline constexpr std::uint32_t is_override_local_exposure_shadow_contrast_scale = 0xB;
        inline constexpr std::uint32_t is_override_local_exposure_shadow_contrast_scale_bit = 0x3;
        inline constexpr std::uint32_t is_override_local_exposure_highlight_contrast_curve = 0xB;
        inline constexpr std::uint32_t is_override_local_exposure_highlight_contrast_curve_bit = 0x4;
        inline constexpr std::uint32_t is_override_local_exposure_shadow_contrast_curve = 0xB;
        inline constexpr std::uint32_t is_override_local_exposure_shadow_contrast_curve_bit = 0x5;
        inline constexpr std::uint32_t is_override_local_exposure_highlight_threshold = 0xB;
        inline constexpr std::uint32_t is_override_local_exposure_highlight_threshold_bit = 0x6;
        inline constexpr std::uint32_t is_override_local_exposure_shadow_threshold = 0xB;
        inline constexpr std::uint32_t is_override_local_exposure_shadow_threshold_bit = 0x7;
        inline constexpr std::uint32_t is_override_local_exposure_detail_strength = 0xC;
        inline constexpr std::uint32_t is_override_local_exposure_detail_strength_bit = 0x0;
        inline constexpr std::uint32_t is_override_local_exposure_blurred_luminance_blend = 0xC;
        inline constexpr std::uint32_t is_override_local_exposure_blurred_luminance_blend_bit = 0x1;
        inline constexpr std::uint32_t is_override_local_exposure_blurred_luminance_kernel_size_percent = 0xC;
        inline constexpr std::uint32_t is_override_local_exposure_blurred_luminance_kernel_size_percent_bit = 0x2;
        inline constexpr std::uint32_t is_override_local_exposure_highlight_threshold_strength = 0xC;
        inline constexpr std::uint32_t is_override_local_exposure_highlight_threshold_strength_bit = 0x3;
        inline constexpr std::uint32_t is_override_local_exposure_shadow_threshold_strength = 0xC;
        inline constexpr std::uint32_t is_override_local_exposure_shadow_threshold_strength_bit = 0x4;
        inline constexpr std::uint32_t is_override_local_exposure_middle_grey_bias = 0xC;
        inline constexpr std::uint32_t is_override_local_exposure_middle_grey_bias_bit = 0x5;
        inline constexpr std::uint32_t is_override_lens_flare_intensity = 0xC;
        inline constexpr std::uint32_t is_override_lens_flare_intensity_bit = 0x6;
        inline constexpr std::uint32_t is_override_lens_flare_tint = 0xC;
        inline constexpr std::uint32_t is_override_lens_flare_tint_bit = 0x7;
        inline constexpr std::uint32_t is_override_lens_flare_tints = 0xD;
        inline constexpr std::uint32_t is_override_lens_flare_tints_bit = 0x0;
        inline constexpr std::uint32_t is_override_lens_flare_bokeh_size = 0xD;
        inline constexpr std::uint32_t is_override_lens_flare_bokeh_size_bit = 0x1;
        inline constexpr std::uint32_t is_override_lens_flare_bokeh_shape = 0xD;
        inline constexpr std::uint32_t is_override_lens_flare_bokeh_shape_bit = 0x2;
        inline constexpr std::uint32_t is_override_lens_flare_threshold = 0xD;
        inline constexpr std::uint32_t is_override_lens_flare_threshold_bit = 0x3;
        inline constexpr std::uint32_t is_override_vignette_intensity = 0xD;
        inline constexpr std::uint32_t is_override_vignette_intensity_bit = 0x4;
        inline constexpr std::uint32_t is_override_vignette_type = 0xD;
        inline constexpr std::uint32_t is_override_vignette_type_bit = 0x5;
        inline constexpr std::uint32_t is_override_vignette_center = 0xD;
        inline constexpr std::uint32_t is_override_vignette_center_bit = 0x6;
        inline constexpr std::uint32_t is_override_vignette_color = 0xD;
        inline constexpr std::uint32_t is_override_vignette_color_bit = 0x7;
        inline constexpr std::uint32_t is_override_vignette_size = 0xE;
        inline constexpr std::uint32_t is_override_vignette_size_bit = 0x0;
        inline constexpr std::uint32_t is_override_vignette_softness = 0xE;
        inline constexpr std::uint32_t is_override_vignette_softness_bit = 0x1;
        inline constexpr std::uint32_t is_override_vignette_texture = 0xE;
        inline constexpr std::uint32_t is_override_vignette_texture_bit = 0x2;
        inline constexpr std::uint32_t is_override_sharpen = 0xE;
        inline constexpr std::uint32_t is_override_sharpen_bit = 0x3;
        inline constexpr std::uint32_t is_override_grain_intensity = 0xE;
        inline constexpr std::uint32_t is_override_grain_intensity_bit = 0x4;
        inline constexpr std::uint32_t is_override_grain_jitter = 0xE;
        inline constexpr std::uint32_t is_override_grain_jitter_bit = 0x5;
        inline constexpr std::uint32_t is_override_film_grain_intensity = 0xE;
        inline constexpr std::uint32_t is_override_film_grain_intensity_bit = 0x6;
        inline constexpr std::uint32_t is_override_film_grain_intensity_shadows = 0xE;
        inline constexpr std::uint32_t is_override_film_grain_intensity_shadows_bit = 0x7;
        inline constexpr std::uint32_t is_override_film_grain_intensity_midtones = 0xF;
        inline constexpr std::uint32_t is_override_film_grain_intensity_midtones_bit = 0x0;
        inline constexpr std::uint32_t is_override_film_grain_intensity_highlights = 0xF;
        inline constexpr std::uint32_t is_override_film_grain_intensity_highlights_bit = 0x1;
        inline constexpr std::uint32_t is_override_film_grain_shadows_max = 0xF;
        inline constexpr std::uint32_t is_override_film_grain_shadows_max_bit = 0x2;
        inline constexpr std::uint32_t is_override_film_grain_highlights_min = 0xF;
        inline constexpr std::uint32_t is_override_film_grain_highlights_min_bit = 0x3;
        inline constexpr std::uint32_t is_override_film_grain_highlights_max = 0xF;
        inline constexpr std::uint32_t is_override_film_grain_highlights_max_bit = 0x4;
        inline constexpr std::uint32_t is_override_film_grain_scale = 0xF;
        inline constexpr std::uint32_t is_override_film_grain_scale_bit = 0x5;
        inline constexpr std::uint32_t is_override_film_grain_texture = 0xF;
        inline constexpr std::uint32_t is_override_film_grain_texture_bit = 0x6;
        inline constexpr std::uint32_t is_override_ambient_occlusion_intensity = 0xF;
        inline constexpr std::uint32_t is_override_ambient_occlusion_intensity_bit = 0x7;
        inline constexpr std::uint32_t is_override_ambient_occlusion_static_fraction = 0x10;
        inline constexpr std::uint32_t is_override_ambient_occlusion_static_fraction_bit = 0x0;
        inline constexpr std::uint32_t is_override_ambient_occlusion_radius = 0x10;
        inline constexpr std::uint32_t is_override_ambient_occlusion_radius_bit = 0x1;
        inline constexpr std::uint32_t is_override_ambient_occlusion_fade_distance = 0x10;
        inline constexpr std::uint32_t is_override_ambient_occlusion_fade_distance_bit = 0x2;
        inline constexpr std::uint32_t is_override_ambient_occlusion_fade_radius = 0x10;
        inline constexpr std::uint32_t is_override_ambient_occlusion_fade_radius_bit = 0x3;
        inline constexpr std::uint32_t is_override_ambient_occlusion_distance = 0x10;
        inline constexpr std::uint32_t is_override_ambient_occlusion_distance_bit = 0x4;
        inline constexpr std::uint32_t is_override_ambient_occlusion_radius_in_ws = 0x10;
        inline constexpr std::uint32_t is_override_ambient_occlusion_radius_in_ws_bit = 0x5;
        inline constexpr std::uint32_t is_override_ambient_occlusion_power = 0x10;
        inline constexpr std::uint32_t is_override_ambient_occlusion_power_bit = 0x6;
        inline constexpr std::uint32_t is_override_ambient_occlusion_bias = 0x10;
        inline constexpr std::uint32_t is_override_ambient_occlusion_bias_bit = 0x7;
        inline constexpr std::uint32_t is_override_ambient_occlusion_quality = 0x11;
        inline constexpr std::uint32_t is_override_ambient_occlusion_quality_bit = 0x0;
        inline constexpr std::uint32_t is_override_ambient_occlusion_mip_blend = 0x11;
        inline constexpr std::uint32_t is_override_ambient_occlusion_mip_blend_bit = 0x1;
        inline constexpr std::uint32_t is_override_ambient_occlusion_mip_scale = 0x11;
        inline constexpr std::uint32_t is_override_ambient_occlusion_mip_scale_bit = 0x2;
        inline constexpr std::uint32_t is_override_ambient_occlusion_mip_threshold = 0x11;
        inline constexpr std::uint32_t is_override_ambient_occlusion_mip_threshold_bit = 0x3;
        inline constexpr std::uint32_t is_override_ambient_occlusion_temporal_blend_weight = 0x11;
        inline constexpr std::uint32_t is_override_ambient_occlusion_temporal_blend_weight_bit = 0x4;
        inline constexpr std::uint32_t is_override_ray_tracing_ao = 0x14;
        inline constexpr std::uint32_t is_override_ray_tracing_ao_bit = 0x0;
        inline constexpr std::uint32_t is_override_ray_tracing_ao_samples_per_pixel = 0x14;
        inline constexpr std::uint32_t is_override_ray_tracing_ao_samples_per_pixel_bit = 0x1;
        inline constexpr std::uint32_t is_override_ray_tracing_ao_intensity = 0x14;
        inline constexpr std::uint32_t is_override_ray_tracing_ao_intensity_bit = 0x2;
        inline constexpr std::uint32_t is_override_ray_tracing_ao_radius = 0x14;
        inline constexpr std::uint32_t is_override_ray_tracing_ao_radius_bit = 0x3;
        inline constexpr std::uint32_t is_override_lpv_intensity = 0x18;
        inline constexpr std::uint32_t is_override_lpv_intensity_bit = 0x0;
        inline constexpr std::uint32_t is_override_lpv_directional_occlusion_intensity = 0x18;
        inline constexpr std::uint32_t is_override_lpv_directional_occlusion_intensity_bit = 0x1;
        inline constexpr std::uint32_t is_override_lpv_directional_occlusion_radius = 0x18;
        inline constexpr std::uint32_t is_override_lpv_directional_occlusion_radius_bit = 0x2;
        inline constexpr std::uint32_t is_override_lpv_diffuse_occlusion_exponent = 0x18;
        inline constexpr std::uint32_t is_override_lpv_diffuse_occlusion_exponent_bit = 0x3;
        inline constexpr std::uint32_t is_override_lpv_specular_occlusion_exponent = 0x18;
        inline constexpr std::uint32_t is_override_lpv_specular_occlusion_exponent_bit = 0x4;
        inline constexpr std::uint32_t is_override_lpv_diffuse_occlusion_intensity = 0x18;
        inline constexpr std::uint32_t is_override_lpv_diffuse_occlusion_intensity_bit = 0x5;
        inline constexpr std::uint32_t is_override_lpv_specular_occlusion_intensity = 0x18;
        inline constexpr std::uint32_t is_override_lpv_specular_occlusion_intensity_bit = 0x6;
        inline constexpr std::uint32_t is_override_lpv_size = 0x18;
        inline constexpr std::uint32_t is_override_lpv_size_bit = 0x7;
        inline constexpr std::uint32_t is_override_lpv_secondary_occlusion_intensity = 0x19;
        inline constexpr std::uint32_t is_override_lpv_secondary_occlusion_intensity_bit = 0x0;
        inline constexpr std::uint32_t is_override_lpv_secondary_bounce_intensity = 0x19;
        inline constexpr std::uint32_t is_override_lpv_secondary_bounce_intensity_bit = 0x1;
        inline constexpr std::uint32_t is_override_lpv_geometry_volume_bias = 0x19;
        inline constexpr std::uint32_t is_override_lpv_geometry_volume_bias_bit = 0x2;
        inline constexpr std::uint32_t is_override_lpv_vpl_injection_bias = 0x19;
        inline constexpr std::uint32_t is_override_lpv_vpl_injection_bias_bit = 0x3;
        inline constexpr std::uint32_t is_override_lpv_emissive_injection_intensity = 0x19;
        inline constexpr std::uint32_t is_override_lpv_emissive_injection_intensity_bit = 0x4;
        inline constexpr std::uint32_t is_override_lpv_fade_range = 0x19;
        inline constexpr std::uint32_t is_override_lpv_fade_range_bit = 0x5;
        inline constexpr std::uint32_t is_override_lpv_directional_occlusion_fade_range = 0x19;
        inline constexpr std::uint32_t is_override_lpv_directional_occlusion_fade_range_bit = 0x6;
        inline constexpr std::uint32_t is_override_indirect_lighting_color = 0x19;
        inline constexpr std::uint32_t is_override_indirect_lighting_color_bit = 0x7;
        inline constexpr std::uint32_t is_override_indirect_lighting_intensity = 0x1A;
        inline constexpr std::uint32_t is_override_indirect_lighting_intensity_bit = 0x0;
        inline constexpr std::uint32_t is_override_color_grading_intensity = 0x1A;
        inline constexpr std::uint32_t is_override_color_grading_intensity_bit = 0x1;
        inline constexpr std::uint32_t is_override_color_grading_lut = 0x1A;
        inline constexpr std::uint32_t is_override_color_grading_lut_bit = 0x2;
        inline constexpr std::uint32_t is_override_depth_of_field_enabled = 0x1A;
        inline constexpr std::uint32_t is_override_depth_of_field_enabled_bit = 0x3;
        inline constexpr std::uint32_t is_override_depth_of_field_focal_distance = 0x1A;
        inline constexpr std::uint32_t is_override_depth_of_field_focal_distance_bit = 0x4;
        inline constexpr std::uint32_t is_override_depth_of_field_fstop = 0x1A;
        inline constexpr std::uint32_t is_override_depth_of_field_fstop_bit = 0x5;
        inline constexpr std::uint32_t is_override_depth_of_field_min_fstop = 0x1A;
        inline constexpr std::uint32_t is_override_depth_of_field_min_fstop_bit = 0x6;
        inline constexpr std::uint32_t is_override_depth_of_field_blade_count = 0x1A;
        inline constexpr std::uint32_t is_override_depth_of_field_blade_count_bit = 0x7;
        inline constexpr std::uint32_t is_override_depth_of_field_sensor_width = 0x1B;
        inline constexpr std::uint32_t is_override_depth_of_field_sensor_width_bit = 0x0;
        inline constexpr std::uint32_t is_override_depth_of_field_squeeze_factor = 0x1B;
        inline constexpr std::uint32_t is_override_depth_of_field_squeeze_factor_bit = 0x1;
        inline constexpr std::uint32_t is_override_depth_of_field_depth_blur_radius = 0x1B;
        inline constexpr std::uint32_t is_override_depth_of_field_depth_blur_radius_bit = 0x2;
        inline constexpr std::uint32_t is_override_depth_of_field_use_hair_depth = 0x1B;
        inline constexpr std::uint32_t is_override_depth_of_field_use_hair_depth_bit = 0x3;
        inline constexpr std::uint32_t is_override_depth_of_field_petzval_bokeh = 0x1B;
        inline constexpr std::uint32_t is_override_depth_of_field_petzval_bokeh_bit = 0x4;
        inline constexpr std::uint32_t is_override_depth_of_field_petzval_bokeh_falloff = 0x1B;
        inline constexpr std::uint32_t is_override_depth_of_field_petzval_bokeh_falloff_bit = 0x5;
        inline constexpr std::uint32_t is_override_depth_of_field_petzval_exclusion_box_extents = 0x1B;
        inline constexpr std::uint32_t is_override_depth_of_field_petzval_exclusion_box_extents_bit = 0x6;
        inline constexpr std::uint32_t is_override_depth_of_field_petzval_exclusion_box_radius = 0x1B;
        inline constexpr std::uint32_t is_override_depth_of_field_petzval_exclusion_box_radius_bit = 0x7;
        inline constexpr std::uint32_t is_override_depth_of_field_aspect_ratio_scalar = 0x1C;
        inline constexpr std::uint32_t is_override_depth_of_field_aspect_ratio_scalar_bit = 0x0;
        inline constexpr std::uint32_t is_override_depth_of_field_matte_box_flags = 0x1C;
        inline constexpr std::uint32_t is_override_depth_of_field_matte_box_flags_bit = 0x1;
        inline constexpr std::uint32_t is_override_depth_of_field_barrel_radius = 0x1C;
        inline constexpr std::uint32_t is_override_depth_of_field_barrel_radius_bit = 0x2;
        inline constexpr std::uint32_t is_override_depth_of_field_barrel_length = 0x1C;
        inline constexpr std::uint32_t is_override_depth_of_field_barrel_length_bit = 0x3;
        inline constexpr std::uint32_t is_override_depth_of_field_depth_blur_amount = 0x1C;
        inline constexpr std::uint32_t is_override_depth_of_field_depth_blur_amount_bit = 0x4;
        inline constexpr std::uint32_t is_override_depth_of_field_focal_region = 0x1C;
        inline constexpr std::uint32_t is_override_depth_of_field_focal_region_bit = 0x5;
        inline constexpr std::uint32_t is_override_depth_of_field_near_transition_region = 0x1C;
        inline constexpr std::uint32_t is_override_depth_of_field_near_transition_region_bit = 0x6;
        inline constexpr std::uint32_t is_override_depth_of_field_far_transition_region = 0x1C;
        inline constexpr std::uint32_t is_override_depth_of_field_far_transition_region_bit = 0x7;
        inline constexpr std::uint32_t is_override_depth_of_field_scale = 0x1D;
        inline constexpr std::uint32_t is_override_depth_of_field_scale_bit = 0x0;
        inline constexpr std::uint32_t is_override_depth_of_field_near_blur_size = 0x1D;
        inline constexpr std::uint32_t is_override_depth_of_field_near_blur_size_bit = 0x1;
        inline constexpr std::uint32_t is_override_depth_of_field_far_blur_size = 0x1D;
        inline constexpr std::uint32_t is_override_depth_of_field_far_blur_size_bit = 0x2;
        inline constexpr std::uint32_t is_override_mobile_hq_gaussian = 0x1D;
        inline constexpr std::uint32_t is_override_mobile_hq_gaussian_bit = 0x3;
        inline constexpr std::uint32_t is_override_depth_of_field_occlusion = 0x1D;
        inline constexpr std::uint32_t is_override_depth_of_field_occlusion_bit = 0x4;
        inline constexpr std::uint32_t is_override_depth_of_field_sky_focus_distance = 0x1D;
        inline constexpr std::uint32_t is_override_depth_of_field_sky_focus_distance_bit = 0x5;
        inline constexpr std::uint32_t is_override_depth_of_field_vignette_size = 0x1D;
        inline constexpr std::uint32_t is_override_depth_of_field_vignette_size_bit = 0x6;
        inline constexpr std::uint32_t is_override_motion_blur_amount = 0x1D;
        inline constexpr std::uint32_t is_override_motion_blur_amount_bit = 0x7;
        inline constexpr std::uint32_t is_override_motion_blur_max = 0x1E;
        inline constexpr std::uint32_t is_override_motion_blur_max_bit = 0x0;
        inline constexpr std::uint32_t is_override_motion_blur_target_fps = 0x1E;
        inline constexpr std::uint32_t is_override_motion_blur_target_fps_bit = 0x1;
        inline constexpr std::uint32_t is_override_motion_blur_per_object_size = 0x1E;
        inline constexpr std::uint32_t is_override_motion_blur_per_object_size_bit = 0x2;
        inline constexpr std::uint32_t is_override_screen_percentage = 0x1E;
        inline constexpr std::uint32_t is_override_screen_percentage_bit = 0x3;
        inline constexpr std::uint32_t is_override_reflection_method = 0x1E;
        inline constexpr std::uint32_t is_override_reflection_method_bit = 0x4;
        inline constexpr std::uint32_t is_override_lumen_reflection_quality = 0x1E;
        inline constexpr std::uint32_t is_override_lumen_reflection_quality_bit = 0x5;
        inline constexpr std::uint32_t is_override_screen_space_reflection_intensity = 0x1E;
        inline constexpr std::uint32_t is_override_screen_space_reflection_intensity_bit = 0x6;
        inline constexpr std::uint32_t is_override_screen_space_reflection_quality = 0x1E;
        inline constexpr std::uint32_t is_override_screen_space_reflection_quality_bit = 0x7;
        inline constexpr std::uint32_t is_override_screen_space_reflection_max_roughness = 0x1F;
        inline constexpr std::uint32_t is_override_screen_space_reflection_max_roughness_bit = 0x0;
        inline constexpr std::uint32_t is_override_screen_space_reflection_roughness_scale = 0x1F;
        inline constexpr std::uint32_t is_override_screen_space_reflection_roughness_scale_bit = 0x1;
        inline constexpr std::uint32_t is_override_user_flags = 0x1F;
        inline constexpr std::uint32_t is_override_user_flags_bit = 0x2;
        inline constexpr std::uint32_t is_override_reflections_type = 0x20;
        inline constexpr std::uint32_t is_override_reflections_type_bit = 0x0;
        inline constexpr std::uint32_t is_override_ray_tracing_reflections_max_roughness = 0x20;
        inline constexpr std::uint32_t is_override_ray_tracing_reflections_max_roughness_bit = 0x1;
        inline constexpr std::uint32_t is_override_ray_tracing_reflections_max_bounces = 0x20;
        inline constexpr std::uint32_t is_override_ray_tracing_reflections_max_bounces_bit = 0x2;
        inline constexpr std::uint32_t is_override_ray_tracing_reflections_samples_per_pixel = 0x20;
        inline constexpr std::uint32_t is_override_ray_tracing_reflections_samples_per_pixel_bit = 0x3;
        inline constexpr std::uint32_t is_override_ray_tracing_reflections_shadows = 0x20;
        inline constexpr std::uint32_t is_override_ray_tracing_reflections_shadows_bit = 0x4;
        inline constexpr std::uint32_t is_override_ray_tracing_reflections_translucency = 0x20;
        inline constexpr std::uint32_t is_override_ray_tracing_reflections_translucency_bit = 0x5;
        inline constexpr std::uint32_t is_override_translucency_type = 0x20;
        inline constexpr std::uint32_t is_override_translucency_type_bit = 0x6;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_max_roughness = 0x20;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_max_roughness_bit = 0x7;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_refraction_rays = 0x21;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_refraction_rays_bit = 0x0;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_samples_per_pixel = 0x21;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_samples_per_pixel_bit = 0x1;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_shadows = 0x21;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_shadows_bit = 0x2;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_refraction = 0x21;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_refraction_bit = 0x3;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_max_primary_hit_events = 0x21;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_max_primary_hit_events_bit = 0x4;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_max_secondary_hit_events = 0x21;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_max_secondary_hit_events_bit = 0x5;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_use_ray_traced_refraction = 0x21;
        inline constexpr std::uint32_t is_override_ray_tracing_translucency_use_ray_traced_refraction_bit = 0x6;
        inline constexpr std::uint32_t is_override_dynamic_global_illumination_method = 0x21;
        inline constexpr std::uint32_t is_override_dynamic_global_illumination_method_bit = 0x7;
        inline constexpr std::uint32_t is_override_lumen_scene_lighting_quality = 0x22;
        inline constexpr std::uint32_t is_override_lumen_scene_lighting_quality_bit = 0x0;
        inline constexpr std::uint32_t is_override_lumen_scene_detail = 0x22;
        inline constexpr std::uint32_t is_override_lumen_scene_detail_bit = 0x1;
        inline constexpr std::uint32_t is_override_lumen_scene_view_distance = 0x22;
        inline constexpr std::uint32_t is_override_lumen_scene_view_distance_bit = 0x2;
        inline constexpr std::uint32_t is_override_lumen_scene_lighting_update_speed = 0x22;
        inline constexpr std::uint32_t is_override_lumen_scene_lighting_update_speed_bit = 0x3;
        inline constexpr std::uint32_t is_override_lumen_final_gather_quality = 0x22;
        inline constexpr std::uint32_t is_override_lumen_final_gather_quality_bit = 0x4;
        inline constexpr std::uint32_t is_override_lumen_final_gather_lighting_update_speed = 0x22;
        inline constexpr std::uint32_t is_override_lumen_final_gather_lighting_update_speed_bit = 0x5;
        inline constexpr std::uint32_t is_override_lumen_final_gather_screen_traces = 0x22;
        inline constexpr std::uint32_t is_override_lumen_final_gather_screen_traces_bit = 0x6;
        inline constexpr std::uint32_t is_override_lumen_max_trace_distance = 0x22;
        inline constexpr std::uint32_t is_override_lumen_max_trace_distance_bit = 0x7;
        inline constexpr std::uint32_t is_override_lumen_diffuse_color_boost = 0x23;
        inline constexpr std::uint32_t is_override_lumen_diffuse_color_boost_bit = 0x0;
        inline constexpr std::uint32_t is_override_lumen_ambient_occlusion_intensity = 0x23;
        inline constexpr std::uint32_t is_override_lumen_ambient_occlusion_intensity_bit = 0x1;
        inline constexpr std::uint32_t is_override_lumen_skylight_leaking = 0x23;
        inline constexpr std::uint32_t is_override_lumen_skylight_leaking_bit = 0x2;
        inline constexpr std::uint32_t is_override_lumen_skylight_leaking_tint = 0x23;
        inline constexpr std::uint32_t is_override_lumen_skylight_leaking_tint_bit = 0x3;
        inline constexpr std::uint32_t is_override_lumen_full_skylight_leaking_distance = 0x23;
        inline constexpr std::uint32_t is_override_lumen_full_skylight_leaking_distance_bit = 0x4;
        inline constexpr std::uint32_t is_override_lumen_ray_lighting_mode = 0x24;
        inline constexpr std::uint32_t is_override_lumen_ray_lighting_mode_bit = 0x0;
        inline constexpr std::uint32_t is_override_lumen_reflections_screen_traces = 0x24;
        inline constexpr std::uint32_t is_override_lumen_reflections_screen_traces_bit = 0x1;
        inline constexpr std::uint32_t is_override_lumen_front_layer_translucency_reflections = 0x24;
        inline constexpr std::uint32_t is_override_lumen_front_layer_translucency_reflections_bit = 0x2;
        inline constexpr std::uint32_t is_override_lumen_max_roughness_to_trace_reflections = 0x28;
        inline constexpr std::uint32_t is_override_lumen_max_roughness_to_trace_reflections_bit = 0x0;
        inline constexpr std::uint32_t is_override_lumen_max_reflection_bounces = 0x28;
        inline constexpr std::uint32_t is_override_lumen_max_reflection_bounces_bit = 0x1;
        inline constexpr std::uint32_t is_override_lumen_max_refraction_bounces = 0x28;
        inline constexpr std::uint32_t is_override_lumen_max_refraction_bounces_bit = 0x2;
        inline constexpr std::uint32_t is_override_lumen_surface_cache_resolution = 0x2C;
        inline constexpr std::uint32_t is_override_lumen_surface_cache_resolution_bit = 0x0;
        inline constexpr std::uint32_t is_override_ray_tracing_gi = 0x30;
        inline constexpr std::uint32_t is_override_ray_tracing_gi_bit = 0x0;
        inline constexpr std::uint32_t is_override_ray_tracing_gi_max_bounces = 0x30;
        inline constexpr std::uint32_t is_override_ray_tracing_gi_max_bounces_bit = 0x1;
        inline constexpr std::uint32_t is_override_ray_tracing_gi_samples_per_pixel = 0x30;
        inline constexpr std::uint32_t is_override_ray_tracing_gi_samples_per_pixel_bit = 0x2;
        inline constexpr std::uint32_t is_override_path_tracing_max_bounces = 0x30;
        inline constexpr std::uint32_t is_override_path_tracing_max_bounces_bit = 0x3;
        inline constexpr std::uint32_t is_override_path_tracing_samples_per_pixel = 0x30;
        inline constexpr std::uint32_t is_override_path_tracing_samples_per_pixel_bit = 0x4;
        inline constexpr std::uint32_t is_override_path_tracing_max_path_intensity = 0x30;
        inline constexpr std::uint32_t is_override_path_tracing_max_path_intensity_bit = 0x5;
        inline constexpr std::uint32_t is_override_path_tracing_enable_emissive_materials = 0x30;
        inline constexpr std::uint32_t is_override_path_tracing_enable_emissive_materials_bit = 0x6;
        inline constexpr std::uint32_t is_override_path_tracing_enable_reference_dof = 0x30;
        inline constexpr std::uint32_t is_override_path_tracing_enable_reference_dof_bit = 0x7;
        inline constexpr std::uint32_t is_override_path_tracing_enable_reference_atmosphere = 0x31;
        inline constexpr std::uint32_t is_override_path_tracing_enable_reference_atmosphere_bit = 0x0;
        inline constexpr std::uint32_t is_override_path_tracing_enable_denoiser = 0x31;
        inline constexpr std::uint32_t is_override_path_tracing_enable_denoiser_bit = 0x1;
        inline constexpr std::uint32_t is_override_path_tracing_include_emissive = 0x31;
        inline constexpr std::uint32_t is_override_path_tracing_include_emissive_bit = 0x2;
        inline constexpr std::uint32_t is_override_path_tracing_include_diffuse = 0x31;
        inline constexpr std::uint32_t is_override_path_tracing_include_diffuse_bit = 0x3;
        inline constexpr std::uint32_t is_override_path_tracing_include_indirect_diffuse = 0x31;
        inline constexpr std::uint32_t is_override_path_tracing_include_indirect_diffuse_bit = 0x4;
        inline constexpr std::uint32_t is_override_path_tracing_include_specular = 0x31;
        inline constexpr std::uint32_t is_override_path_tracing_include_specular_bit = 0x5;
        inline constexpr std::uint32_t is_override_path_tracing_include_indirect_specular = 0x31;
        inline constexpr std::uint32_t is_override_path_tracing_include_indirect_specular_bit = 0x6;
        inline constexpr std::uint32_t is_override_path_tracing_include_volume = 0x31;
        inline constexpr std::uint32_t is_override_path_tracing_include_volume_bit = 0x7;
        inline constexpr std::uint32_t is_override_path_tracing_include_indirect_volume = 0x32;
        inline constexpr std::uint32_t is_override_path_tracing_include_indirect_volume_bit = 0x0;
        inline constexpr std::uint32_t is_mobile_hq_gaussian = 0x34;
        inline constexpr std::uint32_t is_mobile_hq_gaussian_bit = 0x0;
        inline constexpr std::uint32_t bloom_method = 0x35;
        inline constexpr std::uint32_t auto_exposure_method = 0x36;
        inline constexpr std::uint32_t temperature_type = 0x37;
        inline constexpr std::uint32_t white_temp = 0x38;
        inline constexpr std::uint32_t white_tint = 0x3C;
        inline constexpr std::uint32_t color_saturation = 0x40;
        inline constexpr std::uint32_t color_contrast = 0x60;
        inline constexpr std::uint32_t color_gamma = 0x80;
        inline constexpr std::uint32_t color_gain = 0xA0;
        inline constexpr std::uint32_t color_offset = 0xC0;
        inline constexpr std::uint32_t color_saturation_shadows = 0xE0;
        inline constexpr std::uint32_t color_contrast_shadows = 0x100;
        inline constexpr std::uint32_t color_gamma_shadows = 0x120;
        inline constexpr std::uint32_t color_gain_shadows = 0x140;
        inline constexpr std::uint32_t color_offset_shadows = 0x160;
        inline constexpr std::uint32_t color_saturation_midtones = 0x180;
        inline constexpr std::uint32_t color_contrast_midtones = 0x1A0;
        inline constexpr std::uint32_t color_gamma_midtones = 0x1C0;
        inline constexpr std::uint32_t color_gain_midtones = 0x1E0;
        inline constexpr std::uint32_t color_offset_midtones = 0x200;
        inline constexpr std::uint32_t color_saturation_highlights = 0x220;
        inline constexpr std::uint32_t color_contrast_highlights = 0x240;
        inline constexpr std::uint32_t color_gamma_highlights = 0x260;
        inline constexpr std::uint32_t color_gain_highlights = 0x280;
        inline constexpr std::uint32_t color_offset_highlights = 0x2A0;
        inline constexpr std::uint32_t color_correction_highlights_min = 0x2C0;
        inline constexpr std::uint32_t color_correction_highlights_max = 0x2C4;
        inline constexpr std::uint32_t color_correction_shadows_max = 0x2C8;
        inline constexpr std::uint32_t blue_correction = 0x2CC;
        inline constexpr std::uint32_t expand_gamut = 0x2D0;
        inline constexpr std::uint32_t tone_curve_amount = 0x2D4;
        inline constexpr std::uint32_t tonemapping_method = 0x2D8;
        inline constexpr std::uint32_t film_slope = 0x2DC;
        inline constexpr std::uint32_t film_toe = 0x2E0;
        inline constexpr std::uint32_t film_shoulder = 0x2E4;
        inline constexpr std::uint32_t film_black_clip = 0x2E8;
        inline constexpr std::uint32_t film_white_clip = 0x2EC;
        inline constexpr std::uint32_t scene_color_tint = 0x2F0;
        inline constexpr std::uint32_t scene_fringe_intensity = 0x300;
        inline constexpr std::uint32_t chromatic_aberration_start_offset = 0x304;
        inline constexpr std::uint32_t bloom_intensity = 0x308;
        inline constexpr std::uint32_t bloom_gaussian_intensity = 0x30C;
        inline constexpr std::uint32_t bloom_threshold = 0x310;
        inline constexpr std::uint32_t bloom_size_scale = 0x314;
        inline constexpr std::uint32_t bloom1_size = 0x318;
        inline constexpr std::uint32_t bloom2_size = 0x31C;
        inline constexpr std::uint32_t bloom3_size = 0x320;
        inline constexpr std::uint32_t bloom4_size = 0x324;
        inline constexpr std::uint32_t bloom5_size = 0x328;
        inline constexpr std::uint32_t bloom6_size = 0x32C;
        inline constexpr std::uint32_t bloom1_tint = 0x330;
        inline constexpr std::uint32_t bloom2_tint = 0x340;
        inline constexpr std::uint32_t bloom3_tint = 0x350;
        inline constexpr std::uint32_t bloom4_tint = 0x360;
        inline constexpr std::uint32_t bloom5_tint = 0x370;
        inline constexpr std::uint32_t bloom6_tint = 0x380;
        inline constexpr std::uint32_t bloom_convolution_intensity = 0x390;
        inline constexpr std::uint32_t bloom_convolution_scatter_dispersion = 0x394;
        inline constexpr std::uint32_t bloom_convolution_size = 0x398;
        inline constexpr std::uint32_t bloom_convolution_texture = 0x3A0;
        inline constexpr std::uint32_t bloom_convolution_center_uv = 0x3A8;
        inline constexpr std::uint32_t bloom_convolution_pre_filter_min = 0x3B8;
        inline constexpr std::uint32_t bloom_convolution_pre_filter_max = 0x3BC;
        inline constexpr std::uint32_t bloom_convolution_pre_filter_mult = 0x3C0;
        inline constexpr std::uint32_t bloom_convolution_buffer_scale = 0x3C4;
        inline constexpr std::uint32_t bloom_dirt_mask = 0x3C8;
        inline constexpr std::uint32_t bloom_dirt_mask_intensity = 0x3D0;
        inline constexpr std::uint32_t bloom_dirt_mask_tint = 0x3D4;
        inline constexpr std::uint32_t dynamic_global_illumination_method = 0x3E4;
        inline constexpr std::uint32_t indirect_lighting_color = 0x3E8;
        inline constexpr std::uint32_t indirect_lighting_intensity = 0x3F8;
        inline constexpr std::uint32_t lumen_ray_lighting_mode = 0x3FC;
        inline constexpr std::uint32_t lumen_scene_lighting_quality = 0x400;
        inline constexpr std::uint32_t lumen_scene_detail = 0x404;
        inline constexpr std::uint32_t lumen_scene_view_distance = 0x408;
        inline constexpr std::uint32_t lumen_scene_lighting_update_speed = 0x40C;
        inline constexpr std::uint32_t lumen_final_gather_quality = 0x410;
        inline constexpr std::uint32_t lumen_final_gather_lighting_update_speed = 0x414;
        inline constexpr std::uint32_t lumen_final_gather_screen_traces = 0x418;
        inline constexpr std::uint32_t lumen_final_gather_screen_traces_bit = 0x0;
        inline constexpr std::uint32_t lumen_max_trace_distance = 0x41C;
        inline constexpr std::uint32_t lumen_diffuse_color_boost = 0x420;
        inline constexpr std::uint32_t lumen_ambient_occlusion_intensity = 0x424;
        inline constexpr std::uint32_t lumen_skylight_leaking = 0x428;
        inline constexpr std::uint32_t lumen_skylight_leaking_tint = 0x42C;
        inline constexpr std::uint32_t lumen_full_skylight_leaking_distance = 0x43C;
        inline constexpr std::uint32_t lumen_surface_cache_resolution = 0x440;
        inline constexpr std::uint32_t reflection_method = 0x444;
        inline constexpr std::uint32_t reflections_type = 0x445;
        inline constexpr std::uint32_t lumen_reflection_quality = 0x448;
        inline constexpr std::uint32_t lumen_reflections_screen_traces = 0x44C;
        inline constexpr std::uint32_t lumen_reflections_screen_traces_bit = 0x0;
        inline constexpr std::uint32_t lumen_front_layer_translucency_reflections = 0x44C;
        inline constexpr std::uint32_t lumen_front_layer_translucency_reflections_bit = 0x1;
        inline constexpr std::uint32_t lumen_max_roughness_to_trace_reflections = 0x450;
        inline constexpr std::uint32_t lumen_max_reflection_bounces = 0x454;
        inline constexpr std::uint32_t lumen_max_refraction_bounces = 0x458;
        inline constexpr std::uint32_t screen_space_reflection_intensity = 0x45C;
        inline constexpr std::uint32_t screen_space_reflection_quality = 0x460;
        inline constexpr std::uint32_t screen_space_reflection_max_roughness = 0x464;
        inline constexpr std::uint32_t is_mega_lights = 0x468;
        inline constexpr std::uint32_t is_mega_lights_bit = 0x0;
        inline constexpr std::uint32_t mega_lights_front_layer_translucency = 0x468;
        inline constexpr std::uint32_t mega_lights_front_layer_translucency_bit = 0x1;
        inline constexpr std::uint32_t ambient_cubemap_tint = 0x46C;
        inline constexpr std::uint32_t ambient_cubemap_intensity = 0x47C;
        inline constexpr std::uint32_t ambient_cubemap = 0x480;
        inline constexpr std::uint32_t camera_shutter_speed = 0x488;
        inline constexpr std::uint32_t camera_iso = 0x48C;
        inline constexpr std::uint32_t depth_of_field_fstop = 0x490;
        inline constexpr std::uint32_t depth_of_field_min_fstop = 0x494;
        inline constexpr std::uint32_t depth_of_field_blade_count = 0x498;
        inline constexpr std::uint32_t auto_exposure_bias = 0x49C;
        inline constexpr std::uint32_t auto_exposure_bias_backup = 0x4A0;
        inline constexpr std::uint32_t is_override_auto_exposure_bias_backup = 0x4A4;
        inline constexpr std::uint32_t is_override_auto_exposure_bias_backup_bit = 0x0;
        inline constexpr std::uint32_t auto_exposure_apply_physical_camera_exposure = 0x4A8;
        inline constexpr std::uint32_t auto_exposure_apply_physical_camera_exposure_bit = 0x0;
        inline constexpr std::uint32_t auto_exposure_bias_curve = 0x4B0;
        inline constexpr std::uint32_t auto_exposure_meter_mask = 0x4B8;
        inline constexpr std::uint32_t auto_exposure_low_percent = 0x4C0;
        inline constexpr std::uint32_t auto_exposure_high_percent = 0x4C4;
        inline constexpr std::uint32_t auto_exposure_min_brightness = 0x4C8;
        inline constexpr std::uint32_t auto_exposure_max_brightness = 0x4CC;
        inline constexpr std::uint32_t auto_exposure_speed_up = 0x4D0;
        inline constexpr std::uint32_t auto_exposure_speed_down = 0x4D4;
        inline constexpr std::uint32_t histogram_log_min = 0x4D8;
        inline constexpr std::uint32_t histogram_log_max = 0x4DC;
        inline constexpr std::uint32_t auto_exposure_calibration_constant = 0x4E0;
        inline constexpr std::uint32_t local_exposure_method = 0x4E4;
        inline constexpr std::uint32_t local_exposure_contrast_scale = 0x4E8;
        inline constexpr std::uint32_t local_exposure_highlight_contrast_scale = 0x4EC;
        inline constexpr std::uint32_t local_exposure_shadow_contrast_scale = 0x4F0;
        inline constexpr std::uint32_t local_exposure_highlight_contrast_curve = 0x4F8;
        inline constexpr std::uint32_t local_exposure_shadow_contrast_curve = 0x500;
        inline constexpr std::uint32_t local_exposure_highlight_threshold = 0x508;
        inline constexpr std::uint32_t local_exposure_shadow_threshold = 0x50C;
        inline constexpr std::uint32_t local_exposure_detail_strength = 0x510;
        inline constexpr std::uint32_t local_exposure_blurred_luminance_blend = 0x514;
        inline constexpr std::uint32_t local_exposure_blurred_luminance_kernel_size_percent = 0x518;
        inline constexpr std::uint32_t local_exposure_highlight_threshold_strength = 0x51C;
        inline constexpr std::uint32_t local_exposure_shadow_threshold_strength = 0x520;
        inline constexpr std::uint32_t local_exposure_middle_grey_bias = 0x524;
        inline constexpr std::uint32_t lens_flare_intensity = 0x528;
        inline constexpr std::uint32_t lens_flare_tint = 0x52C;
        inline constexpr std::uint32_t lens_flare_bokeh_size = 0x53C;
        inline constexpr std::uint32_t lens_flare_threshold = 0x540;
        inline constexpr std::uint32_t lens_flare_bokeh_shape = 0x548;
        inline constexpr std::uint32_t vignette_intensity = 0x5D0;
        inline constexpr std::uint32_t vignette_type = 0x5D4;
        inline constexpr std::uint32_t vignette_center = 0x5D8;
        inline constexpr std::uint32_t vignette_color = 0x5E0;
        inline constexpr std::uint32_t vignette_size = 0x5F0;
        inline constexpr std::uint32_t vignette_softness = 0x5F8;
        inline constexpr std::uint32_t vignette_texture = 0x600;
        inline constexpr std::uint32_t sharpen = 0x608;
        inline constexpr std::uint32_t grain_jitter = 0x60C;
        inline constexpr std::uint32_t grain_intensity = 0x610;
        inline constexpr std::uint32_t film_grain_intensity = 0x614;
        inline constexpr std::uint32_t film_grain_intensity_shadows = 0x618;
        inline constexpr std::uint32_t film_grain_intensity_midtones = 0x61C;
        inline constexpr std::uint32_t film_grain_intensity_highlights = 0x620;
        inline constexpr std::uint32_t film_grain_shadows_max = 0x624;
        inline constexpr std::uint32_t film_grain_highlights_min = 0x628;
        inline constexpr std::uint32_t film_grain_highlights_max = 0x62C;
        inline constexpr std::uint32_t film_grain_scale = 0x630;
        inline constexpr std::uint32_t film_grain_texture = 0x638;
        inline constexpr std::uint32_t ambient_occlusion_intensity = 0x640;
        inline constexpr std::uint32_t ambient_occlusion_static_fraction = 0x644;
        inline constexpr std::uint32_t ambient_occlusion_radius = 0x648;
        inline constexpr std::uint32_t ambient_occlusion_radius_in_ws = 0x64C;
        inline constexpr std::uint32_t ambient_occlusion_radius_in_ws_bit = 0x0;
        inline constexpr std::uint32_t ambient_occlusion_fade_distance = 0x650;
        inline constexpr std::uint32_t ambient_occlusion_fade_radius = 0x654;
        inline constexpr std::uint32_t ambient_occlusion_distance = 0x658;
        inline constexpr std::uint32_t ambient_occlusion_power = 0x65C;
        inline constexpr std::uint32_t ambient_occlusion_bias = 0x660;
        inline constexpr std::uint32_t ambient_occlusion_quality = 0x664;
        inline constexpr std::uint32_t ambient_occlusion_mip_blend = 0x668;
        inline constexpr std::uint32_t ambient_occlusion_mip_scale = 0x66C;
        inline constexpr std::uint32_t ambient_occlusion_mip_threshold = 0x670;
        inline constexpr std::uint32_t ambient_occlusion_temporal_blend_weight = 0x674;
        inline constexpr std::uint32_t ray_tracing_ao = 0x678;
        inline constexpr std::uint32_t ray_tracing_ao_bit = 0x0;
        inline constexpr std::uint32_t ray_tracing_ao_samples_per_pixel = 0x67C;
        inline constexpr std::uint32_t ray_tracing_ao_intensity = 0x680;
        inline constexpr std::uint32_t ray_tracing_ao_radius = 0x684;
        inline constexpr std::uint32_t color_grading_intensity = 0x688;
        inline constexpr std::uint32_t color_grading_lut = 0x690;
        inline constexpr std::uint32_t depth_of_field_enabled = 0x698;
        inline constexpr std::uint32_t depth_of_field_sensor_width = 0x69C;
        inline constexpr std::uint32_t depth_of_field_squeeze_factor = 0x6A0;
        inline constexpr std::uint32_t depth_of_field_focal_distance = 0x6A4;
        inline constexpr std::uint32_t depth_of_field_depth_blur_amount = 0x6A8;
        inline constexpr std::uint32_t depth_of_field_depth_blur_radius = 0x6AC;
        inline constexpr std::uint32_t depth_of_field_use_hair_depth = 0x6B0;
        inline constexpr std::uint32_t depth_of_field_use_hair_depth_bit = 0x0;
        inline constexpr std::uint32_t depth_of_field_petzval_bokeh = 0x6B4;
        inline constexpr std::uint32_t depth_of_field_petzval_bokeh_falloff = 0x6B8;
        inline constexpr std::uint32_t depth_of_field_petzval_exclusion_box_extents = 0x6BC;
        inline constexpr std::uint32_t depth_of_field_petzval_exclusion_box_radius = 0x6C4;
        inline constexpr std::uint32_t depth_of_field_aspect_ratio_scalar = 0x6C8;
        inline constexpr std::uint32_t depth_of_field_barrel_radius = 0x6CC;
        inline constexpr std::uint32_t depth_of_field_barrel_length = 0x6D0;
        inline constexpr std::uint32_t depth_of_field_focal_region = 0x6F8;
        inline constexpr std::uint32_t depth_of_field_near_transition_region = 0x6FC;
        inline constexpr std::uint32_t depth_of_field_far_transition_region = 0x700;
        inline constexpr std::uint32_t depth_of_field_scale = 0x704;
        inline constexpr std::uint32_t depth_of_field_near_blur_size = 0x708;
        inline constexpr std::uint32_t depth_of_field_far_blur_size = 0x70C;
        inline constexpr std::uint32_t depth_of_field_occlusion = 0x710;
        inline constexpr std::uint32_t depth_of_field_sky_focus_distance = 0x714;
        inline constexpr std::uint32_t depth_of_field_vignette_size = 0x718;
        inline constexpr std::uint32_t motion_blur_amount = 0x71C;
        inline constexpr std::uint32_t motion_blur_max = 0x720;
        inline constexpr std::uint32_t motion_blur_target_fps = 0x724;
        inline constexpr std::uint32_t motion_blur_per_object_size = 0x728;
        inline constexpr std::uint32_t lpv_intensity = 0x72C;
        inline constexpr std::uint32_t lpv_vpl_injection_bias = 0x730;
        inline constexpr std::uint32_t lpv_size = 0x734;
        inline constexpr std::uint32_t lpv_secondary_occlusion_intensity = 0x738;
        inline constexpr std::uint32_t lpv_secondary_bounce_intensity = 0x73C;
        inline constexpr std::uint32_t lpv_geometry_volume_bias = 0x740;
        inline constexpr std::uint32_t lpv_emissive_injection_intensity = 0x744;
        inline constexpr std::uint32_t lpv_directional_occlusion_intensity = 0x748;
        inline constexpr std::uint32_t lpv_directional_occlusion_radius = 0x74C;
        inline constexpr std::uint32_t lpv_diffuse_occlusion_exponent = 0x750;
        inline constexpr std::uint32_t lpv_specular_occlusion_exponent = 0x754;
        inline constexpr std::uint32_t lpv_diffuse_occlusion_intensity = 0x758;
        inline constexpr std::uint32_t lpv_specular_occlusion_intensity = 0x75C;
        inline constexpr std::uint32_t translucency_type = 0x760;
        inline constexpr std::uint32_t ray_tracing_translucency_max_roughness = 0x764;
        inline constexpr std::uint32_t ray_tracing_translucency_refraction_rays = 0x768;
        inline constexpr std::uint32_t ray_tracing_translucency_samples_per_pixel = 0x76C;
        inline constexpr std::uint32_t ray_tracing_translucency_max_primary_hit_events = 0x770;
        inline constexpr std::uint32_t ray_tracing_translucency_max_secondary_hit_events = 0x774;
        inline constexpr std::uint32_t ray_tracing_translucency_shadows = 0x778;
        inline constexpr std::uint32_t ray_tracing_translucency_refraction = 0x779;
        inline constexpr std::uint32_t ray_tracing_translucency_refraction_bit = 0x0;
        inline constexpr std::uint32_t ray_tracing_translucency_use_ray_traced_refraction = 0x779;
        inline constexpr std::uint32_t ray_tracing_translucency_use_ray_traced_refraction_bit = 0x1;
        inline constexpr std::uint32_t path_tracing_max_bounces = 0x77C;
        inline constexpr std::uint32_t path_tracing_samples_per_pixel = 0x780;
        inline constexpr std::uint32_t path_tracing_max_path_intensity = 0x784;
        inline constexpr std::uint32_t path_tracing_enable_emissive_materials = 0x788;
        inline constexpr std::uint32_t path_tracing_enable_emissive_materials_bit = 0x0;
        inline constexpr std::uint32_t path_tracing_enable_reference_dof = 0x788;
        inline constexpr std::uint32_t path_tracing_enable_reference_dof_bit = 0x1;
        inline constexpr std::uint32_t path_tracing_enable_reference_atmosphere = 0x788;
        inline constexpr std::uint32_t path_tracing_enable_reference_atmosphere_bit = 0x2;
        inline constexpr std::uint32_t path_tracing_enable_denoiser = 0x788;
        inline constexpr std::uint32_t path_tracing_enable_denoiser_bit = 0x3;
        inline constexpr std::uint32_t path_tracing_include_emissive = 0x788;
        inline constexpr std::uint32_t path_tracing_include_emissive_bit = 0x4;
        inline constexpr std::uint32_t path_tracing_include_diffuse = 0x788;
        inline constexpr std::uint32_t path_tracing_include_diffuse_bit = 0x5;
        inline constexpr std::uint32_t path_tracing_include_indirect_diffuse = 0x788;
        inline constexpr std::uint32_t path_tracing_include_indirect_diffuse_bit = 0x6;
        inline constexpr std::uint32_t path_tracing_include_specular = 0x788;
        inline constexpr std::uint32_t path_tracing_include_specular_bit = 0x7;
        inline constexpr std::uint32_t path_tracing_include_indirect_specular = 0x789;
        inline constexpr std::uint32_t path_tracing_include_indirect_specular_bit = 0x0;
        inline constexpr std::uint32_t path_tracing_include_volume = 0x789;
        inline constexpr std::uint32_t path_tracing_include_volume_bit = 0x1;
        inline constexpr std::uint32_t path_tracing_include_indirect_volume = 0x789;
        inline constexpr std::uint32_t path_tracing_include_indirect_volume_bit = 0x2;
        inline constexpr std::uint32_t lpv_fade_range = 0x78C;
        inline constexpr std::uint32_t lpv_directional_occlusion_fade_range = 0x790;
        inline constexpr std::uint32_t screen_percentage = 0x794;
        inline constexpr std::uint32_t user_flags = 0x798;
        inline constexpr std::uint32_t weighted_blendables = 0x7A0;
        inline constexpr std::uint32_t byte_size = 0x7B0;
    }

    namespace apost_process_volume {
        inline constexpr std::uint32_t settings = 0x2F0;
        inline constexpr std::uint32_t priority = 0xAA0;
        inline constexpr std::uint32_t blend_radius = 0xAA4;
        inline constexpr std::uint32_t blend_weight = 0xAA8;
        inline constexpr std::uint32_t is_enabled = 0xAAC;
        inline constexpr std::uint32_t is_enabled_bit = 0x0;
        inline constexpr std::uint32_t is_unbound = 0xAAC;
        inline constexpr std::uint32_t is_unbound_bit = 0x1;
        inline constexpr std::uint32_t volume_guid = 0xAB0;
        inline constexpr std::uint32_t byte_size = 0xAC0;
    }

    namespace aexponential_height_fog {
        inline constexpr std::uint32_t component = 0x2A8;
        inline constexpr std::uint32_t is_enabled = 0x2B0;
        inline constexpr std::uint32_t is_enabled_bit = 0x0;
        inline constexpr std::uint32_t byte_size = 0x2B8;
    }

    namespace ufog_component {
        inline constexpr std::uint32_t fog_density = 0x250;
        inline constexpr std::uint32_t fog_height_falloff = 0x254;
        inline constexpr std::uint32_t second_fog_data = 0x258;
        inline constexpr std::uint32_t fog_inscattering_color = 0x264;
        inline constexpr std::uint32_t fog_inscattering_luminance = 0x274;
        inline constexpr std::uint32_t sky_atmosphere_ambient_contribution_color_scale = 0x284;
        inline constexpr std::uint32_t inscattering_color_cubemap = 0x298;
        inline constexpr std::uint32_t sky_light_capture_affects_height_fog_strength = 0x2A0;
        inline constexpr std::uint32_t sky_light_capture_affects_height_fog_roughness = 0x2A4;
        inline constexpr std::uint32_t inscattering_color_cubemap_angle = 0x2A8;
        inline constexpr std::uint32_t inscattering_texture_tint = 0x2AC;
        inline constexpr std::uint32_t fully_directional_inscattering_color_distance = 0x2BC;
        inline constexpr std::uint32_t non_directional_inscattering_color_distance = 0x2C0;
        inline constexpr std::uint32_t directional_inscattering_exponent = 0x2C4;
        inline constexpr std::uint32_t directional_inscattering_start_distance = 0x2C8;
        inline constexpr std::uint32_t directional_inscattering_color = 0x2CC;
        inline constexpr std::uint32_t directional_inscattering_luminance = 0x2DC;
        inline constexpr std::uint32_t fog_max_opacity = 0x2EC;
        inline constexpr std::uint32_t start_distance = 0x2F0;
        inline constexpr std::uint32_t end_distance = 0x2F4;
        inline constexpr std::uint32_t fog_cutoff_distance = 0x2F8;
        inline constexpr std::uint32_t is_enable_volumetric_fog = 0x2FC;
        inline constexpr std::uint32_t volumetric_fog_scattering_distribution = 0x300;
        inline constexpr std::uint32_t volumetric_fog_albedo = 0x304;
        inline constexpr std::uint32_t volumetric_fog_emissive = 0x308;
        inline constexpr std::uint32_t volumetric_fog_extinction_scale = 0x318;
        inline constexpr std::uint32_t volumetric_fog_distance = 0x31C;
        inline constexpr std::uint32_t volumetric_fog_start_distance = 0x320;
        inline constexpr std::uint32_t volumetric_fog_near_fade_in_distance = 0x324;
        inline constexpr std::uint32_t volumetric_fog_static_lighting_scattering_intensity = 0x328;
        inline constexpr std::uint32_t is_override_light_colors_with_fog_inscattering_colors = 0x32C;
        inline constexpr std::uint32_t is_enable_fsss = 0x32D;
        inline constexpr std::uint32_t fsss_scene_color_scattering_amount_scale = 0x330;
        inline constexpr std::uint32_t fsss_scene_color_scattering_amount_power = 0x334;
        inline constexpr std::uint32_t fsss_spread_scale = 0x338;
        inline constexpr std::uint32_t fsss_blur_control = 0x33C;
        inline constexpr std::uint32_t is_holdout = 0x340;
        inline constexpr std::uint32_t is_holdout_bit = 0x0;
        inline constexpr std::uint32_t is_render_in_main_pass = 0x340;
        inline constexpr std::uint32_t is_render_in_main_pass_bit = 0x1;
        inline constexpr std::uint32_t is_visible_in_reflection_captures = 0x340;
        inline constexpr std::uint32_t is_visible_in_reflection_captures_bit = 0x2;
        inline constexpr std::uint32_t is_visible_in_real_time_sky_captures = 0x340;
        inline constexpr std::uint32_t is_visible_in_real_time_sky_captures_bit = 0x3;
        inline constexpr std::uint32_t byte_size = 0x350;
    }

    namespace asky_light {
        inline constexpr std::uint32_t light_component = 0x2A8;
        inline constexpr std::uint32_t is_enabled = 0x2B0;
        inline constexpr std::uint32_t is_enabled_bit = 0x0;
        inline constexpr std::uint32_t byte_size = 0x2B8;
    }

    namespace usky_light_component {
        inline constexpr std::uint32_t is_real_time_capture = 0x2A0;
        inline constexpr std::uint32_t source_type = 0x2A1;
        inline constexpr std::uint32_t cubemap = 0x2A8;
        inline constexpr std::uint32_t source_cubemap_angle = 0x2B0;
        inline constexpr std::uint32_t cubemap_resolution = 0x2B4;
        inline constexpr std::uint32_t sky_distance_threshold = 0x2B8;
        inline constexpr std::uint32_t is_capture_emissive_only = 0x2BC;
        inline constexpr std::uint32_t is_lower_hemisphere_is_black = 0x2BD;
        inline constexpr std::uint32_t lower_hemisphere_color = 0x2C0;
        inline constexpr std::uint32_t occlusion_max_distance = 0x2D0;
        inline constexpr std::uint32_t contrast = 0x2D4;
        inline constexpr std::uint32_t occlusion_exponent = 0x2D8;
        inline constexpr std::uint32_t min_occlusion = 0x2DC;
        inline constexpr std::uint32_t occlusion_tint = 0x2E0;
        inline constexpr std::uint32_t is_cloud_ambient_occlusion = 0x2E4;
        inline constexpr std::uint32_t is_cloud_ambient_occlusion_bit = 0x0;
        inline constexpr std::uint32_t cloud_ambient_occlusion_strength = 0x2E8;
        inline constexpr std::uint32_t cloud_ambient_occlusion_extent = 0x2EC;
        inline constexpr std::uint32_t cloud_ambient_occlusion_map_resolution_scale = 0x2F0;
        inline constexpr std::uint32_t cloud_ambient_occlusion_aperture_scale = 0x2F4;
        inline constexpr std::uint32_t occlusion_combine_mode = 0x2F8;
        inline constexpr std::uint32_t blend_destination_cubemap = 0x3A8;
        inline constexpr std::uint32_t byte_size = 0x480;
    }

    namespace alight {
        inline constexpr std::uint32_t light_component = 0x2A8;
        inline constexpr std::uint32_t is_enabled = 0x2B0;
        inline constexpr std::uint32_t is_enabled_bit = 0x0;
        inline constexpr std::uint32_t byte_size = 0x2B8;
    }

    namespace ulight_base {
        inline constexpr std::uint32_t original_light_guid = 0x250;
        inline constexpr std::uint32_t light_guid = 0x260;
        inline constexpr std::uint32_t brightness = 0x270;
        inline constexpr std::uint32_t intensity = 0x274;
        inline constexpr std::uint32_t light_color = 0x278;
        inline constexpr std::uint32_t is_affects_world = 0x27C;
        inline constexpr std::uint32_t is_affects_world_bit = 0x0;
        inline constexpr std::uint32_t cast_shadows = 0x27C;
        inline constexpr std::uint32_t cast_shadows_bit = 0x1;
        inline constexpr std::uint32_t cast_static_shadows = 0x27C;
        inline constexpr std::uint32_t cast_static_shadows_bit = 0x2;
        inline constexpr std::uint32_t cast_dynamic_shadows = 0x27C;
        inline constexpr std::uint32_t cast_dynamic_shadows_bit = 0x3;
        inline constexpr std::uint32_t is_affect_translucent_lighting = 0x27C;
        inline constexpr std::uint32_t is_affect_translucent_lighting_bit = 0x4;
        inline constexpr std::uint32_t is_transmission = 0x27C;
        inline constexpr std::uint32_t is_transmission_bit = 0x5;
        inline constexpr std::uint32_t is_cast_volumetric_shadow = 0x27C;
        inline constexpr std::uint32_t is_cast_volumetric_shadow_bit = 0x6;
        inline constexpr std::uint32_t is_cast_deep_shadow = 0x27C;
        inline constexpr std::uint32_t is_cast_deep_shadow_bit = 0x7;
        inline constexpr std::uint32_t is_cast_raytraced_shadow = 0x27D;
        inline constexpr std::uint32_t is_cast_raytraced_shadow_bit = 0x0;
        inline constexpr std::uint32_t cast_raytraced_shadow = 0x280;
        inline constexpr std::uint32_t is_affect_reflection = 0x284;
        inline constexpr std::uint32_t is_affect_reflection_bit = 0x0;
        inline constexpr std::uint32_t is_affect_global_illumination = 0x284;
        inline constexpr std::uint32_t is_affect_global_illumination_bit = 0x1;
        inline constexpr std::uint32_t deep_shadow_layer_distribution = 0x288;
        inline constexpr std::uint32_t indirect_lighting_intensity = 0x28C;
        inline constexpr std::uint32_t volumetric_scattering_intensity = 0x290;
        inline constexpr std::uint32_t samples_per_pixel = 0x294;
        inline constexpr std::uint32_t byte_size = 0x2A0;
    }

    namespace ulight_component {
        inline constexpr std::uint32_t temperature = 0x2A0;
        inline constexpr std::uint32_t max_draw_distance = 0x2A4;
        inline constexpr std::uint32_t max_distance_fade_range = 0x2A8;
        inline constexpr std::uint32_t is_use_temperature = 0x2AC;
        inline constexpr std::uint32_t is_use_temperature_bit = 0x0;
        inline constexpr std::uint32_t shadow_map_channel = 0x2B0;
        inline constexpr std::uint32_t preview_shadow_map_channel = 0x2B4;
        inline constexpr std::uint32_t min_roughness = 0x2B8;
        inline constexpr std::uint32_t specular_scale = 0x2BC;
        inline constexpr std::uint32_t diffuse_scale = 0x2C0;
        inline constexpr std::uint32_t shadow_resolution_scale = 0x2C4;
        inline constexpr std::uint32_t shadow_bias = 0x2C8;
        inline constexpr std::uint32_t shadow_slope_bias = 0x2CC;
        inline constexpr std::uint32_t shadow_sharpen = 0x2D0;
        inline constexpr std::uint32_t contact_shadow_length = 0x2D4;
        inline constexpr std::uint32_t contact_shadow_length_in_ws = 0x2D8;
        inline constexpr std::uint32_t contact_shadow_length_in_ws_bit = 0x0;
        inline constexpr std::uint32_t contact_shadow_casting_intensity = 0x2DC;
        inline constexpr std::uint32_t contact_shadow_non_casting_intensity = 0x2E0;
        inline constexpr std::uint32_t inverse_squared_falloff = 0x2E4;
        inline constexpr std::uint32_t inverse_squared_falloff_bit = 0x0;
        inline constexpr std::uint32_t cast_translucent_shadows = 0x2E4;
        inline constexpr std::uint32_t cast_translucent_shadows_bit = 0x1;
        inline constexpr std::uint32_t is_cast_shadows_from_cinematic_objects_only = 0x2E4;
        inline constexpr std::uint32_t is_cast_shadows_from_cinematic_objects_only_bit = 0x2;
        inline constexpr std::uint32_t is_force_cached_shadows_for_movable_primitives = 0x2E4;
        inline constexpr std::uint32_t is_force_cached_shadows_for_movable_primitives_bit = 0x3;
        inline constexpr std::uint32_t is_allow_mega_lights = 0x2E4;
        inline constexpr std::uint32_t is_allow_mega_lights_bit = 0x4;
        inline constexpr std::uint32_t mega_lights_shadow_method = 0x2E8;
        inline constexpr std::uint32_t is_override_ray_end_bias = 0x2EC;
        inline constexpr std::uint32_t is_override_ray_end_bias_bit = 0x0;
        inline constexpr std::uint32_t ray_end_bias = 0x2F0;
        inline constexpr std::uint32_t lighting_channels = 0x2F4;
        inline constexpr std::uint32_t view_lighting_channels = 0x2F5;
        inline constexpr std::uint32_t light_function_material = 0x2F8;
        inline constexpr std::uint32_t light_function_scale = 0x300;
        inline constexpr std::uint32_t ies_texture = 0x318;
        inline constexpr std::uint32_t is_use_ies_brightness = 0x320;
        inline constexpr std::uint32_t is_use_ies_brightness_bit = 0x0;
        inline constexpr std::uint32_t ies_brightness_scale = 0x324;
        inline constexpr std::uint32_t light_function_fade_distance = 0x328;
        inline constexpr std::uint32_t disabled_brightness = 0x32C;
        inline constexpr std::uint32_t is_enable_light_shaft_bloom = 0x330;
        inline constexpr std::uint32_t is_enable_light_shaft_bloom_bit = 0x0;
        inline constexpr std::uint32_t bloom_scale = 0x334;
        inline constexpr std::uint32_t bloom_threshold = 0x338;
        inline constexpr std::uint32_t bloom_max_brightness = 0x33C;
        inline constexpr std::uint32_t bloom_tint = 0x340;
        inline constexpr std::uint32_t is_use_ray_traced_distance_field_shadows = 0x344;
        inline constexpr std::uint32_t ray_start_offset_depth_scale = 0x348;
    }

    namespace udirectional_light {
        inline constexpr std::uint32_t shadow_cascade_bias_distribution = 0x3C8;
        inline constexpr std::uint32_t is_enable_light_shaft_occlusion = 0x3CC;
        inline constexpr std::uint32_t is_enable_light_shaft_occlusion_bit = 0x0;
        inline constexpr std::uint32_t occlusion_mask_darkness = 0x3D0;
        inline constexpr std::uint32_t occlusion_depth_range = 0x3D4;
        inline constexpr std::uint32_t light_shaft_override_direction = 0x3D8;
        inline constexpr std::uint32_t whole_scene_dynamic_shadow_radius = 0x3F0;
        inline constexpr std::uint32_t dynamic_shadow_distance_movable_light = 0x3F4;
        inline constexpr std::uint32_t dynamic_shadow_distance_stationary_light = 0x3F8;
        inline constexpr std::uint32_t dynamic_shadow_cascades = 0x3FC;
        inline constexpr std::uint32_t cascade_distribution_exponent = 0x400;
        inline constexpr std::uint32_t cascade_transition_fraction = 0x404;
        inline constexpr std::uint32_t shadow_distance_fadeout_fraction = 0x408;
        inline constexpr std::uint32_t is_use_inset_shadows_for_movable_objects = 0x40C;
        inline constexpr std::uint32_t is_use_inset_shadows_for_movable_objects_bit = 0x0;
        inline constexpr std::uint32_t far_shadow_cascade_count = 0x410;
        inline constexpr std::uint32_t far_shadow_distance = 0x414;
        inline constexpr std::uint32_t distance_field_shadow_distance = 0x418;
        inline constexpr std::uint32_t forward_shading_priority = 0x41C;
        inline constexpr std::uint32_t light_source_angle = 0x420;
        inline constexpr std::uint32_t light_source_soft_angle = 0x424;
        inline constexpr std::uint32_t shadow_source_angle_factor = 0x428;
        inline constexpr std::uint32_t trace_distance = 0x42C;
        inline constexpr std::uint32_t is_used_as_atmosphere_sun_light = 0x430;
        inline constexpr std::uint32_t is_used_as_atmosphere_sun_light_bit = 0x0;
        inline constexpr std::uint32_t is_atmosphere_sun_light = 0x430;
        inline constexpr std::uint32_t is_atmosphere_sun_light_bit = 0x1;
        inline constexpr std::uint32_t atmosphere_sun_light_index = 0x434;
        inline constexpr std::uint32_t atmosphere_sun_disk_color_scale = 0x438;
        inline constexpr std::uint32_t is_per_pixel_atmosphere_transmittance = 0x448;
        inline constexpr std::uint32_t is_per_pixel_atmosphere_transmittance_bit = 0x0;
        inline constexpr std::uint32_t is_cast_shadows_on_clouds = 0x448;
        inline constexpr std::uint32_t is_cast_shadows_on_clouds_bit = 0x1;
        inline constexpr std::uint32_t is_cast_shadows_on_atmosphere = 0x448;
        inline constexpr std::uint32_t is_cast_shadows_on_atmosphere_bit = 0x2;
        inline constexpr std::uint32_t is_cast_cloud_shadows = 0x448;
        inline constexpr std::uint32_t is_cast_cloud_shadows_bit = 0x3;
        inline constexpr std::uint32_t cloud_shadow_strength = 0x44C;
        inline constexpr std::uint32_t cloud_shadow_on_atmosphere_strength = 0x450;
        inline constexpr std::uint32_t cloud_shadow_on_surface_strength = 0x454;
        inline constexpr std::uint32_t cloud_shadow_depth_bias = 0x458;
        inline constexpr std::uint32_t cloud_shadow_extent = 0x45C;
        inline constexpr std::uint32_t cloud_shadow_map_resolution_scale = 0x460;
        inline constexpr std::uint32_t cloud_shadow_ray_sample_count_scale = 0x464;
        inline constexpr std::uint32_t cloud_scattered_luminance_scale = 0x468;
        inline constexpr std::uint32_t lightmass_settings = 0x478;
        inline constexpr std::uint32_t is_cast_modulated_shadows = 0x488;
        inline constexpr std::uint32_t is_cast_modulated_shadows_bit = 0x0;
        inline constexpr std::uint32_t modulated_shadow_color = 0x48C;
        inline constexpr std::uint32_t shadow_amount = 0x490;
        inline constexpr std::uint32_t byte_size = 0x4A0;
    }

    namespace asky_atmosphere {
        inline constexpr std::uint32_t sky_atmosphere_component = 0x2A8;
        inline constexpr std::uint32_t byte_size = 0x2B0;
    }

    namespace usky_atmosphere_component {
        inline constexpr std::uint32_t transform_mode = 0x250;
        inline constexpr std::uint32_t bottom_radius = 0x254;
        inline constexpr std::uint32_t ground_albedo = 0x258;
        inline constexpr std::uint32_t atmosphere_height = 0x25C;
        inline constexpr std::uint32_t multi_scattering_factor = 0x260;
        inline constexpr std::uint32_t trace_sample_count_scale = 0x264;
        inline constexpr std::uint32_t rayleigh_scattering_scale = 0x268;
        inline constexpr std::uint32_t rayleigh_scattering = 0x26C;
        inline constexpr std::uint32_t rayleigh_exponential_distribution = 0x27C;
        inline constexpr std::uint32_t mie_scattering_scale = 0x280;
        inline constexpr std::uint32_t mie_scattering = 0x284;
        inline constexpr std::uint32_t mie_absorption_scale = 0x294;
        inline constexpr std::uint32_t mie_absorption = 0x298;
        inline constexpr std::uint32_t mie_anisotropy = 0x2A8;
        inline constexpr std::uint32_t mie_exponential_distribution = 0x2AC;
        inline constexpr std::uint32_t other_absorption_scale = 0x2B0;
        inline constexpr std::uint32_t other_absorption = 0x2B4;
        inline constexpr std::uint32_t other_tent_distribution = 0x2C4;
        inline constexpr std::uint32_t sky_luminance_factor = 0x2D0;
        inline constexpr std::uint32_t sky_and_aerial_perspective_luminance_factor = 0x2E0;
        inline constexpr std::uint32_t aerial_pespective_view_distance_scale = 0x2F0;
        inline constexpr std::uint32_t height_fog_contribution = 0x2F4;
        inline constexpr std::uint32_t transmittance_min_light_elevation_angle = 0x2F8;
        inline constexpr std::uint32_t aerial_perspective_start_depth = 0x2FC;
        inline constexpr std::uint32_t is_holdout = 0x300;
        inline constexpr std::uint32_t is_holdout_bit = 0x0;
        inline constexpr std::uint32_t is_render_in_main_pass = 0x300;
        inline constexpr std::uint32_t is_render_in_main_pass_bit = 0x1;
        inline constexpr std::uint32_t is_static_lighting_built_guid = 0x348;
        inline constexpr std::uint32_t byte_size = 0x360;
    }

    namespace avolumetric_cloud {
        inline constexpr std::uint32_t volumetric_cloud_component = 0x2A8;
        inline constexpr std::uint32_t byte_size = 0x2B0;
    }

    namespace ucloud_component {
        inline constexpr std::uint32_t layer_bottom_altitude = 0x250;
        inline constexpr std::uint32_t layer_height = 0x254;
        inline constexpr std::uint32_t tracing_start_max_distance = 0x258;
        inline constexpr std::uint32_t tracing_start_distance_from_camera = 0x25C;
        inline constexpr std::uint32_t tracing_max_distance_mode = 0x260;
        inline constexpr std::uint32_t tracing_max_distance = 0x264;
        inline constexpr std::uint32_t planet_radius = 0x268;
        inline constexpr std::uint32_t ground_albedo = 0x26C;
        inline constexpr std::uint32_t material = 0x270;
        inline constexpr std::uint32_t is_use_per_sample_atmospheric_light_transmittance = 0x298;
        inline constexpr std::uint32_t is_use_per_sample_atmospheric_light_transmittance_bit = 0x0;
        inline constexpr std::uint32_t sky_light_cloud_bottom_occlusion = 0x29C;
        inline constexpr std::uint32_t view_sample_count_scale = 0x2A0;
        inline constexpr std::uint32_t reflection_view_sample_count_scale_value = 0x2A4;
        inline constexpr std::uint32_t reflection_view_sample_count_scale = 0x2A8;
        inline constexpr std::uint32_t reflection_sample_count_scale = 0x2AC;
        inline constexpr std::uint32_t shadow_view_sample_count_scale = 0x2B0;
        inline constexpr std::uint32_t shadow_reflection_view_sample_count_scale_value = 0x2B4;
        inline constexpr std::uint32_t shadow_reflection_view_sample_count_scale = 0x2B8;
        inline constexpr std::uint32_t shadow_reflection_sample_count_scale = 0x2BC;
        inline constexpr std::uint32_t shadow_tracing_distance = 0x2C0;
        inline constexpr std::uint32_t stop_tracing_transmittance_threshold = 0x2C4;
        inline constexpr std::uint32_t aerial_pespective_rayleigh_scattering_start_distance = 0x2C8;
        inline constexpr std::uint32_t aerial_pespective_rayleigh_scattering_fade_distance = 0x2CC;
        inline constexpr std::uint32_t aerial_pespective_mie_scattering_start_distance = 0x2D0;
        inline constexpr std::uint32_t aerial_pespective_mie_scattering_fade_distance = 0x2D4;
        inline constexpr std::uint32_t is_holdout = 0x2D8;
        inline constexpr std::uint32_t is_holdout_bit = 0x0;
        inline constexpr std::uint32_t is_render_in_main_pass = 0x2D8;
        inline constexpr std::uint32_t is_render_in_main_pass_bit = 0x1;
        inline constexpr std::uint32_t is_visible_in_real_time_sky_captures = 0x2D8;
        inline constexpr std::uint32_t is_visible_in_real_time_sky_captures_bit = 0x2;
        inline constexpr std::uint32_t material_lifetime_ptr = 0x2E8;
        inline constexpr std::uint32_t byte_size = 0x2F0;
    }

    namespace alocal_fog_volume {
        inline constexpr std::uint32_t local_fog_volume_volume = 0x2A8;
        inline constexpr std::uint32_t byte_size = 0x2B0;
    }

    namespace ulocal_fog_component {
        inline constexpr std::uint32_t radial_fog_extinction = 0x250;
        inline constexpr std::uint32_t height_fog_extinction = 0x254;
        inline constexpr std::uint32_t height_fog_falloff = 0x258;
        inline constexpr std::uint32_t height_fog_offset = 0x25C;
        inline constexpr std::uint32_t fog_phase_g = 0x260;
        inline constexpr std::uint32_t fog_albedo = 0x264;
        inline constexpr std::uint32_t fog_emissive = 0x274;
        inline constexpr std::uint32_t fog_start_distance = 0x284;
        inline constexpr std::uint32_t fog_sort_priority = 0x288;
        inline constexpr std::uint32_t byte_size = 0x2A0;
    }

    namespace awind_source {
        inline constexpr std::uint32_t component = 0x2A8;
        inline constexpr std::uint32_t byte_size = 0x2B0;
    }

    namespace uwind_component {
        inline constexpr std::uint32_t strength = 0x250;
        inline constexpr std::uint32_t speed = 0x254;
        inline constexpr std::uint32_t min_gust_amount = 0x258;
        inline constexpr std::uint32_t max_gust_amount = 0x25C;
        inline constexpr std::uint32_t radius = 0x260;
        inline constexpr std::uint32_t is_point_wind = 0x264;
        inline constexpr std::uint32_t is_point_wind_bit = 0x0;
        inline constexpr std::uint32_t byte_size = 0x270;
    }

}
