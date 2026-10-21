#include <client/render/ui/tabs/panels.hh>
#include <cstdio>
#include <string>
#include <imgui/imgui.h>
#include <features/data/boards.hh>

namespace render::panels::detail {

    constexpr float media_number_width = 120.0f;

    void draw_capture(const features::studio_snapshot& seen) {
        if (!ImGui::CollapsingHeader("capture", ImGuiTreeNodeFlags_DefaultOpen)) return;

        if (seen.has_cine) ImGui::Text("%s%s - %s", seen.is_recording ? "recording" : "idle", seen.is_god_mode ? ", god mode" : "", seen.cine_status.c_str());

        if (ImGui::Button("record")) features::studio.cine("StartRecording");
        ImGui::SameLine();
        if (ImGui::Button("stop")) features::studio.cine("StopRecording");
        ImGui::SameLine();
        if (ImGui::Button("vertical")) features::studio.cine("StartTikTokRecording");
        ImGui::SameLine();
        if (ImGui::Button("vertical hi-res")) features::studio.cine("StartTikTokHighResRecording");

        if (ImGui::Button("screenshot")) features::studio.cine("TakeScreenshot");
        ImGui::SameLine();
        if (ImGui::Button("drop camera")) features::studio.cine("DropCamera");
        ImGui::SameLine();
        if (ImGui::Button("next camera")) features::studio.cine("CycleActiveCamera");
        ImGui::SameLine();
        if (ImGui::Button("record from camera")) features::studio.cine("ToggleCameraRecording");

        if (ImGui::Button("god mode on")) features::studio.god_mode(true);
        ImGui::SameLine();
        if (ImGui::Button("god mode off")) features::studio.god_mode(false);

        if (ImGui::TreeNode("capture settings")) {
            draw_board(features::boards::cine_capture_board);
            ImGui::TreePop();
        }
    }

    void draw_replays(const features::studio_snapshot& seen) {
        if (!ImGui::CollapsingHeader("replays")) return;

        features::studio_options& options = features::studio_setup;

        if (seen.has_replay) ImGui::Text("%s%s - %s", seen.is_replay_recording ? "recording" : "idle", seen.is_replay_playing ? ", playing" : "", seen.replay_status.c_str());

        ImGui::InputText("name", options.replay_name, sizeof(options.replay_name));
        if (ImGui::Button("record##replay")) features::studio.replay_record();
        ImGui::SameLine();
        if (ImGui::Button("stop##replay")) features::studio.replay_stop();
        ImGui::SameLine();
        ImGui::SetNextItemWidth(media_number_width);
        ImGui::InputFloat("from", &options.replay_start, 10.0f, 60.0f, "%.0f s");
        ImGui::SameLine();
        if (ImGui::Button("play")) features::studio.replay_play();

        if (ImGui::Button("list replays")) features::studio.replay_refresh_list();
        for (const std::string& name : seen.replays)
            if (ImGui::Selectable(name.c_str(), name == options.replay_name)) std::snprintf(options.replay_name, sizeof(options.replay_name), "%s", name.c_str());

        ImGui::Separator();

        ImGui::Checkbox("highlight every kill", &options.is_auto_highlight);
        ImGui::InputText("highlight label", options.highlight, sizeof(options.highlight));
        if (ImGui::Button("mark highlight")) features::studio.replay_highlight();
        ImGui::SameLine();
        if (ImGui::Button("< highlight")) features::studio.replay_jump(-1);
        ImGui::SameLine();
        if (ImGui::Button("highlight >")) features::studio.replay_jump(1);
        ImGui::SameLine();
        if (ImGui::Button("clear")) features::studio.replay_clear_highlights();

        ImGui::Separator();

        ImGui::SetNextItemWidth(media_number_width);
        ImGui::InputFloat("seek to", &options.seek_seconds, 10.0f, 60.0f, "%.0f s");
        ImGui::SameLine();
        if (ImGui::Button("seek")) features::studio.seek_to();
        if (ImGui::Button("-10 s")) features::studio.seek(-10.0f);
        ImGui::SameLine();
        if (ImGui::Button("+10 s")) features::studio.seek(10.0f);
        ImGui::SameLine();
        if (ImGui::Button("pause")) features::studio.spectator("TogglePause");
        ImGui::SameLine();
        if (ImGui::Button("ultra still")) features::studio.spectator("TakeUltraStill");

        ImGui::SetNextItemWidth(media_number_width);
        ImGui::SliderFloat("speed", &options.playback_speed, 0.1f, 4.0f, "%.2fx");
        ImGui::SameLine();
        if (ImGui::Button("set speed")) features::studio.playback_speed();

        ImGui::InputText("follow", options.follow_name, sizeof(options.follow_name));
        ImGui::SameLine();
        if (ImGui::Button("follow player")) features::studio.replay_follow();

        if (ImGui::TreeNode("replay settings")) {
            draw_board(features::boards::replay_options_board);
            ImGui::TreePop();
        }
    }

    void draw_voice() {
        if (!ImGui::CollapsingHeader("voice and sound")) return;

        features::studio_options& options = features::studio_setup;

        features::field_board* boards[] = {
            &features::boards::voice_options_board, &features::boards::voice_save_board, &features::boards::own_voice_board,
            &features::boards::voice_cues_board, &features::boards::audio_output_board,
        };

        for (features::field_board* board : boards) {
            if (!ImGui::TreeNode(board->title)) continue;

            draw_board(*board);
            ImGui::TreePop();
        }

        if (ImGui::Button("reset voice settings")) features::studio.reset_voice();

        ImGui::SetNextItemWidth(media_number_width);
        ImGui::InputInt("voice event", &options.voice_event);
        ImGui::SameLine();
        if (ImGui::Button("say it")) features::studio.try_voice();
        if (ImGui::Button("stop voice")) features::studio.voice("StopVoice");
        ImGui::SameLine();
        if (ImGui::Button("spotted callout")) features::studio.voice("SpotEnemy");
    }

    void draw_input() {
        if (!ImGui::CollapsingHeader("input and camera")) return;

        features::studio_options& options = features::studio_setup;

        draw_board(features::boards::player_input_board);

        ImGui::SetNextItemWidth(media_number_width);
        ImGui::SliderFloat("##game fov", &options.fov, 40.0f, 170.0f, "%.0f deg");
        ImGui::SameLine();
        if (ImGui::Button("set fov the game's way")) features::studio.set_fov();

        if (ImGui::Button("vibration on")) features::studio.vibration(true);
        ImGui::SameLine();
        if (ImGui::Button("vibration off")) features::studio.vibration(false);
        ImGui::SameLine();
        if (ImGui::Button("reset controls")) features::studio.reset_controller();

        if (ImGui::Button("aim assist off")) features::studio.aim_assist(false);
        ImGui::SameLine();
        if (ImGui::Button("aim assist on")) features::studio.aim_assist(true);

        features::field_board* boards[] = {
            &features::boards::input_general_board, &features::boards::input_aim_assist_board,
            &features::boards::third_person_board, &features::boards::controller_options_board,
        };

        for (features::field_board* board : boards) {
            if (!ImGui::TreeNode(board->title)) continue;

            draw_board(*board);
            ImGui::TreePop();
        }
    }

}

void render::panels::draw_media_tab() {
    features::studio.watch();

    const features::studio_snapshot seen = features::studio.snapshot();

    detail::draw_capture(seen);
    detail::draw_replays(seen);
    detail::draw_voice();
    detail::draw_input();
}
