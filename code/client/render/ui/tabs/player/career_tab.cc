#include <client/render/ui/tabs/panels.hh>
#include <imgui/imgui.h>
#include <features/data/boards.hh>

namespace render::panels::detail {

    constexpr float career_number_width = 120.0f;

    void draw_cloud(const features::career_snapshot& seen) {
        if (!ImGui::CollapsingHeader("cloud profile")) return;

        if (seen.has_cloud) ImGui::Text("%s -> cloud level %d, %d xp, %d reports waiting", seen.is_authenticated ? "signed in" : "not signed in",
            seen.cloud_level, seen.cloud_xp, seen.pending);

        if (ImGui::Button("fetch profile")) features::career.fetch_profile();

        draw_board(features::boards::online_progress_board);
    }

    void draw_experience() {
        if (!ImGui::CollapsingHeader("experience and score")) return;

        features::career_options& options = features::career_setup;

        ImGui::SetNextItemWidth(career_number_width);
        ImGui::InputInt("experience", &options.exp_amount, 100, 1000);
        if (ImGui::Button("give exp")) features::career.give_exp();
        ImGui::SameLine();
        if (ImGui::Button("add experience")) features::career.add_experience();
        ImGui::SameLine();
        if (ImGui::Button("level up once")) features::career.level_up();

        if (ImGui::Button("save level")) features::career.save_level();
        ImGui::SameLine();
        if (ImGui::Button("load level")) features::career.load_level();

        ImGui::SetNextItemWidth(career_number_width);
        ImGui::InputFloat("score", &options.score_amount, 10.0f, 100.0f, "%.0f");
        ImGui::SetNextItemWidth(career_number_width);
        ImGui::InputInt("reason", &options.score_reason);
        if (ImGui::Button("add score")) features::career.add_score();
    }

    void draw_missions(const features::career_snapshot& seen) {
        if (!ImGui::CollapsingHeader("missions")) return;

        features::career_options& options = features::career_setup;


        for (std::size_t i = 0; i < seen.missions.size(); ++i) {
            const features::mission_view& mission = seen.missions[i];
            ImGui::Text("%zu. mission %d -> %d / %d, %d xp%s", i, mission.id, mission.progress, mission.target, mission.reward,
                mission.is_completed ? ", done" : "");
        }

        ImGui::SetNextItemWidth(career_number_width);
        ImGui::InputInt("mission", &options.mission_index);
        if (ImGui::Button("complete and save")) features::career.complete_missions();
        ImGui::SameLine();
        if (ImGui::Button("save missions")) features::career.save_missions();

        ImGui::SetNextItemWidth(career_number_width);
        ImGui::InputInt("won mode", &options.won_mode);
        ImGui::SameLine();
        if (ImGui::Button("count a win")) features::career.mission_won();

        ImGui::SetNextItemWidth(career_number_width);
        ImGui::InputInt("weapon type", &options.killed_weapon_type);
        ImGui::SameLine();
        if (ImGui::Button("count a kill")) features::career.mission_kill();
    }

    void draw_challenges() {
        if (!ImGui::CollapsingHeader("challenge credit")) return;

        features::career_options& options = features::career_setup;


        ImGui::Checkbox("as a win", &options.is_won);
        ImGui::SameLine();
        if (ImGui::Button("bank match end")) features::career.match_end();

        ImGui::Checkbox("headshot", &options.is_headshot);
        ImGui::SameLine();
        if (ImGui::Button("record kill")) features::career.record_kill();

        ImGui::SetNextItemWidth(career_number_width);
        ImGui::InputText("##kill kind", options.kill_kind, sizeof(options.kill_kind));
        ImGui::SameLine();
        if (ImGui::Button("note local kill")) features::career.local_kill();

        ImGui::SetNextItemWidth(career_number_width);
        ImGui::InputText("##stat suffix", options.stat_suffix, sizeof(options.stat_suffix));
        ImGui::SameLine();
        if (ImGui::Button("bump held weapon stat")) features::career.bump_stat();

        draw_board(features::boards::own_progression_board);
    }

    void draw_unlocks(const features::career_snapshot& seen) {
        if (!ImGui::CollapsingHeader("unlocks")) return;

        features::career_options& options = features::career_setup;

        ImGui::Text("%d gates held open", seen.gates_open);

        if (ImGui::Button("unlock everything")) features::career.unlock_all();
        ImGui::SameLine();
        if (ImGui::Button("relock")) features::career.relock_all();

        ImGui::Checkbox("keep unlocking as assets load", &options.is_unlock_held);
        ImGui::Checkbox("attachments on every gun", &options.is_attachments_everywhere);
    }

    void draw_saves() {
        if (!ImGui::CollapsingHeader("local saves")) return;


        features::field_board* saves[] = {
            &features::boards::save_level_board, &features::boards::save_game_board,
            &features::boards::save_streaks_board, &features::boards::save_menu_board,
        };

        for (features::field_board* board : saves) {
            if (!ImGui::TreeNode(board->title)) continue;

            draw_board(*board);
            ImGui::TreePop();
        }
    }

}

void render::panels::draw_career_tab() {
    features::career.watch();

    const features::career_snapshot seen = features::career.snapshot();

    ImGui::Separator();

    detail::draw_cloud(seen);
    detail::draw_experience();
    detail::draw_missions(seen);
    detail::draw_challenges();
    detail::draw_unlocks(seen);
    detail::draw_saves();
}
