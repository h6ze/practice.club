#pragma once
#include <atomic>
#include <chrono>
#include <cstdint>
#include <iterator>
#include <mutex>
#include <string>
#include <vector>
#include <features/data/boards.hh>
#include <features/features.hh>
#include <sdk/core/access.hh>
#include <sdk/hw2/pawn/lens.hh>
#include <sdk/unreal/query/scene.hh>
#include <sdk/offsets.generated.hh>
#include <client/diag/log/logger.hh>
#include <features/impl/combat/weapons/arsenal.hh>

namespace features::detail {

    inline std::mutex world_lock;
    inline scenery_snapshot latest_world;
    inline std::atomic<bool> is_world_pass_queued{ false };
    inline std::chrono::steady_clock::time_point world_watched_until;
    inline std::chrono::steady_clock::time_point next_world_refresh;
    inline constexpr std::chrono::milliseconds world_refresh_every{ 500 };
    inline constexpr std::chrono::seconds world_watch_window{ 1 };

    inline constexpr int light_cap = 4096;

    struct light_original {
        sdk::UObject* component = nullptr;
        std::int32_t index = -1;
        float intensity = 0.0f;
        bool is_casting = false;
    };

    inline std::vector<light_original> light_originals;

    struct volume_original {
        sdk::AActor* volume = nullptr;
        std::int32_t index = -1;
        bool is_enabled = false;
    };

    inline std::vector<volume_original> volume_originals;

    [[nodiscard]] inline bool is_still_there(const sdk::UObject* object, std::int32_t index) {
        return object && index >= 0 && sdk::objects::at(index) == object;
    }

    [[nodiscard]] inline light_original* held_light(const sdk::UObject* component) {
        for (light_original& held : light_originals)
            if (held.component == component) return &held;

        return nullptr;
    }

    [[nodiscard]] inline volume_original* held_volume(const sdk::AActor* volume) {
        for (volume_original& held : volume_originals)
            if (held.volume == volume) return &held;

        return nullptr;
    }

    inline void restore_lights() {
        namespace light = sdk::offsets::ulight_base;

        for (const light_original& held : light_originals) {
            if (!is_still_there(held.component, held.index)) continue;

            sdk::mem::write<float>(held.component, light::intensity, held.intensity);
            sdk::mem::write_bit(held.component, light::cast_shadows, light::cast_shadows_bit, held.is_casting);
        }

        light_originals.clear();
    }

    inline void restore_volumes() {
        namespace volume = sdk::offsets::apost_process_volume;

        for (const volume_original& held : volume_originals) {
            if (!is_still_there(held.volume, held.index)) continue;

            sdk::mem::write_bit(held.volume, volume::is_enabled, volume::is_enabled_bit, held.is_enabled);
        }

        volume_originals.clear();
    }

    [[nodiscard]] inline sdk::UObject* own_camera() { return sdk::hw2::camera_of(own_character()); }

    [[nodiscard]] inline bool takes_nudge(board_target target) {
        switch (target) {
        case board_target::level_fog:
        case board_target::sky_light:
        case board_target::sun_light:
        case board_target::sky_atmosphere:
        case board_target::volumetric_clouds:
        case board_target::local_fog:
        case board_target::wind_source: return true;
        default: return false;
        }
    }

    [[nodiscard]] inline double board_mark(const field_board& board) {
        double mark = 0.0;

        for (int i = 0; i < board.count; ++i) {
            if (!board.state[i].is_held) continue;

            mark += board.state[i].value * (i + 1) + (i + 1);
        }

        return mark;
    }

    struct nudge_state {
        const void* object = nullptr;
        double mark = 0.0;
    };

    inline nudge_state nudges[std::size(boards::world_boards)];

    [[nodiscard]] inline bool is_any_world_board_held() {
        for (const field_board* board : boards::world_boards)
            for (int i = 0; i < board->count; ++i)
                if (board->state[i].is_held) return true;

        return false;
    }

    inline void refresh_scenery_snapshot() {
        const bool has_world = sdk::scene::settings() != nullptr;
        const float dilation = sdk::scene::time_dilation();
        const int lights = static_cast<int>(sdk::scene::light_components().size());
        const int shaders = sdk::scene::shaders_left();
        const int volumes = sdk::scene::count_of("PostProcessVolume");

        const std::lock_guard<std::mutex> guard(world_lock);

        latest_world.has_world = has_world;
        latest_world.dilation = dilation;
        latest_world.lights = lights;
        latest_world.post_volumes = volumes;
        latest_world.shaders_left = shaders;
    }

    inline void say_world(bool is_done, const std::string& done, const char* what) {
        if (is_done) { logger::success("[ world ] " + done); return; }

        logger::error(std::string("[ world ] ") + what + " did not go out -> the call could not be made, or the engine refused it");
    }

}
