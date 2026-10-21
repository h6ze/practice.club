#pragma once
#include <string>

namespace features {

    struct scenery_snapshot {
        bool has_world = false;
        float dilation = 0.0f;
        int lights = 0;
        int post_volumes = 0;
        int shaders_left = 0;

        std::string cvar_name;
        float cvar_number = 0.0f;
        int cvar_whole = 0;
        bool is_cvar_on = false;
    };

    struct scenery_options {
        bool is_light_scale = false;
        float light_scale = 2.0f;
        bool is_no_shadows = false;

        bool is_no_post_volumes = false;

        float dilation = 1.0f;

        char command[128] = "r.Fog 0";
        char cvar[64] = "r.Fog";

        int quality = 0;
        float resolution_scale = 1.0f;
        float frame_limit = 0.0f;
    };

    inline scenery_options scenery_setup;

    struct scenery_domain {
        void tick();
        void watch();
        [[nodiscard]] scenery_snapshot snapshot();

        void lights();
        void post_volumes();

        void nudge();

        void restore();

        void set_dilation();
        void reset_dilation();

        void run_command();
        void read_cvar();

        void quality(const char* function_name);
        void resolution_scale();
        void frame_limit();
        void vsync(bool is_enabled);
        void apply_settings();

        void path_tracing(bool is_enabled);
        void refresh_path_tracing();
    };

    inline scenery_domain scenery;

}
