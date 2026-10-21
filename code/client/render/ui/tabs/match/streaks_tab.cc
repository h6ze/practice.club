#include <client/render/ui/tabs/panels.hh>
#include <cstdio>
#include <imgui/imgui.h>
#include <features/data/boards.hh>

namespace render::panels::detail {

    constexpr float count_width = 110.0f;

    void draw_streak_bits(const char* suffix, int& mask) {
        const char* names[] = { "snitch", "homies", "bomber", "drive by" };

        for (int bit = 0; bit < 4; ++bit) {
            char label[32];
            std::snprintf(label, sizeof(label), "%s##%s", names[bit], suffix);

            if (bit > 0) ImGui::SameLine();
            ImGui::CheckboxFlags(label, &mask, 1 << bit);
        }
    }

    void draw_own_streaks(const features::match_snapshot& seen) {
        if (!ImGui::CollapsingHeader("your streaks")) return;

        features::streak_options& options = features::streak_setup;

        draw_board(features::boards::own_streak);

        ImGui::Separator();

        ImGui::TextDisabled("ready");
        draw_streak_bits("ready", options.ready_mask);
        if (ImGui::Button("grant me")) features::arena.grant_streaks(false);
        ImGui::SameLine();
        if (ImGui::Button("grant the picked player")) features::arena.grant_streaks(true);
        draw_player_pick(seen);

        ImGui::TextDisabled("equipped");
        draw_streak_bits("equip", options.equip_mask);
        if (ImGui::Button("equip")) features::arena.equip_streaks();
        ImGui::SameLine();
        if (ImGui::Button("use the streak picked above")) features::arena.use_streak();
    }

    void draw_old_streaks() {
        if (!ImGui::CollapsingHeader("uav and cluster strike")) return;

        features::streak_options& options = features::streak_setup;

        draw_board(features::boards::old_streak);

        if (ImGui::Button("cluster strike")) features::arena.cluster_strike();

        ImGui::SetNextItemWidth(count_width);
        ImGui::InputInt("##streak count", &options.streak_count);
        ImGui::SameLine();
        if (ImGui::Button("set kill streak")) features::arena.set_streak_count();

        ImGui::SliderFloat("uav seconds", &options.uav_seconds, 5.0f, 300.0f, "%.0f s");
        if (ImGui::Button("uav for my team")) features::arena.team_uav();
    }

    void draw_streak_rules() {
        if (!ImGui::CollapsingHeader("rules")) return;


        for (features::field_board* board : features::boards::streak_rule_boards) {
            if (!ImGui::TreeNode(board->title)) continue;

            draw_board(*board);
            ImGui::TreePop();
        }

        if (ImGui::Button("reset rules"))
            for (features::field_board* board : features::boards::streak_rule_boards) features::fields.release(*board);
    }

    void draw_live_car() {
        if (!ImGui::CollapsingHeader("live drive by car")) return;

        features::streak_options& options = features::streak_setup;

        draw_board(features::boards::drive_by_car);

        ImGui::Separator();

        ImGui::SetNextItemWidth(count_width);
        ImGui::InputInt("##summon team", &options.summon_team);
        ImGui::SameLine();
        if (ImGui::Button("summoned bots to team")) features::arena.summons_to_team();
    }

}

void render::panels::draw_streaks_tab() {
    const features::match_snapshot seen = features::host.snapshot();

    detail::draw_own_streaks(seen);
    detail::draw_old_streaks();
    detail::draw_streak_rules();
    detail::draw_live_car();
}
