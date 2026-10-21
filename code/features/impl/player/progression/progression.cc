#include <features/features.hh>
#include <string>
#include <vector>
#include <features/impl/helpers.hh>

namespace features {

    void progression_domain::list_stats() {
        game::dispatch::post([]() {
            sdk::APlayerController* controller = detail::own_controller();
            if (!controller) { logger::error("[ progression ] no player controller -> join a match first"); return; }

            const std::vector<sdk::hw2::stat_entry> stats = sdk::hw2::stats_of(controller);
            if (stats.empty()) { logger::warning("[ progression ] the stats map is empty -> play a round so the game writes one"); return; }

            logger::info("[ progression ] " + std::to_string(stats.size()) + " stat keys:");
            for (const sdk::hw2::stat_entry& entry : stats)
                logger::info("[ progression ]   " + entry.key + " = " + std::to_string(entry.value));
        });
    }

    void progression_domain::raise_every_stat(int value) {
        game::dispatch::post([value]() {
            sdk::APlayerController* controller = detail::own_controller();
            if (!controller) { logger::error("[ progression ] no player controller -> join a match first"); return; }

            const std::vector<sdk::hw2::stat_entry> stats = sdk::hw2::stats_of(controller);
            if (stats.empty()) { logger::warning("[ progression ] no stat keys to raise -> the game writes them as you play"); return; }

            int raised = 0;
            for (const sdk::hw2::stat_entry& entry : stats)
                if (entry.value < value && sdk::hw2::raise_stat_to(controller, entry.key.c_str(), value)) ++raised;

            logger::success("[ progression ] raised " + std::to_string(raised) + " of " + std::to_string(stats.size()) + " stat keys to " + std::to_string(value));
        });
    }

    void progression_domain::list_weapons() {
        game::dispatch::post([]() {
            const std::vector<std::string> names = sdk::hw2::weapon_names();
            if (names.empty()) { logger::error("[ progression ] no weapon names came back from the enum"); return; }

            logger::info("[ progression ] " + std::to_string(names.size()) + " weapons:");
            for (const std::string& weapon : names)
                logger::info("[ progression ]   " + weapon);
        });
    }

    void progression_domain::unlock_every_weapon_stat(int value) {
        game::dispatch::post([value]() {
            sdk::APlayerController* controller = detail::own_controller();
            if (!controller) { logger::error("[ progression ] no player controller -> join a match first"); return; }

            const std::vector<std::string> names = sdk::hw2::weapon_names();
            if (names.empty()) { logger::error("[ progression ] no weapon names came back from the enum"); return; }

            int written = 0;
            for (const std::string& weapon : names)
                for (const char* suffix : tune::weapon_suffixes)
                    if (sdk::hw2::raise_stat_to(controller, (weapon + "|" + suffix).c_str(), value)) ++written;

            sdk::hw2::save_progression(controller);

            logger::success("[ progression ] wrote " + std::to_string(written) + " keys across "
                + std::to_string(names.size()) + " weapons at " + std::to_string(value));
        });
    }

    void progression_domain::set_level(int level) {
        const int wanted = level < tune::level_floor ? tune::level_floor
            : (level > tune::level_ceiling ? tune::level_ceiling : level);

        game::dispatch::post([wanted]() {
            sdk::APlayerState* state = detail::own_state();
            if (!state) { logger::error("[ progression ] no player state -> join a match first"); return; }

            if (!sdk::hw2::call_set_level(state, wanted) && !sdk::hw2::set_level(state, wanted)) {
                logger::error("[ progression ] the level could not be set");
                return;
            }

            logger::success("[ progression ] level set to " + std::to_string(wanted));
        });
    }

    void progression_domain::max_level() {
        game::dispatch::post([]() {
            sdk::APlayerState* state = detail::own_state();
            if (!state) { logger::error("[ progression ] no player state -> join a match first"); return; }

            const int ceiling = sdk::hw2::max_level_of(state);
            if (!sdk::hw2::set_level(state, ceiling > 0 ? ceiling : tune::level_ceiling)) return;

            logger::success("[ progression ] level raised to the game ceiling of " + std::to_string(ceiling));
        });
    }

    void progression_domain::reset_level() {
        set_level(tune::level_floor);
    }

    void progression_domain::grant_experience(int amount) {
        game::dispatch::post([amount]() {
            sdk::APlayerState* state = detail::own_state();
            if (!state) { logger::error("[ progression ] no player state -> join a match first"); return; }

            const int current = sdk::hw2::experience_of(state);
            if (!sdk::hw2::set_experience(state, current + amount)) { logger::error("[ progression ] the experience field could not be written"); return; }

            logger::success("[ progression ] experience " + std::to_string(current) + " -> " + std::to_string(current + amount));
        });
    }

    void progression_domain::apply_unlocks() {
        game::dispatch::post([]() {
            sdk::APlayerController* controller = detail::own_controller();
            if (!controller) { logger::error("[ progression ] no player controller -> join a match first"); return; }

            sdk::APlayerState* state = controller->PlayerState();
            const int level = state ? sdk::hw2::level_of(state) : 0;

            if (!sdk::hw2::apply_unlocks_for_level(controller, level)) { logger::error("[ progression ] CheckUnlocksForLevel did not run"); return; }

            logger::success("[ progression ] unlocks applied for level " + std::to_string(level));
        });
    }

    void progression_domain::save() {
        game::dispatch::post([]() {
            sdk::APlayerController* controller = detail::own_controller();
            if (!controller) { logger::error("[ progression ] no player controller -> join a match first"); return; }

            if (!sdk::hw2::save_progression(controller)) { logger::error("[ progression ] SaveProgression did not run"); return; }

            logger::success("[ progression ] progression saved to its slot");
        });
    }

    void progression_domain::load() {
        game::dispatch::post([]() {
            sdk::APlayerController* controller = detail::own_controller();
            if (!controller) { logger::error("[ progression ] no player controller -> join a match first"); return; }

            if (!sdk::hw2::load_progression(controller)) { logger::error("[ progression ] LoadProgression did not run"); return; }

            logger::success("[ progression ] progression reloaded from its slot");
        });
    }

    void progression_domain::report_unlocks() {
        game::dispatch::post([]() {
            sdk::APlayerController* controller = detail::own_controller();
            if (!controller) { logger::error("[ progression ] no player controller -> join a match first"); return; }

            sdk::APlayerState* state = controller->PlayerState();
            const int level = state ? sdk::hw2::level_of(state) : 0;

            logger::info("[ progression ] level " + std::to_string(level)
                + ", weapon gate at this level is " + (sdk::hw2::is_weapon_unlocked(controller, level) ? "open" : "closed")
                + ", " + std::to_string(sdk::hw2::pending_unlocks(controller)) + " pending");
        });
    }

    void progression_domain::set_stat(const char* key, int value) {
        const std::string wanted = key ? key : "";

        game::dispatch::post([wanted, value]() {
            sdk::APlayerController* controller = detail::own_controller();
            if (!controller) { logger::error("[ progression ] no player controller -> join a match first"); return; }

            if (!sdk::hw2::raise_stat_to(controller, wanted.c_str(), value)) { logger::error("[ progression ] RaiseStatTo did not run"); return; }

            logger::success("[ progression ] stat " + wanted + " raised to " + std::to_string(value));
        });
    }

    void progression_domain::add_stat(const char* key, int amount) {
        const std::string wanted = key ? key : "";

        game::dispatch::post([wanted, amount]() {
            sdk::APlayerController* controller = detail::own_controller();
            if (!controller) { logger::error("[ progression ] no player controller -> join a match first"); return; }

            if (!sdk::hw2::add_stat(controller, wanted.c_str(), amount)) { logger::error("[ progression ] AddStat did not run"); return; }

            logger::success("[ progression ] stat " + wanted + " gained " + std::to_string(amount));
        });
    }

    void progression_domain::fill_level() {
        game::dispatch::post([]() {
            sdk::APlayerState* state = detail::own_state();
            if (!state) { logger::error("[ progression ] no player state -> join a match first"); return; }

            const int needed = sdk::hw2::experience_to_level_of(state);
            if (needed <= 0) { logger::warning("[ progression ] the game has not reported a level threshold yet"); return; }

            if (!sdk::hw2::set_experience(state, needed)) return;

            logger::success("[ progression ] experience filled to the level threshold of " + std::to_string(needed));
        });
    }

    void progression_domain::max_everything() {
        game::dispatch::post([]() {
            sdk::APlayerController* controller = detail::own_controller();
            sdk::APlayerState* state = controller ? controller->PlayerState() : nullptr;
            if (!controller || !state) { logger::error("[ progression ] no player controller - join a match first"); return; }

            const int ceiling = sdk::hw2::max_level_of(state);
            const int wanted = ceiling > 0 ? ceiling : tune::level_ceiling;

            sdk::hw2::call_set_level(state, wanted);
            sdk::hw2::call_set_experience(state, sdk::hw2::experience_to_level_of(state));

            const std::vector<sdk::hw2::stat_entry> stats = sdk::hw2::stats_of(controller);
            for (const sdk::hw2::stat_entry& entry : stats)
                sdk::hw2::raise_stat_to(controller, entry.key.c_str(), tune::stat_ceiling);

            int written = 0;
            for (const std::string& weapon : sdk::hw2::weapon_names())
                for (const char* suffix : tune::weapon_suffixes)
                    if (sdk::hw2::raise_stat_to(controller, (weapon + "|" + suffix).c_str(), tune::stat_ceiling)) ++written;

            sdk::hw2::apply_unlocks_for_level(controller, wanted);
            sdk::hw2::save_progression(controller);

            logger::success("[ progression ] level " + std::to_string(wanted) + ", "
                + std::to_string(stats.size()) + " existing and " + std::to_string(written)
                + " generated stat keys raised, unlocks applied and saved");
        });
    }

}
