#include "overlay.hh"
#include <imgui/imgui.h>
#include <iterator>
#include <features/data/tune.hh>
#include <features/features.hh>
#include <client/util/brand.hh>
#include <client/render/fonts/fonts.hh>
#include <client/render/ui/tabs/panels.hh>

namespace render::overlay::detail {

    void draw_visuals_options() {
        features::visuals_options& options = features::visuals_setup;

        if (!ImGui::CollapsingHeader("visuals", ImGuiTreeNodeFlags_DefaultOpen)) return;

        ImGui::Checkbox("enabled", &options.is_enabled);
        ImGui::Checkbox("box", &options.is_box);
        ImGui::Checkbox("name", &options.is_name);
        ImGui::Checkbox("health", &options.is_health);
        ImGui::Checkbox("distance", &options.is_distance);
        ImGui::Checkbox("snapline", &options.is_snapline);
        ImGui::Checkbox("head dot", &options.is_head_dot);
        ImGui::Checkbox("enemies only", &options.is_enemy_only);
        ImGui::SliderFloat("range", &options.max_distance, 10.0f, 500.0f, "%.0f m");
    }

    void draw_progression_options() {
        features::progression_options& options = features::progression_setup;

        if (!ImGui::CollapsingHeader("progression")) return;

        ImGui::SliderInt("level", &options.level, 1, 500);
        if (ImGui::Button("apply level")) features::progression.set_level(options.level);
        ImGui::SameLine();
        if (ImGui::Button("max")) features::progression.max_level();
        ImGui::SameLine();
        if (ImGui::Button("reset")) features::progression.reset_level();

        ImGui::SliderInt("experience", &options.experience, 100, 1000000);
        if (ImGui::Button("grant experience")) features::progression.grant_experience(options.experience);
        ImGui::SameLine();
        if (ImGui::Button("fill level")) features::progression.fill_level();

        ImGui::Separator();

        if (ImGui::Button("apply unlocks")) features::progression.apply_unlocks();
        ImGui::SameLine();
        if (ImGui::Button("save")) features::progression.save();
        ImGui::SameLine();
        if (ImGui::Button("load")) features::progression.load();

        ImGui::Separator();

        ImGui::InputText("stat key", options.stat_key, sizeof(options.stat_key));
        ImGui::SliderInt("stat value", &options.stat_value, 1, 100000);
        if (ImGui::Button("raise stat to")) features::progression.set_stat(options.stat_key, options.stat_value);
        ImGui::SameLine();
        if (ImGui::Button("add stat")) features::progression.add_stat(options.stat_key, options.stat_value);

        if (ImGui::Button("raise every stat")) features::progression.raise_every_stat(options.stat_value);

        ImGui::Separator();

        if (ImGui::Button("max everything")) features::progression.max_everything();

        ImGui::Separator();

        if (ImGui::Button("unlock every weapon")) features::progression.unlock_every_weapon_stat(options.stat_value);

        features::enforcement_options& keep = features::enforcement_setup;
        ImGui::Checkbox("keep level applied", &keep.is_enabled);
        ImGui::SliderInt("hold at", &keep.level, 1, 55);
    }

    void draw_weapon_options() {
        features::weapon_options& options = features::weapon_setup;

        if (!ImGui::CollapsingHeader("weapons")) return;

        ImGui::Checkbox("fire rate", &options.is_fire_rate);
        ImGui::SliderFloat("##fire rate", &options.fire_rate, 0.25f, 4.0f, "%.2fx");

        ImGui::Checkbox("rapid fire", &options.is_rapid_fire);

        ImGui::Checkbox("auto fire", &options.is_auto_fire);
        ImGui::SliderFloat("shots a second", &options.auto_fire_rate, 1.0f, 30.0f, "%.0f");
        ImGui::SliderFloat("auto fire spread", &options.auto_fire_spread, 0.0f, 5.0f, "%.2f");

        ImGui::Checkbox("recoil control", &options.is_recoil);
        ImGui::SliderFloat("##recoil", &options.recoil, 0.0f, 1.0f, "%.2fx kept");

        ImGui::Separator();

        ImGui::Checkbox("damage", &options.is_damage);
        ImGui::SliderFloat("body", &options.damage, 0.5f, 10.0f, "%.2fx");
        ImGui::SliderFloat("headshot", &options.headshot, 0.5f, 10.0f, "%.2fx");
        ImGui::Checkbox("no damage falloff", &options.is_no_falloff);

        ImGui::Checkbox("bot damage", &options.is_bot_damage);
        ImGui::SliderFloat("##bot damage", &options.bot_damage, 0.0f, 2.0f, "%.2fx");

        ImGui::Separator();

        ImGui::Checkbox("bullet speed", &options.is_bullet_speed);
        ImGui::SliderFloat("##bullet speed", &options.bullet_speed, 0.5f, 10.0f, "%.2fx");
        ImGui::Checkbox("no bullet drop", &options.is_no_drop);

        const char* hit_reg_modes[] = { "game default", "client side", "server side" };
        ImGui::Combo("hit reg", &options.hit_reg, hit_reg_modes, IM_ARRAYSIZE(hit_reg_modes));

        const char* bullet_modes[] = { "game default", "hitscan", "simulated" };
        ImGui::Combo("bullets", &options.hit_scan, bullet_modes, IM_ARRAYSIZE(bullet_modes));

        ImGui::Checkbox("shotgun pellets", &options.is_pellets);
        ImGui::SliderInt("##pellets", &options.pellets, 1, 32);

        ImGui::Separator();

        ImGui::Checkbox("infinite ammo", &options.is_infinite_ammo);
        ImGui::Checkbox("magazine size", &options.is_mag_size);
        ImGui::SliderInt("##magazine", &options.mag_size, 1, 250);

        ImGui::Separator();

        ImGui::Checkbox("recolor", &options.is_recolor);

        ImGui::Checkbox("rgb", &options.is_rgb);

        ImGui::BeginDisabled(!options.is_rgb);
        ImGui::SliderFloat("##rgb speed", &options.rgb_speed, 0.05f, 2.0f, "%.2f turns/s");
        ImGui::Checkbox("opposite second color", &options.is_rgb_split);
        ImGui::EndDisabled();

        ImGui::BeginDisabled(options.is_rgb);
        ImGui::ColorEdit4("color a", options.color_a, ImGuiColorEditFlags_NoInputs);
        ImGui::SameLine();
        ImGui::ColorEdit4("color b", options.color_b, ImGuiColorEditFlags_NoInputs);
        ImGui::EndDisabled();

        ImGui::Separator();

        features::throwable_options& thrown = features::throwable_setup;
        ImGui::Checkbox("throwable tuning", &thrown.is_enabled);
        ImGui::SliderFloat("throw speed", &thrown.speed, 0.25f, 4.0f, "%.2fx");
        ImGui::SliderFloat("gravity", &thrown.gravity, 0.0f, 2.0f, "%.2fx");
        ImGui::SliderFloat("bounce", &thrown.bounce, 0.0f, 3.0f, "%.2fx");

        ImGui::Separator();

        if (ImGui::Button("restore weapons")) features::weapons.restore();
    }

    void draw_movement_options() {
        features::movement_options& options = features::movement_setup;

        if (!ImGui::CollapsingHeader("movement")) return;

        ImGui::Checkbox("speed", &options.is_speed);
        ImGui::SliderFloat("##speed", &options.speed, 0.5f, 5.0f, "%.2fx");

        ImGui::Checkbox("acceleration", &options.is_acceleration);
        ImGui::SliderFloat("##acceleration", &options.acceleration, 1.0f, 20.0f, "%.2fx");

        ImGui::Checkbox("flat ads speed", &options.is_flat_ads_speed);

        ImGui::Checkbox("endless sprint", &options.is_endless_sprint);

        ImGui::Separator();

        ImGui::Checkbox("jump", &options.is_jump);
        ImGui::SliderFloat("##jump", &options.jump, 0.5f, 4.0f, "%.2fx");
        ImGui::SliderInt("jumps", &options.jumps, 1, 10);

        ImGui::Checkbox("gravity", &options.is_gravity);
        ImGui::SliderFloat("##gravity", &options.gravity, 0.0f, 2.0f, "%.2fx");

        ImGui::Checkbox("air control", &options.is_air_control);
        ImGui::SliderFloat("##air control", &options.air_control, 0.0f, 1.0f, "%.2f");

        ImGui::Checkbox("no fall damage", &options.is_no_fall_damage);

        ImGui::Separator();

        ImGui::Checkbox("step height", &options.is_step_height);
        ImGui::SliderFloat("##step height", &options.step_height, 10.0f, 300.0f, "%.0f");

        ImGui::Checkbox("walk up steep slopes", &options.is_steep_slopes);
        ImGui::Checkbox("never walk off ledges", &options.is_edge_guard);

        ImGui::Separator();

        ImGui::Checkbox("fly", &options.is_fly);
        ImGui::SliderFloat("##fly speed", &options.fly_speed, 0.5f, 10.0f, "%.2fx");

        ImGui::Checkbox("ignore position correction", &options.is_no_correction);

        ImGui::Checkbox("spin", &options.is_spin);
        ImGui::SliderFloat("degrees a second", &options.spin_speed, -1440.0f, 1440.0f, "%.0f");

        ImGui::Separator();

        if (ImGui::Button("restore movement")) features::movement.restore();
    }

    void draw_view_options() {
        features::view_options& options = features::view_setup;

        if (!ImGui::CollapsingHeader("view")) return;

        ImGui::Checkbox("fov", &options.is_fov);
        ImGui::SliderFloat("##fov", &options.fov, 60.0f, 160.0f, "%.0f deg");

        ImGui::Checkbox("fixed ads fov", &options.is_fixed_ads_fov);
        ImGui::SliderFloat("##ads fov", &options.ads_fov, 20.0f, 160.0f, "%.0f deg");

        ImGui::Separator();

        ImGui::Checkbox("no sway", &options.is_no_sway);

        ImGui::Checkbox("hold breath", &options.is_hold_breath);
        ImGui::SliderFloat("##hold breath", &options.hold_breath, 0.0f, 1.0f, "%.2f");

        ImGui::Checkbox("no visual recoil", &options.is_no_recoil);

        ImGui::Checkbox("no spread", &options.is_no_spread);

        ImGui::Separator();

        ImGui::Checkbox("clean screen", &options.is_clean_screen);
        ImGui::SliderFloat("##saturation", &options.saturation, 0.0f, 2.0f, "%.2f");

        ImGui::Checkbox("no run shake", &options.is_no_run_shake);

        ImGui::Separator();

        ImGui::Checkbox("third person", &options.is_third_person);
        ImGui::SliderFloat("arm length", &options.arm_length, 0.0f, 600.0f, "%.0f");
        ImGui::SliderFloat("side shift", &options.side_shift, -200.0f, 200.0f, "%.0f");
        ImGui::SliderFloat("pivot rise", &options.pivot_rise, -100.0f, 200.0f, "%.0f");

        ImGui::Separator();

        ImGui::Checkbox("lean", &options.is_lean);
        ImGui::SliderFloat("##lean", &options.lean, -90.0f, 90.0f, "%.0f");

        ImGui::Separator();

        if (ImGui::Button("restore view")) features::view.restore();
    }

    void draw_dev_options() {
        features::dev_options& options = features::dev_setup;

        if (!ImGui::CollapsingHeader("dev mode")) return;

        ImGui::Checkbox("funny mode", &options.is_enabled);

        ImGui::Checkbox("hold", &options.is_hold);

        ImGui::Separator();

        ImGui::Checkbox("game esp", &options.is_esp);
        ImGui::Checkbox("esp in overlay window", &options.is_esp_overlay);
        ImGui::ColorEdit4("dot color", options.esp_color, ImGuiColorEditFlags_NoInputs);
        ImGui::SliderFloat("dot radius", &options.esp_radius, 1.0f, 30.0f, "%.1f");
        ImGui::SliderFloat("above head", &options.esp_height, 0.0f, 150.0f, "%.0f");
        ImGui::SliderFloat("esp distance", &options.esp_distance, 10.0f, 500.0f, "%.0f m");

        ImGui::Separator();

        ImGui::Checkbox("override lobby size", &options.is_lobby_size);
        ImGui::BeginDisabled(!options.is_lobby_size);
        ImGui::SliderInt("team size", &options.team_size, 1, 32);
        ImGui::SliderInt("max players", &options.max_players, 2, 64);
        ImGui::EndDisabled();

        ImGui::Separator();

        if (ImGui::Button("read dev")) features::arena.load_dev();
        ImGui::SameLine();
        if (ImGui::Button("apply dev")) features::arena.apply_dev();
    }

    void draw_bot_options() {
        features::bot_options& options = features::bot_setup;

        if (!ImGui::CollapsingHeader("bot skill")) return;

        ImGui::SliderInt("tier", &options.tier_slot, 0, 7);
        if (ImGui::Button("read tier")) features::arena.load_bots();
        ImGui::SameLine();
        if (ImGui::Button("apply tier")) features::arena.apply_bots();
        ImGui::SameLine();
        ImGui::Checkbox("hold", &options.is_hold);

        ImGui::Separator();
        ImGui::TextDisabled("aim");

        ImGui::SliderFloat("turn rate", &options.aim_turn_rate, 0.0f, 50.0f, "%.1f");
        ImGui::SliderFloat("reaction delay", &options.aim_reaction_delay, 0.0f, 2.0f, "%.2f s");
        ImGui::SliderFloat("reaction time", &options.reaction_time, 0.0f, 2.0f, "%.2f s");
        ImGui::SliderFloat("error initial", &options.aim_error_initial, 0.0f, 20.0f, "%.2f");
        ImGui::SliderFloat("error settled", &options.aim_error_settled, 0.0f, 20.0f, "%.2f");
        ImGui::SliderFloat("settle time", &options.aim_settle_time, 0.0f, 5.0f, "%.2f s");
        ImGui::SliderFloat("fire angle", &options.aim_fire_angle, 0.0f, 90.0f, "%.1f deg");
        ImGui::SliderFloat("latency", &options.aim_latency, 0.0f, 1.0f, "%.3f s");
        ImGui::SliderFloat("predict skill", &options.aim_predict_skill, 0.0f, 1.0f, "%.2f");

        ImGui::Separator();
        ImGui::TextDisabled("fire");

        ImGui::SliderFloat("spread", &options.spread_multiplier, 0.0f, 5.0f, "%.2fx");
        ImGui::SliderFloat("moving spread", &options.moving_spread_scale, 0.0f, 5.0f, "%.2fx");
        ImGui::SliderFloat("flinch spread", &options.flinch_spread, 0.0f, 10.0f, "%.2f");
        ImGui::SliderFloat("burst duration", &options.burst_duration, 0.0f, 5.0f, "%.2f s");
        ImGui::SliderFloat("burst rest", &options.burst_rest, 0.0f, 5.0f, "%.2f s");

        ImGui::Separator();
        ImGui::TextDisabled("engagement");

        ImGui::SliderFloat("engage range", &options.engage_range, 0.0f, 10000.0f, "%.0f");
        ImGui::SliderFloat("max fire range", &options.max_fire_range, 0.0f, 10000.0f, "%.0f");
        ImGui::SliderFloat("detect time", &options.detect_time, 0.0f, 5.0f, "%.2f s");
        ImGui::SliderFloat("pursuit", &options.pursuit_scale, 0.0f, 5.0f, "%.2fx");
        ImGui::SliderInt("bots per target", &options.max_bots_per_target, 0, 16);

        ImGui::Separator();
        ImGui::TextDisabled("brain");

        ImGui::SliderFloat("interp speed", &options.aim_interp_speed, 0.0f, 50.0f, "%.1f");
        ImGui::SliderFloat("error interval", &options.aim_error_interval, 0.0f, 5.0f, "%.2f s");
        ImGui::SliderFloat("target z offset", &options.aim_target_z_offset, -100.0f, 100.0f, "%.1f");
        ImGui::SliderFloat("hearing radius", &options.hearing_radius, 0.0f, 10000.0f, "%.0f");
        ImGui::SliderFloat("memory", &options.memory_seconds, 0.0f, 60.0f, "%.1f s");
        ImGui::Checkbox("aim at perceived position", &options.is_perceived_aim);
        ImGui::Checkbox("movement spread", &options.is_movement_spread);
    }

    void draw_streak_options() {
        features::streak_options& options = features::streak_setup;

        if (!ImGui::CollapsingHeader("killstreaks")) return;

        const char* streaks[] = { "snitch", "homies", "suicide bomber", "drive by" };
        ImGui::Combo("streak", &options.streak_slot, streaks, IM_ARRAYSIZE(streaks));

        if (ImGui::Button("activate")) features::arena.fire_streak();

        ImGui::Separator();

        ImGui::SliderInt("loadout slot", &options.loadout_slot, 0, 5);
        if (ImGui::Button("activate slot")) features::arena.fire_streak_slot();

        ImGui::Separator();

        ImGui::Checkbox("place ahead of the view", &options.is_place_ahead);
        ImGui::BeginDisabled(!options.is_place_ahead);
        ImGui::SliderFloat("distance", &options.place_distance, 1.0f, 100.0f, "%.0f m");
        ImGui::EndDisabled();
        if (ImGui::Button("place")) features::arena.place_streak();

        ImGui::Separator();

        if (ImGui::Button("restore arena")) features::arena.restore();
    }

    bool begin_tab(const char* label) {
        ImGui::PushFont(fonts::medium(), 0.0f);
        const bool is_open = ImGui::BeginTabItem(label);
        ImGui::PopFont();

        return is_open;
    }

    void draw_debug_options() {
        if (!ImGui::CollapsingHeader("debug")) return;

        if (ImGui::Button("report weapon")) features::weapons.report();
        ImGui::SameLine();
        if (ImGui::Button("report movement")) features::movement.report();
        ImGui::SameLine();
        if (ImGui::Button("report view")) features::view.report();

        if (ImGui::Button("probe fov")) features::view.probe();
        ImGui::SameLine();
        if (ImGui::Button("report arena")) features::arena.report();
        ImGui::SameLine();
        if (ImGui::Button("report match")) features::host.report();

        if (ImGui::Button("report unlocks")) features::progression.report_unlocks();
        ImGui::SameLine();
        if (ImGui::Button("list stats")) features::progression.list_stats();
        ImGui::SameLine();
        if (ImGui::Button("list weapons")) features::progression.list_weapons();

        if (ImGui::Button("dump match report")) features::network.dump_report();
    }

    void draw_guard_options() {
        features::guard_options& options = features::guard_setup;

        if (!ImGui::CollapsingHeader("guard tolerances")) return;

        ImGui::Checkbox("apply while hosting", &options.is_enabled);

        ImGui::Separator();

        ImGui::DragFloat("trace offset", &options.max_trace_offset, 1.0f, 0.0f, 100000.0f, "%.0f cm");
        ImGui::DragFloat("hit leeway", &options.hit_leeway, 1.0f, 0.0f, 100000.0f, "%.0f cm");
        ImGui::DragFloat("head zone", &options.head_zone, 0.5f, 0.0f, 10000.0f, "%.1f cm");
        ImGui::DragFloat("sight leeway", &options.sight_leeway, 1.0f, 0.0f, 100000.0f, "%.0f cm");

        ImGui::Separator();

        ImGui::DragFloat("refuse deg", &options.aim_refuse, 0.1f, 0.0f, 180.0f, "%.1f deg");
        ImGui::DragFloat("score deg", &options.aim_score, 0.1f, 0.0f, 180.0f, "%.1f deg");
        ImGui::DragFloat("suspect deg", &options.aim_suspect, 0.1f, 0.0f, 180.0f, "%.1f deg");
        ImGui::DragFloat("recheck", &options.aim_recheck, 0.05f, 0.0f, 600.0f, "%.2f s");
        ImGui::DragFloat("snap deg", &options.snap_degrees, 0.1f, 0.0f, 180.0f, "%.1f deg");
        ImGui::DragFloat("snap window", &options.snap_window, 0.05f, 0.0f, 600.0f, "%.2f s");

        ImGui::Separator();

        ImGui::DragFloat("hits per pellet", &options.hits_per_pellet, 0.1f, 0.0f, 1000.0f, "%.1f");
        ImGui::DragFloat("fire rate tol", &options.fire_rate_tolerance, 0.01f, 0.0f, 100.0f, "%.2f");
        ImGui::DragFloat("burst shots", &options.burst_shots, 1.0f, 0.0f, 1000.0f, "%.0f");
        ImGui::DragFloat("burst seconds", &options.burst_seconds, 0.05f, 0.0f, 600.0f, "%.2f s");

        ImGui::Separator();

        ImGui::DragFloat("melee leeway", &options.melee_leeway, 1.0f, 0.0f, 100000.0f, "%.0f cm");
        ImGui::DragFloat("melee interval", &options.melee_interval, 0.05f, 0.0f, 600.0f, "%.2f s");
        ImGui::DragFloat("max rewind", &options.max_rewind, 0.05f, 0.0f, 600.0f, "%.2f s");
        ImGui::DragFloat("rewind slack", &options.rewind_slack, 0.05f, 0.0f, 600.0f, "%.2f s");

        ImGui::Separator();

        ImGui::DragFloat("warn score", &options.warn_score, 1.0f, 0.0f, 1000000.0f, "%.0f");
        ImGui::DragFloat("kick score", &options.kick_score, 1.0f, 0.0f, 1000000.0f, "%.0f");
        ImGui::DragFloat("score decay", &options.score_decay, 0.1f, 0.0f, 100000.0f, "%.1f /s");
        ImGui::DragFloat("violation gap", &options.violation_gap, 0.05f, 0.0f, 600.0f, "%.2f s");
        ImGui::DragFloat("kick delay", &options.kick_delay, 0.05f, 0.0f, 600.0f, "%.2f s");
    }

    void draw_aim_options() {
        features::aim_options& options = features::aim_setup;
        const features::aim_state& status = features::aim_status;

        if (!ImGui::CollapsingHeader("aim")) return;

        if (status.is_open) ImGui::TextColored({ 0.45f, 0.85f, 0.5f, 1.0f }, "open%s", status.has_target ? " - target" : "");
        else if (!status.is_host) ImGui::TextColored({ 0.9f, 0.45f, 0.4f, 1.0f }, "locked - not hosting");
        else ImGui::TextColored({ 0.9f, 0.45f, 0.4f, 1.0f }, "locked - %d other players", status.humans - 1);

        ImGui::Checkbox("server guard off", &options.is_guard_off);

        ImGui::Separator();

        ImGui::Checkbox("aimbot", &options.is_aimbot);

        const char* keys[std::size(features::tune::aim_keys)];
        for (std::size_t i = 0; i < std::size(keys); ++i) keys[i] = features::tune::aim_keys[i].label;
        ImGui::Combo("key", &options.key_slot, keys, static_cast<int>(std::size(keys)));

        ImGui::SliderFloat("fov", &options.fov, 1.0f, 90.0f, "%.0f deg");
        ImGui::SliderFloat("smooth", &options.smooth, 1.0f, 20.0f, "%.1f");
        ImGui::Checkbox("fov circle##aimbot", &options.is_aimbot_circle);
        ImGui::SameLine();
        ImGui::ColorEdit4("##aimbot circle", options.aimbot_circle, ImGuiColorEditFlags_NoInputs);

        ImGui::Separator();

        ImGui::Checkbox("silent aim", &options.is_silent);
        ImGui::SliderFloat("silent fov", &options.silent_fov, 1.0f, 180.0f, "%.0f deg");
        ImGui::Checkbox("fov circle##silent", &options.is_silent_circle);
        ImGui::SameLine();
        ImGui::ColorEdit4("##silent circle", options.silent_circle, ImGuiColorEditFlags_NoInputs);

        ImGui::Separator();

        ImGui::Checkbox("wallbang", &options.is_wallbang);
        ImGui::SliderFloat("wallbang fov", &options.wallbang_fov, 1.0f, 180.0f, "%.0f deg");
        ImGui::SliderFloat("wallbang rate", &options.wallbang_rate, 1.0f, 30.0f, "%.1f /s");
        ImGui::SliderFloat("wallbang push", &options.wallbang_push, 10.0f, 400.0f, "%.0f cm");

        ImGui::Separator();

        ImGui::Checkbox("bullet teleport", &options.is_bullet_tp);
        ImGui::SliderFloat("teleport fov", &options.bullet_tp_fov, 1.0f, 180.0f, "%.0f deg");
        ImGui::Checkbox("force impact", &options.is_bullet_tp_hit);

        ImGui::Separator();

        const char* bones[std::size(features::tune::aim_bones)];
        for (std::size_t i = 0; i < std::size(bones); ++i) bones[i] = features::tune::aim_bones[i].label;
        ImGui::Combo("bone", &options.bone_slot, bones, static_cast<int>(std::size(bones)));

        ImGui::SliderFloat("max distance", &options.max_distance, 10.0f, 500.0f, "%.0f m");
        ImGui::Checkbox("visible only", &options.is_visible_only);
        ImGui::Checkbox("ignore teams", &options.is_ignore_teams);
    }

}

void render::overlay::draw() {
    ImGui::SetNextWindowSize({ 320.0f, 0.0f }, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos({ 40.0f, 40.0f }, ImGuiCond_FirstUseEver);

    ImGui::PushFont(fonts::bold(), 0.0f);
    const bool is_shown = ImGui::Begin(brand::name, nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::PushFont(fonts::regular(), 0.0f);

    if (is_shown && ImGui::BeginTabBar("##tabs")) {
        if (detail::begin_tab("you")) {
            detail::draw_visuals_options();
            detail::draw_view_options();
            detail::draw_movement_options();
            detail::draw_aim_options();
            detail::draw_guard_options();
            ImGui::EndTabItem();
        }

        if (detail::begin_tab("weapons")) {
            detail::draw_weapon_options();
            ImGui::EndTabItem();
        }

        if (detail::begin_tab("kit")) {
            panels::draw_kit_tab();
            ImGui::EndTabItem();
        }

        if (detail::begin_tab("progress")) {
            detail::draw_progression_options();
            panels::draw_career_tab();
            ImGui::EndTabItem();
        }

        if (detail::begin_tab("match")) {
            panels::draw_match_tab();
            ImGui::EndTabItem();
        }

        if (detail::begin_tab("modes")) {
            panels::draw_modes_tab();
            ImGui::EndTabItem();
        }

        if (detail::begin_tab("bots")) {
            detail::draw_bot_options();
            panels::draw_bots_tab();
            ImGui::EndTabItem();
        }

        if (detail::begin_tab("streaks")) {
            detail::draw_streak_options();
            panels::draw_streaks_tab();
            ImGui::EndTabItem();
        }

        if (detail::begin_tab("online")) {
            panels::draw_online_tab();
            ImGui::EndTabItem();
        }

        if (detail::begin_tab("media")) {
            panels::draw_media_tab();
            ImGui::EndTabItem();
        }

        if (detail::begin_tab("world")) {
            panels::draw_world_tab();
            ImGui::EndTabItem();
        }

        if (detail::begin_tab("dev")) {
            detail::draw_dev_options();
            detail::draw_debug_options();
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::PopFont();
    ImGui::End();
    ImGui::PopFont();
}
