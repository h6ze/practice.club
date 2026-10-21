#include "scene.hh"
#include <algorithm>
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/core/container.hh>
#include <sdk/offsets.generated.hh>
#include <sdk/globals.hh>
#include "lookup.hh"
#include <sdk/unreal/runtime/strings.hh>

namespace sdk::scene::detail {

    inline lookup::held gameplay_statics;
    inline lookup::held system_library;
    inline lookup::held rendering_library;
    inline lookup::held user_settings_class;

    constexpr std::int32_t sane_actor_cap = 200000;

    [[nodiscard]] inline UObject* world_context() { return globals::world(); }

    [[nodiscard]] inline bool name_into(call::invocation& entry, const char* name) {
        if (!name || !name[0]) return false;

        const FString text = strings::make(name);
        if (!text.Data) return false;

        entry.set<FString>(offsets::params::cvar_float::variable_name, text);

        return entry.fire();
    }

}

sdk::AActor* sdk::scene::settings() {
    const UWorld* world = globals::world();
    if (!world) return nullptr;

    return mem::pointer<AActor>(world->PersistentLevel(), offsets::ulevel::world_settings);
}

std::vector<sdk::AActor*> sdk::scene::actors_of(const char* class_name) {
    std::vector<AActor*> found;

    const UWorld* world = globals::world();
    if (!world || !class_name) return found;

    const TArray<AActor*> actors = world->level_actors();
    const std::int32_t total = actors.num();
    if (!actors.Data || total <= 0 || total > detail::sane_actor_cap) return found;

    for (std::int32_t i = 0; i < total; ++i) {
        AActor* actor = mem::read<AActor*>(actors.Data, static_cast<std::uint32_t>(i) * sizeof(void*), nullptr);
        if (lookup::derives_from(actor, class_name)) found.push_back(actor);
    }

    return found;
}

int sdk::scene::count_of(const char* class_name) {
    return static_cast<int>(actors_of(class_name).size());
}

sdk::AActor* sdk::scene::actor_of(const char* class_name, int element, int& count) {
    const std::vector<AActor*> actors = actors_of(class_name);

    count = static_cast<int>(actors.size());
    if (actors.empty()) return nullptr;

    return actors[static_cast<std::size_t>(std::clamp(element, 0, count - 1))];
}

sdk::UObject* sdk::scene::component_of(const char* class_name, std::uint32_t component_offset, int element, int& count) {
    return mem::pointer<UObject>(actor_of(class_name, element, count), component_offset);
}

std::vector<sdk::UObject*> sdk::scene::light_components() {
    std::vector<UObject*> components;

    for (const AActor* light : actors_of("Light")) {
        UObject* component = mem::pointer<UObject>(light, offsets::alight::light_component);
        if (component) components.push_back(component);
    }

    return components;
}

bool sdk::scene::set_light_intensity(UObject* component, float intensity) {
    return call::fire_with<float>(component, "SetIntensity", offsets::params::set_light_intensity::intensity, intensity);
}

bool sdk::scene::set_cast_shadows(UObject* component, bool is_casting) {
    return call::fire_with<bool>(component, "SetCastShadows", offsets::params::set_cast_shadows::is_casting, is_casting);
}

bool sdk::scene::set_visibility(UObject* component, bool is_visible) {
    namespace frame = offsets::params::set_visibility;

    call::invocation entry(component, "SetVisibility");
    if (!entry.is_valid()) return false;

    entry.set<bool>(frame::is_visible, is_visible);
    entry.set<bool>(frame::is_propagated, false);

    return entry.fire();
}

bool sdk::scene::nudge_renderer(UObject* component) {
    namespace scene_component = offsets::uscene_component;

    if (!component) return false;

    const bool was_visible = mem::read_bit(component, scene_component::visible, scene_component::visible_bit);

    return set_visibility(component, !was_visible) && set_visibility(component, was_visible);
}

float sdk::scene::time_dilation() {
    namespace frame = offsets::params::get_global_time_dilation;

    call::invocation entry(lookup::class_default(detail::gameplay_statics, "GameplayStatics"), "GetGlobalTimeDilation");
    if (!entry.is_valid()) return 0.0f;

    entry.set<const UObject*>(frame::context, detail::world_context());
    if (!entry.fire()) return 0.0f;

    return entry.get<float>(frame::return_value);
}

bool sdk::scene::set_time_dilation(float dilation) {
    namespace frame = offsets::params::set_global_time_dilation;

    call::invocation entry(lookup::class_default(detail::gameplay_statics, "GameplayStatics"), "SetGlobalTimeDilation");
    if (!entry.is_valid()) return false;

    entry.set<const UObject*>(frame::context, detail::world_context());
    entry.set<float>(frame::time_dilation, dilation);

    return entry.fire();
}

bool sdk::scene::run_command(const char* command) {
    namespace frame = offsets::params::console_command;

    if (!command || !command[0]) return false;

    const FString text = strings::make(command);
    if (!text.Data) return false;

    call::invocation entry(lookup::class_default(detail::system_library, "KismetSystemLibrary"), "ExecuteConsoleCommand");
    if (!entry.is_valid()) return false;

    entry.set<const UObject*>(frame::context, detail::world_context());
    entry.set<FString>(frame::command, text);
    entry.set<APlayerController*>(frame::specific_player, nullptr);

    return entry.fire();
}

float sdk::scene::cvar_float(const char* name) {
    call::invocation entry(lookup::class_default(detail::system_library, "KismetSystemLibrary"), "GetConsoleVariableFloatValue");
    if (!entry.is_valid() || !detail::name_into(entry, name)) return 0.0f;

    return entry.get<float>(offsets::params::cvar_float::return_value);
}

std::int32_t sdk::scene::cvar_int(const char* name) {
    call::invocation entry(lookup::class_default(detail::system_library, "KismetSystemLibrary"), "GetConsoleVariableIntValue");
    if (!entry.is_valid() || !detail::name_into(entry, name)) return 0;

    return entry.get<std::int32_t>(offsets::params::cvar_int::return_value);
}

bool sdk::scene::cvar_bool(const char* name) {
    call::invocation entry(lookup::class_default(detail::system_library, "KismetSystemLibrary"), "GetConsoleVariableBoolValue");
    if (!entry.is_valid() || !detail::name_into(entry, name)) return false;

    return entry.get<bool>(offsets::params::cvar_bool::return_value);
}

sdk::UObject* sdk::scene::user_settings() {
    call::invocation entry(lookup::class_default(detail::user_settings_class, "GameUserSettings"), "GetGameUserSettings");
    if (!entry.is_valid() || !entry.fire()) return nullptr;

    return entry.get<UObject*>(offsets::params::get_user_settings::return_value);
}

bool sdk::scene::set_quality(const char* function_name, std::int32_t level) {
    return call::fire_with<std::int32_t>(user_settings(), function_name, offsets::params::user_quality::value, level);
}

bool sdk::scene::set_resolution_scale(float scale) {
    return call::fire_with<float>(user_settings(), "SetResolutionScaleNormalized", offsets::params::user_resolution_scale::scale, scale);
}

bool sdk::scene::set_frame_limit(float limit) {
    return call::fire_with<float>(user_settings(), "SetFrameRateLimit", offsets::params::user_frame_limit::limit, limit);
}

bool sdk::scene::set_vsync(bool is_enabled) {
    return call::fire_with<bool>(user_settings(), "SetVSyncEnabled", offsets::params::user_vsync::is_enabled, is_enabled);
}

bool sdk::scene::apply_user_settings() {
    return call::fire_with<bool>(user_settings(), "ApplySettings", offsets::params::user_apply::is_command_line_checked, false);
}

bool sdk::scene::set_path_tracing(bool is_enabled) {
    return call::fire_with<bool>(lookup::class_default(detail::rendering_library, "KismetRenderingLibrary"), "EnablePathTracing",
        offsets::params::enable_path_tracing::is_enabled, is_enabled);
}

bool sdk::scene::refresh_path_tracing() {
    return call::fire(lookup::class_default(detail::rendering_library, "KismetRenderingLibrary"), "RefreshPathTracingOutput");
}

std::int32_t sdk::scene::shaders_left() {
    call::invocation entry(lookup::class_default(detail::rendering_library, "KismetRenderingLibrary"), "NumPrecompilingPSOsRemaining");
    if (!entry.is_valid() || !entry.fire()) return 0;

    return entry.get<std::int32_t>(offsets::params::psos_remaining::return_value);
}
