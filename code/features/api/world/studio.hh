#pragma once
#include <string>
#include <vector>

namespace features {

    struct studio_snapshot {
        bool has_cine = false;
        bool is_recording = false;
        bool is_god_mode = false;
        float seconds = 0.0f;
        std::string cine_status;

        bool has_replay = false;
        bool is_replay_recording = false;
        bool is_replay_playing = false;
        std::string replay_status;
        std::vector<std::string> replays;
    };

    struct studio_options {
        char replay_name[64] = "practice";
        char highlight[32] = "kill";
        float replay_start = 0.0f;
        float seek_seconds = 10.0f;
        float playback_speed = 1.0f;
        char follow_name[32] = "";

        bool is_auto_highlight = false;

        int voice_event = 0;
        float fov = 110.0f;
    };

    inline studio_options studio_setup;

    struct studio_domain {
        void tick();
        void watch();
        [[nodiscard]] studio_snapshot snapshot();

        void cine(const char* function_name);
        void god_mode(bool is_enabled);

        void replay_record();
        void replay_stop();
        void replay_play();
        void replay_highlight();
        void replay_jump(int direction);
        void replay_follow();
        void replay_clear_highlights();
        void replay_refresh_list();

        void seek_to();
        void seek(float delta);
        void playback_speed();
        void spectator(const char* function_name);

        void try_voice();
        void voice(const char* function_name);
        void reset_voice();

        void aim_assist(bool is_enabled);
        void set_fov();
        void vibration(bool is_enabled);
        void reset_controller();
    };

    inline studio_domain studio;

}
