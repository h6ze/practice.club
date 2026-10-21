#pragma once
#include <cstdint>
#include <imgui/imgui.h>

namespace features::tune {

    inline constexpr ImU32 enemy = IM_COL32(235, 92, 92, 255);
    inline constexpr ImU32 friendly = IM_COL32(104, 176, 255, 255);
    inline constexpr ImU32 downed = IM_COL32(150, 150, 158, 255);

    inline constexpr float head_dot_radius = 2.5f;

    inline constexpr float widest_circle_cone = 89.0f;

    inline constexpr int level_floor = 1;
    inline constexpr int level_ceiling = 9999;
    inline constexpr int stat_ceiling = 100000;

    inline constexpr const char* weapon_suffixes[] = {
        "Kills", "Headshots", "ADS", "NoOptic", "Objective",
        "Longshots", "BestStreak", "Doubles", "Triples",
    };

    inline constexpr int enforce_every_ms = 1000;

    inline constexpr double fire_interval_ceiling = 2.0;

    inline constexpr double auto_fire_gap_ceiling = 0.25;

    inline constexpr int auto_fire_burst_ceiling = 4;

    inline constexpr double spin_gap_ceiling = 0.25;

    inline constexpr float rgb_split = 0.5f;

    inline constexpr double no_falloff_floor = 1.0;

    inline constexpr std::int32_t sane_actor_cap = 200000;

    inline constexpr double units_per_metre = 100.0;

    inline constexpr float steep_slope_angle = 89.0f;

    struct aim_key {
        const char* label;
        int code;
    };

    inline constexpr aim_key aim_keys[] = {
        { "right mouse", 0x02 }, { "left mouse", 0x01 }, { "mouse 4", 0x05 },
        { "mouse 5", 0x06 }, { "shift", 0x10 }, { "alt", 0x12 },
    };

    struct aim_bone {
        const char* label;
        const char* socket;
        double fallback_lift;
    };

    inline constexpr aim_bone aim_bones[] = {
        { "head", "head", 70.0 },
        { "chest", "spine_03", 30.0 },
    };

    struct console_preset {
        const char* label;
        const char* command;
    };

    inline constexpr console_preset console_presets[] = {
        { "fog off", "r.Fog 0" },
        { "fog on", "r.Fog 1" },
        { "volumetric fog off", "r.VolumetricFog 0" },
        { "clouds off", "r.VolumetricCloud 0" },
        { "shadows off", "r.ShadowQuality 0" },
        { "shadows back", "r.ShadowQuality 5" },
        { "post materials off", "r.PostProcessing.DisableMaterials 1" },
        { "bloom off", "r.BloomQuality 0" },
        { "motion blur off", "r.MotionBlurQuality 0" },
        { "ambient occlusion off", "r.AmbientOcclusionLevels 0" },
        { "lumen reflections off", "r.Lumen.Reflections 0" },
        { "lumen gi off", "r.Lumen.DiffuseIndirect.Allow 0" },
        { "depth of field off", "r.DepthOfFieldQuality 0" },
        { "lens flare off", "r.LensFlareQuality 0" },
        { "anti aliasing off", "r.AntiAliasingMethod 0" },
        { "wireframe", "showflag.wireframe 1" },
        { "wireframe off", "showflag.wireframe 0" },
        { "unlit", "showflag.lighting 0" },
        { "lit", "showflag.lighting 1" },
    };

    struct quality_setter {
        const char* label;
        const char* function_name;
    };

    inline constexpr quality_setter quality_setters[] = {
        { "overall", "SetOverallScalabilityLevel" },
        { "shadows", "SetShadowQuality" },
        { "post process", "SetPostProcessingQuality" },
        { "view distance", "SetViewDistanceQuality" },
        { "textures", "SetTextureQuality" },
        { "effects", "SetVisualEffectQuality" },
        { "global illumination", "SetGlobalIlluminationQuality" },
        { "reflections", "SetReflectionQuality" },
        { "shading", "SetShadingQuality" },
        { "anti aliasing", "SetAntiAliasingQuality" },
        { "foliage", "SetFoliageQuality" },
        { "landscape", "SetLandscapeQuality" },
    };

}
