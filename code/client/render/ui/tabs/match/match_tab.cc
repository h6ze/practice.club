#include <client/render/ui/tabs/panels.hh>
#include <cstdio>
#include <imgui/imgui.h>
#include <features/data/boards.hh>

namespace render::panels::detail {

    constexpr float number_width = 110.0f;

    constexpr ImVec4 good = { 0.45f, 0.85f, 0.5f, 1.0f };
    constexpr ImVec4 bad = { 0.9f, 0.45f, 0.4f, 1.0f };

    void draw_match_status(const features::match_snapshot& seen) {
        if (seen.is_host) ImGui::TextColored(good, "hosting");
        else ImGui::TextColored(bad, "not hosting");

        if (!seen.has_match) return;

        ImGui::Text("score %d - %d   rounds %d - %d   winner %d", seen.team_a, seen.team_b, seen.rounds_a, seen.rounds_b, seen.winner);
        ImGui::Text("clock %.0f s   to start %.0f s   match state %d   round state %d",
            static_cast<double>(seen.clock), seen.time_to_start, seen.match_state, seen.round_state);
    }

    void draw_team_number(features::host_options& options, const char* label) {
        ImGui::SetNextItemWidth(number_width);
        ImGui::InputInt(label, &options.team);
    }

    void draw_score(features::host_options& options) {
        if (!ImGui::CollapsingHeader("score")) return;

        ImGui::SetNextItemWidth(number_width);
        ImGui::InputInt("##team a points", &options.team_a_points);
        ImGui::SameLine();
        if (ImGui::Button("set team a")) features::host.set_points(0);

        ImGui::SetNextItemWidth(number_width);
        ImGui::InputInt("##team b points", &options.team_b_points);
        ImGui::SameLine();
        if (ImGui::Button("set team b")) features::host.set_points(1);

        ImGui::Separator();

        draw_team_number(options, "team");

        if (ImGui::Button("+1 point")) features::host.add_point();
        ImGui::SameLine();
        if (ImGui::Button("+1 round")) features::host.add_round();
        ImGui::SameLine();
        if (ImGui::Button("set winner")) features::host.set_winner();

        if (ImGui::Button("end round, team wins")) features::host.end_round();
        ImGui::SameLine();
        if (ImGui::Button("end game")) features::host.end_game();

        if (ImGui::Button("reset scores")) features::host.reset_scores();
        ImGui::SameLine();
        if (ImGui::Button("swap rounds")) features::host.flip_rounds();

        ImGui::Separator();

        ImGui::SetNextItemWidth(number_width);
        ImGui::InputInt("##match state", &options.match_state);
        ImGui::SameLine();
        if (ImGui::Button("force match state")) features::host.set_match_state();

        ImGui::SetNextItemWidth(number_width);
        ImGui::InputInt("##round state", &options.round_state);
        ImGui::SameLine();
        if (ImGui::Button("force round state")) features::host.set_round_state();

        if (ImGui::Button("restart clock")) features::host.start_clock();
        ImGui::SameLine();
        if (ImGui::Button("call time")) features::host.time_out();

        if (ImGui::TreeNode("holds")) {
            draw_board(features::boards::match_clock);
            ImGui::TreePop();
        }
    }

    void draw_rules() {
        if (!ImGui::CollapsingHeader("rules")) return;

        draw_board(features::boards::match_rules);

        if (ImGui::Button("push dev lobby size")) features::host.apply_lobby_size();
    }

    void draw_game_mode() {
        if (!ImGui::CollapsingHeader("game mode")) return;

        draw_board(features::boards::game_mode_rules);

        if (ImGui::Button("restart match")) features::host.restart_match();
        ImGui::SameLine();
        if (ImGui::Button("start match")) features::host.start_match();
        ImGui::SameLine();
        if (ImGui::Button("end match")) features::host.end_match();
    }

    const char* chosen_name(const features::match_snapshot& seen, std::uintptr_t target) {
        for (const features::lobby_entry& entry : seen.players)
            if (entry.id == target) return entry.name.c_str();

        return nullptr;
    }

    void draw_player_table(features::host_options& options, const features::match_snapshot& seen) {
        constexpr ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_SizingFixedFit;
        if (!ImGui::BeginTable("##players", 5, flags)) return;

        ImGui::TableSetupColumn("name");
        ImGui::TableSetupColumn("team");
        ImGui::TableSetupColumn("kind");
        ImGui::TableSetupColumn("k / d / a");
        ImGui::TableSetupColumn("score");
        ImGui::TableHeadersRow();

        for (const features::lobby_entry& entry : seen.players) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();

            char label[96];
            std::snprintf(label, sizeof(label), "%s%s##%llx", entry.name.c_str(), entry.is_local ? " (you)" : "",
                static_cast<unsigned long long>(entry.id));

            if (ImGui::Selectable(label, options.target == entry.id, ImGuiSelectableFlags_SpanAllColumns)) {
                options.target = entry.id;
                options.kills = entry.kills;
                options.deaths = entry.deaths;
                options.assists = entry.assists;
                options.score = static_cast<float>(entry.score);
                options.team = entry.team;
            }

            ImGui::TableNextColumn();
            ImGui::Text("%d", entry.team);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(entry.is_bot ? (entry.is_alive ? "bot" : "bot, dead") : (entry.is_alive ? "human" : "human, dead"));
            ImGui::TableNextColumn();
            ImGui::Text("%d / %d / %d", entry.kills, entry.deaths, entry.assists);
            ImGui::TableNextColumn();
            ImGui::Text("%.0f", entry.score);
        }

        ImGui::EndTable();
    }

    void draw_players(features::host_options& options, const features::match_snapshot& seen) {
        if (!ImGui::CollapsingHeader("players")) return;

        if (seen.players.empty()) return;

        draw_player_table(options, seen);

        const char* name = chosen_name(seen, options.target);
        if (name) ImGui::Text("selected %s", name);

        ImGui::BeginDisabled(!name);

        draw_team_number(options, "to team");
        if (ImGui::Button("move to team")) features::host.move_target();
        ImGui::SameLine();
        if (ImGui::Button("can join?")) features::host.check_target_team();

        if (ImGui::Button("respawn now")) features::host.respawn_target();
        ImGui::SameLine();
        if (ImGui::Button("respawn bot")) features::host.respawn_bot();
        ImGui::SameLine();
        if (ImGui::Button("remove bot")) features::host.remove_bot();

        ImGui::SetNextItemWidth(number_width * 1.6f);
        ImGui::InputText("##new name", options.new_name, sizeof(options.new_name));
        ImGui::SameLine();
        if (ImGui::Button("rename")) features::host.rename_target();

        ImGui::SetNextItemWidth(number_width);
        ImGui::InputInt("kills", &options.kills);
        ImGui::SetNextItemWidth(number_width);
        ImGui::InputInt("deaths", &options.deaths);
        ImGui::SetNextItemWidth(number_width);
        ImGui::InputInt("assists", &options.assists);
        ImGui::SetNextItemWidth(number_width);
        ImGui::InputFloat("score", &options.score, 10.0f, 100.0f, "%.0f");
        if (ImGui::Button("set stats")) features::host.set_target_stats();

        ImGui::EndDisabled();

        ImGui::Separator();

        if (ImGui::Button("switch my team")) features::host.switch_own_team();
        ImGui::SameLine();
        if (ImGui::Button("flip teams")) features::host.flip_teams();
        ImGui::SameLine();
        if (ImGui::Button("balance teams")) features::host.balance_teams();
    }

    void draw_bots(features::host_options& options) {
        if (!ImGui::CollapsingHeader("bots")) return;

        ImGui::SetNextItemWidth(number_width);
        ImGui::InputInt("team a##bots", &options.bots_a);
        ImGui::SetNextItemWidth(number_width);
        ImGui::InputInt("team b##bots", &options.bots_b);
        if (ImGui::Button("add bots")) features::host.add_bots();

        ImGui::SetNextItemWidth(number_width);
        ImGui::InputInt("free for all##bots", &options.bots_ffa);
        ImGui::SameLine();
        if (ImGui::Button("add ffa bots")) features::host.add_bots_ffa();

        draw_team_number(options, "from team");
        if (ImGui::Button("remove one")) features::host.remove_one_bot();
        ImGui::SameLine();
        if (ImGui::Button("remove all bots")) features::host.remove_all_bots();
    }

    void draw_lobby(features::host_options& options) {
        if (!ImGui::CollapsingHeader("lobby and map")) return;

        draw_board(features::boards::lobby_presets);

        ImGui::Separator();

        ImGui::SetNextItemWidth(number_width * 1.8f);
        ImGui::InputText("##map", options.travel_level, sizeof(options.travel_level));
        ImGui::SameLine();
        if (ImGui::Button("travel")) features::host.travel();

        ImGui::SetNextItemWidth(number_width * 1.8f);
        ImGui::InputText("##mode", options.match_mode, sizeof(options.match_mode));
        ImGui::SameLine();
        if (ImGui::Button("create match")) features::host.create_match();
    }

}

void render::panels::draw_match_tab() {
    features::host_options& options = features::host_setup;
    const features::match_snapshot seen = features::host.snapshot();

    detail::draw_match_status(seen);

    ImGui::Separator();

    detail::draw_score(options);
    detail::draw_rules();
    detail::draw_game_mode();
    detail::draw_players(options, seen);
    detail::draw_bots(options);
    detail::draw_lobby(options);

    ImGui::Separator();

    if (ImGui::Button("reset all")) features::fields.release_all();
}
