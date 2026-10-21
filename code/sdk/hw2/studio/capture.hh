#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <sdk/unreal/engine.hh>

namespace sdk::hw2 {

    [[nodiscard]] UObject* cine_settings();
    [[nodiscard]] UObject* replay_settings();
    [[nodiscard]] UObject* voice_settings();
    [[nodiscard]] UObject* audio_output_settings();
    [[nodiscard]] UObject* voice_cue_settings();
    [[nodiscard]] UObject* input_settings();
    [[nodiscard]] UObject* third_person_settings();

    [[nodiscard]] UObject* cine_system();
    [[nodiscard]] UObject* replay_system();
    [[nodiscard]] UObject* voice_save();

    struct cine_status {
        bool is_found = false;
        bool is_recording = false;
        bool is_god_mode = false;
        float seconds = 0.0f;
        std::string status;
    };

    [[nodiscard]] cine_status read_cine();

    bool cine_call(const char* function_name);
    bool set_god_mode(bool is_enabled);

    struct replay_status {
        bool is_found = false;
        bool is_recording = false;
        bool is_playing = false;
        std::string status;
    };

    [[nodiscard]] replay_status read_replay();
    [[nodiscard]] std::vector<std::string> replay_files();

    bool replay_call(const char* function_name);
    bool replay_record(const char* name);
    bool replay_play(const char* name, float start_seconds);
    bool replay_highlight(const char* label);
    bool replay_jump(int direction);
    bool replay_follow(const char* player_name);

    [[nodiscard]] UObject* replay_spectator(const APlayerController* controller);
    bool spectator_call(const APlayerController* controller, const char* function_name);
    bool replay_seek_to(const APlayerController* controller, float seconds);
    bool replay_seek(const APlayerController* controller, float delta);
    bool replay_speed(const APlayerController* controller, float speed);

    bool reset_voice(const UObject* context);
    bool set_aim_assist(const UObject* context, bool is_enabled);
    bool set_input_fov(const UObject* context, float fov);
    bool set_vibration(const UObject* context, bool is_enabled);
    bool reset_controller(const UObject* context);

    [[nodiscard]] UObject* voice_of(const APawn* pawn) noexcept;
    bool try_voice(const APawn* pawn, int event_id);
    bool voice_call(const APawn* pawn, const char* function_name);

}
