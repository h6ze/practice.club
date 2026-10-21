#include <client/render/ui/tabs/panels.hh>
#include <cstdio>
#include <imgui/imgui.h>
#include <features/data/boards.hh>

namespace render::panels::detail {

    constexpr float online_number_width = 120.0f;

    const char* phase_name(int phase) {
        const char* names[] = { "idle", "electing", "becoming host", "searching", "joining", "failed" };

        return phase >= 0 && phase < static_cast<int>(IM_ARRAYSIZE(names)) ? names[phase] : "unknown";
    }

    void draw_lobby_admin(const features::match_snapshot& seen) {
        if (!ImGui::CollapsingHeader("lobby admin")) return;

        features::network_options& options = features::network_setup;

        draw_player_pick(seen);

        ImGui::InputText("reason", options.reason, sizeof(options.reason));
        if (ImGui::Button("kick")) features::network.kick();
        ImGui::SameLine();
        if (ImGui::Button("ban from this lobby")) features::network.ban();

        ImGui::Separator();

        ImGui::SetNextItemWidth(online_number_width);
        ImGui::InputInt("public slots", &options.public_connections);
        ImGui::Checkbox("joining mid match", &options.is_join_in_progress);
        ImGui::SameLine();
        ImGui::Checkbox("invites", &options.is_allow_invites);
        if (ImGui::Button("update the lobby")) features::network.lobby_access();
    }

    void draw_announcements() {
        if (!ImGui::CollapsingHeader("announcements")) return;

        features::network_options& options = features::network_setup;

        ImGui::InputText("message", options.announcement, sizeof(options.announcement));
        if (ImGui::Button("to everyone")) features::network.announce();
        ImGui::SameLine();
        if (ImGui::Button("as an objective banner")) features::network.objective_message();

        ImGui::InputText("team a", options.team_0_text, sizeof(options.team_0_text));
        ImGui::InputText("team b", options.team_1_text, sizeof(options.team_1_text));
        if (ImGui::Button("to each team")) features::network.announce_teams();
    }

    void draw_browser_and_friends(const features::network_snapshot& seen) {
        if (!ImGui::CollapsingHeader("browser, friends and invites")) return;

        features::network_options& options = features::network_setup;

        if (ImGui::Button("open server browser")) features::network.open_browser();
        ImGui::SameLine();
        if (ImGui::Button("refresh##browser")) features::network.refresh_browser();
        ImGui::SameLine();
        if (ImGui::Button("join selected")) features::network.join_selected();

        ImGui::Separator();

        for (const features::friend_view& entry : seen.friends)
            ImGui::Text("%d. %s - %s%s", entry.index, entry.name.c_str(), entry.status.c_str(), entry.is_joinable ? ", joinable" : "");

        ImGui::SetNextItemWidth(online_number_width);
        ImGui::InputInt("friend", &options.friend_index);
        if (ImGui::Button("refresh friends")) features::network.refresh_friends();
        ImGui::SameLine();
        if (ImGui::Button("join")) features::network.join_friend();
        ImGui::SameLine();
        if (ImGui::Button("invite")) features::network.invite_friend();
        ImGui::SameLine();
        if (ImGui::Button("invite screen")) features::network.open_invites();

        if (seen.has_invite) ImGui::Text("invite from %s", seen.inviter.c_str());
        if (ImGui::Button("accept invite")) features::network.answer_invite(true);
        ImGui::SameLine();
        if (ImGui::Button("decline invite")) features::network.answer_invite(false);
    }

    void draw_migration_and_report(const features::network_snapshot& seen) {
        if (!ImGui::CollapsingHeader("migration and match report")) return;

        features::network_options& options = features::network_setup;

        if (seen.has_migration) ImGui::Text("migration %s%s%s", phase_name(seen.phase), seen.is_migrating ? ", migrating" : "", seen.is_migration_host ? ", you are next host" : "");
        if (!seen.successor.empty()) ImGui::Text("next host %s", seen.successor.c_str());

        if (ImGui::Button("hand over and leave")) features::network.hand_over_and_leave();
        ImGui::SameLine();
        if (ImGui::Button("leave")) features::network.leave(false);
        ImGui::SameLine();
        if (ImGui::Button("leave to desktop")) features::network.leave(true);

        ImGui::Separator();

        ImGui::SetNextItemWidth(online_number_width);
        ImGui::InputText("match id", options.match_id, sizeof(options.match_id));
        if (ImGui::Button("save match report")) features::network.save_report();
    }

}

void render::panels::draw_online_tab() {
    features::network.watch();

    const features::network_snapshot seen = features::network.snapshot();
    const features::match_snapshot lobby = features::host.snapshot();

    detail::draw_lobby_admin(lobby);
    detail::draw_announcements();
    detail::draw_browser_and_friends(seen);
    detail::draw_migration_and_report(seen);

    if (ImGui::CollapsingHeader("matchmaking")) {
        draw_board(features::boards::matchmaking_board);
    }
}
