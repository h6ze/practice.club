#include <client/render/ui/tabs/panels.hh>
#include <cstdio>
#include <imgui/imgui.h>
#include <features/data/boards.hh>

namespace render::panels::detail {

    constexpr float modes_number_width = 110.0f;

    const char* mode_name(int mode) {
        switch (mode) {
        case 1: return "conquest";
        case 2: return "rush";
        case 3: return "search and destroy";
        case 4: return "free for all";
        case 5: return "team deathmatch";
        }

        return "no mode game state - load into a match";
    }

    void draw_actor(const features::match_snapshot& seen) {
        features::modes_options& options = features::modes_setup;

        ImGui::Checkbox("act as the picked player", &options.is_by_picked);
        if (options.is_by_picked) draw_player_pick(seen);
    }

    void draw_objective_list(const features::modes_snapshot& modes) {
        features::modes_options& options = features::modes_setup;

        if (modes.objectives.empty()) return;

        for (const features::objective_entry& entry : modes.objectives) {
            char label[128];
            std::snprintf(label, sizeof(label), "%s - state %d, team %d, %d##%llx", entry.label.c_str(), entry.state, entry.team, entry.points,
                static_cast<unsigned long long>(entry.id));

            if (ImGui::Selectable(label, options.objective == entry.id)) options.objective = entry.id;
        }
    }

    int picked_kind(const features::modes_snapshot& modes) {
        for (const features::objective_entry& entry : modes.objectives)
            if (entry.id == features::modes_setup.objective) return entry.kind;

        return -1;
    }

    void draw_capture_actions() {
        features::modes_options& options = features::modes_setup;

        draw_board(features::boards::picked_capture_point);

        ImGui::SetNextItemWidth(modes_number_width);
        ImGui::InputInt("##capture state", &options.capture_state);
        ImGui::SameLine();
        if (ImGui::Button("capture")) features::modes.capture();

        if (ImGui::Button("secure")) features::modes.secure();
        ImGui::SameLine();
        if (ImGui::Button("undo capture")) features::modes.recover();

        ImGui::Checkbox("to team b", &options.is_points_team);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(modes_number_width);
        ImGui::InputFloat("##points score", &options.points_score, 10.0f, 100.0f, "%.0f");
        ImGui::SameLine();
        if (ImGui::Button("give points")) features::modes.give_points();
    }

    void draw_site_actions(bool is_rush) {
        draw_board(is_rush ? features::boards::picked_rush_site : features::boards::picked_snd_site);

        if (ImGui::Button("plant")) features::modes.plant();
        ImGui::SameLine();
        if (ImGui::Button("disarm")) features::modes.disarm();
        ImGui::SameLine();
        if (ImGui::Button("explode now")) features::modes.explode();
        ImGui::SameLine();
        if (ImGui::Button("defuse now")) features::modes.defuse();
    }

    void draw_objectives(const features::modes_snapshot& modes) {
        if (!ImGui::CollapsingHeader("objectives", ImGuiTreeNodeFlags_DefaultOpen)) return;

        draw_objective_list(modes);

        switch (picked_kind(modes)) {
        case 1: draw_capture_actions(); break;
        case 2: draw_site_actions(false); break;
        case 3: draw_site_actions(true); break;
        default: break;
        }
    }

    void draw_bomb(const features::modes_snapshot& modes) {
        if (!modes.has_bomb || !ImGui::CollapsingHeader("the bomb")) return;

        if (!modes.bomb_carrier.empty()) ImGui::Text("carried by %s", modes.bomb_carrier.c_str());

        draw_board(features::boards::snd_bomb_board);

        if (ImGui::Button("hand it over")) features::modes.give_bomb();
        ImGui::SameLine();
        if (ImGui::Button("drop")) features::modes.drop_bomb();
        ImGui::SameLine();
        if (ImGui::Button("send home")) features::modes.reset_bomb();
    }

    void draw_mode_rules(const features::modes_snapshot& modes) {
        if (!ImGui::CollapsingHeader("this mode's rules")) return;

        features::modes_options& options = features::modes_setup;

        switch (modes.mode) {
        case 1:
            draw_board(features::boards::conquest_state_board);
            ImGui::SetNextItemWidth(modes_number_width);
            ImGui::InputInt("point", &options.holder_point);
            ImGui::Checkbox("held by team b", &options.is_holder_team);
            ImGui::SameLine();
            if (ImGui::Button("set holder")) features::modes.set_holder();
            break;
        case 2:
            draw_board(features::boards::rush_state_board);
            if (ImGui::Button("refill reinforcements")) features::modes.reset_reinforcements();
            ImGui::SetNextItemWidth(modes_number_width);
            ImGui::InputInt("phase", &options.rush_phase);
            ImGui::SetNextItemWidth(modes_number_width);
            ImGui::InputInt("for team", &options.rush_team);
            if (ImGui::Button("turn on that phase's spawns")) features::modes.rush_phase();
            break;
        case 3:
            draw_board(features::boards::snd_state_board);
            if (ImGui::Button("re-roll the site")) features::modes.choose_site();
            ImGui::SameLine();
            if (ImGui::Button("pick round sites")) features::modes.pick_sites();
            if (ImGui::Button("respawn everyone")) features::modes.force_spawn();
            ImGui::SameLine();
            if (ImGui::Button("rebuild rosters")) features::modes.refresh_rosters();
            break;
        case 4:
            draw_board(features::boards::ffa_state_board);
            if (ImGui::Button("check winner")) features::modes.check_ffa();
            break;
        default:
            break;
        }
    }

    void draw_spawns(const features::modes_snapshot& modes) {
        if (!ImGui::CollapsingHeader("spawning")) return;

        features::modes_options& options = features::modes_setup;


        if (ImGui::BeginListBox("##spawns", ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 8.0f))) {
            for (const features::spawn_entry& entry : modes.spawns) {
                char label[128];
                std::snprintf(label, sizeof(label), "#%d team %d phase %d %s%s %.0f m##%llx", entry.index, entry.team, entry.phase,
                    entry.is_active ? "on" : "off", entry.is_claimed ? " claimed" : "", static_cast<double>(entry.distance),
                    static_cast<unsigned long long>(entry.id));

                if (ImGui::Selectable(label, options.spawn == entry.id)) options.spawn = entry.id;
            }

            ImGui::EndListBox();
        }

        draw_board(features::boards::picked_spawn_board);

        if (ImGui::Button("point on")) features::modes.spawn_on(true);
        ImGui::SameLine();
        if (ImGui::Button("point off")) features::modes.spawn_on(false);

        if (ImGui::Button("spawn here")) features::modes.spawn_here();
        ImGui::SameLine();
        if (ImGui::Button("native spawn here")) features::modes.spawn_native();

        ImGui::SetNextItemWidth(modes_number_width);
        ImGui::InputInt("team##preview", &options.spawn_team);
        ImGui::SameLine();
        ImGui::Checkbox("free for all", &options.is_ffa_preview);
        if (ImGui::Button("where would they spawn")) features::modes.preview_spawn();

        ImGui::Separator();

        if (ImGui::Button("respawn me")) features::modes.respawn_me(false);
        ImGui::SameLine();
        if (ImGui::Button("force respawn me")) features::modes.respawn_me(true);

        if (ImGui::TreeNode("your spectator")) {
            draw_board(features::boards::own_spectator_board);
            ImGui::TreePop();
        }
    }

    void draw_migration() {
        if (!ImGui::CollapsingHeader("host migration")) return;

        features::modes_options& options = features::modes_setup;

        draw_board(features::boards::host_migration_board);

        ImGui::SetNextItemWidth(modes_number_width);
        ImGui::InputFloat("clock", &options.resume_clock, 10.0f, 60.0f, "%.0f s");
        ImGui::SetNextItemWidth(modes_number_width);
        ImGui::InputInt("team a##resume", &options.resume_a);
        ImGui::SetNextItemWidth(modes_number_width);
        ImGui::InputInt("team b##resume", &options.resume_b);
        if (ImGui::Button("resume with these")) features::modes.simulate_resume();
    }

}

void render::panels::draw_modes_tab() {
    features::modes.watch();

    const features::modes_snapshot modes = features::modes.snapshot();
    const features::match_snapshot seen = features::host.snapshot();

    ImGui::Text("mode: %s", detail::mode_name(modes.mode));

    detail::draw_actor(seen);

    ImGui::Separator();

    detail::draw_objectives(modes);
    detail::draw_bomb(modes);
    detail::draw_mode_rules(modes);
    detail::draw_spawns(modes);
    detail::draw_migration();
}
