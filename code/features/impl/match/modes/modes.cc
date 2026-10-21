#include <features/features.hh>
#include <cstdio>
#include <string>
#include <utility>
#include <features/impl/helpers.hh>

namespace features {

    void modes_domain::tick() {
        const auto now = std::chrono::steady_clock::now();
        if (now > detail::modes_watched_until || now < detail::next_modes_refresh) return;
        if (detail::is_modes_pass_queued.exchange(true)) return;

        detail::next_modes_refresh = now + detail::modes_refresh_every;

        game::dispatch::post([]() {
            modes_snapshot fresh = detail::take_modes_snapshot();

            {
                const std::lock_guard<std::mutex> guard(detail::modes_lock);
                detail::latest_modes = std::move(fresh);
            }

            detail::is_modes_pass_queued = false;
        });
    }

    void modes_domain::watch() {
        detail::modes_watched_until = std::chrono::steady_clock::now() + detail::modes_watch_window;
    }

    modes_snapshot modes_domain::snapshot() {
        const std::lock_guard<std::mutex> guard(detail::modes_lock);

        return detail::latest_modes;
    }

    void modes_domain::capture() {
        const std::uintptr_t picked = modes_setup.objective;
        const int state = modes_setup.capture_state;

        game::dispatch::post([picked, state]() {
            if (!detail::require_host("capturing a point")) return;

            detail::say_mode(sdk::hw2::capture_point(detail::picked_objective(picked), static_cast<std::uint8_t>(state)),
                "point set to state " + std::to_string(state), "CapturePoint");
        });
    }

    void modes_domain::secure() {
        const std::uintptr_t picked = modes_setup.objective;

        game::dispatch::post([picked]() {
            if (!detail::require_host("securing a point")) return;

            detail::say_mode(sdk::hw2::secure_point(detail::picked_objective(picked)), "point secured", "SecurePoint");
        });
    }

    void modes_domain::recover() {
        const std::uintptr_t picked = modes_setup.objective;

        game::dispatch::post([picked]() {
            if (!detail::require_host("undoing a capture")) return;

            detail::say_mode(sdk::hw2::recover_point(detail::picked_objective(picked)), "point back to its last state", "RecoverLastState");
        });
    }

    void modes_domain::give_points() {
        const modes_options chosen = modes_setup;

        game::dispatch::post([chosen]() {
            if (!detail::require_host("giving objective points")) return;

            const bool is_given = sdk::hw2::give_objective_points(detail::picked_objective(chosen.objective), chosen.is_points_team,
                chosen.points_score, static_cast<std::uint8_t>(chosen.points_reason));

            detail::say_mode(is_given, std::to_string(static_cast<int>(chosen.points_score)) + " points to team " + (chosen.is_points_team ? "b" : "a"), "Server_GivePoints");
        });
    }

    void modes_domain::set_holder() {
        const bool is_team = modes_setup.is_holder_team;
        const int point = modes_setup.holder_point;

        game::dispatch::post([is_team, point]() {
            if (!detail::require_host("setting a point's holder")) return;

            detail::say_mode(sdk::hw2::set_point_holder(is_team, static_cast<std::uint8_t>(point)),
                "point " + std::to_string(point) + " held by team " + (is_team ? "b" : "a"), "SetCapturePointHolder");
        });
    }

    void modes_domain::plant() {
        const std::uintptr_t picked = modes_setup.objective;
        const bool is_by_picked = modes_setup.is_by_picked;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([picked, is_by_picked, target]() {
            if (!detail::require_host("planting a bomb")) return;

            std::string who;
            sdk::APawn* pawn = detail::acting_pawn(is_by_picked, target, who);
            if (!pawn) { logger::error("[ modes ] " + (who.empty() ? std::string("nobody") : who) + " has no live pawn to plant with"); return; }

            detail::say_mode(sdk::hw2::plant_bomb(detail::picked_objective(picked), pawn), "bomb planted by " + who, "Server_ActivateBomb");
        });
    }

    void modes_domain::disarm() {
        const std::uintptr_t picked = modes_setup.objective;
        const bool is_by_picked = modes_setup.is_by_picked;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([picked, is_by_picked, target]() {
            if (!detail::require_host("disarming a bomb")) return;

            std::string who;
            sdk::APawn* pawn = detail::acting_pawn(is_by_picked, target, who);
            if (!pawn) { logger::error("[ modes ] " + (who.empty() ? std::string("nobody") : who) + " has no live pawn to disarm with"); return; }

            detail::say_mode(sdk::hw2::disarm_bomb(detail::picked_objective(picked), pawn), "bomb disarmed by " + who, "Deactivate_Bomb");
        });
    }

    void modes_domain::explode() {
        const std::uintptr_t picked = modes_setup.objective;

        game::dispatch::post([picked]() {
            if (!detail::require_host("exploding a bomb")) return;

            detail::say_mode(sdk::hw2::explode_bomb(detail::picked_objective(picked)), "bomb exploded", "ExplodeBomb");
        });
    }

    void modes_domain::defuse() {
        const std::uintptr_t picked = modes_setup.objective;

        game::dispatch::post([picked]() {
            if (!detail::require_host("defusing a bomb")) return;

            detail::say_mode(sdk::hw2::defuse_bomb(detail::picked_objective(picked)), "bomb defused", "Defuse_Bomb");
        });
    }

    void modes_domain::give_bomb() {
        const bool is_by_picked = modes_setup.is_by_picked;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([is_by_picked, target]() {
            if (!detail::require_host("handing over the bomb")) return;

            sdk::AActor* bomb = sdk::hw2::snd_bomb();
            if (!bomb) { logger::error("[ modes ] no bomb -> this is not search and destroy"); return; }

            std::string who;
            sdk::APawn* pawn = detail::acting_pawn(is_by_picked, target, who);
            if (!pawn) { logger::error("[ modes ] " + (who.empty() ? std::string("nobody") : who) + " has no live pawn to carry it"); return; }

            detail::say_mode(sdk::hw2::give_bomb(bomb, pawn), who + " now carries the bomb", "AttachToCharacter");
        });
    }

    void modes_domain::drop_bomb() {
        game::dispatch::post([]() {
            if (!detail::require_host("dropping the bomb")) return;

            detail::say_mode(sdk::hw2::drop_bomb(sdk::hw2::snd_bomb()), "bomb dropped", "DropBomb");
        });
    }

    void modes_domain::reset_bomb() {
        game::dispatch::post([]() {
            if (!detail::require_host("resetting the bomb")) return;

            detail::say_mode(sdk::hw2::reset_bomb(sdk::hw2::snd_bomb()), "bomb sent home", "ResetBomb");
        });
    }

    void modes_domain::reset_reinforcements() {
        game::dispatch::post([]() {
            if (!detail::require_host("refilling reinforcements")) return;

            detail::say_mode(sdk::hw2::reset_reinforcements(), "reinforcements refilled", "ResetReinforcements");
        });
    }

    void modes_domain::rush_phase() {
        const int phase = modes_setup.rush_phase;
        const int team = modes_setup.rush_team;

        game::dispatch::post([phase, team]() {
            if (!detail::require_host("switching rush spawns")) return;

            detail::say_mode(sdk::hw2::rush_phase_spawns(phase, team),
                "phase " + std::to_string(phase) + " spawns on for team " + std::to_string(team), "ActivateSpawnsForTheNewPhase");
        });
    }

    void modes_domain::choose_site() {
        game::dispatch::post([]() {
            if (!detail::require_host("re-rolling the site")) return;

            detail::say_mode(sdk::hw2::choose_attack_site(), "attack site re-rolled", "ChooseAttackSiteRandom");
        });
    }

    void modes_domain::pick_sites() {
        game::dispatch::post([]() {
            if (!detail::require_host("picking round sites")) return;

            detail::say_mode(sdk::hw2::pick_round_sites(), "round sites picked again", "PickRoundSites");
        });
    }

    void modes_domain::force_spawn() {
        game::dispatch::post([]() {
            if (!detail::require_host("respawning everyone")) return;

            detail::say_mode(sdk::hw2::force_spawn(), "force spawn run", "ForceSpawn");
        });
    }

    void modes_domain::refresh_rosters() {
        game::dispatch::post([]() {
            if (!detail::require_host("rebuilding rosters")) return;

            detail::say_mode(sdk::hw2::refresh_rosters(), "attacker and defender rosters rebuilt", "RefreshRosters");
        });
    }

    void modes_domain::check_ffa() {
        game::dispatch::post([]() {
            if (!detail::require_host("checking the winner")) return;

            detail::say_mode(sdk::hw2::check_ffa_winner(), "free for all winner check run", "CheckWinnerPoints");
        });
    }

    void modes_domain::spawn_on(bool is_active) {
        const std::uintptr_t picked = modes_setup.spawn;

        game::dispatch::post([picked, is_active]() {
            if (!detail::require_host("switching a spawn point")) return;

            detail::say_mode(sdk::hw2::set_spawn_active(detail::picked_spawn(picked), is_active),
                std::string("spawn point ") + (is_active ? "on" : "off"), "SetActive");
        });
    }

    void modes_domain::spawn_here() {
        const std::uintptr_t picked = modes_setup.spawn;
        const bool is_by_picked = modes_setup.is_by_picked;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([picked, is_by_picked, target]() {
            if (!detail::require_host("spawning someone")) return;

            std::string who;
            sdk::AController* controller = detail::acting_controller(is_by_picked, target, who);
            if (!sdk::lookup::derives_from(controller, "PlayerController")) {
                logger::error("[ modes ] the spawn system only takes a player's controller -> use native spawn for a bot");
                return;
            }

            const sdk::APlayerState* state = controller->PlayerState();
            detail::say_mode(sdk::hw2::spawn_at_point(detail::picked_spawn(picked), static_cast<sdk::APlayerController*>(controller), sdk::hw2::team_of(state)),
                who + " spawned at the picked point", "SpawnPlayer");
        });
    }

    void modes_domain::spawn_native() {
        const std::uintptr_t picked = modes_setup.spawn;
        const bool is_by_picked = modes_setup.is_by_picked;
        const std::uintptr_t target = host_setup.target;
        const int operator_pick = kit_setup.operator_pick;

        game::dispatch::post([picked, is_by_picked, target, operator_pick]() {
            if (!detail::require_host("spawning someone")) return;

            std::string who;
            sdk::AController* controller = detail::acting_controller(is_by_picked, target, who);
            if (!controller) { logger::error("[ modes ] " + (who.empty() ? std::string("nobody") : who) + " has no controller the host can see"); return; }

            sdk::AActor* point = detail::picked_spawn(picked);
            if (!point) { logger::error("[ modes ] pick a spawn point first"); return; }

            const kit_catalog list = detail::catalog_copy();
            const sdk::UObject* operator_info = detail::chosen_object<sdk::UObject>(list.operators, operator_pick);
            if (!operator_info) { logger::error("[ modes ] pick a character on the kit tab -> the pawn class comes from it"); return; }

            detail::say_mode(sdk::hw2::spawn_player_pawn(controller, point, operator_info),
                who + " spawned as " + list.operators[static_cast<size_t>(operator_pick)].name, "HW2SpawnPlayerPawn");
        });
    }

    void modes_domain::preview_spawn() {
        const int team = modes_setup.spawn_team;
        const bool is_ffa = modes_setup.is_ffa_preview;
        const bool is_by_picked = modes_setup.is_by_picked;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([team, is_ffa, is_by_picked, target]() {
            if (!detail::require_host("asking where someone would spawn")) return;

            std::string who;
            sdk::AController* controller = detail::acting_controller(is_by_picked, target, who);

            sdk::AActor* chosen = sdk::hw2::preview_spawn(team, is_ffa, controller);
            if (!chosen) { logger::error("[ modes ] HW2ChooseSpawn gave nothing back"); return; }

            modes_setup.spawn = reinterpret_cast<std::uintptr_t>(chosen);

            const sdk::FVector at = chosen->origin();
            char line[160];
            std::snprintf(line, sizeof(line), "[ modes ] the game would spawn %s at %.0f %.0f %.0f -> now picked", who.c_str(), at.X, at.Y, at.Z);
            logger::success(line);
        });
    }

    void modes_domain::respawn_me(bool is_force) {
        game::dispatch::post([is_force]() {
            sdk::APlayerController* controller = detail::own_controller();
            if (!controller) { logger::error("[ modes ] no player controller -> join a match first"); return; }

            detail::say_mode(sdk::hw2::request_spawn(controller, is_force),
                std::string("respawn requested") + (is_force ? ", forced" : ""), "Spawn");
        });
    }

    void modes_domain::simulate_resume() {
        const modes_options chosen = modes_setup;

        game::dispatch::post([chosen]() {
            if (!detail::require_host("restoring the score and clock")) return;

            detail::say_mode(sdk::hw2::simulate_resume(chosen.resume_clock, chosen.resume_a, chosen.resume_b),
                "DebugSimulateResume sent -> compare the scoreboard, the body may be compiled out of shipping", "DebugSimulateResume");
        });
    }

}
