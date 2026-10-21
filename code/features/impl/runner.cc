#include <features/features.hh>
#include <imgui/imgui.h>
#include <sdk/unreal/view/camera.hh>
#include <sdk/unreal/view/players.hh>
#include <sdk/unreal/runtime/stage.hh>

void features::draw_frame() {
    enforcement.tick();

    const game::loading_stage now = game::stage();
    if (now == game::loading_stage::main_menu || now == game::loading_stage::in_game) {
        fields.tick();
        career.tick();
        network.tick();
        studio.tick();
    }

    if (now != game::loading_stage::in_game) return;

    weapons.tick();
    movement.tick();
    view.tick();
    arena.tick();
    host.tick();
    kit.tick();
    modes.tick();
    scenery.tick();

    const ImGuiIO& io = ImGui::GetIO();
    game::camera::refresh(io.DisplaySize.x, io.DisplaySize.y);

    aim.circles();

    if (!visuals_setup.is_enabled) return;

    game::players::refresh();

    if (visuals_setup.is_snapline) visuals.snaplines();
    if (visuals_setup.is_box) visuals.boxes();
    if (visuals_setup.is_health) visuals.health();
    if (visuals_setup.is_head_dot) visuals.head_dots();
    if (visuals_setup.is_name) visuals.names();
    if (visuals_setup.is_distance) visuals.distance();
}
