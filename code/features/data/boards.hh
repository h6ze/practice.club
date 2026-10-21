#pragma once
#include <iterator>
#include <features/features.hh>
#include <sdk/offsets.generated.hh>

namespace features::boards {

    namespace off = sdk::offsets;

    inline constexpr field match_rules_fields[] = {
        { "respawns", off::hw2_match_settings::allow_respawn, field_kind::flag, 0.0f, 1.0f },
        { "friendly fire", off::hw2_match_settings::allow_friendly_fire, field_kind::flag },
        { "friendly fire damage", off::hw2_match_settings::friendly_fire_multiplier, field_kind::wide, 0.0f, 3.0f },
        { "bots allowed", off::hw2_match_settings::allow_bots, field_kind::flag },
        { "bots team a", off::hw2_match_settings::bots_team_a, field_kind::whole, 0.0f, 32.0f },
        { "bots team b", off::hw2_match_settings::bots_team_b, field_kind::whole, 0.0f, 32.0f },
        { "bot difficulty", off::hw2_match_settings::ai_difficulty, field_kind::byte, 0.0f, 5.0f },
        { "points to win", off::hw2_match_settings::points_to_win, field_kind::whole, 1.0f, 1000.0f },
        { "rounds to win", off::hw2_match_settings::rounds_to_win, field_kind::whole, 1.0f, 50.0f },
        { "team switching", off::hw2_match_settings::allow_change_team, field_kind::flag },
        { "time limit", off::hw2_match_settings::match_with_time_limit, field_kind::flag },
        { "round time limit", off::hw2_match_settings::round_time_limit, field_kind::wide, 0.0f, 3600.0f },
        { "pre match wait", off::hw2_match_settings::pre_match_time, field_kind::wide, 0.0f, 120.0f },
        { "post round wait", off::hw2_match_settings::post_round_time, field_kind::wide, 0.0f, 60.0f },
        { "post match wait", off::hw2_match_settings::post_match_time, field_kind::wide, 0.0f, 120.0f },
        { "max players", off::hw2_match_settings::max_players, field_kind::whole, 2.0f, 64.0f },
        { "game mode", off::hw2_match_settings::game_mode, field_kind::byte, 0.0f, 10.0f },
    };

    inline constexpr field match_clock_fields[] = {
        { "team a points", off::hw2_match_state::team_a_points, field_kind::whole, 0.0f, 1000.0f },
        { "team b points", off::hw2_match_state::team_b_points, field_kind::whole, 0.0f, 1000.0f },
        { "rounds won a", off::hw2_match_state::rounds_won_a, field_kind::whole, 0.0f, 50.0f },
        { "rounds won b", off::hw2_match_state::rounds_won_b, field_kind::whole, 0.0f, 50.0f },
        { "match clock", off::hw2_match_state::match_time, field_kind::single, 0.0f, 3600.0f },
        { "time to start", off::hw2_match_state::time_left_to_start, field_kind::wide, 0.0f, 120.0f },
        { "pre match length", off::hw2_match_state::pre_match_time, field_kind::single, 0.0f, 120.0f },
        { "results screen length", off::hw2_match_state::post_match_time, field_kind::single, 0.0f, 120.0f },
        { "winner team", off::hw2_match_state::winner_team, field_kind::whole, -1.0f, 3.0f },
    };

    inline constexpr field game_mode_fields[] = {
        { "respawn delay", off::agame_mode::min_respawn_delay, field_kind::single, 0.0f, 30.0f },
        { "delayed start", off::agame_mode::delayed_start, field_kind::bit, 0.0f, 1.0f, off::agame_mode::delayed_start_bit },
        { "pauseable", off::agame_mode::pauseable, field_kind::bit, 0.0f, 1.0f, off::agame_mode::pauseable_bit },
        { "start as spectators", off::agame_mode::start_as_spectators, field_kind::bit, 0.0f, 1.0f, off::agame_mode::start_as_spectators_bit },
    };

    inline constexpr field lobby_preset_fields[] = {
        { "max players", off::hw2_game_instance::max_players, field_kind::whole, 2.0f, 64.0f },
        { "bots allowed", off::hw2_game_instance::allow_bots, field_kind::flag },
        { "friendly fire", off::hw2_game_instance::allow_friendly_fire, field_kind::flag },
        { "bots team a", off::hw2_game_instance::team_a_bots, field_kind::whole, 0.0f, 32.0f },
        { "bots team b", off::hw2_game_instance::team_b_bots, field_kind::whole, 0.0f, 32.0f },
        { "points to win", off::hw2_game_instance::points_to_win, field_kind::whole, 1.0f, 1000.0f },
        { "bot difficulty", off::hw2_game_instance::ai_difficulty, field_kind::byte, 0.0f, 5.0f },
        { "round time limit", off::hw2_game_instance::round_time_limit, field_kind::wide, 0.0f, 3600.0f },
        { "rounds to win", off::hw2_game_instance::rounds_to_win, field_kind::whole, 1.0f, 50.0f },
        { "use custom settings", off::hw2_game_instance::use_custom_settings, field_kind::flag, 0.0f, 1.0f },
        { "apply mode defaults", off::hw2_game_instance::apply_mode_defaults, field_kind::flag },
    };

    inline constexpr field bot_targeting_fields[] = {
        { "fair roaming", off::hw2_bot_config::is_fair_roaming, field_kind::flag, 0.0f, 1.0f },
        { "anti pile on", off::hw2_bot_config::is_anti_pile_on, field_kind::flag, 0.0f, 1.0f },
        { "anti pile on humans only", off::hw2_bot_config::is_anti_pile_on_humans_only, field_kind::flag, 0.0f, 1.0f },
        { "pile on distance penalty", off::hw2_bot_config::pile_on_distance_penalty, field_kind::single, 0.0f, 10000.0f },
        { "sticky target distance", off::hw2_bot_config::sticky_target_distance, field_kind::single, 0.0f, 10000.0f },
        { "attacker preference seconds", off::hw2_bot_config::attacker_preference_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field bot_chasing_fields[] = {
        { "threat memory", off::hw2_bot_config::is_threat_memory, field_kind::flag, 0.0f, 1.0f },
        { "hold min seconds", off::hw2_bot_config::hold_min_seconds, field_kind::single, 0.0f, 60.0f },
        { "hold max seconds", off::hw2_bot_config::hold_max_seconds, field_kind::single, 0.0f, 60.0f },
        { "pursue lead seconds", off::hw2_bot_config::pursue_lead_seconds, field_kind::single, 0.0f, 60.0f },
        { "pursue lead max", off::hw2_bot_config::pursue_lead_max, field_kind::single, 0.0f, 10000.0f },
        { "pursue max seconds", off::hw2_bot_config::pursue_max_seconds, field_kind::single, 0.0f, 60.0f },
        { "pursue max distance", off::hw2_bot_config::pursue_max_distance, field_kind::single, 0.0f, 10000.0f },
        { "pursue clear range", off::hw2_bot_config::pursue_clear_range, field_kind::single, 0.0f, 10000.0f },
        { "search point count", off::hw2_bot_config::search_point_count, field_kind::whole, 0.0f, 20.0f },
        { "search radius", off::hw2_bot_config::search_radius, field_kind::single, 0.0f, 180.0f },
        { "search point seconds", off::hw2_bot_config::search_point_seconds, field_kind::single, 0.0f, 60.0f },
        { "search max seconds", off::hw2_bot_config::search_max_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field bot_memory_fields[] = {
        { "memory max seconds", off::hw2_bot_config::memory_max_seconds, field_kind::single, 0.0f, 60.0f },
        { "memory refresh radius", off::hw2_bot_config::memory_refresh_radius, field_kind::single, 0.0f, 10000.0f },
        { "max memory refreshes", off::hw2_bot_config::max_memory_refreshes, field_kind::whole, 0.0f, 20.0f },
        { "objective leash radius", off::hw2_bot_config::objective_leash_radius, field_kind::single, 0.0f, 10000.0f },
        { "objective pursue slack", off::hw2_bot_config::objective_pursue_slack, field_kind::single, 0.0f, 10000.0f },
    };

    inline constexpr field bot_alerts_fields[] = {
        { "alerts", off::hw2_bot_config::is_alerts, field_kind::flag, 0.0f, 1.0f },
        { "damage alert seconds", off::hw2_bot_config::damage_alert_seconds, field_kind::single, 0.0f, 60.0f },
        { "hearing alert seconds", off::hw2_bot_config::hearing_alert_seconds, field_kind::single, 0.0f, 60.0f },
        { "hearing alert radius", off::hw2_bot_config::hearing_alert_radius, field_kind::single, 0.0f, 10000.0f },
        { "hearing alert cooldown", off::hw2_bot_config::hearing_alert_cooldown, field_kind::single, 0.0f, 60.0f },
        { "attention turn scale", off::hw2_bot_config::attention_turn_scale, field_kind::single, 0.0f, 10.0f },
        { "investigate noise", off::hw2_bot_config::is_investigate_noise, field_kind::flag, 0.0f, 1.0f },
        { "investigate min distance", off::hw2_bot_config::investigate_min_distance, field_kind::single, 0.0f, 10000.0f },
        { "investigate max distance", off::hw2_bot_config::investigate_max_distance, field_kind::single, 0.0f, 10000.0f },
        { "investigate cooldown", off::hw2_bot_config::investigate_cooldown, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field bot_hit_reaction_fields[] = {
        { "damage reaction", off::hw2_bot_config::is_damage_reaction, field_kind::flag, 0.0f, 1.0f },
        { "damage hold min seconds", off::hw2_bot_config::damage_hold_min_seconds, field_kind::single, 0.0f, 60.0f },
        { "damage hold max seconds", off::hw2_bot_config::damage_hold_max_seconds, field_kind::single, 0.0f, 60.0f },
        { "damage hit window seconds", off::hw2_bot_config::damage_hit_window_seconds, field_kind::single, 0.0f, 60.0f },
        { "flank turn seconds", off::hw2_bot_config::flank_turn_seconds, field_kind::single, 0.0f, 60.0f },
        { "flank switch hits", off::hw2_bot_config::flank_switch_hits, field_kind::whole, 0.0f, 20.0f },
    };

    inline constexpr field bot_reloading_fields[] = {
        { "reload movement", off::hw2_bot_config::is_reload_movement, field_kind::flag, 0.0f, 1.0f },
        { "reload move min distance", off::hw2_bot_config::reload_move_min_distance, field_kind::single, 0.0f, 10000.0f },
        { "reload move max distance", off::hw2_bot_config::reload_move_max_distance, field_kind::single, 0.0f, 10000.0f },
        { "reload move candidates", off::hw2_bot_config::reload_move_candidates, field_kind::whole, 0.0f, 20.0f },
        { "reload stall seconds", off::hw2_bot_config::reload_stall_seconds, field_kind::single, 0.0f, 60.0f },
        { "tactical reload fraction", off::hw2_bot_config::tactical_reload_fraction, field_kind::single, 0.0f, 1.0f },
        { "tactical reload calm seconds", off::hw2_bot_config::tactical_reload_calm_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field bot_strafing_fields[] = {
        { "combat strafe", off::hw2_bot_config::is_combat_strafe, field_kind::flag, 0.0f, 1.0f },
        { "strafe idle seconds", off::hw2_bot_config::strafe_idle_seconds, field_kind::single, 0.0f, 60.0f },
        { "strafe min distance", off::hw2_bot_config::strafe_min_distance, field_kind::single, 0.0f, 10000.0f },
        { "strafe max distance", off::hw2_bot_config::strafe_max_distance, field_kind::single, 0.0f, 10000.0f },
        { "strafe interval min", off::hw2_bot_config::strafe_interval_min, field_kind::single, 0.0f, 60.0f },
        { "strafe interval max", off::hw2_bot_config::strafe_interval_max, field_kind::single, 0.0f, 60.0f },
        { "objective first", off::hw2_bot_config::is_objective_first, field_kind::flag, 0.0f, 1.0f },
        { "fire on move", off::hw2_bot_config::is_fire_on_move, field_kind::flag, 0.0f, 1.0f },
        { "move fire interval", off::hw2_bot_config::move_fire_interval, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field bot_vehicles_fields[] = {
        { "shoot hostile vehicles", off::hw2_bot_config::is_shoot_hostile_vehicles, field_kind::flag, 0.0f, 1.0f },
        { "hostile vehicle range", off::hw2_bot_config::hostile_vehicle_range, field_kind::single, 0.0f, 10000.0f },
        { "hostile vehicle burst min", off::hw2_bot_config::hostile_vehicle_burst_min, field_kind::whole, 0.0f, 20.0f },
        { "hostile vehicle burst max", off::hw2_bot_config::hostile_vehicle_burst_max, field_kind::whole, 0.0f, 20.0f },
        { "hostile vehicle pause min", off::hw2_bot_config::hostile_vehicle_pause_min, field_kind::single, 0.0f, 100.0f },
        { "hostile vehicle pause max", off::hw2_bot_config::hostile_vehicle_pause_max, field_kind::single, 0.0f, 100.0f },
        { "hostile vehicle aim tolerance", off::hw2_bot_config::hostile_vehicle_aim_tolerance, field_kind::single, 0.0f, 100.0f },
    };

    inline constexpr field bot_engaging_fields[] = {
        { "engage min seconds", off::hw2_bot_config::engage_min_seconds, field_kind::single, 0.0f, 60.0f },
        { "disengage scale", off::hw2_bot_config::disengage_scale, field_kind::single, 0.0f, 10.0f },
        { "engage when shot seconds", off::hw2_bot_config::engage_when_shot_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field bot_roles_fields[] = {
        { "carrier engage radius", off::hw2_bot_config::carrier_engage_radius, field_kind::single, 0.0f, 10000.0f },
        { "carrier path check distance", off::hw2_bot_config::carrier_path_check_distance, field_kind::single, 0.0f, 10000.0f },
        { "carrier path block radius", off::hw2_bot_config::carrier_path_block_radius, field_kind::single, 0.0f, 10000.0f },
        { "carrier stall seconds", off::hw2_bot_config::carrier_stall_seconds, field_kind::single, 0.0f, 60.0f },
        { "carrier sprint threat radius", off::hw2_bot_config::carrier_sprint_threat_radius, field_kind::single, 0.0f, 10000.0f },
        { "escort engage radius", off::hw2_bot_config::escort_engage_radius, field_kind::single, 0.0f, 10000.0f },
        { "capturer engage radius", off::hw2_bot_config::capturer_engage_radius, field_kind::single, 0.0f, 10000.0f },
        { "capture circle margin", off::hw2_bot_config::capture_circle_margin, field_kind::single, 0.0f, 10000.0f },
        { "defender post radius", off::hw2_bot_config::defender_post_radius, field_kind::single, 0.0f, 10000.0f },
        { "defender leash radius", off::hw2_bot_config::defender_leash_radius, field_kind::single, 0.0f, 10000.0f },
        { "interactor engage radius", off::hw2_bot_config::interactor_engage_radius, field_kind::single, 0.0f, 10000.0f },
        { "interactor arrive radius", off::hw2_bot_config::interactor_arrive_radius, field_kind::single, 0.0f, 10000.0f },
    };

    inline constexpr field bot_bags_fields[] = {
        { "retrieve dropped bags", off::hw2_bot_config::is_retrieve_dropped_bags, field_kind::flag, 0.0f, 1.0f },
        { "retrievers per bag", off::hw2_bot_config::retrievers_per_bag, field_kind::whole, 0.0f, 20.0f },
        { "retriever engage radius", off::hw2_bot_config::retriever_engage_radius, field_kind::single, 0.0f, 10000.0f },
        { "bag home radius", off::hw2_bot_config::bag_home_radius, field_kind::single, 0.0f, 10000.0f },
        { "carrier reload on the move", off::hw2_bot_config::is_carrier_reload_on_the_move, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field bot_cover_fields[] = {
        { "combat stances", off::hw2_bot_config::is_combat_stances, field_kind::flag, 0.0f, 1.0f },
        { "cover search radius", off::hw2_bot_config::cover_search_radius, field_kind::single, 0.0f, 180.0f },
        { "retreat search radius", off::hw2_bot_config::retreat_search_radius, field_kind::single, 0.0f, 180.0f },
        { "cover candidates", off::hw2_bot_config::cover_candidates, field_kind::whole, 0.0f, 20.0f },
        { "cover max traces", off::hw2_bot_config::cover_max_traces, field_kind::whole, 0.0f, 200.0f },
        { "cover queries per team per second", off::hw2_bot_config::cover_queries_per_team_per_second, field_kind::single, 0.0f, 60.0f },
        { "cover min threat distance", off::hw2_bot_config::cover_min_threat_distance, field_kind::single, 0.0f, 10000.0f },
        { "cover max advance", off::hw2_bot_config::cover_max_advance, field_kind::single, 0.0f, 10000.0f },
        { "cover claim radius", off::hw2_bot_config::cover_claim_radius, field_kind::single, 0.0f, 10000.0f },
        { "cover max path factor", off::hw2_bot_config::cover_max_path_factor, field_kind::single, 0.0f, 10.0f },
        { "crouch in half cover", off::hw2_bot_config::is_crouch_in_half_cover, field_kind::flag, 0.0f, 1.0f },
        { "cover hide max seconds", off::hw2_bot_config::cover_hide_max_seconds, field_kind::single, 0.0f, 60.0f },
        { "cover hide min seconds", off::hw2_bot_config::cover_hide_min_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field bot_peeking_fields[] = {
        { "peek min seconds", off::hw2_bot_config::peek_min_seconds, field_kind::single, 0.0f, 60.0f },
        { "peek max seconds", off::hw2_bot_config::peek_max_seconds, field_kind::single, 0.0f, 60.0f },
        { "peek damage to hide", off::hw2_bot_config::peek_damage_to_hide, field_kind::single, 0.0f, 500.0f },
        { "peeks before pursuit", off::hw2_bot_config::peeks_before_pursuit, field_kind::whole, 0.0f, 20.0f },
        { "cover standoff max seconds", off::hw2_bot_config::cover_standoff_max_seconds, field_kind::single, 0.0f, 60.0f },
        { "stance eval min seconds", off::hw2_bot_config::stance_eval_min_seconds, field_kind::single, 0.0f, 60.0f },
        { "stance eval max seconds", off::hw2_bot_config::stance_eval_max_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field bot_retreat_fields[] = {
        { "retreat health min", off::hw2_bot_config::retreat_health_min, field_kind::single, 0.0f, 1.0f },
        { "retreat health max", off::hw2_bot_config::retreat_health_max, field_kind::single, 0.0f, 1.0f },
        { "retreat recover health", off::hw2_bot_config::retreat_recover_health, field_kind::single, 0.0f, 1.0f },
        { "retreat max seconds", off::hw2_bot_config::retreat_max_seconds, field_kind::single, 0.0f, 60.0f },
        { "retreat cooldown seconds", off::hw2_bot_config::retreat_cooldown_seconds, field_kind::single, 0.0f, 60.0f },
        { "heal before roaming", off::hw2_bot_config::is_heal_before_roaming, field_kind::flag, 0.0f, 1.0f },
        { "retreat cornered radius", off::hw2_bot_config::retreat_cornered_radius, field_kind::single, 0.0f, 10000.0f },
    };

    inline constexpr field bot_pushing_fields[] = {
        { "push damage dealt", off::hw2_bot_config::push_damage_dealt, field_kind::single, 0.0f, 500.0f },
        { "push aggression min", off::hw2_bot_config::push_aggression_min, field_kind::single, 0.0f, 10.0f },
        { "push aggressive chance", off::hw2_bot_config::push_aggressive_chance, field_kind::single, 0.0f, 1.0f },
        { "cover reload fraction", off::hw2_bot_config::cover_reload_fraction, field_kind::single, 0.0f, 1.0f },
        { "peek low mag fraction", off::hw2_bot_config::peek_low_mag_fraction, field_kind::single, 0.0f, 1.0f },
        { "objective cover slack", off::hw2_bot_config::objective_cover_slack, field_kind::single, 0.0f, 10000.0f },
        { "objective standoff scale", off::hw2_bot_config::objective_standoff_scale, field_kind::single, 0.0f, 10.0f },
        { "hold circle margin", off::hw2_bot_config::hold_circle_margin, field_kind::single, 0.0f, 10000.0f },
        { "defender hold radius", off::hw2_bot_config::defender_hold_radius, field_kind::single, 0.0f, 10000.0f },
    };

    inline constexpr field bot_coordinator_fields[] = {
        { "team coordinator", off::hw2_bot_config::is_team_coordinator, field_kind::flag, 0.0f, 1.0f },
        { "coordinator interval", off::hw2_bot_config::coordinator_interval, field_kind::single, 0.0f, 60.0f },
        { "assignment min seconds", off::hw2_bot_config::assignment_min_seconds, field_kind::single, 0.0f, 60.0f },
        { "assignment sticky bonus", off::hw2_bot_config::assignment_sticky_bonus, field_kind::single, 0.0f, 100.0f },
        { "personality cost scale", off::hw2_bot_config::personality_cost_scale, field_kind::single, 0.0f, 10.0f },
        { "human slot radius", off::hw2_bot_config::human_slot_radius, field_kind::single, 0.0f, 10000.0f },
        { "redirect distance", off::hw2_bot_config::redirect_distance, field_kind::single, 0.0f, 10000.0f },
    };

    inline constexpr field bot_conquest_fields[] = {
        { "conquest defender share", off::hw2_bot_config::conquest_defender_share, field_kind::single, 0.0f, 1.0f },
        { "conquest threat defenders", off::hw2_bot_config::conquest_threat_defenders, field_kind::whole, 0.0f, 20.0f },
        { "conquest split share", off::hw2_bot_config::conquest_split_share, field_kind::single, 0.0f, 1.0f },
        { "conquest post radius", off::hw2_bot_config::conquest_post_radius, field_kind::single, 0.0f, 10000.0f },
        { "conquest post swap min seconds", off::hw2_bot_config::conquest_post_swap_min_seconds, field_kind::single, 0.0f, 60.0f },
        { "conquest post swap max seconds", off::hw2_bot_config::conquest_post_swap_max_seconds, field_kind::single, 0.0f, 60.0f },
        { "conquest post angle", off::hw2_bot_config::conquest_post_angle, field_kind::single, 0.0f, 180.0f },
    };

    inline constexpr field bot_lanes_fields[] = {
        { "bag mode interceptors", off::hw2_bot_config::ctf_interceptors, field_kind::whole, 0.0f, 20.0f },
        { "bag mode intercept radius", off::hw2_bot_config::ctf_intercept_radius, field_kind::single, 0.0f, 10000.0f },
        { "bag mode escort lead distance", off::hw2_bot_config::ctf_escort_lead_distance, field_kind::single, 0.0f, 10000.0f },
        { "bag mode escort cover distance", off::hw2_bot_config::ctf_escort_cover_distance, field_kind::single, 0.0f, 10000.0f },
        { "bag mode home defender min team", off::hw2_bot_config::ctf_home_defender_min_team, field_kind::whole, 0.0f, 20.0f },
        { "kill confirmed max collect distance", off::hw2_bot_config::kc_max_collect_distance, field_kind::single, 0.0f, 10000.0f },
        { "lane count", off::hw2_bot_config::lane_count, field_kind::whole, 0.0f, 20.0f },
        { "lane roam chance", off::hw2_bot_config::lane_roam_chance, field_kind::single, 0.0f, 1.0f },
        { "lane width share", off::hw2_bot_config::lane_width_share, field_kind::single, 0.0f, 1.0f },
    };

    inline constexpr field bot_callouts_fields[] = {
        { "callouts", off::hw2_bot_config::is_callouts, field_kind::flag, 0.0f, 1.0f },
        { "callout delay min", off::hw2_bot_config::callout_delay_min, field_kind::single, 0.0f, 60.0f },
        { "callout delay max", off::hw2_bot_config::callout_delay_max, field_kind::single, 0.0f, 60.0f },
        { "callout recipients", off::hw2_bot_config::callout_recipients, field_kind::whole, 0.0f, 20.0f },
        { "callout radius", off::hw2_bot_config::callout_radius, field_kind::single, 0.0f, 10000.0f },
        { "callout error", off::hw2_bot_config::callout_error, field_kind::single, 0.0f, 100.0f },
        { "callout cooldown", off::hw2_bot_config::callout_cooldown, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field bot_personalities_fields[] = {
        { "personalities", off::hw2_bot_config::is_personalities, field_kind::flag, 0.0f, 1.0f },
        { "aggression min", off::hw2_bot_config::aggression_min, field_kind::single, 0.0f, 10.0f },
        { "aggression max", off::hw2_bot_config::aggression_max, field_kind::single, 0.0f, 10.0f },
        { "patience min", off::hw2_bot_config::patience_min, field_kind::single, 0.0f, 10.0f },
        { "patience max", off::hw2_bot_config::patience_max, field_kind::single, 0.0f, 10.0f },
        { "leash min", off::hw2_bot_config::leash_min, field_kind::single, 0.0f, 10000.0f },
        { "leash max", off::hw2_bot_config::leash_max, field_kind::single, 0.0f, 10000.0f },
        { "retreat bias range", off::hw2_bot_config::retreat_bias_range, field_kind::single, 0.0f, 10000.0f },
        { "reaction scale min", off::hw2_bot_config::reaction_scale_min, field_kind::single, 0.0f, 10.0f },
        { "reaction scale max", off::hw2_bot_config::reaction_scale_max, field_kind::single, 0.0f, 10.0f },
        { "tier pursuit tilt", off::hw2_bot_config::is_tier_pursuit_tilt, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field bot_detection_fields[] = {
        { "gradual detection", off::hw2_bot_config::is_gradual_detection, field_kind::flag, 0.0f, 1.0f },
        { "detect focus half angle", off::hw2_bot_config::detect_focus_half_angle, field_kind::single, 0.0f, 180.0f },
        { "detect peripheral factor", off::hw2_bot_config::detect_peripheral_factor, field_kind::single, 0.0f, 10.0f },
        { "detect near distance", off::hw2_bot_config::detect_near_distance, field_kind::single, 0.0f, 10000.0f },
        { "detect near factor", off::hw2_bot_config::detect_near_factor, field_kind::single, 0.0f, 10.0f },
        { "detect reference distance", off::hw2_bot_config::detect_reference_distance, field_kind::single, 0.0f, 10000.0f },
        { "detect far distance", off::hw2_bot_config::detect_far_distance, field_kind::single, 0.0f, 10000.0f },
        { "detect far factor", off::hw2_bot_config::detect_far_factor, field_kind::single, 0.0f, 10.0f },
        { "detect moving factor", off::hw2_bot_config::detect_moving_factor, field_kind::single, 0.0f, 10.0f },
        { "detect moving speed", off::hw2_bot_config::detect_moving_speed, field_kind::single, 0.0f, 3000.0f },
        { "detect crouch factor", off::hw2_bot_config::detect_crouch_factor, field_kind::single, 0.0f, 10.0f },
        { "detect alert factor", off::hw2_bot_config::detect_alert_factor, field_kind::single, 0.0f, 10.0f },
        { "awareness keep seconds", off::hw2_bot_config::awareness_keep_seconds, field_kind::single, 0.0f, 60.0f },
        { "awareness decay seconds", off::hw2_bot_config::awareness_decay_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field bot_flinch_voice_fields[] = {
        { "flinch", off::hw2_bot_config::is_flinch, field_kind::flag, 0.0f, 1.0f },
        { "flinch seconds", off::hw2_bot_config::flinch_seconds, field_kind::single, 0.0f, 60.0f },
        { "bot voice", off::hw2_bot_config::is_bot_voice, field_kind::flag, 0.0f, 1.0f },
        { "voice spotted event id", off::hw2_bot_config::voice_spotted_event_id, field_kind::whole, 0.0f, 200.0f },
        { "voice retreat event id", off::hw2_bot_config::voice_retreat_event_id, field_kind::whole, 0.0f, 200.0f },
        { "voice push event id", off::hw2_bot_config::voice_push_event_id, field_kind::whole, 0.0f, 200.0f },
        { "voice min gap seconds", off::hw2_bot_config::voice_min_gap_seconds, field_kind::single, 0.0f, 60.0f },
        { "voice team gap seconds", off::hw2_bot_config::voice_team_gap_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field bot_unstuck_fields[] = {
        { "face off recovery", off::hw2_bot_config::is_face_off_recovery, field_kind::flag, 0.0f, 1.0f },
        { "face off radius", off::hw2_bot_config::face_off_radius, field_kind::single, 0.0f, 10000.0f },
        { "face off speed", off::hw2_bot_config::face_off_speed, field_kind::single, 0.0f, 3000.0f },
        { "face off seconds", off::hw2_bot_config::face_off_seconds, field_kind::single, 0.0f, 60.0f },
        { "stuck yield seconds", off::hw2_bot_config::stuck_yield_seconds, field_kind::single, 0.0f, 60.0f },
        { "yield step min", off::hw2_bot_config::yield_step_min, field_kind::single, 0.0f, 10000.0f },
        { "yield step max", off::hw2_bot_config::yield_step_max, field_kind::single, 0.0f, 10000.0f },
        { "stuck reroute seconds", off::hw2_bot_config::stuck_reroute_seconds, field_kind::single, 0.0f, 60.0f },
        { "reroute offset min", off::hw2_bot_config::reroute_offset_min, field_kind::single, 0.0f, 10000.0f },
        { "reroute offset max", off::hw2_bot_config::reroute_offset_max, field_kind::single, 0.0f, 10000.0f },
        { "post min spacing", off::hw2_bot_config::post_min_spacing, field_kind::single, 0.0f, 10000.0f },
    };

    inline constexpr field bot_defence_fields[] = {
        { "active defence", off::hw2_bot_config::is_active_defence, field_kind::flag, 0.0f, 1.0f },
        { "watch points", off::hw2_bot_config::is_watch_points, field_kind::flag, 0.0f, 1.0f },
        { "focal sanity", off::hw2_bot_config::is_focal_sanity, field_kind::flag, 0.0f, 1.0f },
        { "focal sanity tolerance", off::hw2_bot_config::focal_sanity_tolerance, field_kind::single, 0.0f, 100.0f },
        { "defend weight hold angle", off::hw2_bot_config::defend_activity_weights + off::hw2_bot_defend_weights::hold_angle, field_kind::single, 0.0f, 180.0f },
        { "defend weight shift", off::hw2_bot_config::defend_activity_weights + off::hw2_bot_defend_weights::shift, field_kind::single, 0.0f, 100.0f },
        { "defend weight crouch watch", off::hw2_bot_config::defend_activity_weights + off::hw2_bot_defend_weights::crouch_watch, field_kind::single, 0.0f, 100.0f },
        { "defend weight reposition", off::hw2_bot_config::defend_activity_weights + off::hw2_bot_defend_weights::reposition, field_kind::single, 0.0f, 100.0f },
        { "defend weight clear angle", off::hw2_bot_config::defend_activity_weights + off::hw2_bot_defend_weights::clear_angle, field_kind::single, 0.0f, 180.0f },
        { "defend hold min seconds", off::hw2_bot_config::defend_hold_min_seconds, field_kind::single, 0.0f, 60.0f },
        { "defend hold max seconds", off::hw2_bot_config::defend_hold_max_seconds, field_kind::single, 0.0f, 60.0f },
        { "defend shift min distance", off::hw2_bot_config::defend_shift_min_distance, field_kind::single, 0.0f, 10000.0f },
        { "defend shift max distance", off::hw2_bot_config::defend_shift_max_distance, field_kind::single, 0.0f, 10000.0f },
        { "defend crouch min seconds", off::hw2_bot_config::defend_crouch_min_seconds, field_kind::single, 0.0f, 60.0f },
        { "defend crouch max seconds", off::hw2_bot_config::defend_crouch_max_seconds, field_kind::single, 0.0f, 60.0f },
        { "defend reposition min", off::hw2_bot_config::defend_reposition_min, field_kind::single, 0.0f, 100.0f },
        { "defend reposition max", off::hw2_bot_config::defend_reposition_max, field_kind::single, 0.0f, 100.0f },
        { "defend clear share min", off::hw2_bot_config::defend_clear_share_min, field_kind::single, 0.0f, 1.0f },
        { "defend clear share max", off::hw2_bot_config::defend_clear_share_max, field_kind::single, 0.0f, 1.0f },
        { "approach length", off::hw2_bot_config::approach_length, field_kind::single, 0.0f, 10000.0f },
        { "approaches max", off::hw2_bot_config::approaches_max, field_kind::whole, 0.0f, 20.0f },
        { "approach merge degrees", off::hw2_bot_config::approach_merge_degrees, field_kind::single, 0.0f, 180.0f },
        { "danger seconds", off::hw2_bot_config::danger_seconds, field_kind::single, 0.0f, 60.0f },
        { "seen post avoid seconds", off::hw2_bot_config::seen_post_avoid_seconds, field_kind::single, 0.0f, 60.0f },
        { "defend post candidates", off::hw2_bot_config::defend_post_candidates, field_kind::whole, 0.0f, 20.0f },
        { "defend post trace budget", off::hw2_bot_config::defend_post_trace_budget, field_kind::whole, 0.0f, 200.0f },
        { "defend posts per slot", off::hw2_bot_config::defend_posts_per_slot, field_kind::whole, 0.0f, 20.0f },
        { "defend occupant leash scale", off::hw2_bot_config::defend_occupant_leash_scale, field_kind::single, 0.0f, 10000.0f },
        { "site defend radius", off::hw2_bot_config::site_defend_radius, field_kind::single, 0.0f, 10000.0f },
    };

    inline constexpr field bot_advantage_fields[] = {
        { "advantage stance", off::hw2_bot_config::is_advantage_stance, field_kind::flag, 0.0f, 1.0f },
        { "aggression in chaos", off::hw2_bot_config::mode_aggression_bias + off::hw2_bot_mode_bias::chaos, field_kind::single, 0.0f, 100.0f },
        { "aggression in gang bang", off::hw2_bot_config::mode_aggression_bias + off::hw2_bot_mode_bias::gang_bang, field_kind::single, 0.0f, 100.0f },
        { "aggression in chain snatch", off::hw2_bot_config::mode_aggression_bias + off::hw2_bot_mode_bias::chain_snatch, field_kind::single, 0.0f, 100.0f },
        { "aggression in turf war", off::hw2_bot_config::mode_aggression_bias + off::hw2_bot_mode_bias::turf_war, field_kind::single, 0.0f, 100.0f },
        { "aggression in hit a lick", off::hw2_bot_config::mode_aggression_bias + off::hw2_bot_mode_bias::hit_a_lick, field_kind::single, 0.0f, 100.0f },
        { "aggression in destroy the block", off::hw2_bot_config::mode_aggression_bias + off::hw2_bot_mode_bias::destroy_the_block, field_kind::single, 0.0f, 100.0f },
        { "advantage push above", off::hw2_bot_config::advantage_push_above, field_kind::single, 0.0f, 100.0f },
        { "advantage cover below", off::hw2_bot_config::advantage_cover_below, field_kind::single, 0.0f, 100.0f },
        { "peek hit extend seconds", off::hw2_bot_config::peek_hit_extend_seconds, field_kind::single, 0.0f, 60.0f },
        { "purpose sprint", off::hw2_bot_config::is_purpose_sprint, field_kind::flag, 0.0f, 1.0f },
        { "chaos gunfire roam chance", off::hw2_bot_config::chaos_gunfire_roam_chance, field_kind::single, 0.0f, 1.0f },
    };

    inline constexpr field bot_weapons_fields[] = {
        { "weapon archetypes", off::hw2_bot_config::is_weapon_archetypes, field_kind::flag, 0.0f, 1.0f },
        { "sidearm swap", off::hw2_bot_config::is_sidearm_swap, field_kind::flag, 0.0f, 1.0f },
        { "sidearm reload seconds threshold", off::hw2_bot_config::sidearm_reload_seconds_threshold, field_kind::single, 0.0f, 60.0f },
        { "sidearm max range", off::hw2_bot_config::sidearm_max_range, field_kind::single, 0.0f, 10000.0f },
        { "sidearm cover radius", off::hw2_bot_config::sidearm_cover_radius, field_kind::single, 0.0f, 10000.0f },
        { "sidearm fight seen seconds", off::hw2_bot_config::sidearm_fight_seen_seconds, field_kind::single, 0.0f, 60.0f },
        { "sidearm return seconds", off::hw2_bot_config::sidearm_return_seconds, field_kind::single, 0.0f, 60.0f },
        { "shotgun interrupt reload", off::hw2_bot_config::is_shotgun_interrupt_reload, field_kind::flag, 0.0f, 1.0f },
        { "shotgun interrupt shells", off::hw2_bot_config::shotgun_interrupt_shells, field_kind::whole, 0.0f, 20.0f },
        { "dry melee range", off::hw2_bot_config::dry_melee_range, field_kind::single, 0.0f, 10000.0f },
        { "give bots sidearm", off::hw2_bot_config::is_give_bots_sidearm, field_kind::flag, 0.0f, 1.0f },
        { "sidearm swap seconds", off::hw2_bot_config::sidearm_swap_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field bot_sight_fields[] = {
        { "sight ignores friendlies", off::hw2_bot_config::is_sight_ignores_friendlies, field_kind::flag, 0.0f, 1.0f },
        { "investigate contact chance", off::hw2_bot_config::investigate_contact_chance, field_kind::single, 0.0f, 1.0f },
        { "contact lifetime", off::hw2_bot_config::contact_lifetime, field_kind::single, 0.0f, 60.0f },
        { "noise error fraction", off::hw2_bot_config::noise_error_fraction, field_kind::single, 0.0f, 1.0f },
        { "noise error max", off::hw2_bot_config::noise_error_max, field_kind::single, 0.0f, 100.0f },
        { "damage direction error degrees", off::hw2_bot_config::damage_direction_error_degrees, field_kind::single, 0.0f, 180.0f },
        { "roam min distance", off::hw2_bot_config::roam_min_distance, field_kind::single, 0.0f, 10000.0f },
        { "roam max distance", off::hw2_bot_config::roam_max_distance, field_kind::single, 0.0f, 10000.0f },
        { "roam claim radius", off::hw2_bot_config::roam_claim_radius, field_kind::single, 0.0f, 10000.0f },
    };

    inline constexpr field bot_spawns_fields[] = {
        { "smart spawns", off::hw2_bot_config::is_smart_spawns, field_kind::flag, 0.0f, 1.0f },
        { "spawn enemy hard radius", off::hw2_bot_config::spawn_enemy_hard_radius, field_kind::single, 0.0f, 10000.0f },
        { "spawn safe distance", off::hw2_bot_config::spawn_safe_distance, field_kind::single, 0.0f, 10000.0f },
        { "spawn sight check radius", off::hw2_bot_config::spawn_sight_check_radius, field_kind::single, 0.0f, 10000.0f },
        { "spawn sight penalty", off::hw2_bot_config::spawn_sight_penalty, field_kind::single, 0.0f, 10.0f },
        { "spawn reuse seconds", off::hw2_bot_config::spawn_reuse_seconds, field_kind::single, 0.0f, 60.0f },
        { "spawn reuse penalty", off::hw2_bot_config::spawn_reuse_penalty, field_kind::single, 0.0f, 10.0f },
        { "spawn danger seconds", off::hw2_bot_config::spawn_danger_seconds, field_kind::single, 0.0f, 60.0f },
        { "spawn danger radius", off::hw2_bot_config::spawn_danger_radius, field_kind::single, 0.0f, 10000.0f },
        { "spawn danger penalty", off::hw2_bot_config::spawn_danger_penalty, field_kind::single, 0.0f, 10.0f },
        { "spawn pick margin", off::hw2_bot_config::spawn_pick_margin, field_kind::single, 0.0f, 10000.0f },
        { "end spawn protection on attack", off::hw2_bot_config::is_end_spawn_protection_on_attack, field_kind::flag, 0.0f, 1.0f },
        { "spawn protection seconds", off::hw2_bot_config::spawn_protection_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field bot_glass_fields[] = {
        { "glass see through", off::hw2_bot_config::is_glass_see_through, field_kind::flag, 0.0f, 1.0f },
        { "glass shoot through", off::hw2_bot_config::is_glass_shoot_through, field_kind::flag, 0.0f, 1.0f },
        { "glass sight recheck seconds", off::hw2_bot_config::glass_sight_recheck_seconds, field_kind::single, 0.0f, 60.0f },
        { "glass sight max distance", off::hw2_bot_config::glass_sight_max_distance, field_kind::single, 0.0f, 10000.0f },
    };

    inline constexpr field bot_snd_plans_fields[] = {
        { "s&d director", off::hw2_bot_config::is_sn_d_director, field_kind::flag, 0.0f, 1.0f },
        { "s&d observe only", off::hw2_bot_config::is_sn_d_observe_only, field_kind::flag, 0.0f, 1.0f },
        { "s&d weight default", off::hw2_bot_config::sn_d_weight_default, field_kind::single, 0.0f, 10.0f },
        { "s&d weight split", off::hw2_bot_config::sn_d_weight_split, field_kind::single, 0.0f, 10.0f },
        { "s&d weight fake", off::hw2_bot_config::sn_d_weight_fake, field_kind::single, 0.0f, 10.0f },
        { "s&d weight rush", off::hw2_bot_config::sn_d_weight_rush, field_kind::single, 0.0f, 10.0f },
    };

    inline constexpr field bot_snd_staging_fields[] = {
        { "s&d stage hold min", off::hw2_bot_config::sn_d_stage_hold_min, field_kind::single, 0.0f, 100.0f },
        { "s&d stage hold max", off::hw2_bot_config::sn_d_stage_hold_max, field_kind::single, 0.0f, 100.0f },
        { "s&d stall seconds", off::hw2_bot_config::sn_d_stall_seconds, field_kind::single, 0.0f, 60.0f },
        { "s&d advance engage scale", off::hw2_bot_config::sn_d_advance_engage_scale, field_kind::single, 0.0f, 10000.0f },
        { "s&d stage gather share", off::hw2_bot_config::sn_d_stage_gather_share, field_kind::single, 0.0f, 1.0f },
        { "s&d fake hold min", off::hw2_bot_config::sn_d_fake_hold_min, field_kind::single, 0.0f, 100.0f },
        { "s&d fake hold max", off::hw2_bot_config::sn_d_fake_hold_max, field_kind::single, 0.0f, 100.0f },
        { "s&d late round seconds", off::hw2_bot_config::sn_d_late_round_seconds, field_kind::single, 0.0f, 60.0f },
        { "s&d contested distance", off::hw2_bot_config::sn_d_contested_distance, field_kind::single, 0.0f, 10000.0f },
        { "s&d careful tail", off::hw2_bot_config::sn_d_careful_tail, field_kind::single, 0.0f, 100.0f },
        { "s&d corner slow seconds", off::hw2_bot_config::sn_d_corner_slow_seconds, field_kind::single, 0.0f, 60.0f },
        { "s&d attacker aggression bias", off::hw2_bot_config::sn_d_attacker_aggression_bias, field_kind::single, 0.0f, 10.0f },
        { "s&d holder aggression bias", off::hw2_bot_config::sn_d_holder_aggression_bias, field_kind::single, 0.0f, 10.0f },
        { "s&d corner min open", off::hw2_bot_config::sn_d_corner_min_open, field_kind::single, 0.0f, 100.0f },
        { "s&d corner pause open", off::hw2_bot_config::sn_d_corner_pause_open, field_kind::single, 0.0f, 100.0f },
        { "s&d corner pause min", off::hw2_bot_config::sn_d_corner_pause_min, field_kind::single, 0.0f, 100.0f },
        { "s&d corner pause max", off::hw2_bot_config::sn_d_corner_pause_max, field_kind::single, 0.0f, 100.0f },
    };

    inline constexpr field bot_snd_roles_fields[] = {
        { "s&d follow spacing", off::hw2_bot_config::sn_d_follow_spacing, field_kind::single, 0.0f, 10000.0f },
        { "s&d trade radius", off::hw2_bot_config::sn_d_trade_radius, field_kind::single, 0.0f, 10000.0f },
        { "s&d lurker chance", off::hw2_bot_config::sn_d_lurker_chance, field_kind::single, 0.0f, 1.0f },
        { "s&d forward chance", off::hw2_bot_config::sn_d_forward_chance, field_kind::single, 0.0f, 1.0f },
        { "s&d forward seconds min", off::hw2_bot_config::sn_d_forward_seconds_min, field_kind::single, 0.0f, 60.0f },
        { "s&d forward seconds max", off::hw2_bot_config::sn_d_forward_seconds_max, field_kind::single, 0.0f, 60.0f },
        { "s&d push chance", off::hw2_bot_config::sn_d_push_chance, field_kind::single, 0.0f, 1.0f },
        { "s&d push start min", off::hw2_bot_config::sn_d_push_start_min, field_kind::single, 0.0f, 100.0f },
        { "s&d push start max", off::hw2_bot_config::sn_d_push_start_max, field_kind::single, 0.0f, 100.0f },
        { "s&d push seconds", off::hw2_bot_config::sn_d_push_seconds, field_kind::single, 0.0f, 60.0f },
        { "s&d second pusher chance", off::hw2_bot_config::sn_d_second_pusher_chance, field_kind::single, 0.0f, 1.0f },
        { "s&d push share min", off::hw2_bot_config::sn_d_push_share_min, field_kind::single, 0.0f, 1.0f },
        { "s&d push share max", off::hw2_bot_config::sn_d_push_share_max, field_kind::single, 0.0f, 1.0f },
        { "s&d push max distance", off::hw2_bot_config::sn_d_push_max_distance, field_kind::single, 0.0f, 10000.0f },
        { "s&d rotate danger", off::hw2_bot_config::sn_d_rotate_danger, field_kind::single, 0.0f, 100.0f },
        { "s&d relocate min", off::hw2_bot_config::sn_d_relocate_min, field_kind::single, 0.0f, 100.0f },
        { "s&d relocate max", off::hw2_bot_config::sn_d_relocate_max, field_kind::single, 0.0f, 100.0f },
        { "s&d shift min", off::hw2_bot_config::sn_d_shift_min, field_kind::single, 0.0f, 100.0f },
        { "s&d shift max", off::hw2_bot_config::sn_d_shift_max, field_kind::single, 0.0f, 100.0f },
        { "s&d retake gather max", off::hw2_bot_config::sn_d_retake_gather_max, field_kind::single, 0.0f, 100.0f },
        { "s&d interact seconds", off::hw2_bot_config::sn_d_interact_seconds, field_kind::single, 0.0f, 60.0f },
        { "s&d hold leash", off::hw2_bot_config::sn_d_hold_leash, field_kind::single, 0.0f, 10000.0f },
        { "s&d move leash", off::hw2_bot_config::sn_d_move_leash, field_kind::single, 0.0f, 10000.0f },
        { "s&d push leash", off::hw2_bot_config::sn_d_push_leash, field_kind::single, 0.0f, 10000.0f },
    };

    inline constexpr field bot_telemetry_fields[] = {
        { "telemetry", off::hw2_bot_config::is_telemetry, field_kind::flag, 0.0f, 1.0f },
        { "auto dump stats on world end", off::hw2_bot_config::is_auto_dump_stats_on_world_end, field_kind::flag, 0.0f, 1.0f },
        { "contact gap seconds", off::hw2_bot_config::contact_gap_seconds, field_kind::single, 0.0f, 60.0f },
        { "first shot window seconds", off::hw2_bot_config::first_shot_window_seconds, field_kind::single, 0.0f, 60.0f },
        { "pile on window seconds", off::hw2_bot_config::pile_on_window_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field streak_rules_fields[] = {
        { "enabled", off::hw2_streak_config::is_enabled, field_kind::flag, 0.0f, 1.0f },
        { "free killstreaks for testing", off::hw2_streak_config::is_free_killstreaks_for_testing, field_kind::flag, 0.0f, 1.0f },
        { "max equipped", off::hw2_streak_config::max_equipped, field_kind::whole, 0.0f, 20.0f },
        { "gamepad picker", off::hw2_streak_config::is_gamepad_picker, field_kind::flag, 0.0f, 1.0f },
        { "picker tap seconds", off::hw2_streak_config::picker_tap_seconds, field_kind::single, 0.0f, 60.0f },
        { "picker timeout seconds", off::hw2_streak_config::picker_timeout_seconds, field_kind::single, 0.0f, 60.0f },
        { "keep earned on death", off::hw2_streak_config::is_keep_earned_on_death, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field streak_bots_fields[] = {
        { "bots use killstreaks", off::hw2_streak_config::is_bots_use_killstreaks, field_kind::flag, 0.0f, 1.0f },
        { "bot random loadout", off::hw2_streak_config::is_bot_random_loadout, field_kind::flag, 0.0f, 1.0f },
        { "bot use delay min", off::hw2_streak_config::bot_use_delay_min, field_kind::single, 0.0f, 60.0f },
        { "bot use delay max", off::hw2_streak_config::bot_use_delay_max, field_kind::single, 0.0f, 60.0f },
        { "bot fight grace seconds", off::hw2_streak_config::bot_fight_grace_seconds, field_kind::single, 0.0f, 60.0f },
        { "bot max wait seconds", off::hw2_streak_config::bot_max_wait_seconds, field_kind::single, 0.0f, 60.0f },
        { "bot free killstreaks for testing", off::hw2_streak_config::is_bot_free_killstreaks_for_testing, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field streak_call_fields[] = {
        { "max placement distance", off::hw2_streak_config::max_placement_distance, field_kind::single, 0.0f, 10000.0f },
        { "nav projection extent", off::hw2_streak_config::nav_projection_extent, field_kind::single, 0.0f, 10000.0f },
        { "phone call", off::hw2_streak_config::is_phone_call, field_kind::flag, 0.0f, 1.0f },
        { "phone call seconds", off::hw2_streak_config::phone_call_seconds, field_kind::single, 0.0f, 60.0f },
        { "phone equip timeout", off::hw2_streak_config::phone_equip_timeout, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field streak_homies_fields[] = {
        { "arrive in front", off::hw2_streak_config::is_arrive_in_front, field_kind::flag, 0.0f, 1.0f },
        { "front distance", off::hw2_streak_config::front_distance, field_kind::single, 0.0f, 10000.0f },
        { "front min distance", off::hw2_streak_config::front_min_distance, field_kind::single, 0.0f, 10000.0f },
        { "front max distance", off::hw2_streak_config::front_max_distance, field_kind::single, 0.0f, 10000.0f },
        { "front max angle", off::hw2_streak_config::front_max_angle, field_kind::single, 0.0f, 180.0f },
        { "behind distance", off::hw2_streak_config::behind_distance, field_kind::single, 0.0f, 10000.0f },
        { "behind min distance", off::hw2_streak_config::behind_min_distance, field_kind::single, 0.0f, 10000.0f },
        { "behind max distance", off::hw2_streak_config::behind_max_distance, field_kind::single, 0.0f, 10000.0f },
        { "behind min angle", off::hw2_streak_config::behind_min_angle, field_kind::single, 0.0f, 180.0f },
        { "behind max path ratio", off::hw2_streak_config::behind_max_path_ratio, field_kind::single, 0.0f, 100.0f },
        { "homie count", off::hw2_streak_config::homie_count, field_kind::whole, 0.0f, 20.0f },
        { "homie spacing", off::hw2_streak_config::homie_spacing, field_kind::single, 0.0f, 10000.0f },
        { "homie max life seconds", off::hw2_streak_config::homie_max_life_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field streak_bomber_fields[] = {
        { "bomber hold time", off::hw2_streak_config::bomber_hold_time, field_kind::single, 0.0f, 60.0f },
        { "detonate distance", off::hw2_streak_config::detonate_distance, field_kind::single, 0.0f, 10000.0f },
        { "fuse seconds", off::hw2_streak_config::fuse_seconds, field_kind::single, 0.0f, 60.0f },
        { "max life seconds", off::hw2_streak_config::max_life_seconds, field_kind::single, 0.0f, 60.0f },
        { "detonate on death", off::hw2_streak_config::is_detonate_on_death, field_kind::flag, 0.0f, 1.0f },
        { "blast base damage", off::hw2_streak_config::blast_base_damage, field_kind::single, 0.0f, 500.0f },
        { "blast minimum damage", off::hw2_streak_config::blast_minimum_damage, field_kind::single, 0.0f, 500.0f },
        { "blast inner radius", off::hw2_streak_config::blast_inner_radius, field_kind::single, 0.0f, 10000.0f },
        { "blast outer radius", off::hw2_streak_config::blast_outer_radius, field_kind::single, 0.0f, 10000.0f },
        { "blast effect scale", off::hw2_streak_config::blast_effect_scale, field_kind::single, 0.0f, 10.0f },
        { "beep interval", off::hw2_streak_config::beep_interval, field_kind::single, 0.0f, 60.0f },
        { "beep near interval", off::hw2_streak_config::beep_near_interval, field_kind::single, 0.0f, 60.0f },
        { "beep far distance", off::hw2_streak_config::beep_far_distance, field_kind::single, 0.0f, 10000.0f },
        { "armed beep interval", off::hw2_streak_config::armed_beep_interval, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field streak_car_fields[] = {
        { "drive by health", off::hw2_streak_config::drive_by_health, field_kind::single, 0.0f, 5000.0f },
        { "drive by stall seconds min", off::hw2_streak_config::drive_by_stall_seconds_min, field_kind::single, 0.0f, 60.0f },
        { "drive by stall seconds max", off::hw2_streak_config::drive_by_stall_seconds_max, field_kind::single, 0.0f, 60.0f },
        { "drive by speed", off::hw2_streak_config::drive_by_speed, field_kind::single, 0.0f, 3000.0f },
        { "drive by brake distance", off::hw2_streak_config::drive_by_brake_distance, field_kind::single, 0.0f, 10000.0f },
        { "drive by patrol speed", off::hw2_streak_config::drive_by_patrol_speed, field_kind::single, 0.0f, 3000.0f },
        { "drive by patrol half length", off::hw2_streak_config::drive_by_patrol_half_length, field_kind::single, 0.0f, 10000.0f },
        { "drive by u turn radius", off::hw2_streak_config::drive_by_u_turn_radius, field_kind::single, 0.0f, 10000.0f },
        { "drive by avoidance", off::hw2_streak_config::is_drive_by_avoidance, field_kind::flag, 0.0f, 1.0f },
        { "drive by open doors", off::hw2_streak_config::is_drive_by_open_doors, field_kind::flag, 0.0f, 1.0f },
        { "drive by door radius", off::hw2_streak_config::drive_by_door_radius, field_kind::single, 0.0f, 10000.0f },
        { "drive by knock down fences", off::hw2_streak_config::is_drive_by_knock_down_fences, field_kind::flag, 0.0f, 1.0f },
        { "drive by avoid max offset", off::hw2_streak_config::drive_by_avoid_max_offset, field_kind::single, 0.0f, 10000.0f },
        { "drive by avoid slope", off::hw2_streak_config::drive_by_avoid_slope, field_kind::single, 0.0f, 10.0f },
        { "drive by avoid margin", off::hw2_streak_config::drive_by_avoid_margin, field_kind::single, 0.0f, 10000.0f },
        { "drive by destroy score", off::hw2_streak_config::drive_by_destroy_score, field_kind::whole, 0.0f, 1000.0f },
        { "drive by wreck seconds", off::hw2_streak_config::drive_by_wreck_seconds, field_kind::single, 0.0f, 60.0f },
        { "drive by wreck blast damage", off::hw2_streak_config::drive_by_wreck_blast_damage, field_kind::single, 0.0f, 500.0f },
        { "drive by wreck blast minimum damage", off::hw2_streak_config::drive_by_wreck_blast_minimum_damage, field_kind::single, 0.0f, 500.0f },
        { "drive by wreck blast inner radius", off::hw2_streak_config::drive_by_wreck_blast_inner_radius, field_kind::single, 0.0f, 10000.0f },
        { "drive by wreck blast outer radius", off::hw2_streak_config::drive_by_wreck_blast_outer_radius, field_kind::single, 0.0f, 10000.0f },
    };

    inline constexpr field streak_gun_fields[] = {
        { "drive by damage", off::hw2_streak_config::drive_by_damage, field_kind::single, 0.0f, 500.0f },
        { "drive by headshot multiplier", off::hw2_streak_config::drive_by_headshot_multiplier, field_kind::single, 0.0f, 10.0f },
        { "drive by range", off::hw2_streak_config::drive_by_range, field_kind::single, 0.0f, 10000.0f },
        { "drive by arc half angle", off::hw2_streak_config::drive_by_arc_half_angle, field_kind::single, 0.0f, 180.0f },
        { "drive by fire interval", off::hw2_streak_config::drive_by_fire_interval, field_kind::single, 0.0f, 60.0f },
        { "drive by burst min", off::hw2_streak_config::drive_by_burst_min, field_kind::whole, 0.0f, 20.0f },
        { "drive by burst max", off::hw2_streak_config::drive_by_burst_max, field_kind::whole, 0.0f, 20.0f },
        { "drive by burst pause min", off::hw2_streak_config::drive_by_burst_pause_min, field_kind::single, 0.0f, 100.0f },
        { "drive by burst pause max", off::hw2_streak_config::drive_by_burst_pause_max, field_kind::single, 0.0f, 100.0f },
        { "drive by magazine", off::hw2_streak_config::drive_by_magazine, field_kind::whole, 0.0f, 200.0f },
        { "drive by reload seconds", off::hw2_streak_config::drive_by_reload_seconds, field_kind::single, 0.0f, 60.0f },
        { "drive by reaction seconds", off::hw2_streak_config::drive_by_reaction_seconds, field_kind::single, 0.0f, 60.0f },
        { "drive by moving target spread", off::hw2_streak_config::drive_by_moving_target_spread, field_kind::single, 0.0f, 10.0f },
        { "drive by car moving spread", off::hw2_streak_config::drive_by_car_moving_spread, field_kind::single, 0.0f, 10.0f },
        { "drive by aim wander", off::hw2_streak_config::drive_by_aim_wander, field_kind::single, 0.0f, 10.0f },
        { "drive by spread", off::hw2_streak_config::drive_by_spread, field_kind::single, 0.0f, 10.0f },
        { "drive by spread fresh", off::hw2_streak_config::drive_by_spread_fresh, field_kind::single, 0.0f, 10.0f },
        { "drive by settle seconds", off::hw2_streak_config::drive_by_settle_seconds, field_kind::single, 0.0f, 60.0f },
        { "drive by head chance", off::hw2_streak_config::drive_by_head_chance, field_kind::single, 0.0f, 1.0f },
    };

    inline constexpr field streak_sound_fields[] = {
        { "drive by music volume", off::hw2_streak_config::drive_by_music_volume, field_kind::single, 0.0f, 4.0f },
        { "drive by music start fraction", off::hw2_streak_config::drive_by_music_start_fraction, field_kind::single, 0.0f, 1.0f },
        { "drive by music inner radius", off::hw2_streak_config::drive_by_music_inner_radius, field_kind::single, 0.0f, 10000.0f },
        { "drive by music falloff", off::hw2_streak_config::drive_by_music_falloff, field_kind::single, 0.0f, 10000.0f },
        { "drive by engine volume", off::hw2_streak_config::drive_by_engine_volume, field_kind::single, 0.0f, 4.0f },
    };

    inline constexpr field bot_weapon_profile_fields[] = {
        { "archetype", off::hw2_bot_weapon_profile::archetype, field_kind::byte, 0.0f, 6.0f },
        { "band min", off::hw2_bot_weapon_profile::band_min, field_kind::single, 0.0f, 100.0f },
        { "band ideal", off::hw2_bot_weapon_profile::band_ideal, field_kind::single, 0.0f, 100.0f },
        { "band max", off::hw2_bot_weapon_profile::band_max, field_kind::single, 0.0f, 100.0f },
        { "engage range scale", off::hw2_bot_weapon_profile::engage_range_scale, field_kind::single, 0.0f, 10000.0f },
        { "push bias", off::hw2_bot_weapon_profile::push_bias, field_kind::single, 0.0f, 10.0f },
        { "close out of band", off::hw2_bot_weapon_profile::is_close_out_of_band, field_kind::flag, 0.0f, 1.0f },
        { "peek scale", off::hw2_bot_weapon_profile::peek_scale, field_kind::single, 0.0f, 10.0f },
        { "hide scale", off::hw2_bot_weapon_profile::hide_scale, field_kind::single, 0.0f, 10.0f },
        { "strafe scale", off::hw2_bot_weapon_profile::strafe_scale, field_kind::single, 0.0f, 10.0f },
        { "retreat health bias", off::hw2_bot_weapon_profile::retreat_health_bias, field_kind::single, 0.0f, 1.0f },
        { "fire angle scale", off::hw2_bot_weapon_profile::fire_angle_scale, field_kind::single, 0.0f, 180.0f },
        { "burst rest scale", off::hw2_bot_weapon_profile::burst_rest_scale, field_kind::single, 0.0f, 10.0f },
        { "vantage weight", off::hw2_bot_weapon_profile::vantage_weight, field_kind::single, 0.0f, 10.0f },
        { "relocate after kill", off::hw2_bot_weapon_profile::is_relocate_after_kill, field_kind::flag, 0.0f, 1.0f },
        { "aim while holding", off::hw2_bot_weapon_profile::is_aim_while_holding, field_kind::flag, 0.0f, 1.0f },
        { "sidearm chance min", off::hw2_bot_weapon_profile::sidearm_chance_min, field_kind::single, 0.0f, 1.0f },
        { "sidearm chance max", off::hw2_bot_weapon_profile::sidearm_chance_max, field_kind::single, 0.0f, 1.0f },
        { "sidearm mag fraction", off::hw2_bot_weapon_profile::sidearm_mag_fraction, field_kind::single, 0.0f, 1.0f },
        { "seed reload seconds", off::hw2_bot_weapon_profile::seed_reload_seconds, field_kind::single, 0.0f, 60.0f },
        { "hold fire beyond band", off::hw2_bot_weapon_profile::hold_fire_beyond_band, field_kind::single, 0.0f, 100.0f },
        { "close sidearm range", off::hw2_bot_weapon_profile::close_sidearm_range, field_kind::single, 0.0f, 10000.0f },
    };

    inline constexpr field chosen_bot_fields[] = {
        { "ai difficulty", off::hw2_bot_controller::ai_difficulty, field_kind::byte, 0.0f, 5.0f },
        { "aim turn rate", off::hw2_bot_controller::aim_turn_rate, field_kind::wide, 0.0f, 50.0f },
        { "aim interp speed", off::hw2_bot_controller::aim_interp_speed, field_kind::wide, 0.0f, 50.0f },
        { "aim reaction delay", off::hw2_bot_controller::aim_reaction_delay, field_kind::wide, 0.0f, 2.0f },
        { "aim error initial", off::hw2_bot_controller::aim_error_initial, field_kind::wide, 0.0f, 20.0f },
        { "aim error settled", off::hw2_bot_controller::aim_error_settled, field_kind::wide, 0.0f, 20.0f },
        { "aim settle time", off::hw2_bot_controller::aim_settle_time, field_kind::wide, 0.0f, 5.0f },
        { "aim error interval", off::hw2_bot_controller::aim_error_interval, field_kind::wide, 0.0f, 5.0f },
        { "aim fire angle", off::hw2_bot_controller::aim_fire_angle, field_kind::wide, 0.0f, 90.0f },
        { "aim target z offset", off::hw2_bot_controller::aim_target_z_offset, field_kind::wide, -100.0f, 100.0f },
        { "burst duration", off::hw2_bot_controller::burst_duration, field_kind::wide, 0.0f, 5.0f },
        { "burst rest", off::hw2_bot_controller::burst_rest, field_kind::wide, 0.0f, 5.0f },
        { "bot role index", off::hw2_bot_controller::bot_role_index_ue, field_kind::byte, 0.0f, 10.0f },
        { "bot aggression", off::hw2_bot_controller::bot_aggression_ue, field_kind::wide, 0.0f, 10.0f },
    };

    inline constexpr field streak_cost_fields[] = {
        { "streak 1 kills", off::hw2_streak_definition::byte_size * 0 + off::hw2_streak_definition::kills_required, field_kind::whole, 0.0f, 30.0f },
        { "streak 2 kills", off::hw2_streak_definition::byte_size * 1 + off::hw2_streak_definition::kills_required, field_kind::whole, 0.0f, 30.0f },
        { "streak 3 kills", off::hw2_streak_definition::byte_size * 2 + off::hw2_streak_definition::kills_required, field_kind::whole, 0.0f, 30.0f },
        { "streak 4 kills", off::hw2_streak_definition::byte_size * 3 + off::hw2_streak_definition::kills_required, field_kind::whole, 0.0f, 30.0f },
        { "streak 5 kills", off::hw2_streak_definition::byte_size * 4 + off::hw2_streak_definition::kills_required, field_kind::whole, 0.0f, 30.0f },
        { "streak 6 kills", off::hw2_streak_definition::byte_size * 5 + off::hw2_streak_definition::kills_required, field_kind::whole, 0.0f, 30.0f },
    };

    inline constexpr field own_streak_fields[] = {
        { "ready mask", off::hw2_streak_component::ready_mask, field_kind::byte, 0.0f, 15.0f },
        { "equipped mask", off::hw2_streak_component::equipped_mask, field_kind::byte, 0.0f, 15.0f },
        { "team snitch up", off::hw2_streak_component::is_team_snitch_up, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field old_streak_fields[] = {
        { "current kill streak", off::hw2_old_streaks::current_kill_streak, field_kind::whole, 0.0f, 50.0f },
        { "can use uav", off::hw2_old_streaks::is_can_use_uav, field_kind::flag, 0.0f, 1.0f },
        { "uav time", off::hw2_old_streaks::uav_time, field_kind::wide, 0.0f, 120.0f },
        { "can use cluster strike", off::hw2_old_streaks::is_can_use_cluster_strike, field_kind::flag, 0.0f, 1.0f },
        { "cluster strike cooldown", off::hw2_old_streaks::cluster_strike_cool_down, field_kind::single, 0.0f, 120.0f },
        { "killstreaks enabled", off::hw2_old_streaks::is_killstreaks_enabled, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field drive_by_car_fields[] = {
        { "health", off::hw2_drive_by_car::health, field_kind::single, 0.0f, 5000.0f },
        { "patrol speed", off::hw2_drive_by_car::patrol_speed, field_kind::single, 0.0f, 3000.0f },
        { "stall seconds", off::hw2_drive_by_car::stall_seconds, field_kind::single, 0.0f, 60.0f },
        { "stall distance", off::hw2_drive_by_car::stall_distance, field_kind::single, 0.0f, 10000.0f },
        { "team", off::hw2_drive_by_car::team, field_kind::whole, 0.0f, 3.0f },
    };

    inline constexpr field held_weapon_fields[] = {
        { "firing mode", off::hw2_weapon_actor::firing_mode, field_kind::byte, 0.0f, 3.0f },
        { "needs pump", off::hw2_weapon_actor::is_needs_pump, field_kind::flag, 0.0f, 1.0f },
        { "bolt cycling", off::hw2_weapon_actor::is_bolt_cycling, field_kind::flag, 0.0f, 1.0f },
        { "no stock", off::hw2_weapon_actor::hw2_b_no_stock, field_kind::flag, 0.0f, 1.0f },
        { "ammo when picked up", off::hw2_weapon_actor::pick_up_weapon_ammo, field_kind::whole, 0.0f, 500.0f },
        { "start with a full mag", off::hw2_weapon_actor::is_start_with_full_mag, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field held_weapon_data_fields[] = {
        { "bullets per burst", off::hw2_weapon_data::bullets_per_burst, field_kind::whole, 1.0f, 10.0f },
        { "ads zoom", off::hw2_weapon_data::aim_fov, field_kind::wide, 10.0f, 120.0f },
        { "ads speed", off::hw2_weapon_data::aiming_interpolation_speed, field_kind::wide, 0.0f, 50.0f },
        { "hip spread", off::hw2_weapon_data::bullet_spread, field_kind::wide, 0.0f, 10.0f },
        { "ads spread", off::hw2_weapon_data::aiming_bullet_spread, field_kind::wide, 0.0f, 10.0f },
        { "crouched spread", off::hw2_weapon_data::bullet_spread_crouched, field_kind::wide, 0.0f, 10.0f },
        { "falling ads spread", off::hw2_weapon_data::aiming_bullet_spread_while_falling, field_kind::wide, 0.0f, 10.0f },
        { "moving spread", off::hw2_weapon_data::movement_spread_multiplier, field_kind::wide, 0.0f, 10.0f },
        { "recoil recovery", off::hw2_weapon_data::recoil_interpolation_speed, field_kind::wide, 0.0f, 50.0f },
        { "noise range", off::hw2_weapon_data::noise_range, field_kind::wide, 0.0f, 10000.0f },
        { "noise loudness", off::hw2_weapon_data::noise_loudness, field_kind::wide, 0.0f, 5.0f },
        { "ammo pool", off::hw2_weapon_data::ammo_type, field_kind::byte, 0.0f, 10.0f },
        { "silenced", off::hw2_weapon_data::is_uses_silencer, field_kind::flag, 0.0f, 1.0f },
        { "pump action", off::hw2_weapon_data::is_pump_action, field_kind::flag, 0.0f, 1.0f },
        { "uses ammo", off::hw2_weapon_data::uses_ammo, field_kind::flag, 0.0f, 1.0f },
        { "can aim", off::hw2_weapon_data::is_can_aim, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field held_magazine_fields[] = {
        { "magazine size", off::hw2_magazine::ammo_per_mag, field_kind::whole, 1.0f, 250.0f },
    };

    inline constexpr field held_optic_fields[] = {
        { "scope zoom", off::hw2_optic::aim_fov, field_kind::wide, 5.0f, 120.0f },
    };

    inline constexpr field vitals_fields[] = {
        { "health", off::hw2_vitals::health, field_kind::wide, 0.0f, 1000.0f },
        { "max health", off::hw2_vitals::max_health, field_kind::wide, 1.0f, 1000.0f },
        { "regen", off::hw2_vitals::is_health_regen_enabled, field_kind::flag, 0.0f, 1.0f },
        { "regen delay", off::hw2_vitals::health_regen_initial_delay, field_kind::wide, 0.0f, 30.0f },
        { "regen tick", off::hw2_vitals::regen_tick_frecuency, field_kind::single, 0.0f, 5.0f },
        { "health per tick", off::hw2_vitals::health_per_tick, field_kind::wide, 0.0f, 100.0f },
        { "spawn protected", off::hw2_vitals::is_spawn_protected, field_kind::flag, 0.0f, 1.0f },
        { "spawn protection length", off::hw2_vitals::spawn_protection_duration, field_kind::wide, 0.0f, 30.0f },
    };

    inline constexpr field own_body_fields[] = {
        { "melee range", off::hw2_character::melee_range, field_kind::wide, 0.0f, 2000.0f },
        { "melee allowed", off::hw2_character::can_melee, field_kind::flag, 0.0f, 1.0f },
        { "skill cooldown", off::hw2_character::ability_cooldown, field_kind::wide, 0.0f, 120.0f },
        { "skill ready", off::hw2_character::can_use_skill, field_kind::flag, 0.0f, 1.0f },
        { "fire allowed", off::hw2_character::fire_enabled, field_kind::flag, 0.0f, 1.0f },
        { "field upgrade", off::hw2_character::field_upgrade, field_kind::byte, 0.0f, 2.0f },
    };

    inline constexpr field own_interaction_fields[] = {
        { "interact range", off::hw2_interaction::interact_range, field_kind::wide, 0.0f, 2000.0f },
    };

    inline constexpr field own_lethal_fields[] = {
        { "fuse", off::hw2_lethal_equipment::time_to_explode, field_kind::wide, 0.0f, 10.0f },
        { "has to be armed", off::hw2_lethal_equipment::is_has_to_be_armed, field_kind::flag, 0.0f, 1.0f },
        { "delayed throw", off::hw2_lethal_equipment::is_has_delayed_throw, field_kind::flag, 0.0f, 1.0f },
        { "lethal type", off::hw2_lethal_equipment::lethal_type, field_kind::byte, 0.0f, 5.0f },
    };

    inline constexpr field own_loadout_fields[] = {
        { "selected loadout", off::hw2_loadout::selected_loadout_index, field_kind::whole, 0.0f, 10.0f },
        { "loadout slots", off::hw2_loadout::max_loadouts, field_kind::whole, 1.0f, 20.0f },
        { "field upgrade", off::hw2_loadout::field_upgrade, field_kind::byte, 0.0f, 2.0f },
    };

    inline constexpr field frag_default_fields[] = {
        { "fuse", off::hw2_frag::time_to_explode, field_kind::wide, 0.0f, 10.0f },
        { "throw strength", off::hw2_frag::pawn_velocity, field_kind::wide, 0.0f, 5000.0f },
        { "blast radius", off::hw2_frag::radius, field_kind::wide, 0.0f, 3000.0f },
    };

    inline constexpr field claymore_default_fields[] = {
        { "trigger radius", off::hw2_claymore::radius, field_kind::wide, 0.0f, 3000.0f },
    };

    inline constexpr field pickup_default_fields[] = {
        { "stays for", off::hw2_pickup_weapon::life_span, field_kind::wide, 0.0f, 600.0f },
        { "ammo", off::hw2_pickup_weapon::ammo, field_kind::whole, 0.0f, 500.0f },
        { "full mag", off::hw2_pickup_weapon::is_full_mag, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field medkit_default_fields[] = {
        { "team", off::hw2_medkit::team, field_kind::whole, -1.0f, 3.0f },
    };

    inline constexpr field damage_type_fields[] = {
        { "headshots count", off::hw2_damage_type::is_can_headshot, field_kind::flag, 0.0f, 1.0f },
        { "ragdoll launch", off::hw2_damage_type::hw2_ragdoll_launch_speed, field_kind::wide, 0.0f, 5000.0f },
        { "ragdoll lift", off::hw2_damage_type::hw2_ragdoll_lift_speed, field_kind::wide, 0.0f, 5000.0f },
    };

    inline constexpr field capture_point_fields[] = {
        { "state", off::hw2_capture_point::objetive_state, field_kind::byte, 0.0f, 4.0f },
        { "held by team b", off::hw2_capture_point::is_holder_team, field_kind::flag, 0.0f, 1.0f },
        { "progress", off::hw2_capture_point::points, field_kind::whole, 0.0f, 200.0f },
        { "points to capture", off::hw2_capture_point::points_to_capture, field_kind::whole, 1.0f, 500.0f },
        { "team a inside", off::hw2_capture_point::team_a_players, field_kind::whole, 0.0f, 16.0f },
        { "team b inside", off::hw2_capture_point::team_b_players, field_kind::whole, 0.0f, 16.0f },
        { "last state", off::hw2_capture_point::last_flag_state, field_kind::byte, 0.0f, 4.0f },
    };

    inline constexpr field snd_site_fields[] = {
        { "bomb state", off::hw2_snd_site::bomb_state, field_kind::byte, 0.0f, 3.0f },
        { "fuse", off::hw2_snd_site::bomb_time_to_explode, field_kind::wide, 0.0f, 120.0f },
        { "about to explode", off::hw2_snd_site::is_is_about_to_explode, field_kind::flag, 0.0f, 1.0f },
        { "phase", off::hw2_snd_site::phase, field_kind::whole, 0.0f, 5.0f },
        { "team", off::hw2_snd_site::team, field_kind::whole, -1.0f, 3.0f },
    };

    inline constexpr field rush_site_fields[] = {
        { "bomb state", off::hw2_rush_site::bomb_state, field_kind::byte, 0.0f, 3.0f },
        { "fuse", off::hw2_rush_site::bomb_time_to_explode, field_kind::wide, 0.0f, 120.0f },
        { "about to explode", off::hw2_rush_site::is_is_about_to_explode, field_kind::flag, 0.0f, 1.0f },
        { "phase", off::hw2_rush_site::phase, field_kind::whole, 0.0f, 5.0f },
        { "team", off::hw2_rush_site::team, field_kind::whole, -1.0f, 3.0f },
    };

    inline constexpr field snd_bomb_fields[] = {
        { "taken", off::hw2_snd_bomb::is_bomb_taken, field_kind::flag, 0.0f, 1.0f },
        { "active", off::hw2_snd_bomb::is_active, field_kind::flag, 0.0f, 1.0f },
        { "team", off::hw2_snd_bomb::team, field_kind::whole, -1.0f, 3.0f },
    };

    inline constexpr field conquest_state_fields[] = {
        { "point a holder", off::hw2_conquest_state::point_a_holder, field_kind::byte, 0.0f, 4.0f },
        { "point b holder", off::hw2_conquest_state::point_b_holder, field_kind::byte, 0.0f, 4.0f },
        { "point c holder", off::hw2_conquest_state::point_c_holder, field_kind::byte, 0.0f, 4.0f },
        { "points to capture", off::hw2_conquest_state::points_to_capture, field_kind::whole, 1.0f, 500.0f },
    };

    inline constexpr field rush_state_fields[] = {
        { "reinforcements", off::hw2_rush_state::reinforcements, field_kind::whole, 0.0f, 500.0f },
        { "max reinforcements", off::hw2_rush_state::max_reinforcements, field_kind::whole, 0.0f, 500.0f },
        { "phase", off::hw2_rush_state::phase, field_kind::whole, 0.0f, 10.0f },
        { "final phase", off::hw2_rush_state::final_phase, field_kind::whole, 0.0f, 10.0f },
        { "timed out", off::hw2_rush_state::is_time_out, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field snd_state_fields[] = {
        { "site locked", off::hw2_snd_state::attack_site_locked, field_kind::flag, 0.0f, 1.0f },
        { "roster ready", off::hw2_snd_state::round_roster_ready, field_kind::flag, 0.0f, 1.0f },
        { "show round results", off::hw2_snd_state::is_show_round_results, field_kind::flag, 0.0f, 1.0f },
        { "objective shown", off::hw2_snd_state::hw2_objective_shown, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field ffa_state_fields[] = {
        { "kills to win", off::hw2_ffa_state::kills, field_kind::whole, 1.0f, 200.0f },
        { "leader's kills", off::hw2_ffa_state::onest_player_kills, field_kind::whole, 0.0f, 200.0f },
        { "second's kills", off::hw2_ffa_state::twond_player_kills, field_kind::whole, 0.0f, 200.0f },
    };

    inline constexpr field picked_spawn_fields[] = {
        { "team", off::hw2_player_spawn::team, field_kind::whole, -1.0f, 3.0f },
        { "active", off::hw2_player_spawn::is_active, field_kind::flag, 0.0f, 1.0f },
        { "claimed", off::hw2_player_spawn::is_claimed, field_kind::flag, 0.0f, 1.0f },
        { "phase", off::hw2_player_spawn::phase, field_kind::whole, 0.0f, 10.0f },
    };

    inline constexpr field spectator_fields[] = {
        { "can respawn", off::hw2_spectator::is_can_respawn, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field migration_fields[] = {
        { "snapshot every", off::hw2_migration::snapshot_interval_seconds, field_kind::single, 0.0f, 60.0f },
        { "resume delay", off::hw2_migration::resume_delay_seconds, field_kind::single, 0.0f, 60.0f },
        { "stats every", off::hw2_migration::stats_interval_seconds, field_kind::single, 0.0f, 60.0f },
        { "reconcile window", off::hw2_migration::reconcile_window_seconds, field_kind::single, 0.0f, 60.0f },
        { "host silence", off::hw2_migration::host_silence_seconds, field_kind::single, 0.0f, 120.0f },
        { "silence check every", off::hw2_migration::host_silence_check_seconds, field_kind::single, 0.0f, 60.0f },
        { "silence arm delay", off::hw2_migration::host_silence_arm_delay_seconds, field_kind::single, 0.0f, 120.0f },
        { "migration pending", off::hw2_migration::is_migration_pending, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field online_progress_fields[] = {
        { "cloud progression", off::hw2_online_settings::is_enable_cloud_progression, field_kind::flag, 0.0f, 1.0f },
        { "show cached cloud level", off::hw2_online_settings::is_show_cached_cloud_level, field_kind::flag, 0.0f, 1.0f },
        { "sync choices to cloud", off::hw2_online_settings::is_sync_choices_to_cloud, field_kind::flag, 0.0f, 1.0f },
        { "restore choices from cloud", off::hw2_online_settings::is_restore_choices_from_cloud, field_kind::flag, 0.0f, 1.0f },
        { "retire local missions", off::hw2_online_settings::is_retire_legacy_missions, field_kind::flag, 0.0f, 1.0f },
        { "restore missions from cloud", off::hw2_online_settings::is_restore_missions_from_cloud, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field own_progression_fields[] = {
        { "demo mode", off::hw2_progression_full::is_demo_mode, field_kind::flag, 0.0f, 1.0f },
        { "point blank distance", off::hw2_progression_full::point_blank_distance, field_kind::whole, 0.0f, 5000.0f },
        { "loaded", off::hw2_progression_full::is_loaded, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field save_level_fields[] = {
        { "level", off::hw2_save_level::level, field_kind::whole, 1.0f, 55.0f },
        { "experience", off::hw2_save_level::experience, field_kind::whole, 0.0f, 1000000.0f },
    };

    inline constexpr field save_game_fields[] = {
        { "selected loadout", off::hw2_save_game::selected_loadout_index, field_kind::whole, 0.0f, 10.0f },
        { "field upgrade", off::hw2_save_game::field_upgrade, field_kind::byte, 0.0f, 2.0f },
        { "toggle aim", off::hw2_save_game::is_toggle_aim, field_kind::flag, 0.0f, 1.0f },
        { "toggle sniper aim", off::hw2_save_game::is_toggle_aim_sniper, field_kind::flag, 0.0f, 1.0f },
        { "controller sensitivity", off::hw2_save_game::controller_sensitivity, field_kind::wide, 0.0f, 10.0f },
        { "controller ads sensitivity", off::hw2_save_game::controller_ads_sensitivity, field_kind::wide, 0.0f, 10.0f },
        { "controller scope sensitivity", off::hw2_save_game::controller_scope_sensitivity, field_kind::wide, 0.0f, 10.0f },
        { "vibration", off::hw2_save_game::is_controller_vibration, field_kind::flag, 0.0f, 1.0f },
        { "aim assist", off::hw2_save_game::is_controller_aim_assist, field_kind::flag, 0.0f, 1.0f },
        { "field of view", off::hw2_save_game::hw2_field_of_view, field_kind::wide, 60.0f, 160.0f },
    };

    inline constexpr field save_streaks_fields[] = {
        { "equipped streaks", off::hw2_save_streaks::equipped_mask, field_kind::whole, 0.0f, 15.0f },
    };

    inline constexpr field save_menu_fields[] = {
        { "favorite loadout", off::hw2_save_menu::favorite_loadout_index, field_kind::whole, 0.0f, 10.0f },
        { "preview team", off::hw2_save_menu::preview_operator_team, field_kind::whole, 0.0f, 1.0f },
    };

    inline constexpr field matchmaking_fields[] = {
        { "quick play preferred ping", off::hw2_online_settings::quick_play_preferred_ping_ms, field_kind::whole, 0.0f, 500.0f },
        { "quick play max ping", off::hw2_online_settings::quick_play_max_ping_ms, field_kind::whole, 0.0f, 1000.0f },
        { "quick play open slots", off::hw2_online_settings::quick_play_min_open_slots, field_kind::whole, 0.0f, 32.0f },
        { "failed lobby retry", off::hw2_online_settings::quick_play_failed_lobby_seconds, field_kind::single, 0.0f, 120.0f },
        { "full lobby retry", off::hw2_online_settings::quick_play_full_lobby_seconds, field_kind::single, 0.0f, 120.0f },
        { "join budget", off::hw2_online_settings::quick_play_join_budget_seconds, field_kind::single, 0.0f, 300.0f },
        { "server probe every", off::hw2_online_settings::server_probe_interval_seconds, field_kind::single, 0.0f, 120.0f },
        { "server probe results", off::hw2_online_settings::server_probe_max_results, field_kind::whole, 0.0f, 500.0f },
        { "measure ping", off::hw2_online_settings::is_measure_server_ping, field_kind::flag, 0.0f, 1.0f },
        { "ping probe every", off::hw2_online_settings::ping_probe_interval_seconds, field_kind::single, 0.0f, 60.0f },
        { "ping probe give up", off::hw2_online_settings::ping_probe_give_up_seconds, field_kind::single, 0.0f, 60.0f },
        { "ping probe hosts", off::hw2_online_settings::ping_probe_max_hosts, field_kind::whole, 0.0f, 200.0f },
        { "live lobby refresh", off::hw2_online_settings::is_live_lobby_refresh, field_kind::flag, 0.0f, 1.0f },
        { "ask before joining an invite", off::hw2_online_settings::is_prompt_before_joining_invite, field_kind::flag, 0.0f, 1.0f },
        { "invite offline friends", off::hw2_online_settings::is_allow_inviting_offline_friends, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field cine_capture_fields[] = {
        { "hotkeys enabled", off::hw2_cine_settings::is_hotkeys_enabled, field_kind::flag, 0.0f, 1.0f },
        { "hotkeys work while paused", off::hw2_cine_settings::is_hotkeys_work_while_paused, field_kind::flag, 0.0f, 1.0f },
        { "tik tok high res record key needs shift", off::hw2_cine_settings::is_tik_tok_high_res_record_key_needs_shift, field_kind::flag, 0.0f, 1.0f },
        { "god mode tap window", off::hw2_cine_settings::god_mode_tap_window, field_kind::single, 0.0f, 60.0f },
        { "frame rate", off::hw2_cine_settings::frame_rate, field_kind::whole, 0.0f, 240.0f },
        { "capture width", off::hw2_cine_settings::capture_width, field_kind::whole, 0.0f, 7680.0f },
        { "capture height", off::hw2_cine_settings::capture_height, field_kind::whole, 0.0f, 7680.0f },
        { "tik tok capture width", off::hw2_cine_settings::tik_tok_capture_width, field_kind::whole, 0.0f, 7680.0f },
        { "tik tok capture height", off::hw2_cine_settings::tik_tok_capture_height, field_kind::whole, 0.0f, 7680.0f },
        { "tik tok high res capture width", off::hw2_cine_settings::tik_tok_high_res_capture_width, field_kind::whole, 0.0f, 7680.0f },
        { "tik tok high res capture height", off::hw2_cine_settings::tik_tok_high_res_capture_height, field_kind::whole, 0.0f, 7680.0f },
        { "tik tok high res bitrate mbps", off::hw2_cine_settings::tik_tok_high_res_bitrate_mbps, field_kind::whole, 0.0f, 240.0f },
        { "tik tok high res max bitrate mbps", off::hw2_cine_settings::tik_tok_high_res_max_bitrate_mbps, field_kind::whole, 0.0f, 240.0f },
        { "tik tok high res game screen percentage", off::hw2_cine_settings::tik_tok_high_res_game_screen_percentage, field_kind::whole, 0.0f, 100.0f },
        { "tik tok high res locked frame rate", off::hw2_cine_settings::is_tik_tok_high_res_locked_frame_rate, field_kind::flag, 0.0f, 1.0f },
        { "tik tok high res high fidelity lighting", off::hw2_cine_settings::is_tik_tok_high_res_high_fidelity_lighting, field_kind::flag, 0.0f, 1.0f },
        { "tik tok circular scope", off::hw2_cine_settings::is_tik_tok_circular_scope, field_kind::flag, 0.0f, 1.0f },
        { "tik tok scope width fraction", off::hw2_cine_settings::tik_tok_scope_width_fraction, field_kind::single, 0.0f, 10.0f },
        { "camera capture width", off::hw2_cine_settings::camera_capture_width, field_kind::whole, 0.0f, 7680.0f },
        { "camera capture height", off::hw2_cine_settings::camera_capture_height, field_kind::whole, 0.0f, 7680.0f },
        { "camera supersample", off::hw2_cine_settings::camera_supersample, field_kind::single, 0.0f, 100.0f },
        { "sync groom hair", off::hw2_cine_settings::is_sync_groom_hair, field_kind::flag, 0.0f, 1.0f },
        { "encoder", off::hw2_cine_settings::encoder, field_kind::byte, 0.0f, 5.0f },
        { "quality", off::hw2_cine_settings::quality, field_kind::whole, 0.0f, 100000.0f },
        { "cap frame rate while recording", off::hw2_cine_settings::is_cap_frame_rate_while_recording, field_kind::flag, 0.0f, 1.0f },
        { "locked frame rate", off::hw2_cine_settings::is_locked_frame_rate, field_kind::flag, 0.0f, 1.0f },
        { "camera temporal aa", off::hw2_cine_settings::is_camera_temporal_aa, field_kind::flag, 0.0f, 1.0f },
        { "camera global illumination", off::hw2_cine_settings::camera_global_illumination, field_kind::byte, 0.0f, 5.0f },
        { "camera cinematic quality", off::hw2_cine_settings::is_camera_cinematic_quality, field_kind::flag, 0.0f, 1.0f },
        { "camera exposure", off::hw2_cine_settings::camera_exposure, field_kind::byte, 0.0f, 5.0f },
        { "camera exposure bias", off::hw2_cine_settings::camera_exposure_bias, field_kind::single, 0.0f, 10.0f },
        { "camera exposure speed up", off::hw2_cine_settings::camera_exposure_speed_up, field_kind::single, 0.0f, 10.0f },
        { "camera exposure speed down", off::hw2_cine_settings::camera_exposure_speed_down, field_kind::single, 0.0f, 10.0f },
        { "camera high fidelity lighting", off::hw2_cine_settings::is_camera_high_fidelity_lighting, field_kind::flag, 0.0f, 1.0f },
        { "camera depth of field", off::hw2_cine_settings::is_camera_depth_of_field, field_kind::flag, 0.0f, 1.0f },
        { "camera motion blur", off::hw2_cine_settings::is_camera_motion_blur, field_kind::flag, 0.0f, 1.0f },
        { "camera motion blur amount", off::hw2_cine_settings::camera_motion_blur_amount, field_kind::single, 0.0f, 100.0f },
        { "camera motion blur max", off::hw2_cine_settings::camera_motion_blur_max, field_kind::single, 0.0f, 100.0f },
        { "record audio", off::hw2_cine_settings::is_record_audio, field_kind::flag, 0.0f, 1.0f },
        { "audio bitrate kbps", off::hw2_cine_settings::audio_bitrate_kbps, field_kind::whole, 0.0f, 240.0f },
        { "offline audio for locked takes", off::hw2_cine_settings::is_offline_audio_for_locked_takes, field_kind::flag, 0.0f, 1.0f },
        { "keep locked take wav", off::hw2_cine_settings::is_keep_locked_take_wav, field_kind::flag, 0.0f, 1.0f },
        { "offline audio buffer frames", off::hw2_cine_settings::offline_audio_buffer_frames, field_kind::whole, 0.0f, 100.0f },
        { "hide ui", off::hw2_cine_settings::is_hide_ui, field_kind::flag, 0.0f, 1.0f },
        { "drop camera type", off::hw2_cine_settings::drop_camera_type, field_kind::byte, 0.0f, 5.0f },
        { "screenshot width", off::hw2_cine_settings::screenshot_width, field_kind::whole, 0.0f, 7680.0f },
        { "screenshot height", off::hw2_cine_settings::screenshot_height, field_kind::whole, 0.0f, 7680.0f },
        { "screenshot match viewport aspect", off::hw2_cine_settings::is_screenshot_match_viewport_aspect, field_kind::flag, 0.0f, 1.0f },
        { "screenshot ultra quality", off::hw2_cine_settings::is_screenshot_ultra_quality, field_kind::flag, 0.0f, 1.0f },
        { "screenshot convergence frames", off::hw2_cine_settings::screenshot_convergence_frames, field_kind::whole, 0.0f, 100.0f },
        { "screenshot warm up frames", off::hw2_cine_settings::screenshot_warm_up_frames, field_kind::whole, 0.0f, 100.0f },
        { "screenshot freeze world", off::hw2_cine_settings::is_screenshot_freeze_world, field_kind::flag, 0.0f, 1.0f },
        { "screenshot flush texture streaming", off::hw2_cine_settings::is_screenshot_flush_texture_streaming, field_kind::flag, 0.0f, 1.0f },
        { "screenshot unpause for capture", off::hw2_cine_settings::is_screenshot_unpause_for_capture, field_kind::flag, 0.0f, 1.0f },
        { "screenshot pause policy", off::hw2_cine_settings::screenshot_pause_policy, field_kind::byte, 0.0f, 5.0f },
        { "keep intermediate files", off::hw2_cine_settings::is_keep_intermediate_files, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field replay_options_fields[] = {
        { "auto record matches", off::hw2_replay_settings::is_auto_record_matches, field_kind::flag, 0.0f, 1.0f },
        { "max retained replays", off::hw2_replay_settings::max_retained_replays, field_kind::whole, 0.0f, 100.0f },
        { "hotkeys enabled", off::hw2_replay_settings::is_hotkeys_enabled, field_kind::flag, 0.0f, 1.0f },
        { "camera speed", off::hw2_replay_settings::camera_speed, field_kind::single, 0.0f, 2000.0f },
        { "camera boost multiplier", off::hw2_replay_settings::camera_boost_multiplier, field_kind::single, 0.0f, 10.0f },
        { "seek step seconds", off::hw2_replay_settings::seek_step_seconds, field_kind::single, 0.0f, 60.0f },
        { "show playback readout", off::hw2_replay_settings::is_show_playback_readout, field_kind::flag, 0.0f, 1.0f },
        { "control bar inactive opacity", off::hw2_replay_settings::control_bar_inactive_opacity, field_kind::single, 0.0f, 100.0f },
        { "restore last grade", off::hw2_replay_settings::is_restore_last_grade, field_kind::flag, 0.0f, 1.0f },
        { "follow pan speed", off::hw2_replay_settings::follow_pan_speed, field_kind::single, 0.0f, 2000.0f },
        { "invert follow pan", off::hw2_replay_settings::is_invert_follow_pan, field_kind::flag, 0.0f, 1.0f },
        { "follow distance", off::hw2_replay_settings::follow_distance, field_kind::single, 0.0f, 2000.0f },
        { "min follow distance", off::hw2_replay_settings::min_follow_distance, field_kind::single, 0.0f, 2000.0f },
        { "max follow distance", off::hw2_replay_settings::max_follow_distance, field_kind::single, 0.0f, 2000.0f },
        { "follow distance step", off::hw2_replay_settings::follow_distance_step, field_kind::single, 0.0f, 2000.0f },
        { "follow focus height", off::hw2_replay_settings::follow_focus_height, field_kind::single, 0.0f, 2000.0f },
        { "follow smooth time", off::hw2_replay_settings::follow_smooth_time, field_kind::single, 0.0f, 60.0f },
        { "chase pitch", off::hw2_replay_settings::chase_pitch, field_kind::single, 0.0f, 180.0f },
        { "follow smooth by default", off::hw2_replay_settings::is_follow_smooth_by_default, field_kind::flag, 0.0f, 1.0f },
        { "follow avoid geometry", off::hw2_replay_settings::is_follow_avoid_geometry, field_kind::flag, 0.0f, 1.0f },
        { "flying breaks follow", off::hw2_replay_settings::is_flying_breaks_follow, field_kind::flag, 0.0f, 1.0f },
        { "tactile movement time", off::hw2_replay_settings::tactile_movement_time, field_kind::single, 0.0f, 60.0f },
        { "smooth movement time", off::hw2_replay_settings::smooth_movement_time, field_kind::single, 0.0f, 60.0f },
        { "look smoothing time", off::hw2_replay_settings::look_smoothing_time, field_kind::single, 0.0f, 60.0f },
        { "smooth movement by default", off::hw2_replay_settings::is_smooth_movement_by_default, field_kind::flag, 0.0f, 1.0f },
        { "smooth look by default", off::hw2_replay_settings::is_smooth_look_by_default, field_kind::flag, 0.0f, 1.0f },
        { "camera speed step", off::hw2_replay_settings::camera_speed_step, field_kind::single, 0.0f, 2000.0f },
        { "min camera speed", off::hw2_replay_settings::min_camera_speed, field_kind::single, 0.0f, 2000.0f },
        { "max camera speed", off::hw2_replay_settings::max_camera_speed, field_kind::single, 0.0f, 2000.0f },
        { "zoom step scale", off::hw2_replay_settings::zoom_step_scale, field_kind::single, 0.0f, 10.0f },
        { "sequence frame rate", off::hw2_replay_settings::sequence_frame_rate, field_kind::whole, 0.0f, 240.0f },
    };

    inline constexpr field voice_options_fields[] = {
        { "voice chat allowed", off::hw2_voice_settings::is_voice_chat_allowed, field_kind::flag, 0.0f, 1.0f },
        { "push to talk gate threshold", off::hw2_voice_settings::push_to_talk_gate_threshold, field_kind::single, 0.0f, 10.0f },
        { "open mic threshold scale", off::hw2_voice_settings::open_mic_threshold_scale, field_kind::single, 0.0f, 10.0f },
        { "max mic gain", off::hw2_voice_settings::max_mic_gain, field_kind::single, 0.0f, 10.0f },
        { "default voice chat enabled", off::hw2_voice_settings::is_default_voice_chat_enabled, field_kind::flag, 0.0f, 1.0f },
        { "default voice mode", off::hw2_voice_settings::default_voice_mode, field_kind::byte, 0.0f, 5.0f },
        { "default voice channel", off::hw2_voice_settings::default_voice_channel, field_kind::byte, 0.0f, 5.0f },
        { "default voice volume", off::hw2_voice_settings::default_voice_volume, field_kind::single, 0.0f, 10.0f },
        { "default mic volume", off::hw2_voice_settings::default_mic_volume, field_kind::single, 0.0f, 10.0f },
        { "default open mic threshold", off::hw2_voice_settings::default_open_mic_threshold, field_kind::single, 0.0f, 10.0f },
        { "max talkers shown", off::hw2_voice_settings::max_talkers_shown, field_kind::whole, 0.0f, 100.0f },
        { "show local talker", off::hw2_voice_settings::is_show_local_talker, field_kind::flag, 0.0f, 1.0f },
        { "talkers z order", off::hw2_voice_settings::talkers_z_order, field_kind::whole, 0.0f, 100.0f },
        { "talking hold seconds", off::hw2_voice_settings::talking_hold_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field voice_save_fields[] = {
        { "enabled", off::hw2_voice_save::is_enabled, field_kind::flag, 0.0f, 1.0f },
        { "mode", off::hw2_voice_save::mode, field_kind::byte, 0.0f, 5.0f },
        { "channel", off::hw2_voice_save::channel, field_kind::byte, 0.0f, 5.0f },
        { "voice volume", off::hw2_voice_save::voice_volume, field_kind::single, 0.0f, 10.0f },
        { "mic volume", off::hw2_voice_save::mic_volume, field_kind::single, 0.0f, 10.0f },
        { "open mic threshold", off::hw2_voice_save::open_mic_threshold, field_kind::single, 0.0f, 10.0f },
    };

    inline constexpr field audio_output_fields[] = {
        { "manage output device", off::hw2_audio_output::is_manage_output_device, field_kind::flag, 0.0f, 1.0f },
        { "recover from null device", off::hw2_audio_output::is_recover_from_null_device, field_kind::flag, 0.0f, 1.0f },
        { "null recovery delay seconds", off::hw2_audio_output::null_recovery_delay_seconds, field_kind::single, 0.0f, 60.0f },
        { "swap grace seconds", off::hw2_audio_output::swap_grace_seconds, field_kind::single, 0.0f, 60.0f },
        { "poll interval seconds", off::hw2_audio_output::poll_interval_seconds, field_kind::single, 0.0f, 60.0f },
        { "auto audio backend", off::hw2_audio_output::is_auto_audio_backend, field_kind::flag, 0.0f, 1.0f },
        { "show audio mode row", off::hw2_audio_output::is_show_audio_mode_row, field_kind::flag, 0.0f, 1.0f },
        { "na n guard", off::hw2_audio_output::is_na_n_guard, field_kind::flag, 0.0f, 1.0f },
        { "signal report seconds", off::hw2_audio_output::signal_report_seconds, field_kind::single, 0.0f, 60.0f },
        { "max label length", off::hw2_audio_output::max_label_length, field_kind::whole, 0.0f, 100.0f },
    };

    inline constexpr field voice_cues_fields[] = {
        { "enabled", off::hw2_voice_cues::is_enabled, field_kind::flag, 0.0f, 1.0f },
        { "volume", off::hw2_voice_cues::volume, field_kind::single, 0.0f, 10.0f },
        { "pitch", off::hw2_voice_cues::pitch, field_kind::single, 0.0f, 180.0f },
        { "claim generic voice", off::hw2_voice_cues::is_claim_generic_voice, field_kind::flag, 0.0f, 1.0f },
        { "spawn line delay", off::hw2_voice_cues::spawn_line_delay, field_kind::single, 0.0f, 60.0f },
        { "post match delay", off::hw2_voice_cues::post_match_delay, field_kind::single, 0.0f, 60.0f },
        { "round result delay", off::hw2_voice_cues::round_result_delay, field_kind::single, 0.0f, 60.0f },
        { "generic round start lines", off::hw2_voice_cues::is_generic_round_start_lines, field_kind::flag, 0.0f, 1.0f },
        { "round start lines", off::hw2_voice_cues::is_round_start_lines, field_kind::flag, 0.0f, 1.0f },
        { "round result lines", off::hw2_voice_cues::is_round_result_lines, field_kind::flag, 0.0f, 1.0f },
        { "round start line every", off::hw2_voice_cues::round_start_line_every, field_kind::whole, 0.0f, 100.0f },
        { "round result line every", off::hw2_voice_cues::round_result_line_every, field_kind::whole, 0.0f, 100.0f },
        { "generic result on deciding round", off::hw2_voice_cues::is_generic_result_on_deciding_round, field_kind::flag, 0.0f, 1.0f },
        { "lead hold seconds", off::hw2_voice_cues::lead_hold_seconds, field_kind::single, 0.0f, 60.0f },
        { "line gap", off::hw2_voice_cues::line_gap, field_kind::single, 0.0f, 60.0f },
        { "queue stale seconds", off::hw2_voice_cues::queue_stale_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field own_voice_fields[] = {
        { "enabled", off::hw2_generic_voice::enabled, field_kind::flag, 0.0f, 1.0f },
        { "volume", off::hw2_generic_voice::volume, field_kind::wide, 0.0f, 10.0f },
        { "global cooldown", off::hw2_generic_voice::global_cooldown, field_kind::wide, 0.0f, 100.0f },
        { "debug force play", off::hw2_generic_voice::debug_force_play, field_kind::flag, 0.0f, 1.0f },
        { "silenced", off::hw2_generic_voice::silenced, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field controller_options_fields[] = {
        { "use tpp", off::hw2_controller_options::is_use_tpp, field_kind::flag, 0.0f, 1.0f },
        { "vertical axis inverted", off::hw2_controller_options::is_vertical_axis_inverted, field_kind::flag, 0.0f, 1.0f },
        { "horizontal axis inverted", off::hw2_controller_options::is_horizontal_axis_inverted, field_kind::flag, 0.0f, 1.0f },
        { "show fps", off::hw2_controller_options::is_show_fps, field_kind::flag, 0.0f, 1.0f },
        { "ui volume", off::hw2_controller_options::ui_volume, field_kind::wide, 0.0f, 10.0f },
        { "ambient volume", off::hw2_controller_options::ambient_volume, field_kind::wide, 0.0f, 10.0f },
        { "characters volume", off::hw2_controller_options::characters_volume, field_kind::wide, 0.0f, 10.0f },
        { "master volume", off::hw2_controller_options::master_volume, field_kind::wide, 0.0f, 10.0f },
        { "music volume", off::hw2_controller_options::music_volume, field_kind::wide, 0.0f, 10.0f },
        { "mouse sensitivity", off::hw2_controller_options::mouse_sensitivity, field_kind::wide, 0.0f, 100.0f },
        { "aim sensitivity", off::hw2_controller_options::aim_sensitivity, field_kind::wide, 0.0f, 100.0f },
        { "show latency", off::hw2_controller_options::is_show_latency, field_kind::flag, 0.0f, 1.0f },
        { "toggle run", off::hw2_controller_options::is_toggle_run, field_kind::flag, 0.0f, 1.0f },
        { "toggle crouch", off::hw2_controller_options::is_toggle_crouch, field_kind::flag, 0.0f, 1.0f },
        { "toggle aim", off::hw2_controller_options::is_toggle_aim, field_kind::flag, 0.0f, 1.0f },
        { "toggle aim sniper", off::hw2_controller_options::is_toggle_aim_sniper, field_kind::flag, 0.0f, 1.0f },
        { "controller sensitivity", off::hw2_controller_options::controller_sensitivity, field_kind::wide, 0.0f, 100.0f },
        { "controller ads sensitivity", off::hw2_controller_options::controller_ads_sensitivity, field_kind::wide, 0.0f, 100.0f },
        { "controller scope sensitivity", off::hw2_controller_options::controller_scope_sensitivity, field_kind::wide, 0.0f, 100.0f },
        { "controller vibration", off::hw2_controller_options::is_controller_vibration, field_kind::flag, 0.0f, 1.0f },
        { "controller aim assist", off::hw2_controller_options::is_controller_aim_assist, field_kind::flag, 0.0f, 1.0f },
        { "hw2 field of view", off::hw2_controller_options::hw2_field_of_view, field_kind::wide, 0.0f, 180.0f },
    };

    inline constexpr field input_general_fields[] = {
        { "base yaw rate", off::hw2_input_settings::base_yaw_rate, field_kind::single, 0.0f, 180.0f },
        { "base pitch rate", off::hw2_input_settings::base_pitch_rate, field_kind::single, 0.0f, 180.0f },
        { "inner dead zone", off::hw2_input_settings::inner_dead_zone, field_kind::single, 0.0f, 100.0f },
        { "outer dead zone", off::hw2_input_settings::outer_dead_zone, field_kind::single, 0.0f, 100.0f },
        { "response exponent", off::hw2_input_settings::response_exponent, field_kind::single, 0.0f, 100.0f },
        { "acceleration multiplier", off::hw2_input_settings::acceleration_multiplier, field_kind::single, 0.0f, 10.0f },
        { "acceleration start delay", off::hw2_input_settings::acceleration_start_delay, field_kind::single, 0.0f, 10.0f },
        { "acceleration ramp time", off::hw2_input_settings::acceleration_ramp_time, field_kind::single, 0.0f, 10.0f },
        { "acceleration engage threshold", off::hw2_input_settings::acceleration_engage_threshold, field_kind::single, 0.0f, 10.0f },
        { "stick device activation", off::hw2_input_settings::stick_device_activation, field_kind::single, 0.0f, 100.0f },
        { "scale stick with zoom", off::hw2_input_settings::is_scale_stick_with_zoom, field_kind::flag, 0.0f, 1.0f },
        { "default sensitivity", off::hw2_input_settings::default_sensitivity, field_kind::single, 0.0f, 100.0f },
        { "default ads sensitivity", off::hw2_input_settings::default_ads_sensitivity, field_kind::single, 0.0f, 100.0f },
        { "default scope sensitivity", off::hw2_input_settings::default_scope_sensitivity, field_kind::single, 0.0f, 100.0f },
        { "default vibration", off::hw2_input_settings::is_default_vibration, field_kind::flag, 0.0f, 1.0f },
        { "default aim assist", off::hw2_input_settings::is_default_aim_assist, field_kind::flag, 0.0f, 1.0f },
        { "default field of view", off::hw2_input_settings::default_field_of_view, field_kind::single, 0.0f, 180.0f },
        { "min field of view", off::hw2_input_settings::min_field_of_view, field_kind::single, 0.0f, 180.0f },
        { "max field of view", off::hw2_input_settings::max_field_of_view, field_kind::single, 0.0f, 180.0f },
        { "weapon field of view follows", off::hw2_input_settings::is_weapon_field_of_view_follows, field_kind::flag, 0.0f, 1.0f },
        { "hide first person legs at low quality", off::hw2_input_settings::is_hide_first_person_legs_at_low_quality, field_kind::flag, 0.0f, 1.0f },
        { "hide first person legs at or below view distance quality", off::hw2_input_settings::hide_first_person_legs_at_or_below_view_distance_quality, field_kind::whole, 0.0f, 100000.0f },
        { "hide pawn until weapon ready", off::hw2_input_settings::is_hide_pawn_until_weapon_ready, field_kind::flag, 0.0f, 1.0f },
        { "pawn weapon ready timeout seconds", off::hw2_input_settings::pawn_weapon_ready_timeout_seconds, field_kind::single, 0.0f, 60.0f },
        { "restore stranded pawn view", off::hw2_input_settings::is_restore_stranded_pawn_view, field_kind::flag, 0.0f, 1.0f },
        { "stranded pawn view grace seconds", off::hw2_input_settings::stranded_pawn_view_grace_seconds, field_kind::single, 0.0f, 60.0f },
        { "unacknowledged pawn view grace seconds", off::hw2_input_settings::unacknowledged_pawn_view_grace_seconds, field_kind::single, 0.0f, 60.0f },
        { "global rumble scale", off::hw2_input_settings::global_rumble_scale, field_kind::single, 0.0f, 10.0f },
        { "fire large intensity", off::hw2_input_settings::fire_large_intensity, field_kind::single, 0.0f, 100.0f },
        { "fire small intensity", off::hw2_input_settings::fire_small_intensity, field_kind::single, 0.0f, 100.0f },
        { "fire duration", off::hw2_input_settings::fire_duration, field_kind::single, 0.0f, 10.0f },
        { "fire heavy large intensity", off::hw2_input_settings::fire_heavy_large_intensity, field_kind::single, 0.0f, 100.0f },
        { "fire heavy small intensity", off::hw2_input_settings::fire_heavy_small_intensity, field_kind::single, 0.0f, 100.0f },
        { "fire heavy duration", off::hw2_input_settings::fire_heavy_duration, field_kind::single, 0.0f, 10.0f },
        { "damage large intensity", off::hw2_input_settings::damage_large_intensity, field_kind::single, 0.0f, 100.0f },
        { "damage small intensity", off::hw2_input_settings::damage_small_intensity, field_kind::single, 0.0f, 100.0f },
        { "damage duration", off::hw2_input_settings::damage_duration, field_kind::single, 0.0f, 10.0f },
        { "damage full strength fraction", off::hw2_input_settings::damage_full_strength_fraction, field_kind::single, 0.0f, 10.0f },
        { "damage minimum scale", off::hw2_input_settings::damage_minimum_scale, field_kind::single, 0.0f, 10.0f },
        { "explosion large intensity", off::hw2_input_settings::explosion_large_intensity, field_kind::single, 0.0f, 100.0f },
        { "explosion small intensity", off::hw2_input_settings::explosion_small_intensity, field_kind::single, 0.0f, 100.0f },
        { "explosion duration", off::hw2_input_settings::explosion_duration, field_kind::single, 0.0f, 10.0f },
        { "death large intensity", off::hw2_input_settings::death_large_intensity, field_kind::single, 0.0f, 100.0f },
        { "death small intensity", off::hw2_input_settings::death_small_intensity, field_kind::single, 0.0f, 100.0f },
        { "death duration", off::hw2_input_settings::death_duration, field_kind::single, 0.0f, 10.0f },
        { "hitmarker small intensity", off::hw2_input_settings::hitmarker_small_intensity, field_kind::single, 0.0f, 100.0f },
        { "hitmarker duration", off::hw2_input_settings::hitmarker_duration, field_kind::single, 0.0f, 10.0f },
        { "keybind notice seconds", off::hw2_input_settings::keybind_notice_seconds, field_kind::single, 0.0f, 60.0f },
    };

    inline constexpr field input_aim_assist_fields[] = {
        { "aim assist allowed", off::hw2_input_settings::is_aim_assist_allowed, field_kind::flag, 0.0f, 1.0f },
        { "max target distance", off::hw2_input_settings::max_target_distance, field_kind::single, 0.0f, 2000.0f },
        { "rotation cone degrees", off::hw2_input_settings::rotation_cone_degrees, field_kind::single, 0.0f, 180.0f },
        { "slowdown cone degrees", off::hw2_input_settings::slowdown_cone_degrees, field_kind::single, 0.0f, 180.0f },
        { "slowdown scale", off::hw2_input_settings::slowdown_scale, field_kind::single, 0.0f, 10.0f },
        { "rotation degrees per second", off::hw2_input_settings::rotation_degrees_per_second, field_kind::single, 0.0f, 60.0f },
        { "rotation falloff exponent", off::hw2_input_settings::rotation_falloff_exponent, field_kind::single, 0.0f, 100.0f },
        { "rotation min motion", off::hw2_input_settings::rotation_min_motion, field_kind::single, 0.0f, 100.0f },
        { "rotation reference speed", off::hw2_input_settings::rotation_reference_speed, field_kind::single, 0.0f, 2000.0f },
        { "target height fraction", off::hw2_input_settings::target_height_fraction, field_kind::single, 0.0f, 10.0f },
        { "require line of sight", off::hw2_input_settings::is_require_line_of_sight, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field player_input_fields[] = {
        { "vibration enabled", off::hw2_input_system::is_vibration_enabled, field_kind::flag, 0.0f, 1.0f },
        { "aim assist enabled", off::hw2_input_system::is_aim_assist_enabled, field_kind::flag, 0.0f, 1.0f },
    };

    inline constexpr field third_person_fields[] = {
        { "enabled", off::hw2_third_person::is_enabled, field_kind::flag, 0.0f, 1.0f },
        { "pivot height", off::hw2_third_person::pivot_height, field_kind::single, 0.0f, 2000.0f },
        { "pivot height smoothing speed", off::hw2_third_person::pivot_height_smoothing_speed, field_kind::single, 0.0f, 2000.0f },
        { "hip distance", off::hw2_third_person::hip_distance, field_kind::single, 0.0f, 2000.0f },
        { "hip shoulder offset", off::hw2_third_person::hip_shoulder_offset, field_kind::single, 0.0f, 2000.0f },
        { "hip height", off::hw2_third_person::hip_height, field_kind::single, 0.0f, 2000.0f },
        { "aim distance", off::hw2_third_person::aim_distance, field_kind::single, 0.0f, 2000.0f },
        { "aim shoulder offset", off::hw2_third_person::aim_shoulder_offset, field_kind::single, 0.0f, 2000.0f },
        { "aim height", off::hw2_third_person::aim_height, field_kind::single, 0.0f, 2000.0f },
        { "look up distance scale", off::hw2_third_person::look_up_distance_scale, field_kind::single, 0.0f, 10.0f },
        { "aim smoothing time", off::hw2_third_person::aim_smoothing_time, field_kind::single, 0.0f, 60.0f },
        { "shoulder swap smoothing time", off::hw2_third_person::shoulder_swap_smoothing_time, field_kind::single, 0.0f, 60.0f },
        { "remember shoulder side", off::hw2_third_person::is_remember_shoulder_side, field_kind::flag, 0.0f, 1.0f },
        { "min ads field of view ratio", off::hw2_third_person::min_ads_field_of_view_ratio, field_kind::single, 0.0f, 10.0f },
        { "scope from eye", off::hw2_third_person::is_scope_from_eye, field_kind::flag, 0.0f, 1.0f },
        { "probe radius", off::hw2_third_person::probe_radius, field_kind::single, 0.0f, 2000.0f },
        { "probe channel", off::hw2_third_person::probe_channel, field_kind::byte, 0.0f, 5.0f },
        { "collision return smoothing time", off::hw2_third_person::collision_return_smoothing_time, field_kind::single, 0.0f, 60.0f },
        { "auto shoulder swap", off::hw2_third_person::is_auto_shoulder_swap, field_kind::flag, 0.0f, 1.0f },
        { "auto swap blocked fraction", off::hw2_third_person::auto_swap_blocked_fraction, field_kind::single, 0.0f, 10.0f },
        { "auto swap other side fraction", off::hw2_third_person::auto_swap_other_side_fraction, field_kind::single, 0.0f, 10.0f },
        { "auto swap return fraction", off::hw2_third_person::auto_swap_return_fraction, field_kind::single, 0.0f, 10.0f },
        { "auto swap hold seconds", off::hw2_third_person::auto_swap_hold_seconds, field_kind::single, 0.0f, 60.0f },
        { "hide character when close", off::hw2_third_person::is_hide_character_when_close, field_kind::flag, 0.0f, 1.0f },
        { "hide distance", off::hw2_third_person::hide_distance, field_kind::single, 0.0f, 2000.0f },
        { "show distance", off::hw2_third_person::show_distance, field_kind::single, 0.0f, 2000.0f },
        { "cancel inspect in third person", off::hw2_third_person::is_cancel_inspect_in_third_person, field_kind::flag, 0.0f, 1.0f },
        { "show shoulder hint", off::hw2_third_person::is_show_shoulder_hint, field_kind::flag, 0.0f, 1.0f },
        { "shoulder hint display seconds", off::hw2_third_person::shoulder_hint_display_seconds, field_kind::single, 0.0f, 60.0f },
        { "shoulder hint opacity", off::hw2_third_person::shoulder_hint_opacity, field_kind::single, 0.0f, 100.0f },
        { "shoulder hint fade time", off::hw2_third_person::shoulder_hint_fade_time, field_kind::single, 0.0f, 60.0f },
    };

    inline field_state match_rules_state[std::size(match_rules_fields)];
    inline field_state match_clock_state[std::size(match_clock_fields)];
    inline field_state game_mode_state[std::size(game_mode_fields)];
    inline field_state lobby_preset_state[std::size(lobby_preset_fields)];

    inline field_board match_rules{ "match rules", board_target::match_settings, match_rules_fields, static_cast<int>(std::size(match_rules_fields)), match_rules_state };
    inline field_board match_clock{ "score and clock holds", board_target::match_state, match_clock_fields, static_cast<int>(std::size(match_clock_fields)), match_clock_state };
    inline field_board game_mode_rules{ "game mode", board_target::game_mode, game_mode_fields, static_cast<int>(std::size(game_mode_fields)), game_mode_state };
    inline field_board lobby_presets{ "lobby presets", board_target::lobby_instance, lobby_preset_fields, static_cast<int>(std::size(lobby_preset_fields)), lobby_preset_state };

    inline field_state bot_targeting_state[std::size(bot_targeting_fields)];
    inline field_state bot_chasing_state[std::size(bot_chasing_fields)];
    inline field_state bot_memory_state[std::size(bot_memory_fields)];
    inline field_state bot_alerts_state[std::size(bot_alerts_fields)];
    inline field_state bot_hit_reaction_state[std::size(bot_hit_reaction_fields)];
    inline field_state bot_reloading_state[std::size(bot_reloading_fields)];
    inline field_state bot_strafing_state[std::size(bot_strafing_fields)];
    inline field_state bot_vehicles_state[std::size(bot_vehicles_fields)];
    inline field_state bot_engaging_state[std::size(bot_engaging_fields)];
    inline field_state bot_roles_state[std::size(bot_roles_fields)];
    inline field_state bot_bags_state[std::size(bot_bags_fields)];
    inline field_state bot_cover_state[std::size(bot_cover_fields)];
    inline field_state bot_peeking_state[std::size(bot_peeking_fields)];
    inline field_state bot_retreat_state[std::size(bot_retreat_fields)];
    inline field_state bot_pushing_state[std::size(bot_pushing_fields)];
    inline field_state bot_coordinator_state[std::size(bot_coordinator_fields)];
    inline field_state bot_conquest_state[std::size(bot_conquest_fields)];
    inline field_state bot_lanes_state[std::size(bot_lanes_fields)];
    inline field_state bot_callouts_state[std::size(bot_callouts_fields)];
    inline field_state bot_personalities_state[std::size(bot_personalities_fields)];
    inline field_state bot_detection_state[std::size(bot_detection_fields)];
    inline field_state bot_flinch_voice_state[std::size(bot_flinch_voice_fields)];
    inline field_state bot_unstuck_state[std::size(bot_unstuck_fields)];
    inline field_state bot_defence_state[std::size(bot_defence_fields)];
    inline field_state bot_advantage_state[std::size(bot_advantage_fields)];
    inline field_state bot_weapons_state[std::size(bot_weapons_fields)];
    inline field_state bot_sight_state[std::size(bot_sight_fields)];
    inline field_state bot_spawns_state[std::size(bot_spawns_fields)];
    inline field_state bot_glass_state[std::size(bot_glass_fields)];
    inline field_state bot_snd_plans_state[std::size(bot_snd_plans_fields)];
    inline field_state bot_snd_staging_state[std::size(bot_snd_staging_fields)];
    inline field_state bot_snd_roles_state[std::size(bot_snd_roles_fields)];
    inline field_state bot_telemetry_state[std::size(bot_telemetry_fields)];
    inline field_state bot_weapon_profile_state[std::size(bot_weapon_profile_fields)];
    inline field_state chosen_bot_state[std::size(chosen_bot_fields)];
    inline field_state streak_rules_state[std::size(streak_rules_fields)];
    inline field_state streak_bots_state[std::size(streak_bots_fields)];
    inline field_state streak_call_state[std::size(streak_call_fields)];
    inline field_state streak_cost_state[std::size(streak_cost_fields)];
    inline field_state streak_homies_state[std::size(streak_homies_fields)];
    inline field_state streak_bomber_state[std::size(streak_bomber_fields)];
    inline field_state streak_car_state[std::size(streak_car_fields)];
    inline field_state streak_gun_state[std::size(streak_gun_fields)];
    inline field_state streak_sound_state[std::size(streak_sound_fields)];
    inline field_state own_streak_state[std::size(own_streak_fields)];
    inline field_state old_streak_state[std::size(old_streak_fields)];
    inline field_state drive_by_car_state[std::size(drive_by_car_fields)];

    inline field_board bot_targeting{ "targeting and pile on", board_target::bot_settings, bot_targeting_fields, static_cast<int>(std::size(bot_targeting_fields)), bot_targeting_state };
    inline field_board bot_chasing{ "holding, chasing, searching", board_target::bot_settings, bot_chasing_fields, static_cast<int>(std::size(bot_chasing_fields)), bot_chasing_state };
    inline field_board bot_memory{ "memory and objective leash", board_target::bot_settings, bot_memory_fields, static_cast<int>(std::size(bot_memory_fields)), bot_memory_state };
    inline field_board bot_alerts{ "alerts and noises", board_target::bot_settings, bot_alerts_fields, static_cast<int>(std::size(bot_alerts_fields)), bot_alerts_state };
    inline field_board bot_hit_reaction{ "reacting to being shot", board_target::bot_settings, bot_hit_reaction_fields, static_cast<int>(std::size(bot_hit_reaction_fields)), bot_hit_reaction_state };
    inline field_board bot_reloading{ "reloading", board_target::bot_settings, bot_reloading_fields, static_cast<int>(std::size(bot_reloading_fields)), bot_reloading_state };
    inline field_board bot_strafing{ "strafing and shooting on the move", board_target::bot_settings, bot_strafing_fields, static_cast<int>(std::size(bot_strafing_fields)), bot_strafing_state };
    inline field_board bot_vehicles{ "shooting at the drive by car", board_target::bot_settings, bot_vehicles_fields, static_cast<int>(std::size(bot_vehicles_fields)), bot_vehicles_state };
    inline field_board bot_engaging{ "engaging and disengaging", board_target::bot_settings, bot_engaging_fields, static_cast<int>(std::size(bot_engaging_fields)), bot_engaging_state };
    inline field_board bot_roles{ "objective roles", board_target::bot_settings, bot_roles_fields, static_cast<int>(std::size(bot_roles_fields)), bot_roles_state };
    inline field_board bot_bags{ "bag retrieval", board_target::bot_settings, bot_bags_fields, static_cast<int>(std::size(bot_bags_fields)), bot_bags_state };
    inline field_board bot_cover{ "cover", board_target::bot_settings, bot_cover_fields, static_cast<int>(std::size(bot_cover_fields)), bot_cover_state };
    inline field_board bot_peeking{ "peeking", board_target::bot_settings, bot_peeking_fields, static_cast<int>(std::size(bot_peeking_fields)), bot_peeking_state };
    inline field_board bot_retreat{ "retreating and healing", board_target::bot_settings, bot_retreat_fields, static_cast<int>(std::size(bot_retreat_fields)), bot_retreat_state };
    inline field_board bot_pushing{ "pushing and holding points", board_target::bot_settings, bot_pushing_fields, static_cast<int>(std::size(bot_pushing_fields)), bot_pushing_state };
    inline field_board bot_coordinator{ "team coordinator", board_target::bot_settings, bot_coordinator_fields, static_cast<int>(std::size(bot_coordinator_fields)), bot_coordinator_state };
    inline field_board bot_conquest{ "conquest plan", board_target::bot_settings, bot_conquest_fields, static_cast<int>(std::size(bot_conquest_fields)), bot_conquest_state };
    inline field_board bot_lanes{ "bag mode plan and lanes", board_target::bot_settings, bot_lanes_fields, static_cast<int>(std::size(bot_lanes_fields)), bot_lanes_state };
    inline field_board bot_callouts{ "callouts", board_target::bot_settings, bot_callouts_fields, static_cast<int>(std::size(bot_callouts_fields)), bot_callouts_state };
    inline field_board bot_personalities{ "personalities", board_target::bot_settings, bot_personalities_fields, static_cast<int>(std::size(bot_personalities_fields)), bot_personalities_state };
    inline field_board bot_detection{ "detection", board_target::bot_settings, bot_detection_fields, static_cast<int>(std::size(bot_detection_fields)), bot_detection_state };
    inline field_board bot_flinch_voice{ "flinch and voice", board_target::bot_settings, bot_flinch_voice_fields, static_cast<int>(std::size(bot_flinch_voice_fields)), bot_flinch_voice_state };
    inline field_board bot_unstuck{ "getting unstuck", board_target::bot_settings, bot_unstuck_fields, static_cast<int>(std::size(bot_unstuck_fields)), bot_unstuck_state };
    inline field_board bot_defence{ "active defence", board_target::bot_settings, bot_defence_fields, static_cast<int>(std::size(bot_defence_fields)), bot_defence_state };
    inline field_board bot_advantage{ "advantage and per mode aggression", board_target::bot_settings, bot_advantage_fields, static_cast<int>(std::size(bot_advantage_fields)), bot_advantage_state };
    inline field_board bot_weapons{ "weapons and sidearms", board_target::bot_settings, bot_weapons_fields, static_cast<int>(std::size(bot_weapons_fields)), bot_weapons_state };
    inline field_board bot_sight{ "sight, noise error, roaming", board_target::bot_settings, bot_sight_fields, static_cast<int>(std::size(bot_sight_fields)), bot_sight_state };
    inline field_board bot_spawns{ "spawns and spawn protection", board_target::bot_settings, bot_spawns_fields, static_cast<int>(std::size(bot_spawns_fields)), bot_spawns_state };
    inline field_board bot_glass{ "glass", board_target::bot_settings, bot_glass_fields, static_cast<int>(std::size(bot_glass_fields)), bot_glass_state };
    inline field_board bot_snd_plans{ "s&d director plans", board_target::bot_settings, bot_snd_plans_fields, static_cast<int>(std::size(bot_snd_plans_fields)), bot_snd_plans_state };
    inline field_board bot_snd_staging{ "s&d staging, fakes, late round", board_target::bot_settings, bot_snd_staging_fields, static_cast<int>(std::size(bot_snd_staging_fields)), bot_snd_staging_state };
    inline field_board bot_snd_roles{ "s&d lurk, push, rotate, retake", board_target::bot_settings, bot_snd_roles_fields, static_cast<int>(std::size(bot_snd_roles_fields)), bot_snd_roles_state };
    inline field_board bot_telemetry{ "stats recorder", board_target::bot_settings, bot_telemetry_fields, static_cast<int>(std::size(bot_telemetry_fields)), bot_telemetry_state };
    inline field_board bot_weapon_profile{ "weapon profile", board_target::bot_weapon_profile, bot_weapon_profile_fields, static_cast<int>(std::size(bot_weapon_profile_fields)), bot_weapon_profile_state };
    inline field_board chosen_bot{ "picked bot", board_target::chosen_bot, chosen_bot_fields, static_cast<int>(std::size(chosen_bot_fields)), chosen_bot_state };
    inline field_board streak_rules{ "rules and picker", board_target::streak_settings, streak_rules_fields, static_cast<int>(std::size(streak_rules_fields)), streak_rules_state };
    inline field_board streak_bots{ "bots and streaks", board_target::streak_settings, streak_bots_fields, static_cast<int>(std::size(streak_bots_fields)), streak_bots_state };
    inline field_board streak_call{ "placement and phone call", board_target::streak_settings, streak_call_fields, static_cast<int>(std::size(streak_call_fields)), streak_call_state };
    inline field_board streak_cost{ "kill costs", board_target::streak_definitions, streak_cost_fields, static_cast<int>(std::size(streak_cost_fields)), streak_cost_state };
    inline field_board streak_homies{ "homies", board_target::streak_settings, streak_homies_fields, static_cast<int>(std::size(streak_homies_fields)), streak_homies_state };
    inline field_board streak_bomber{ "suicide bomber", board_target::streak_settings, streak_bomber_fields, static_cast<int>(std::size(streak_bomber_fields)), streak_bomber_state };
    inline field_board streak_car{ "drive by car", board_target::streak_settings, streak_car_fields, static_cast<int>(std::size(streak_car_fields)), streak_car_state };
    inline field_board streak_gun{ "drive by gun", board_target::streak_settings, streak_gun_fields, static_cast<int>(std::size(streak_gun_fields)), streak_gun_state };
    inline field_board streak_sound{ "drive by music and engine", board_target::streak_settings, streak_sound_fields, static_cast<int>(std::size(streak_sound_fields)), streak_sound_state };
    inline field_board own_streak{ "your streak component", board_target::own_streaks, own_streak_fields, static_cast<int>(std::size(own_streak_fields)), own_streak_state };
    inline field_board old_streak{ "uav and cluster strike", board_target::own_old_streaks, old_streak_fields, static_cast<int>(std::size(old_streak_fields)), old_streak_state };
    inline field_board drive_by_car{ "live drive by car", board_target::drive_by_car, drive_by_car_fields, static_cast<int>(std::size(drive_by_car_fields)), drive_by_car_state };

    inline field_state held_weapon_state[std::size(held_weapon_fields)];
    inline field_state held_weapon_data_state[std::size(held_weapon_data_fields)];
    inline field_state held_magazine_state[std::size(held_magazine_fields)];
    inline field_state held_optic_state[std::size(held_optic_fields)];
    inline field_state own_vitals_state[std::size(vitals_fields)];
    inline field_state picked_vitals_state[std::size(vitals_fields)];
    inline field_state own_body_state[std::size(own_body_fields)];
    inline field_state own_interaction_state[std::size(own_interaction_fields)];
    inline field_state own_lethal_state[std::size(own_lethal_fields)];
    inline field_state own_loadout_state[std::size(own_loadout_fields)];
    inline field_state frag_defaults_state[std::size(frag_default_fields)];
    inline field_state claymore_defaults_state[std::size(claymore_default_fields)];
    inline field_state pickup_defaults_state[std::size(pickup_default_fields)];
    inline field_state medkit_defaults_state[std::size(medkit_default_fields)];
    inline field_state damage_type_board_state[std::size(damage_type_fields)];

    inline field_board held_weapon{ "gun in your hands", board_target::held_weapon, held_weapon_fields, static_cast<int>(std::size(held_weapon_fields)), held_weapon_state };
    inline field_board held_weapon_data{ "its model's settings", board_target::held_weapon_data, held_weapon_data_fields, static_cast<int>(std::size(held_weapon_data_fields)), held_weapon_data_state };
    inline field_board held_magazine{ "magazine", board_target::held_magazine, held_magazine_fields, static_cast<int>(std::size(held_magazine_fields)), held_magazine_state };
    inline field_board held_optic{ "optic", board_target::held_optic, held_optic_fields, static_cast<int>(std::size(held_optic_fields)), held_optic_state };
    inline field_board own_vitals{ "your health", board_target::own_vitals, vitals_fields, static_cast<int>(std::size(vitals_fields)), own_vitals_state };
    inline field_board picked_vitals{ "picked player's health", board_target::picked_vitals, vitals_fields, static_cast<int>(std::size(vitals_fields)), picked_vitals_state };
    inline field_board own_body{ "your body", board_target::own_body, own_body_fields, static_cast<int>(std::size(own_body_fields)), own_body_state };
    inline field_board own_interaction{ "interaction", board_target::own_interaction, own_interaction_fields, static_cast<int>(std::size(own_interaction_fields)), own_interaction_state };
    inline field_board own_lethal{ "your lethal", board_target::own_lethal, own_lethal_fields, static_cast<int>(std::size(own_lethal_fields)), own_lethal_state };
    inline field_board own_loadout{ "your loadout", board_target::own_loadout, own_loadout_fields, static_cast<int>(std::size(own_loadout_fields)), own_loadout_state };
    inline field_board frag_defaults{ "new frag grenades", board_target::frag_defaults, frag_default_fields, static_cast<int>(std::size(frag_default_fields)), frag_defaults_state };
    inline field_board claymore_defaults{ "new claymores", board_target::claymore_defaults, claymore_default_fields, static_cast<int>(std::size(claymore_default_fields)), claymore_defaults_state };
    inline field_board pickup_defaults{ "dropped guns", board_target::pickup_defaults, pickup_default_fields, static_cast<int>(std::size(pickup_default_fields)), pickup_defaults_state };
    inline field_board medkit_defaults{ "new medkits", board_target::medkit_defaults, medkit_default_fields, static_cast<int>(std::size(medkit_default_fields)), medkit_defaults_state };
    inline field_board damage_type_board{ "damage type", board_target::damage_type, damage_type_fields, static_cast<int>(std::size(damage_type_fields)), damage_type_board_state };

    inline field_state picked_capture_point_state[std::size(capture_point_fields)];
    inline field_state picked_snd_site_state[std::size(snd_site_fields)];
    inline field_state picked_rush_site_state[std::size(rush_site_fields)];
    inline field_state snd_bomb_board_state[std::size(snd_bomb_fields)];
    inline field_state conquest_state_board_state[std::size(conquest_state_fields)];
    inline field_state rush_state_board_state[std::size(rush_state_fields)];
    inline field_state snd_state_board_state[std::size(snd_state_fields)];
    inline field_state ffa_state_board_state[std::size(ffa_state_fields)];
    inline field_state picked_spawn_board_state[std::size(picked_spawn_fields)];
    inline field_state own_spectator_board_state[std::size(spectator_fields)];
    inline field_state host_migration_board_state[std::size(migration_fields)];

    inline field_board picked_capture_point{ "picked capture point", board_target::picked_capture_point, capture_point_fields, static_cast<int>(std::size(capture_point_fields)), picked_capture_point_state };
    inline field_board picked_snd_site{ "picked bomb site", board_target::picked_snd_site, snd_site_fields, static_cast<int>(std::size(snd_site_fields)), picked_snd_site_state };
    inline field_board picked_rush_site{ "picked rush site", board_target::picked_rush_site, rush_site_fields, static_cast<int>(std::size(rush_site_fields)), picked_rush_site_state };
    inline field_board snd_bomb_board{ "the bomb", board_target::snd_bomb, snd_bomb_fields, static_cast<int>(std::size(snd_bomb_fields)), snd_bomb_board_state };
    inline field_board conquest_state_board{ "conquest", board_target::conquest_state, conquest_state_fields, static_cast<int>(std::size(conquest_state_fields)), conquest_state_board_state };
    inline field_board rush_state_board{ "rush", board_target::rush_state, rush_state_fields, static_cast<int>(std::size(rush_state_fields)), rush_state_board_state };
    inline field_board snd_state_board{ "search and destroy", board_target::snd_state, snd_state_fields, static_cast<int>(std::size(snd_state_fields)), snd_state_board_state };
    inline field_board ffa_state_board{ "free for all", board_target::ffa_state, ffa_state_fields, static_cast<int>(std::size(ffa_state_fields)), ffa_state_board_state };
    inline field_board picked_spawn_board{ "picked spawn point", board_target::picked_spawn, picked_spawn_fields, static_cast<int>(std::size(picked_spawn_fields)), picked_spawn_board_state };
    inline field_board own_spectator_board{ "your spectator", board_target::own_spectator, spectator_fields, static_cast<int>(std::size(spectator_fields)), own_spectator_board_state };
    inline field_board host_migration_board{ "host migration timings", board_target::host_migration, migration_fields, static_cast<int>(std::size(migration_fields)), host_migration_board_state };

    inline field_state online_progress_board_state[std::size(online_progress_fields)];
    inline field_state own_progression_board_state[std::size(own_progression_fields)];
    inline field_state save_level_board_state[std::size(save_level_fields)];
    inline field_state save_game_board_state[std::size(save_game_fields)];
    inline field_state save_streaks_board_state[std::size(save_streaks_fields)];
    inline field_state save_menu_board_state[std::size(save_menu_fields)];

    inline field_board online_progress_board{ "cloud and missions settings", board_target::online_settings, online_progress_fields, static_cast<int>(std::size(online_progress_fields)), online_progress_board_state };
    inline field_board own_progression_board{ "your progression component", board_target::own_progression, own_progression_fields, static_cast<int>(std::size(own_progression_fields)), own_progression_board_state };
    inline field_board save_level_board{ "level save", board_target::save_level, save_level_fields, static_cast<int>(std::size(save_level_fields)), save_level_board_state };
    inline field_board save_game_board{ "settings and loadout save", board_target::save_game, save_game_fields, static_cast<int>(std::size(save_game_fields)), save_game_board_state };
    inline field_board save_streaks_board{ "killstreak save", board_target::save_streaks, save_streaks_fields, static_cast<int>(std::size(save_streaks_fields)), save_streaks_board_state };
    inline field_board save_menu_board{ "menu preferences save", board_target::save_menu, save_menu_fields, static_cast<int>(std::size(save_menu_fields)), save_menu_board_state };

    inline field_state cine_capture_board_state[std::size(cine_capture_fields)];
    inline field_state replay_options_board_state[std::size(replay_options_fields)];
    inline field_state voice_options_board_state[std::size(voice_options_fields)];
    inline field_state voice_save_board_state[std::size(voice_save_fields)];
    inline field_state audio_output_board_state[std::size(audio_output_fields)];
    inline field_state voice_cues_board_state[std::size(voice_cues_fields)];
    inline field_state own_voice_board_state[std::size(own_voice_fields)];
    inline field_state controller_options_board_state[std::size(controller_options_fields)];
    inline field_state input_general_board_state[std::size(input_general_fields)];
    inline field_state input_aim_assist_board_state[std::size(input_aim_assist_fields)];
    inline field_state player_input_board_state[std::size(player_input_fields)];
    inline field_state third_person_board_state[std::size(third_person_fields)];

    inline field_board cine_capture_board{ "capture settings", board_target::cine_settings, cine_capture_fields, static_cast<int>(std::size(cine_capture_fields)), cine_capture_board_state };
    inline field_board replay_options_board{ "replay settings", board_target::replay_settings, replay_options_fields, static_cast<int>(std::size(replay_options_fields)), replay_options_board_state };
    inline field_board voice_options_board{ "voice chat settings", board_target::voice_settings, voice_options_fields, static_cast<int>(std::size(voice_options_fields)), voice_options_board_state };
    inline field_board voice_save_board{ "your voice settings", board_target::voice_save, voice_save_fields, static_cast<int>(std::size(voice_save_fields)), voice_save_board_state };
    inline field_board audio_output_board{ "audio device", board_target::audio_output, audio_output_fields, static_cast<int>(std::size(audio_output_fields)), audio_output_board_state };
    inline field_board voice_cues_board{ "announcer", board_target::voice_cues, voice_cues_fields, static_cast<int>(std::size(voice_cues_fields)), voice_cues_board_state };
    inline field_board own_voice_board{ "your character's voice", board_target::own_voice, own_voice_fields, static_cast<int>(std::size(own_voice_fields)), own_voice_board_state };
    inline field_board controller_options_board{ "your controls and volumes", board_target::own_controller_options, controller_options_fields, static_cast<int>(std::size(controller_options_fields)), controller_options_board_state };
    inline field_board input_general_board{ "input, fov clamp and rumble", board_target::input_settings, input_general_fields, static_cast<int>(std::size(input_general_fields)), input_general_board_state };
    inline field_board input_aim_assist_board{ "aim assist tuning", board_target::input_aim_gated, input_aim_assist_fields, static_cast<int>(std::size(input_aim_assist_fields)), input_aim_assist_board_state };
    inline field_board player_input_board{ "your input switches", board_target::player_input, player_input_fields, static_cast<int>(std::size(player_input_fields)), player_input_board_state };
    inline field_board third_person_board{ "native third person rig", board_target::third_person, third_person_fields, static_cast<int>(std::size(third_person_fields)), third_person_board_state };

    inline field_state matchmaking_state[std::size(matchmaking_fields)];
    inline field_board matchmaking_board{ "matchmaking", board_target::online_settings, matchmaking_fields, static_cast<int>(std::size(matchmaking_fields)), matchmaking_state };

    namespace screen = sdk::offsets::post_process_settings;

    inline constexpr std::uint32_t wheel_all = 0x18;

    [[nodiscard]] inline constexpr field screen_knob(const char* label, std::uint32_t offset, field_kind kind,
        float low, float high, std::uint32_t gate, std::uint32_t gate_bit) {
        constexpr std::uint32_t base = off::ucamera_component::post_process_settings;

        return { label, base + offset, kind, low, high, 0, base + gate, gate_bit };
    }

    [[nodiscard]] inline constexpr field volume_knob(const char* label, std::uint32_t offset, field_kind kind,
        float low, float high, std::uint32_t gate, std::uint32_t gate_bit) {
        constexpr std::uint32_t base = off::apost_process_volume::settings;

        return { label, base + offset, kind, low, high, 0, base + gate, gate_bit };
    }

    inline constexpr field world_settings_fields[] = {
        { "gravity", off::aworld_settings::world_gravity_z, field_kind::single, -4000.0f, 4000.0f },
        { "gravity default", off::aworld_settings::global_gravity_z, field_kind::single, -4000.0f, 4000.0f },
        { "gravity override set", off::aworld_settings::is_global_gravity_set, field_kind::bit, 0.0f, 1.0f, off::aworld_settings::is_global_gravity_set_bit },
        { "time dilation", off::aworld_settings::time_dilation, field_kind::single, 0.0f, 4.0f },
        { "cinematic dilation", off::aworld_settings::cinematic_time_dilation, field_kind::single, 0.0f, 4.0f },
        { "replay dilation", off::aworld_settings::demo_play_time_dilation, field_kind::single, 0.0f, 4.0f },
        { "dilation allowed", off::aworld_settings::is_allow_time_dilation, field_kind::bit, 0.0f, 1.0f, off::aworld_settings::is_allow_time_dilation_bit },
        { "dilation floor", off::aworld_settings::min_global_time_dilation, field_kind::single, 0.0f, 1.0f },
        { "dilation ceiling", off::aworld_settings::max_global_time_dilation, field_kind::single, 1.0f, 100.0f },
        { "frame time floor", off::aworld_settings::min_undilated_frame_time, field_kind::single, 0.0f, 0.1f },
        { "frame time ceiling", off::aworld_settings::max_undilated_frame_time, field_kind::single, 0.0f, 1.0f },
    };

    inline constexpr field screen_post_fields[] = {
        screen_knob("saturation", screen::color_saturation + wheel_all, field_kind::wide, 0.0f, 2.0f, screen::is_override_color_saturation, screen::is_override_color_saturation_bit),
        screen_knob("contrast", screen::color_contrast + wheel_all, field_kind::wide, 0.0f, 2.0f, screen::is_override_color_contrast, screen::is_override_color_contrast_bit),
        screen_knob("gamma", screen::color_gamma + wheel_all, field_kind::wide, 0.0f, 2.0f, screen::is_override_color_gamma, screen::is_override_color_gamma_bit),
        screen_knob("gain", screen::color_gain + wheel_all, field_kind::wide, 0.0f, 4.0f, screen::is_override_color_gain, screen::is_override_color_gain_bit),
        screen_knob("offset", screen::color_offset + wheel_all, field_kind::wide, -1.0f, 1.0f, screen::is_override_color_offset, screen::is_override_color_offset_bit),
        screen_knob("tint red", screen::scene_color_tint, field_kind::single, 0.0f, 2.0f, screen::is_override_scene_color_tint, screen::is_override_scene_color_tint_bit),
        screen_knob("tint green", screen::scene_color_tint + 0x4, field_kind::single, 0.0f, 2.0f, screen::is_override_scene_color_tint, screen::is_override_scene_color_tint_bit),
        screen_knob("tint blue", screen::scene_color_tint + 0x8, field_kind::single, 0.0f, 2.0f, screen::is_override_scene_color_tint, screen::is_override_scene_color_tint_bit),
        screen_knob("exposure bias", screen::auto_exposure_bias, field_kind::single, -8.0f, 8.0f, screen::is_override_auto_exposure_bias, screen::is_override_auto_exposure_bias_bit),
        screen_knob("exposure floor", screen::auto_exposure_min_brightness, field_kind::single, -10.0f, 20.0f, screen::is_override_auto_exposure_min_brightness, screen::is_override_auto_exposure_min_brightness_bit),
        screen_knob("exposure ceiling", screen::auto_exposure_max_brightness, field_kind::single, -10.0f, 20.0f, screen::is_override_auto_exposure_max_brightness, screen::is_override_auto_exposure_max_brightness_bit),
        screen_knob("exposure method", screen::auto_exposure_method, field_kind::byte, 0.0f, 2.0f, screen::is_override_auto_exposure_method, screen::is_override_auto_exposure_method_bit),
        screen_knob("bloom", screen::bloom_intensity, field_kind::single, 0.0f, 8.0f, screen::is_override_bloom_intensity, screen::is_override_bloom_intensity_bit),
        screen_knob("vignette", screen::vignette_intensity, field_kind::single, 0.0f, 2.0f, screen::is_override_vignette_intensity, screen::is_override_vignette_intensity_bit),
        screen_knob("film grain", screen::film_grain_intensity, field_kind::single, 0.0f, 2.0f, screen::is_override_film_grain_intensity, screen::is_override_film_grain_intensity_bit),
        screen_knob("sharpen", screen::sharpen, field_kind::single, 0.0f, 4.0f, screen::is_override_sharpen, screen::is_override_sharpen_bit),
        screen_knob("chromatic", screen::scene_fringe_intensity, field_kind::single, 0.0f, 5.0f, screen::is_override_scene_fringe_intensity, screen::is_override_scene_fringe_intensity_bit),
        screen_knob("ambient occlusion", screen::ambient_occlusion_intensity, field_kind::single, 0.0f, 1.0f, screen::is_override_ambient_occlusion_intensity, screen::is_override_ambient_occlusion_intensity_bit),
        screen_knob("motion blur", screen::motion_blur_amount, field_kind::single, 0.0f, 1.0f, screen::is_override_motion_blur_amount, screen::is_override_motion_blur_amount_bit),
        screen_knob("focal distance", screen::depth_of_field_focal_distance, field_kind::single, 0.0f, 10000.0f, screen::is_override_depth_of_field_focal_distance, screen::is_override_depth_of_field_focal_distance_bit),
        screen_knob("indirect lighting", screen::indirect_lighting_intensity, field_kind::single, 0.0f, 8.0f, screen::is_override_indirect_lighting_intensity, screen::is_override_indirect_lighting_intensity_bit),
        screen_knob("colour grading", screen::color_grading_intensity, field_kind::single, 0.0f, 1.0f, screen::is_override_color_grading_intensity, screen::is_override_color_grading_intensity_bit),
        screen_knob("tone curve", screen::tone_curve_amount, field_kind::single, 0.0f, 1.0f, screen::is_override_tone_curve_amount, screen::is_override_tone_curve_amount_bit),
        screen_knob("skylight leaking", screen::lumen_skylight_leaking, field_kind::single, 0.0f, 1.0f, screen::is_override_lumen_skylight_leaking, screen::is_override_lumen_skylight_leaking_bit),
        screen_knob("global illumination", screen::dynamic_global_illumination_method, field_kind::byte, 0.0f, 2.0f, screen::is_override_dynamic_global_illumination_method, screen::is_override_dynamic_global_illumination_method_bit),
        screen_knob("reflections", screen::reflection_method, field_kind::byte, 0.0f, 3.0f, screen::is_override_reflection_method, screen::is_override_reflection_method_bit),
    };

    inline constexpr field post_volume_fields[] = {
        { "enabled", off::apost_process_volume::is_enabled, field_kind::bit, 0.0f, 1.0f, off::apost_process_volume::is_enabled_bit },
        { "unbound", off::apost_process_volume::is_unbound, field_kind::bit, 0.0f, 1.0f, off::apost_process_volume::is_unbound_bit },
        { "priority", off::apost_process_volume::priority, field_kind::single, -10.0f, 10.0f },
        { "blend radius", off::apost_process_volume::blend_radius, field_kind::single, 0.0f, 10000.0f },
        { "blend weight", off::apost_process_volume::blend_weight, field_kind::single, 0.0f, 1.0f },
        volume_knob("saturation", screen::color_saturation + wheel_all, field_kind::wide, 0.0f, 2.0f, screen::is_override_color_saturation, screen::is_override_color_saturation_bit),
        volume_knob("gain", screen::color_gain + wheel_all, field_kind::wide, 0.0f, 4.0f, screen::is_override_color_gain, screen::is_override_color_gain_bit),
        volume_knob("exposure bias", screen::auto_exposure_bias, field_kind::single, -8.0f, 8.0f, screen::is_override_auto_exposure_bias, screen::is_override_auto_exposure_bias_bit),
        volume_knob("bloom", screen::bloom_intensity, field_kind::single, 0.0f, 8.0f, screen::is_override_bloom_intensity, screen::is_override_bloom_intensity_bit),
        volume_knob("vignette", screen::vignette_intensity, field_kind::single, 0.0f, 2.0f, screen::is_override_vignette_intensity, screen::is_override_vignette_intensity_bit),
        volume_knob("film grain", screen::film_grain_intensity, field_kind::single, 0.0f, 2.0f, screen::is_override_film_grain_intensity, screen::is_override_film_grain_intensity_bit),
        volume_knob("motion blur", screen::motion_blur_amount, field_kind::single, 0.0f, 1.0f, screen::is_override_motion_blur_amount, screen::is_override_motion_blur_amount_bit),
        volume_knob("ambient occlusion", screen::ambient_occlusion_intensity, field_kind::single, 0.0f, 1.0f, screen::is_override_ambient_occlusion_intensity, screen::is_override_ambient_occlusion_intensity_bit),
        volume_knob("global illumination", screen::dynamic_global_illumination_method, field_kind::byte, 0.0f, 2.0f, screen::is_override_dynamic_global_illumination_method, screen::is_override_dynamic_global_illumination_method_bit),
    };

    inline constexpr field level_fog_fields[] = {
        { "density", off::ufog_component::fog_density, field_kind::single, 0.0f, 1.0f },
        { "height falloff", off::ufog_component::fog_height_falloff, field_kind::single, 0.0f, 2.0f },
        { "max opacity", off::ufog_component::fog_max_opacity, field_kind::single, 0.0f, 1.0f },
        { "start distance", off::ufog_component::start_distance, field_kind::single, 0.0f, 10000.0f },
        { "end distance", off::ufog_component::end_distance, field_kind::single, 0.0f, 100000.0f },
        { "cutoff distance", off::ufog_component::fog_cutoff_distance, field_kind::single, 0.0f, 100000.0f },
        { "directional exponent", off::ufog_component::directional_inscattering_exponent, field_kind::single, 2.0f, 64.0f },
        { "directional start", off::ufog_component::directional_inscattering_start_distance, field_kind::single, 0.0f, 10000.0f },
        { "volumetric fog", off::ufog_component::is_enable_volumetric_fog, field_kind::flag },
        { "volumetric scattering", off::ufog_component::volumetric_fog_scattering_distribution, field_kind::single, -0.9f, 0.9f },
        { "volumetric extinction", off::ufog_component::volumetric_fog_extinction_scale, field_kind::single, 0.0f, 10.0f },
        { "volumetric distance", off::ufog_component::volumetric_fog_distance, field_kind::single, 0.0f, 20000.0f },
        { "volumetric start", off::ufog_component::volumetric_fog_start_distance, field_kind::single, 0.0f, 20000.0f },
        { "render in main pass", off::ufog_component::is_render_in_main_pass, field_kind::bit, 0.0f, 1.0f, off::ufog_component::is_render_in_main_pass_bit },
    };

    inline constexpr field sky_light_fields[] = {
        { "intensity", off::ulight_base::intensity, field_kind::single, 0.0f, 20.0f },
        { "indirect intensity", off::ulight_base::indirect_lighting_intensity, field_kind::single, 0.0f, 10.0f },
        { "volumetric scattering", off::ulight_base::volumetric_scattering_intensity, field_kind::single, 0.0f, 10.0f },
        { "affects world", off::ulight_base::is_affects_world, field_kind::bit, 0.0f, 1.0f, off::ulight_base::is_affects_world_bit },
        { "cast shadows", off::ulight_base::cast_shadows, field_kind::bit, 0.0f, 1.0f, off::ulight_base::cast_shadows_bit },
        { "real time capture", off::usky_light_component::is_real_time_capture, field_kind::flag },
        { "lower hemisphere black", off::usky_light_component::is_lower_hemisphere_is_black, field_kind::flag },
        { "min occlusion", off::usky_light_component::min_occlusion, field_kind::single, 0.0f, 1.0f },
        { "occlusion exponent", off::usky_light_component::occlusion_exponent, field_kind::single, 0.1f, 4.0f },
        { "occlusion max distance", off::usky_light_component::occlusion_max_distance, field_kind::single, 0.0f, 20000.0f },
        { "contrast", off::usky_light_component::contrast, field_kind::single, 0.0f, 4.0f },
        { "sky distance", off::usky_light_component::sky_distance_threshold, field_kind::single, 0.0f, 500000.0f },
        { "cloud occlusion", off::usky_light_component::is_cloud_ambient_occlusion, field_kind::bit, 0.0f, 1.0f, off::usky_light_component::is_cloud_ambient_occlusion_bit },
        { "cloud occlusion strength", off::usky_light_component::cloud_ambient_occlusion_strength, field_kind::single, 0.0f, 4.0f },
    };

    inline constexpr field sun_light_fields[] = {
        { "intensity", off::ulight_base::intensity, field_kind::single, 0.0f, 200.0f },
        { "indirect intensity", off::ulight_base::indirect_lighting_intensity, field_kind::single, 0.0f, 10.0f },
        { "volumetric scattering", off::ulight_base::volumetric_scattering_intensity, field_kind::single, 0.0f, 10.0f },
        { "affects world", off::ulight_base::is_affects_world, field_kind::bit, 0.0f, 1.0f, off::ulight_base::is_affects_world_bit },
        { "cast shadows", off::ulight_base::cast_shadows, field_kind::bit, 0.0f, 1.0f, off::ulight_base::cast_shadows_bit },
        { "cast dynamic shadows", off::ulight_base::cast_dynamic_shadows, field_kind::bit, 0.0f, 1.0f, off::ulight_base::cast_dynamic_shadows_bit },
        { "temperature", off::ulight_component::temperature, field_kind::single, 1000.0f, 12000.0f },
        { "use temperature", off::ulight_component::is_use_temperature, field_kind::bit, 0.0f, 1.0f, off::ulight_component::is_use_temperature_bit },
        { "specular scale", off::ulight_component::specular_scale, field_kind::single, 0.0f, 4.0f },
        { "diffuse scale", off::ulight_component::diffuse_scale, field_kind::single, 0.0f, 4.0f },
        { "shadow bias", off::ulight_component::shadow_bias, field_kind::single, 0.0f, 2.0f },
        { "light shaft bloom", off::ulight_component::is_enable_light_shaft_bloom, field_kind::bit, 0.0f, 1.0f, off::ulight_component::is_enable_light_shaft_bloom_bit },
        { "bloom scale", off::ulight_component::bloom_scale, field_kind::single, 0.0f, 4.0f },
        { "shadow distance", off::udirectional_light::dynamic_shadow_distance_movable_light, field_kind::single, 0.0f, 50000.0f },
        { "shadow cascades", off::udirectional_light::dynamic_shadow_cascades, field_kind::whole, 0.0f, 8.0f },
        { "cascade exponent", off::udirectional_light::cascade_distribution_exponent, field_kind::single, 1.0f, 8.0f },
        { "far shadow cascades", off::udirectional_light::far_shadow_cascade_count, field_kind::whole, 0.0f, 8.0f },
        { "far shadow distance", off::udirectional_light::far_shadow_distance, field_kind::single, 0.0f, 100000.0f },
        { "source angle", off::udirectional_light::light_source_angle, field_kind::single, 0.0f, 10.0f },
        { "light shaft occlusion", off::udirectional_light::is_enable_light_shaft_occlusion, field_kind::bit, 0.0f, 1.0f, off::udirectional_light::is_enable_light_shaft_occlusion_bit },
        { "occlusion darkness", off::udirectional_light::occlusion_mask_darkness, field_kind::single, 0.0f, 1.0f },
        { "shadows on clouds", off::udirectional_light::is_cast_shadows_on_clouds, field_kind::bit, 0.0f, 1.0f, off::udirectional_light::is_cast_shadows_on_clouds_bit },
        { "cloud shadow strength", off::udirectional_light::cloud_shadow_strength, field_kind::single, 0.0f, 4.0f },
    };

    inline constexpr field sky_atmosphere_fields[] = {
        { "atmosphere height", off::usky_atmosphere_component::atmosphere_height, field_kind::single, 1.0f, 200.0f },
        { "ground radius", off::usky_atmosphere_component::bottom_radius, field_kind::single, 1.0f, 10000.0f },
        { "multi scattering", off::usky_atmosphere_component::multi_scattering_factor, field_kind::single, 0.0f, 2.0f },
        { "trace samples", off::usky_atmosphere_component::trace_sample_count_scale, field_kind::single, 0.25f, 8.0f },
        { "rayleigh scale", off::usky_atmosphere_component::rayleigh_scattering_scale, field_kind::single, 0.0f, 2.0f },
        { "rayleigh falloff", off::usky_atmosphere_component::rayleigh_exponential_distribution, field_kind::single, 0.0f, 64.0f },
        { "mie scattering scale", off::usky_atmosphere_component::mie_scattering_scale, field_kind::single, 0.0f, 5.0f },
        { "mie absorption scale", off::usky_atmosphere_component::mie_absorption_scale, field_kind::single, 0.0f, 5.0f },
        { "mie anisotropy", off::usky_atmosphere_component::mie_anisotropy, field_kind::single, 0.0f, 1.0f },
        { "mie falloff", off::usky_atmosphere_component::mie_exponential_distribution, field_kind::single, 0.0f, 64.0f },
        { "other absorption scale", off::usky_atmosphere_component::other_absorption_scale, field_kind::single, 0.0f, 5.0f },
        { "aerial view distance", off::usky_atmosphere_component::aerial_pespective_view_distance_scale, field_kind::single, 0.0f, 10.0f },
        { "aerial start depth", off::usky_atmosphere_component::aerial_perspective_start_depth, field_kind::single, 0.0f, 100.0f },
        { "height fog contribution", off::usky_atmosphere_component::height_fog_contribution, field_kind::single, 0.0f, 1.0f },
        { "min sun elevation", off::usky_atmosphere_component::transmittance_min_light_elevation_angle, field_kind::single, -90.0f, 90.0f },
        { "render in main pass", off::usky_atmosphere_component::is_render_in_main_pass, field_kind::bit, 0.0f, 1.0f, off::usky_atmosphere_component::is_render_in_main_pass_bit },
    };

    inline constexpr field volumetric_cloud_fields[] = {
        { "layer altitude", off::ucloud_component::layer_bottom_altitude, field_kind::single, 0.0f, 20.0f },
        { "layer height", off::ucloud_component::layer_height, field_kind::single, 0.1f, 20.0f },
        { "tracing start distance", off::ucloud_component::tracing_start_distance_from_camera, field_kind::single, 0.0f, 50.0f },
        { "tracing start max", off::ucloud_component::tracing_start_max_distance, field_kind::single, 0.0f, 500.0f },
        { "tracing max distance", off::ucloud_component::tracing_max_distance, field_kind::single, 0.0f, 500.0f },
        { "planet radius", off::ucloud_component::planet_radius, field_kind::single, 100.0f, 10000.0f },
        { "sky light occlusion", off::ucloud_component::sky_light_cloud_bottom_occlusion, field_kind::single, 0.0f, 1.0f },
        { "view samples", off::ucloud_component::view_sample_count_scale, field_kind::single, 0.0f, 8.0f },
        { "shadow samples", off::ucloud_component::shadow_view_sample_count_scale, field_kind::single, 0.0f, 8.0f },
        { "shadow tracing distance", off::ucloud_component::shadow_tracing_distance, field_kind::single, 0.1f, 50.0f },
        { "transmittance cutoff", off::ucloud_component::stop_tracing_transmittance_threshold, field_kind::single, 0.0f, 1.0f },
        { "render in main pass", off::ucloud_component::is_render_in_main_pass, field_kind::bit, 0.0f, 1.0f, off::ucloud_component::is_render_in_main_pass_bit },
    };

    inline constexpr field local_fog_fields[] = {
        { "radial extinction", off::ulocal_fog_component::radial_fog_extinction, field_kind::single, 0.0f, 10.0f },
        { "height extinction", off::ulocal_fog_component::height_fog_extinction, field_kind::single, 0.0f, 10.0f },
        { "height falloff", off::ulocal_fog_component::height_fog_falloff, field_kind::single, 0.0f, 20.0f },
        { "height offset", off::ulocal_fog_component::height_fog_offset, field_kind::single, -10.0f, 10.0f },
        { "phase", off::ulocal_fog_component::fog_phase_g, field_kind::single, -0.9f, 0.9f },
        { "start distance", off::ulocal_fog_component::fog_start_distance, field_kind::single, 0.0f, 10000.0f },
        { "sort priority", off::ulocal_fog_component::fog_sort_priority, field_kind::whole, -10.0f, 10.0f },
    };

    inline constexpr field wind_source_fields[] = {
        { "strength", off::uwind_component::strength, field_kind::single, 0.0f, 10.0f },
        { "speed", off::uwind_component::speed, field_kind::single, 0.0f, 50.0f },
        { "gust floor", off::uwind_component::min_gust_amount, field_kind::single, 0.0f, 10.0f },
        { "gust ceiling", off::uwind_component::max_gust_amount, field_kind::single, 0.0f, 10.0f },
        { "radius", off::uwind_component::radius, field_kind::single, 0.0f, 10000.0f },
        { "point wind", off::uwind_component::is_point_wind, field_kind::bit, 0.0f, 1.0f, off::uwind_component::is_point_wind_bit },
    };

    inline field_state world_settings_state[std::size(world_settings_fields)];
    inline field_state screen_post_state[std::size(screen_post_fields)];
    inline field_state post_volume_state[std::size(post_volume_fields)];
    inline field_state level_fog_state[std::size(level_fog_fields)];
    inline field_state sky_light_state[std::size(sky_light_fields)];
    inline field_state sun_light_state[std::size(sun_light_fields)];
    inline field_state sky_atmosphere_state[std::size(sky_atmosphere_fields)];
    inline field_state volumetric_cloud_state[std::size(volumetric_cloud_fields)];
    inline field_state local_fog_state[std::size(local_fog_fields)];
    inline field_state wind_source_state[std::size(wind_source_fields)];

    inline field_board world_settings_board{ "gravity and time", board_target::world_settings, world_settings_fields, static_cast<int>(std::size(world_settings_fields)), world_settings_state };
    inline field_board screen_post_board{ "your screen's post process", board_target::screen_post, screen_post_fields, static_cast<int>(std::size(screen_post_fields)), screen_post_state };
    inline field_board post_volume_board{ "post process volumes", board_target::post_volume, post_volume_fields, static_cast<int>(std::size(post_volume_fields)), post_volume_state };
    inline field_board level_fog_board{ "height fog", board_target::level_fog, level_fog_fields, static_cast<int>(std::size(level_fog_fields)), level_fog_state };
    inline field_board sky_light_board{ "sky light", board_target::sky_light, sky_light_fields, static_cast<int>(std::size(sky_light_fields)), sky_light_state };
    inline field_board sun_light_board{ "sun", board_target::sun_light, sun_light_fields, static_cast<int>(std::size(sun_light_fields)), sun_light_state };
    inline field_board sky_atmosphere_board{ "sky atmosphere", board_target::sky_atmosphere, sky_atmosphere_fields, static_cast<int>(std::size(sky_atmosphere_fields)), sky_atmosphere_state };
    inline field_board volumetric_cloud_board{ "volumetric clouds", board_target::volumetric_clouds, volumetric_cloud_fields, static_cast<int>(std::size(volumetric_cloud_fields)), volumetric_cloud_state };
    inline field_board local_fog_board{ "local fog volumes", board_target::local_fog, local_fog_fields, static_cast<int>(std::size(local_fog_fields)), local_fog_state };
    inline field_board wind_source_board{ "wind", board_target::wind_source, wind_source_fields, static_cast<int>(std::size(wind_source_fields)), wind_source_state };

    inline field_board* const world_boards[] = {
        &world_settings_board, &screen_post_board, &post_volume_board, &level_fog_board, &sky_light_board,
        &sun_light_board, &sky_atmosphere_board, &volumetric_cloud_board, &local_fog_board, &wind_source_board,
    };

    inline field_board* const bot_brain_boards[] = { &bot_targeting, &bot_chasing, &bot_memory, &bot_alerts, &bot_hit_reaction, &bot_reloading, &bot_strafing, &bot_vehicles, &bot_engaging, &bot_roles, &bot_bags, &bot_cover, &bot_peeking, &bot_retreat, &bot_pushing, &bot_coordinator, &bot_conquest, &bot_lanes, &bot_callouts, &bot_personalities, &bot_detection, &bot_flinch_voice, &bot_unstuck, &bot_defence, &bot_advantage, &bot_weapons, &bot_sight, &bot_spawns, &bot_glass, &bot_snd_plans, &bot_snd_staging, &bot_snd_roles, &bot_telemetry };
    inline field_board* const streak_rule_boards[] = { &streak_rules, &streak_bots, &streak_call, &streak_cost, &streak_homies, &streak_bomber, &streak_car, &streak_gun, &streak_sound };

    inline field_board* const every[] = {
        &match_rules, &match_clock, &game_mode_rules, &lobby_presets,
        &bot_targeting, &bot_chasing, &bot_memory, &bot_alerts, &bot_hit_reaction, &bot_reloading,
        &bot_strafing, &bot_vehicles, &bot_engaging, &bot_roles, &bot_bags, &bot_cover,
        &bot_peeking, &bot_retreat, &bot_pushing, &bot_coordinator, &bot_conquest, &bot_lanes,
        &bot_callouts, &bot_personalities, &bot_detection, &bot_flinch_voice, &bot_unstuck, &bot_defence,
        &bot_advantage, &bot_weapons, &bot_sight, &bot_spawns, &bot_glass, &bot_snd_plans,
        &bot_snd_staging, &bot_snd_roles, &bot_telemetry, &bot_weapon_profile, &chosen_bot, &streak_rules,
        &streak_bots, &streak_call, &streak_cost, &streak_homies, &streak_bomber, &streak_car,
        &streak_gun, &streak_sound, &own_streak, &old_streak, &drive_by_car,
        &held_weapon, &held_weapon_data, &held_magazine, &held_optic, &own_vitals, &picked_vitals, &own_body, &own_interaction, &own_lethal, &own_loadout, &frag_defaults, &claymore_defaults, &pickup_defaults, &medkit_defaults, &damage_type_board,
        &picked_capture_point, &picked_snd_site, &picked_rush_site, &snd_bomb_board, &conquest_state_board, &rush_state_board, &snd_state_board, &ffa_state_board, &picked_spawn_board, &own_spectator_board, &host_migration_board,
        &online_progress_board, &own_progression_board, &save_level_board, &save_game_board, &save_streaks_board, &save_menu_board,
        &cine_capture_board, &replay_options_board, &voice_options_board, &voice_save_board, &audio_output_board, &voice_cues_board, &own_voice_board, &controller_options_board, &input_general_board, &input_aim_assist_board, &player_input_board, &third_person_board,
        &matchmaking_board,
        &world_settings_board, &screen_post_board, &post_volume_board, &level_fog_board, &sky_light_board, &sun_light_board, &sky_atmosphere_board, &volumetric_cloud_board, &local_fog_board, &wind_source_board,
    };

}
