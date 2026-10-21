#pragma once
#include <cstdint>
#include <vector>
#include <sdk/unreal/engine.hh>

namespace sdk::scene {

    [[nodiscard]] AActor* settings();

    [[nodiscard]] std::vector<AActor*> actors_of(const char* class_name);

    [[nodiscard]] int count_of(const char* class_name);

    [[nodiscard]] AActor* actor_of(const char* class_name, int element, int& count);

    [[nodiscard]] UObject* component_of(const char* class_name, std::uint32_t component_offset, int element, int& count);

    [[nodiscard]] std::vector<UObject*> light_components();

    bool set_light_intensity(UObject* component, float intensity);
    bool set_cast_shadows(UObject* component, bool is_casting);
    bool set_visibility(UObject* component, bool is_visible);

    bool nudge_renderer(UObject* component);

    [[nodiscard]] float time_dilation();
    bool set_time_dilation(float dilation);

    bool run_command(const char* command);
    [[nodiscard]] float cvar_float(const char* name);
    [[nodiscard]] std::int32_t cvar_int(const char* name);
    [[nodiscard]] bool cvar_bool(const char* name);

    [[nodiscard]] UObject* user_settings();

    bool set_quality(const char* function_name, std::int32_t level);
    bool set_resolution_scale(float scale);
    bool set_frame_limit(float limit);
    bool set_vsync(bool is_enabled);
    bool apply_user_settings();

    bool set_path_tracing(bool is_enabled);
    bool refresh_path_tracing();

    [[nodiscard]] std::int32_t shaders_left();

}
