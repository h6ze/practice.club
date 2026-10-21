#include <features/features.hh>
#include <string>
#include <utility>
#include <features/impl/helpers.hh>

namespace features {

    void career_domain::tick() {
        const auto now = std::chrono::steady_clock::now();

        if (career_setup.is_unlock_held && now >= detail::next_gate_pass) {
            detail::next_gate_pass = now + detail::gate_hold_every;
            const bool is_attachments = career_setup.is_attachments_everywhere;

            game::dispatch::post([is_attachments]() { (void)detail::open_gates(is_attachments); });
        }

        if (now > detail::career_watched_until || now < detail::next_career_refresh) return;
        if (detail::is_career_pass_queued.exchange(true)) return;

        detail::next_career_refresh = now + detail::career_refresh_every;

        game::dispatch::post([]() {
            career_snapshot fresh = detail::take_career_snapshot();

            {
                const std::lock_guard<std::mutex> guard(detail::career_lock);
                detail::latest_career = std::move(fresh);
            }

            detail::is_career_pass_queued = false;
        });
    }

    void career_domain::watch() {
        detail::career_watched_until = std::chrono::steady_clock::now() + detail::career_watch_window;
    }

    career_snapshot career_domain::snapshot() {
        const std::lock_guard<std::mutex> guard(detail::career_lock);

        return detail::latest_career;
    }

    void career_domain::fetch_profile() {
        game::dispatch::post([]() {
            detail::say_career(sdk::hw2::fetch_profile(detail::own_controller()), "cloud profile fetch requested -> the read below refreshes when it lands", "FetchProfile");
        });
    }

    void career_domain::give_exp() {
        const int amount = career_setup.exp_amount;

        game::dispatch::post([amount]() {
            detail::say_career(sdk::hw2::give_exp(detail::own_state(), amount), std::to_string(amount) + " experience through GiveExp", "GiveExp");
        });
    }

    void career_domain::add_experience() {
        const int amount = career_setup.exp_amount;

        game::dispatch::post([amount]() {
            detail::say_career(sdk::hw2::add_experience(detail::own_state(), amount), std::to_string(amount) + " experience through AddExperience", "AddExperience");
        });
    }

    void career_domain::add_score() {
        const double score = career_setup.score_amount;
        const int reason = career_setup.score_reason;

        game::dispatch::post([score, reason]() {
            if (!detail::require_host("adding score")) return;

            detail::say_career(sdk::hw2::add_score(detail::own_state(), score, static_cast<std::uint8_t>(reason)),
                std::to_string(static_cast<int>(score)) + " score added with reason " + std::to_string(reason), "AddScoreToPlayer");
        });
    }

    void career_domain::level_up() {
        game::dispatch::post([]() {
            detail::say_career(sdk::hw2::increase_level(detail::own_state()), "one level up through IncreaseLevel", "IncreaseLevel");
        });
    }

    void career_domain::save_level() {
        game::dispatch::post([]() {
            detail::say_career(sdk::hw2::save_level(detail::own_state()), "level and experience written to the local save", "SaveLevel_Exp");
        });
    }

    void career_domain::load_level() {
        game::dispatch::post([]() {
            detail::say_career(sdk::hw2::load_level(detail::own_state()), "level and experience read back from the local save", "Load_Level_Exp");
        });
    }

    void career_domain::complete_missions() {
        const int index = career_setup.mission_index;

        game::dispatch::post([index]() {
            const int completed = sdk::hw2::complete_missions(detail::own_state(), index);
            if (completed == 0) { logger::error("[ career ] no mission was completed -> the missions component may not be loaded"); return; }

            const bool is_saved = sdk::hw2::save_missions(detail::own_state());
            logger::success("[ career ] " + std::to_string(completed) + " missions completed" + (is_saved ? " and saved" : ", but SaveProgress could not be called"));
        });
    }

    void career_domain::save_missions() {
        game::dispatch::post([]() {
            detail::say_career(sdk::hw2::save_missions(detail::own_state()), "missions saved", "SaveProgress");
        });
    }

    void career_domain::mission_won() {
        const int mode = career_setup.won_mode;

        game::dispatch::post([mode]() {
            detail::say_career(sdk::hw2::missions_game_won(detail::own_state(), static_cast<std::uint8_t>(mode)),
                "a win in game mode " + std::to_string(mode) + " counted toward missions", "GameWon");
        });
    }

    void career_domain::mission_kill() {
        const int weapon_type = career_setup.killed_weapon_type;

        game::dispatch::post([weapon_type]() {
            detail::say_career(sdk::hw2::missions_player_killed(detail::own_state(), static_cast<std::uint8_t>(weapon_type)),
                "a kill with weapon type " + std::to_string(weapon_type) + " counted toward missions", "PlayerKilled");
        });
    }

    void career_domain::match_end() {
        const bool is_won = career_setup.is_won;

        game::dispatch::post([is_won]() {
            detail::say_career(sdk::hw2::notify_match_end(detail::own_controller(), is_won),
                std::string("match end banked as a ") + (is_won ? "win" : "loss"), "NotifyMatchEnd");
        });
    }

    void career_domain::record_kill() {
        const bool is_headshot = career_setup.is_headshot;

        game::dispatch::post([is_headshot]() {
            detail::say_career(sdk::hw2::record_kill(detail::own_controller(), is_headshot),
                std::string("a kill recorded") + (is_headshot ? ", headshot" : ""), "RecordKill");
        });
    }

    void career_domain::local_kill() {
        const std::string kind = career_setup.kill_kind;

        game::dispatch::post([kind]() {
            detail::say_career(sdk::hw2::notify_local_kill(detail::own_controller(), kind.c_str()), "local kill of kind " + kind + " noted", "NotifyLocalKill");
        });
    }

    void career_domain::bump_stat() {
        const std::string suffix = career_setup.stat_suffix;

        game::dispatch::post([suffix]() {
            detail::say_career(sdk::hw2::bump_weapon_stat(detail::own_controller(), suffix.c_str()),
                "the held weapon's " + suffix + " stat bumped through the game's own key", "BumpWeaponStat");
        });
    }

    void career_domain::unlock_all() {
        const bool is_attachments = career_setup.is_attachments_everywhere;

        game::dispatch::post([is_attachments]() {
            const int opened = detail::open_gates(is_attachments);
            logger::success("[ career ] " + std::to_string(opened) + " unlock gates opened on loaded assets, "
                + std::to_string(detail::gate_originals.size()) + " held open in all -> memory only, nothing saved");
        });
    }

    void career_domain::relock_all() {
        career_setup.is_unlock_held = false;

        game::dispatch::post([]() {
            logger::success("[ career ] " + std::to_string(detail::close_gates()) + " unlock gates put back as the game had them");
        });
    }

}
