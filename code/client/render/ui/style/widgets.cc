#include <client/render/ui/tabs/panels.hh>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <imgui/imgui.h>

namespace render::panels::detail {

    constexpr float mode_width = 64.0f;

    void draw_switch(const features::field& entry, features::field_state& state) {
        const char* modes[] = { "game", "on", "off" };
        int mode = state.is_held ? (state.value != 0.0 ? 1 : 2) : 0;

        ImGui::SetNextItemWidth(mode_width);
        if (ImGui::Combo("##mode", &mode, modes, IM_ARRAYSIZE(modes))) {
            state.is_held = mode != 0;
            if (state.is_held) state.value = mode == 1 ? 1.0 : 0.0;
        }

        ImGui::SameLine();

        if (state.is_held) ImGui::TextUnformatted(entry.label);
        else ImGui::Text("%s (game: %s)", entry.label, state.live != 0.0 ? "on" : "off");
    }

    void draw_number(const features::field& entry, features::field_state& state) {
        ImGui::Checkbox("##hold", &state.is_held);

        ImGui::SameLine();

        const double low = std::min(static_cast<double>(entry.low), state.value);
        const double high = std::max(static_cast<double>(entry.high), state.value);

        const bool is_whole = entry.kind == features::field_kind::byte || entry.kind == features::field_kind::whole;
        if (is_whole) {
            int value = static_cast<int>(std::lround(state.value));
            if (ImGui::SliderInt(entry.label, &value, static_cast<int>(std::floor(low)), static_cast<int>(std::ceil(high)))) {
                state.value = value;
                state.is_held = true;
            }

            return;
        }

        double value = state.value;
        if (ImGui::SliderScalar(entry.label, ImGuiDataType_Double, &value, &low, &high, "%.2f")) {
            state.value = value;
            state.is_held = true;
        }
    }

    [[nodiscard]] bool takes_element(features::board_target target) {
        switch (target) {
        case features::board_target::bot_weapon_profile:
        case features::board_target::post_volume:
        case features::board_target::level_fog:
        case features::board_target::sky_light:
        case features::board_target::sun_light:
        case features::board_target::sky_atmosphere:
        case features::board_target::volumetric_clouds:
        case features::board_target::local_fog:
        case features::board_target::wind_source: return true;
        default: return false;
        }
    }

    void draw_element_pick(features::field_board& board) {
        if (!takes_element(board.target) || board.element_count <= 0) return;

        const int last = board.element_count - 1;
        ImGui::SliderInt("element", &board.element, 0, last);
        if (board.element > last) board.element = last;
    }

}

void render::panels::draw_player_pick(const features::match_snapshot& seen) {
    features::host_options& options = features::host_setup;

    const char* chosen = "nobody picked";
    for (const features::lobby_entry& entry : seen.players)
        if (entry.id == options.target) chosen = entry.name.c_str();

    if (!ImGui::BeginCombo("player", chosen)) return;

    for (const features::lobby_entry& entry : seen.players) {
        char label[96];
        std::snprintf(label, sizeof(label), "%s - team %d, %s##%llx", entry.name.c_str(), entry.team,
            entry.is_bot ? "bot" : "human", static_cast<unsigned long long>(entry.id));

        if (ImGui::Selectable(label, entry.id == options.target)) options.target = entry.id;
    }

    ImGui::EndCombo();
}

void render::panels::draw_board(features::field_board& board) {
    board.is_watched = true;

    ImGui::PushID(board.title);

    detail::draw_element_pick(board);

    for (int i = 0; i < board.count; ++i) {
        const features::field& entry = board.fields[i];
        features::field_state& state = board.state[i];

        if (!state.is_present) continue;

        ImGui::PushID(i);

        if (!state.is_held) state.value = state.live;

        const bool is_switch = entry.kind == features::field_kind::flag || entry.kind == features::field_kind::bit;
        if (is_switch) detail::draw_switch(entry, state);
        else detail::draw_number(entry, state);

        ImGui::PopID();
    }

    if (ImGui::Button("reset")) features::fields.release(board);

    ImGui::PopID();
}
