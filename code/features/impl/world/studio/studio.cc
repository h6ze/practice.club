#include <features/features.hh>
#include <string>
#include <utility>
#include <features/impl/helpers.hh>

namespace features {

    void studio_domain::tick() {
        const auto now = std::chrono::steady_clock::now();

        if (studio_setup.is_auto_highlight && now >= detail::next_highlight_check) {
            detail::next_highlight_check = now + detail::highlight_check_every;
            game::dispatch::post([]() { detail::check_kill_highlight(); });
        }

        if (now > detail::studio_watched_until || now < detail::next_studio_refresh) return;
        if (detail::is_studio_pass_queued.exchange(true)) return;

        detail::next_studio_refresh = now + detail::panel_refresh_every;

        game::dispatch::post([]() {
            studio_snapshot fresh = detail::take_studio_snapshot();

            {
                const std::lock_guard<std::mutex> guard(detail::studio_lock);
                detail::latest_studio = std::move(fresh);
            }

            detail::is_studio_pass_queued = false;
        });
    }

    void studio_domain::watch() {
        detail::studio_watched_until = std::chrono::steady_clock::now() + detail::panel_watch_window;
    }

    studio_snapshot studio_domain::snapshot() {
        const std::lock_guard<std::mutex> guard(detail::studio_lock);

        return detail::latest_studio;
    }

    void studio_domain::cine(const char* function_name) {
        const std::string name = function_name;

        game::dispatch::post([name]() {
            detail::say_studio(sdk::hw2::cine_call(name.c_str()), name + " sent to the capture tool", name.c_str());
        });
    }

    void studio_domain::god_mode(bool is_enabled) {
        game::dispatch::post([is_enabled]() {
            detail::say_studio(sdk::hw2::set_god_mode(is_enabled), std::string("capture god mode ") + (is_enabled ? "on" : "off"), "SetGodMode");
        });
    }

    void studio_domain::replay_record() {
        const std::string name = studio_setup.replay_name;

        game::dispatch::post([name]() {
            detail::highlight_kills = -1;
            detail::say_studio(sdk::hw2::replay_record(name.c_str()), "replay recording as " + name, "StartRecording");
        });
    }

    void studio_domain::replay_stop() {
        game::dispatch::post([]() {
            detail::say_studio(sdk::hw2::replay_call("StopRecording"), "replay recording stopped", "StopRecording");
        });
    }

    void studio_domain::replay_play() {
        const std::string name = studio_setup.replay_name;
        const float start = studio_setup.replay_start;

        game::dispatch::post([name, start]() {
            detail::say_studio(sdk::hw2::replay_play(name.c_str(), start), "playing replay " + name, "PlayReplayFile");
        });
    }

    void studio_domain::replay_highlight() {
        const std::string label = studio_setup.highlight;

        game::dispatch::post([label]() {
            detail::say_studio(sdk::hw2::replay_highlight(label.c_str()), "highlight marked: " + label, "MarkHighlight");
        });
    }

    void studio_domain::replay_jump(int direction) {
        game::dispatch::post([direction]() {
            detail::say_studio(sdk::hw2::replay_jump(direction), direction > 0 ? "to the next highlight" : "to the previous highlight", "JumpToHighlight");
        });
    }

    void studio_domain::replay_follow() {
        const std::string name = studio_setup.follow_name;

        game::dispatch::post([name]() {
            detail::say_studio(sdk::hw2::replay_follow(name.c_str()), "following " + name, "FollowPlayer");
        });
    }

    void studio_domain::replay_clear_highlights() {
        game::dispatch::post([]() {
            detail::say_studio(sdk::hw2::replay_call("ClearHighlights"), "highlights cleared", "ClearHighlights");
        });
    }

    void studio_domain::replay_refresh_list() {
        game::dispatch::post([]() {
            detail::known_replays = sdk::hw2::replay_files();
            logger::success("[ studio ] " + std::to_string(detail::known_replays.size()) + " replays on disk");
        });
    }

    void studio_domain::seek_to() {
        const float seconds = studio_setup.seek_seconds;

        game::dispatch::post([seconds]() {
            detail::say_studio(sdk::hw2::replay_seek_to(detail::own_controller(), seconds), "replay at " + std::to_string(static_cast<int>(seconds)) + "s", "SeekTo");
        });
    }

    void studio_domain::seek(float delta) {
        game::dispatch::post([delta]() {
            detail::say_studio(sdk::hw2::replay_seek(detail::own_controller(), delta), "replay moved " + std::to_string(static_cast<int>(delta)) + "s", "Seek");
        });
    }

    void studio_domain::playback_speed() {
        const float speed = studio_setup.playback_speed;

        game::dispatch::post([speed]() {
            detail::say_studio(sdk::hw2::replay_speed(detail::own_controller(), speed), "playback speed " + std::to_string(speed), "SetPlaybackSpeed");
        });
    }

    void studio_domain::spectator(const char* function_name) {
        const std::string name = function_name;

        game::dispatch::post([name]() {
            detail::say_studio(sdk::hw2::spectator_call(detail::own_controller(), name.c_str()), name + " sent to the replay spectator", name.c_str());
        });
    }

    void studio_domain::try_voice() {
        const int event_id = studio_setup.voice_event;

        game::dispatch::post([event_id]() {
            detail::say_studio(sdk::hw2::try_voice(detail::own_character(), event_id), "voice event " + std::to_string(event_id) + " tried", "TryVoice");
        });
    }

    void studio_domain::voice(const char* function_name) {
        const std::string name = function_name;

        game::dispatch::post([name]() {
            detail::say_studio(sdk::hw2::voice_call(detail::own_character(), name.c_str()), name + " sent to your character's voice", name.c_str());
        });
    }

    void studio_domain::reset_voice() {
        game::dispatch::post([]() {
            detail::say_studio(sdk::hw2::reset_voice(detail::own_controller()), "voice settings back to defaults", "HW2ResetVoiceSettings");
        });
    }

    void studio_domain::aim_assist(bool is_enabled) {
        game::dispatch::post([is_enabled]() {
            if (is_enabled && !aim_status.is_open) { logger::error("[ studio ] aim assist on needs the aim gate open -> host with no other gay men"); return; }

            detail::say_studio(sdk::hw2::set_aim_assist(detail::own_controller(), is_enabled), std::string("aim assist ") + (is_enabled ? "on" : "off"), "HW2SetControllerAimAssist");
        });
    }

    void studio_domain::set_fov() {
        const float fov = studio_setup.fov;

        game::dispatch::post([fov]() {
            detail::say_studio(sdk::hw2::set_input_fov(detail::own_controller(), fov),
                "fov " + std::to_string(static_cast<int>(fov)) + " games own setter -> for past the menus range", "HW2SetFieldOfView");
        });
    }

    void studio_domain::vibration(bool is_enabled) {
        game::dispatch::post([is_enabled]() {
            detail::say_studio(sdk::hw2::set_vibration(detail::own_controller(), is_enabled), std::string("vibration ") + (is_enabled ? "on" : "off"), "HW2SetControllerVibration");
        });
    }

    void studio_domain::reset_controller() {
        game::dispatch::post([]() {
            detail::say_studio(sdk::hw2::reset_controller(detail::own_controller()), "controller settings back to defaults", "HW2ResetControllerSettings");
        });
    }

}
