#include <client/render/ui/tabs/panels.hh>
#include <imgui/imgui.h>
#include <features/data/boards.hh>

namespace render::panels::detail {

    void draw_bot_orders(const features::match_snapshot& seen) {
        if (!ImGui::CollapsingHeader("orders")) return;

        draw_player_pick(seen);

        features::aggro_options& aggro = features::aggro_setup;
        ImGui::Checkbox("every bot hunts this player", &aggro.is_hunt);
        ImGui::SliderFloat("every", &aggro.interval, 0.5f, 10.0f, "%.1f s");
        ImGui::Checkbox("only bots on other teams", &aggro.is_enemies_only);

        if (ImGui::Button("hunt once")) features::arena.hunt_once();
        ImGui::SameLine();
        if (ImGui::Button("drop spawn protection")) features::arena.drop_protection();

        if (ImGui::TreeNode("picked bot's own aim")) {
            draw_board(features::boards::chosen_bot);
            ImGui::TreePop();
        }
    }

    void draw_bot_brain() {
        if (!ImGui::CollapsingHeader("behaviour")) return;


        for (features::field_board* board : features::boards::bot_brain_boards) {
            if (!ImGui::TreeNode(board->title)) continue;

            draw_board(*board);
            ImGui::TreePop();
        }

        if (ImGui::Button("reset behaviour"))
            for (features::field_board* board : features::boards::bot_brain_boards) features::fields.release(*board);
    }

    void draw_bot_weapons() {
        if (!ImGui::CollapsingHeader("weapon profiles")) return;

        draw_board(features::boards::bot_weapon_profile);
    }

}

void render::panels::draw_bots_tab() {
    const features::match_snapshot seen = features::host.snapshot();

    detail::draw_bot_orders(seen);
    detail::draw_bot_brain();
    detail::draw_bot_weapons();
}
