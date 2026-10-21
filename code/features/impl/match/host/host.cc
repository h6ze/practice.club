#include <features/features.hh>
#include <cstdio>
#include <string>
#include <utility>
#include <features/impl/helpers.hh>

namespace features {

    void host_domain::tick() {
        if (detail::is_host_pass_queued.exchange(true)) return;

        game::dispatch::post([]() {
            match_snapshot fresh = detail::take_snapshot();

            {
                const std::lock_guard<std::mutex> guard(detail::snapshot_lock);
                detail::latest_snapshot = std::move(fresh);
            }

            detail::is_host_pass_queued = false;
        });
    }

    match_snapshot host_domain::snapshot() {
        const std::lock_guard<std::mutex> guard(detail::snapshot_lock);

        return detail::latest_snapshot;
    }

    void host_domain::set_points(int side) {
        const int points = side == 0 ? host_setup.team_a_points : host_setup.team_b_points;

        game::dispatch::post([side, points]() {
            if (!detail::require_host("setting the score")) return;

            detail::say_call(sdk::hw2::set_team_points(side, points),
                std::string("team ") + (side == 0 ? "a" : "b") + " points set to " + std::to_string(points), "SetTeamPoints");
        });
    }

    void host_domain::add_point() {
        const int team = host_setup.team;

        game::dispatch::post([team]() {
            if (!detail::require_host("adding a point")) return;

            detail::say_call(sdk::hw2::add_point(team), "a point added for team " + std::to_string(team), "AddPoints");
        });
    }

    void host_domain::add_round() {
        const int team = host_setup.team;

        game::dispatch::post([team]() {
            if (!detail::require_host("adding a round")) return;

            bool is_game_over = false;
            if (!sdk::hw2::add_round_won(team, is_game_over)) { detail::say_call(false, "", "AddRoundsWon"); return; }

            logger::success("[ host ] a round added for team " + std::to_string(team) + (is_game_over ? " -> the game says that wins it" : ""));
        });
    }

    void host_domain::set_winner() {
        const int team = host_setup.team;

        game::dispatch::post([team]() {
            if (!detail::require_host("picking the winner")) return;

            detail::say_call(sdk::hw2::set_winner(team), "winner set to team " + std::to_string(team), "SetWinnerTeam");
        });
    }

    void host_domain::end_round() {
        const int team = host_setup.team;

        game::dispatch::post([team]() {
            if (!detail::require_host("ending the round")) return;

            detail::say_call(sdk::hw2::end_round(team), "round ended with team " + std::to_string(team) + " as the winner", "EndRound");
        });
    }

    void host_domain::end_game() {
        game::dispatch::post([]() {
            if (!detail::require_host("ending the game")) return;

            detail::say_call(sdk::hw2::end_game(), "game ended", "EndGame");
        });
    }

    void host_domain::reset_scores() {
        game::dispatch::post([]() {
            if (!detail::require_host("resetting the score")) return;

            detail::say_call(sdk::hw2::reset_scores(), "both scores reset", "ResetScores");
        });
    }

    void host_domain::flip_rounds() {
        game::dispatch::post([]() {
            if (!detail::require_host("swapping rounds")) return;

            detail::say_call(sdk::hw2::flip_rounds(), "rounds won swapped between the teams", "FlipRoundsWon");
        });
    }

    void host_domain::set_match_state() {
        const int state = host_setup.match_state;

        game::dispatch::post([state]() {
            if (!detail::require_host("forcing the match state")) return;

            detail::say_call(sdk::hw2::set_match_state(static_cast<std::uint8_t>(state)), "match state set to " + std::to_string(state), "SetMatchState");
        });
    }

    void host_domain::set_round_state() {
        const int state = host_setup.round_state;

        game::dispatch::post([state]() {
            if (!detail::require_host("forcing the round state")) return;

            detail::say_call(sdk::hw2::set_round_state(static_cast<std::uint8_t>(state)), "round state set to " + std::to_string(state), "SetRoundState");
        });
    }

    void host_domain::start_clock() {
        game::dispatch::post([]() {
            if (!detail::require_host("restarting the clock")) return;

            detail::say_call(sdk::hw2::start_match_timer(), "match timer started again", "StartMatchTimer");
        });
    }

    void host_domain::time_out() {
        game::dispatch::post([]() {
            if (!detail::require_host("calling time")) return;

            detail::say_call(sdk::hw2::time_out(), "time out called", "Timeout");
        });
    }

    void host_domain::apply_lobby_size() {
        game::dispatch::post([]() {
            if (!detail::require_host("pushing the lobby size")) return;

            detail::say_call(sdk::hw2::apply_funny_match_settings(), "the dev module's lobby size pushed into the match settings", "ApplyFunnyMatchSettings");
        });
    }

    void host_domain::restart_match() {
        game::dispatch::post([]() {
            if (!detail::require_host("restarting the match")) return;

            detail::say_call(sdk::hw2::restart_game(), "match restarted on the same map", "RestartGame");
        });
    }

    void host_domain::start_match() {
        game::dispatch::post([]() {
            if (!detail::require_host("starting the match")) return;

            detail::say_call(sdk::hw2::start_match(), "match started", "StartMatch");
        });
    }

    void host_domain::end_match() {
        game::dispatch::post([]() {
            if (!detail::require_host("ending the match")) return;

            detail::say_call(sdk::hw2::end_match(), "match ended through the stock game mode", "EndMatch");
        });
    }

    void host_domain::travel() {
        const std::string level = host_setup.travel_level;

        game::dispatch::post([level]() {
            if (level.empty()) { logger::error("[ host ] type a map name first"); return; }
            if (!detail::require_host("changing the map")) return;

            detail::say_call(sdk::hw2::server_travel(level.c_str()), "travelling to " + level, "ServerTravelToMap");
        });
    }

    void host_domain::create_match() {
        const std::string mode = host_setup.match_mode;

        game::dispatch::post([mode]() {
            if (mode.empty()) { logger::error("[ host ] type a game mode name first"); return; }

            detail::say_call(sdk::hw2::create_new_match(mode.c_str()), "asked the game instance for a new " + mode + " match", "CreateNewMatch");
        });
    }

    void host_domain::respawn_target() {
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([target]() {
            if (!detail::require_host("respawning a player")) return;

            sdk::APlayerState* member = detail::chosen_member(target);
            if (!member) return;

            sdk::AController* controller = sdk::hw2::controller_of(member);
            if (!controller) { logger::error("[ host ] " + detail::name_of(member) + " has no controller the host can see"); return; }

            detail::say_call(sdk::hw2::restart_player(controller), detail::name_of(member) + " respawned through the game mode", "RestartPlayer");
        });
    }

    void host_domain::respawn_bot() {
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([target]() {
            if (!detail::require_host("respawning a bot")) return;

            sdk::APlayerState* member = detail::chosen_member(target);
            if (!member) return;

            sdk::AController* controller = sdk::hw2::controller_of(member);
            if (!controller) { logger::error("[ host ] " + detail::name_of(member) + " has no controller the host can see"); return; }

            detail::say_call(sdk::hw2::respawn_bot(controller), detail::name_of(member) + " respawned through the bot manager", "RespawnBot");
        });
    }

    void host_domain::remove_bot() {
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([target]() {
            if (!detail::require_host("removing a bot")) return;

            sdk::APlayerState* member = detail::chosen_member(target);
            if (!member) return;

            if (!sdk::hw2::is_bot(member)) { logger::error("[ host ] " + detail::name_of(member) + " is a human -> kick is a later batch"); return; }

            const std::string name = detail::name_of(member);
            detail::say_call(sdk::hw2::remove_bot(member), name + " removed", "RemoveBot");
        });
    }

    void host_domain::move_target() {
        const std::uintptr_t target = host_setup.target;
        const int team = host_setup.team;

        game::dispatch::post([target, team]() {
            if (!detail::require_host("moving a player")) return;

            sdk::APlayerState* member = detail::chosen_member(target);
            if (!member) return;

            const int before = sdk::hw2::team_of(member);
            if (!sdk::hw2::set_team(member, team)) { detail::say_call(false, "", "SetTeam"); return; }

            logger::success("[ host ] " + detail::name_of(member) + " moved from team " + std::to_string(before)
                + " to " + std::to_string(team) + ", now reads " + std::to_string(sdk::hw2::team_of(member)));
        });
    }

    void host_domain::check_target_team() {
        const std::uintptr_t target = host_setup.target;
        const int team = host_setup.team;

        game::dispatch::post([target, team]() {
            sdk::APlayerState* member = detail::chosen_member(target);
            if (!member) return;

            const bool is_allowed = sdk::hw2::can_join_team(member, team);
            logger::info("[ host ] HW2CanJoinTeam says " + detail::name_of(member) + (is_allowed ? " can" : " cannot")
                + " join team " + std::to_string(team));
        });
    }

    void host_domain::rename_target() {
        const std::uintptr_t target = host_setup.target;
        const std::string name = host_setup.new_name;

        game::dispatch::post([target, name]() {
            if (name.empty()) { logger::error("[ host ] type the new name first"); return; }
            if (!detail::require_host("renaming a player")) return;

            sdk::APlayerState* member = detail::chosen_member(target);
            if (!member) return;

            sdk::AController* controller = sdk::hw2::controller_of(member);
            if (!controller) { logger::error("[ host ] " + detail::name_of(member) + " has no controller the host can see"); return; }

            const std::string before = detail::name_of(member);
            detail::say_call(sdk::hw2::change_name(controller, name.c_str()), before + " renamed to " + name, "ChangeName");
        });
    }

    void host_domain::set_target_stats() {
        const std::uintptr_t target = host_setup.target;
        const host_options chosen = host_setup;

        game::dispatch::post([target, chosen]() {
            if (!detail::require_host("editing the scoreboard")) return;

            sdk::APlayerState* member = detail::chosen_member(target);
            if (!member) return;

            const bool is_set = sdk::hw2::set_kills(member, chosen.kills)
                && sdk::hw2::set_deaths(member, chosen.deaths)
                && sdk::hw2::set_assists(member, chosen.assists)
                && sdk::hw2::set_player_score(member, static_cast<double>(chosen.score));

            char line[160];
            std::snprintf(line, sizeof(line), "%s now %d kills, %d deaths, %d assists, %.0f score", detail::name_of(member).c_str(),
                chosen.kills, chosen.deaths, chosen.assists, static_cast<double>(chosen.score));
            detail::say_call(is_set, line, "SetKills/SetDeaths/SetAssists/SetPlayerScore");
        });
    }

    void host_domain::switch_own_team() {
        game::dispatch::post([]() {
            sdk::APlayerController* controller = detail::own_controller();
            if (!controller) { logger::error("[ host ] no player controller -> join a match first"); return; }

            detail::say_call(sdk::hw2::toggle_team(controller), "team switch requested", "ToggleTeam");
        });
    }

    void host_domain::flip_teams() {
        game::dispatch::post([]() {
            if (!detail::require_host("flipping the teams")) return;

            detail::say_call(sdk::hw2::flip_teams(), "teams flipped", "FlipTeams");
        });
    }

    void host_domain::balance_teams() {
        game::dispatch::post([]() {
            if (!detail::require_host("balancing the teams")) return;

            detail::say_call(sdk::hw2::balance_teams(), "teams balanced", "BalanceTeams");
        });
    }

    void host_domain::add_bots() {
        const int team_a = host_setup.bots_a;
        const int team_b = host_setup.bots_b;

        game::dispatch::post([team_a, team_b]() {
            if (!detail::require_host("adding bots")) return;

            detail::say_call(sdk::hw2::create_bots(team_a, team_b),
                "asked for " + std::to_string(team_a) + " more on team a and " + std::to_string(team_b) + " on team b", "CreateBots");
        });
    }

    void host_domain::add_bots_ffa() {
        const int count = host_setup.bots_ffa;

        game::dispatch::post([count]() {
            if (!detail::require_host("adding bots")) return;

            detail::say_call(sdk::hw2::create_bots_ffa(count), "asked for " + std::to_string(count) + " free for all bots", "CreateBotsFFA");
        });
    }

    void host_domain::remove_one_bot() {
        const int team = host_setup.team;

        game::dispatch::post([team]() {
            if (!detail::require_host("removing a bot")) return;

            detail::say_call(sdk::hw2::remove_one_bot(team), "one bot removed from team " + std::to_string(team), "RemoveOneBotFromTeam");
        });
    }

    void host_domain::remove_all_bots() {
        game::dispatch::post([]() {
            if (!detail::require_host("removing the bots")) return;

            detail::say_call(sdk::hw2::remove_all_bots(), "every bot removed", "RemoveAllBots");
        });
    }

    void host_domain::report() {
        game::dispatch::post([]() {
            const match_snapshot seen = detail::take_snapshot();

            logger::info(std::string("[ host ] ") + (seen.is_host ? "hosting" : "not hosting")
                + (seen.has_match ? "" : ", no match state component"));

            char line[192];
            std::snprintf(line, sizeof(line), "[ host ] score %d -> %d, rounds %d -> %d, winner %d, match state %d, round state %d, clock %.1f, start in %.1f",
                seen.team_a, seen.team_b, seen.rounds_a, seen.rounds_b, seen.winner, seen.match_state, seen.round_state,
                static_cast<double>(seen.clock), seen.time_to_start);
            logger::info(line);

            logger::info("[ host ] " + std::to_string(seen.players.size()) + " players:");
            for (const lobby_entry& entry : seen.players) {
                std::snprintf(line, sizeof(line), "[ host ]   %s -> team %d, %s%s, %d/%d/%d, score %.0f", entry.name.c_str(), entry.team,
                    entry.is_bot ? "bot" : "human", entry.is_local ? " (you)" : "", entry.kills, entry.deaths, entry.assists, entry.score);
                logger::info(line);
            }

            for (const field_board* board : boards::every) {
                int held = 0;
                for (int i = 0; i < board->count; ++i) held += board->state[i].is_held ? 1 : 0;

                logger::info(std::string("[ host ] board ") + board->title + (board->is_found ? " found" : " not found")
                    + ", " + std::to_string(held) + " of " + std::to_string(board->count) + " held");
            }
        });
    }

}
