#include <client/render/ui/tabs/panels.hh>
#include <cstdio>
#include <iterator>
#include <imgui/imgui.h>
#include <features/data/boards.hh>
#include <features/data/tune.hh>

namespace render::panels::detail {

    constexpr float world_number_width = 120.0f;
    constexpr std::size_t presets_per_row = 2;

    void draw_world_lights(const features::scenery_snapshot& seen) {
        if (!ImGui::CollapsingHeader("lighting", ImGuiTreeNodeFlags_DefaultOpen)) return;

        features::scenery_options& options = features::scenery_setup;

        ImGui::Text("%d lights, %d post process volumes", seen.lights, seen.post_volumes);

        ImGui::Checkbox("light intensity", &options.is_light_scale);
        ImGui::SliderFloat("##light intensity", &options.light_scale, 0.0f, 20.0f, "%.2fx");

        ImGui::Checkbox("no shadows", &options.is_no_shadows);
        ImGui::Checkbox("map grading off", &options.is_no_post_volumes);

        if (ImGui::Button("restore the level")) features::scenery.restore();
    }

    void draw_world_time(const features::scenery_snapshot& seen) {
        if (!ImGui::CollapsingHeader("time")) return;

        features::scenery_options& options = features::scenery_setup;

        ImGui::Text("running at %.3fx", seen.dilation);

        ImGui::SetNextItemWidth(world_number_width);
        ImGui::SliderFloat("##dilation", &options.dilation, 0.05f, 4.0f, "%.2fx");
        ImGui::SameLine();
        if (ImGui::Button("set")) features::scenery.set_dilation();
        ImGui::SameLine();
        if (ImGui::Button("back to one")) features::scenery.reset_dilation();

        if (!ImGui::TreeNode(features::boards::world_settings_board.title)) return;

        draw_board(features::boards::world_settings_board);
        ImGui::TreePop();
    }

    void draw_world_console(const features::scenery_snapshot& seen) {
        if (!ImGui::CollapsingHeader("console")) return;

        features::scenery_options& options = features::scenery_setup;

        ImGui::InputText("command", options.command, sizeof(options.command));
        if (ImGui::Button("send")) features::scenery.run_command();

        ImGui::InputText("variable", options.cvar, sizeof(options.cvar));
        if (ImGui::Button("read")) features::scenery.read_cvar();

        if (!seen.cvar_name.empty())
            ImGui::Text("%s: %.3f float, %d int, %s switch", seen.cvar_name.c_str(), seen.cvar_number,
                seen.cvar_whole, seen.is_cvar_on ? "on" : "off");

        if (!ImGui::TreeNode("presets")) return;

        for (std::size_t i = 0; i < std::size(features::tune::console_presets); ++i) {
            const features::tune::console_preset& preset = features::tune::console_presets[i];

            if (i % presets_per_row != 0) ImGui::SameLine();
            if (!ImGui::Button(preset.label)) continue;

            std::snprintf(options.command, sizeof(options.command), "%s", preset.command);
            features::scenery.run_command();
        }

        ImGui::TreePop();
    }

    void draw_world_quality(const features::scenery_snapshot& seen) {
        if (!ImGui::CollapsingHeader("renderer")) return;

        features::scenery_options& options = features::scenery_setup;

        ImGui::SliderInt("quality", &options.quality, 0, 4);

        for (std::size_t i = 0; i < std::size(features::tune::quality_setters); ++i) {
            const features::tune::quality_setter& setter = features::tune::quality_setters[i];

            if (i % presets_per_row != 0) ImGui::SameLine();
            if (ImGui::Button(setter.label)) features::scenery.quality(setter.function_name);
        }

        ImGui::Separator();

        ImGui::SetNextItemWidth(world_number_width);
        ImGui::SliderFloat("##resolution scale", &options.resolution_scale, 0.25f, 1.0f, "%.2f");
        ImGui::SameLine();
        if (ImGui::Button("resolution scale")) features::scenery.resolution_scale();

        ImGui::SetNextItemWidth(world_number_width);
        ImGui::InputFloat("##frame limit", &options.frame_limit, 10.0f, 60.0f, "%.0f fps");
        ImGui::SameLine();
        if (ImGui::Button("frame limit")) features::scenery.frame_limit();

        if (ImGui::Button("vsync on")) features::scenery.vsync(true);
        ImGui::SameLine();
        if (ImGui::Button("vsync off")) features::scenery.vsync(false);
        ImGui::SameLine();
        if (ImGui::Button("apply")) features::scenery.apply_settings();

        ImGui::Separator();

        ImGui::Text("%d shaders left to compile", seen.shaders_left);

        if (ImGui::Button("path tracer on")) features::scenery.path_tracing(true);
        ImGui::SameLine();
        if (ImGui::Button("path tracer off")) features::scenery.path_tracing(false);
        ImGui::SameLine();
        if (ImGui::Button("refresh output")) features::scenery.refresh_path_tracing();
    }

    void draw_world_boards() {
        if (!ImGui::CollapsingHeader("the map")) return;

        for (features::field_board* board : features::boards::world_boards) {
            if (board == &features::boards::world_settings_board) continue;
            if (!ImGui::TreeNode(board->title)) continue;

            draw_board(*board);
            ImGui::TreePop();
        }
    }

}

void render::panels::draw_world_tab() {
    features::scenery.watch();

    const features::scenery_snapshot seen = features::scenery.snapshot();

    detail::draw_world_lights(seen);
    detail::draw_world_time(seen);
    detail::draw_world_console(seen);
    detail::draw_world_quality(seen);
    detail::draw_world_boards();
}
