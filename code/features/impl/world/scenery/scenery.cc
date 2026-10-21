#include <features/features.hh>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <features/impl/helpers.hh>

namespace features {

    void scenery_domain::tick() {
        const scenery_options& options = scenery_setup;

        const bool is_sweeping = options.is_light_scale || options.is_no_shadows || options.is_no_post_volumes
            || !detail::light_originals.empty() || !detail::volume_originals.empty();

        const auto now = std::chrono::steady_clock::now();
        const bool is_watched = now <= detail::world_watched_until && now >= detail::next_world_refresh;
        if (!is_sweeping && !is_watched && !detail::is_any_world_board_held()) return;
        if (detail::is_world_pass_queued.exchange(true)) return;

        if (is_watched) detail::next_world_refresh = now + detail::world_refresh_every;

        game::dispatch::post([this, is_watched]() {
            lights();
            post_volumes();
            nudge();

            if (is_watched) detail::refresh_scenery_snapshot();

            detail::is_world_pass_queued = false;
        });
    }

    void scenery_domain::watch() {
        detail::world_watched_until = std::chrono::steady_clock::now() + detail::world_watch_window;
    }

    scenery_snapshot scenery_domain::snapshot() {
        const std::lock_guard<std::mutex> guard(detail::world_lock);

        return detail::latest_world;
    }

    void scenery_domain::lights() {
        namespace light = sdk::offsets::ulight_base;

        const scenery_options& options = scenery_setup;

        detail::light_originals.erase(std::remove_if(detail::light_originals.begin(), detail::light_originals.end(),
            [](const detail::light_original& held) { return !detail::is_still_there(held.component, held.index); }),
            detail::light_originals.end());

        if (!options.is_light_scale && !options.is_no_shadows) { detail::restore_lights(); return; }

        const std::vector<sdk::UObject*> components = sdk::scene::light_components();
        if (components.empty() || static_cast<int>(components.size()) > detail::light_cap) return;

        for (sdk::UObject* component : components) {
            detail::light_original* held = detail::held_light(component);

            if (!held) {
                detail::light_originals.push_back({ component, component->index(),
                    sdk::mem::read<float>(component, light::intensity),
                    sdk::mem::read_bit(component, light::cast_shadows, light::cast_shadows_bit) });

                held = &detail::light_originals.back();
            }

            const float intensity = options.is_light_scale ? held->intensity * options.light_scale : held->intensity;
            if (sdk::mem::read<float>(component, light::intensity) != intensity)
                sdk::scene::set_light_intensity(component, intensity);

            const bool is_casting = options.is_no_shadows ? false : held->is_casting;
            if (sdk::mem::read_bit(component, light::cast_shadows, light::cast_shadows_bit) != is_casting)
                sdk::scene::set_cast_shadows(component, is_casting);
        }
    }

    void scenery_domain::nudge() {
        for (std::size_t i = 0; i < std::size(boards::world_boards); ++i) {
            field_board* board = boards::world_boards[i];
            if (!detail::takes_nudge(board->target) || !board->object) continue;

            detail::nudge_state& last = detail::nudges[i];
            const double mark = detail::board_mark(*board);
            if (last.object == board->object && last.mark == mark) continue;

            last = { board->object, mark };

            sdk::scene::nudge_renderer(static_cast<sdk::UObject*>(const_cast<void*>(board->object)));
        }
    }

    void scenery_domain::post_volumes() {
        namespace volume = sdk::offsets::apost_process_volume;

        detail::volume_originals.erase(std::remove_if(detail::volume_originals.begin(), detail::volume_originals.end(),
            [](const detail::volume_original& held) { return !detail::is_still_there(held.volume, held.index); }),
            detail::volume_originals.end());

        if (!scenery_setup.is_no_post_volumes) { detail::restore_volumes(); return; }

        for (sdk::AActor* actor : sdk::scene::actors_of("PostProcessVolume")) {
            if (!detail::held_volume(actor))
                detail::volume_originals.push_back({ actor, actor->index(),
                    sdk::mem::read_bit(actor, volume::is_enabled, volume::is_enabled_bit) });

            sdk::mem::write_bit(actor, volume::is_enabled, volume::is_enabled_bit, false);
        }
    }

    void scenery_domain::restore() {
        game::dispatch::post([]() {
            detail::restore_lights();
            detail::restore_volumes();

            logger::success("[ world ] every light and post process volume the sweep wrote is back to what it was found with");
        });
    }

    void scenery_domain::set_dilation() {
        const float dilation = scenery_setup.dilation;

        game::dispatch::post([dilation]() {
            detail::say_world(sdk::scene::set_time_dilation(dilation), "time dilation set to " + std::to_string(dilation), "time dilation");
        });
    }

    void scenery_domain::reset_dilation() {
        game::dispatch::post([]() {
            detail::say_world(sdk::scene::set_time_dilation(1.0f), "time dilation back to one", "time dilation");
        });
    }

    void scenery_domain::run_command() {
        const std::string command = scenery_setup.command;
        if (command.empty()) { logger::error("[ world ] nothing typed to send to the console"); return; }

        game::dispatch::post([command]() {
            detail::say_world(sdk::scene::run_command(command.c_str()), command + " sent to the console", command.c_str());
        });
    }

    void scenery_domain::read_cvar() {
        const std::string name = scenery_setup.cvar;
        if (name.empty()) { logger::error("[ world ] no console variable named to read"); return; }

        game::dispatch::post([name]() {
            const float number = sdk::scene::cvar_float(name.c_str());
            const int whole = sdk::scene::cvar_int(name.c_str());
            const bool is_on = sdk::scene::cvar_bool(name.c_str());

            {
                const std::lock_guard<std::mutex> guard(detail::world_lock);

                detail::latest_world.cvar_name = name;
                detail::latest_world.cvar_number = number;
                detail::latest_world.cvar_whole = whole;
                detail::latest_world.is_cvar_on = is_on;
            }

            logger::info("[ world ] " + name + " reads " + std::to_string(number) + " as a float, "
                + std::to_string(whole) + " as an int, " + (is_on ? "on" : "off") + " as a switch");
        });
    }

    void scenery_domain::quality(const char* function_name) {
        const std::string name = function_name;
        const int level = scenery_setup.quality;

        game::dispatch::post([name, level]() {
            detail::say_world(sdk::scene::set_quality(name.c_str(), level), name + " set to " + std::to_string(level), name.c_str());
        });
    }

    void scenery_domain::resolution_scale() {
        const float scale = scenery_setup.resolution_scale;

        game::dispatch::post([scale]() {
            detail::say_world(sdk::scene::set_resolution_scale(scale), "resolution scale set to " + std::to_string(scale), "resolution scale");
        });
    }

    void scenery_domain::frame_limit() {
        const float limit = scenery_setup.frame_limit;

        game::dispatch::post([limit]() {
            detail::say_world(sdk::scene::set_frame_limit(limit), "frame rate limit set to " + std::to_string(limit), "frame rate limit");
        });
    }

    void scenery_domain::vsync(bool is_enabled) {
        game::dispatch::post([is_enabled]() {
            detail::say_world(sdk::scene::set_vsync(is_enabled), is_enabled ? "vsync on" : "vsync off", "vsync");
        });
    }

    void scenery_domain::apply_settings() {
        game::dispatch::post([]() {
            detail::say_world(sdk::scene::apply_user_settings(), "settings applied", "apply settings");
        });
    }

    void scenery_domain::path_tracing(bool is_enabled) {
        game::dispatch::post([is_enabled]() {
            detail::say_world(sdk::scene::set_path_tracing(is_enabled), is_enabled ? "path tracer on" : "path tracer off", "path tracer");
        });
    }

    void scenery_domain::refresh_path_tracing() {
        game::dispatch::post([]() {
            detail::say_world(sdk::scene::refresh_path_tracing(), "path tracer output refreshed", "path tracer refresh");
        });
    }

}
