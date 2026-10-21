#include <features/features.hh>
#include <cstdio>
#include <string>
#include <sdk/unreal/view/camera.hh>
#include <sdk/unreal/runtime/stage.hh>
#include <features/impl/helpers.hh>

namespace features {

    void arena_domain::tick() {
        if (!bot_setup.is_hold && !dev_setup.is_hold && !aggro_setup.is_hunt) return;
        if (detail::is_arena_pass_queued.exchange(true)) return;

        game::dispatch::post([]() {
            if (game::stage() != game::loading_stage::in_game) { detail::is_arena_pass_queued = false; return; }

            if (dev_setup.is_hold) sdk::hw2::write_dev_mode(detail::dev_from_options());

            if (bot_setup.is_hold) {
                sdk::hw2::write_bot_tier(bot_setup.tier_slot, detail::tier_from_options());
                sdk::hw2::write_bot_brain(detail::brain_from_options());
            }

            const auto now = std::chrono::steady_clock::now();
            if (aggro_setup.is_hunt && now >= detail::next_hunt && detail::is_hosting()) {
                detail::next_hunt = now + std::chrono::milliseconds(static_cast<int>(aggro_setup.interval * 1000.0f));
                (void)detail::hunt_with_bots(host_setup.target, aggro_setup.is_enemies_only);
            }

            detail::is_arena_pass_queued = false;
        });
    }

    void arena_domain::load_dev() {
        game::dispatch::post([]() {
            if (!detail::saved_dev()) { logger::error("[ arena ] no HW2FunnyModeSettings object -> the dev module is not loaded"); return; }

            sdk::hw2::dev_mode live;
            if (!sdk::hw2::read_dev_mode(live)) { logger::error("[ arena ] the dev settings went away mid read"); return; }

            detail::dev_to_options(live);
            logger::success("[ arena ] dev mode read, the game reports it " + std::string(sdk::hw2::is_dev_mode_active() ? "active" : "inactive"));
        });
    }

    void arena_domain::apply_dev() {
        game::dispatch::post([]() {
            if (!detail::saved_dev()) { logger::error("[ arena ] no HW2FunnyModeSettings object to write"); return; }
            if (!sdk::hw2::write_dev_mode(detail::dev_from_options())) { logger::error("[ arena ] the dev settings write failed"); return; }

            logger::success("[ arena ] dev mode written, the game now reports it " + std::string(sdk::hw2::is_dev_mode_active() ? "active" : "inactive"));
        });
    }

    void arena_domain::load_bots() {
        game::dispatch::post([]() {
            const int tiers = sdk::hw2::bot_tier_count();
            if (tiers <= 0) { logger::error("[ arena ] UHW2BotSettings has no tiers -> load into a match first"); return; }

            if (bot_setup.tier_slot >= tiers) bot_setup.tier_slot = tiers - 1;
            if (bot_setup.tier_slot < 0) bot_setup.tier_slot = 0;

            sdk::hw2::bot_tier live;
            sdk::hw2::bot_brain brain;
            if (!detail::saved_tier(bot_setup.tier_slot) || !detail::saved_brain()) { logger::error("[ arena ] that tier could not be read"); return; }
            if (!sdk::hw2::read_bot_tier(bot_setup.tier_slot, live) || !sdk::hw2::read_bot_brain(brain)) { logger::error("[ arena ] the bot settings went away mid read"); return; }

            detail::tier_to_options(live);
            detail::brain_to_options(brain);

            logger::success("[ arena ] tier " + std::to_string(bot_setup.tier_slot) + " "
                + sdk::hw2::bot_tier_name(bot_setup.tier_slot) + " read, " + std::to_string(tiers) + " in all");
        });
    }

    void arena_domain::apply_bots() {
        game::dispatch::post([]() {
            if (!detail::saved_tier(bot_setup.tier_slot) || !detail::saved_brain()) { logger::error("[ arena ] no bot settings to write -> load into a match first"); return; }

            const bool is_tier = sdk::hw2::write_bot_tier(bot_setup.tier_slot, detail::tier_from_options());
            const bool is_brain = sdk::hw2::write_bot_brain(detail::brain_from_options());
            if (!is_tier || !is_brain) { logger::error("[ arena ] the bot settings write failed"); return; }

            logger::success("[ arena ] tier " + std::to_string(bot_setup.tier_slot) + " written");
        });
    }

    void arena_domain::fire_streak() {
        game::dispatch::post([]() {
            sdk::APawn* pawn = detail::own_character();
            if (!pawn) { logger::error("[ arena ] no pawn -> spawn in first"); return; }

            const sdk::hw2::killstreak streak = static_cast<sdk::hw2::killstreak>(streak_setup.streak_slot);
            if (!sdk::hw2::activate_killstreak(pawn, streak)) {
                logger::error(std::string("[ arena ] the game refused ") + sdk::hw2::killstreak_name(streak) + " -> it may be host only, on cooldown, or not in your loadout");
                return;
            }

            logger::success(std::string("[ arena ] ") + sdk::hw2::killstreak_name(streak) + " activated");
        });
    }

    void arena_domain::fire_streak_slot() {
        game::dispatch::post([]() {
            sdk::APawn* pawn = detail::own_character();
            if (!pawn) { logger::error("[ arena ] no pawn -> spawn in first"); return; }

            if (!sdk::hw2::activate_killstreak_slot(pawn, streak_setup.loadout_slot)) { logger::error("[ arena ] the game refused that loadout slot -> it may be empty???"); return; }

            logger::success("[ arena ] loadout slot " + std::to_string(streak_setup.loadout_slot) + " activated");
        });
    }

    void arena_domain::place_streak() {
        game::dispatch::post([]() {
            sdk::APawn* pawn = detail::own_character();
            if (!pawn) { logger::error("[ arena ] no pawn -> spawn in first"); return; }

            sdk::FVector where;
            if (!detail::streak_point(pawn, where)) { logger::error("[ arena ] no camera this frame -> open the overlay in a match and try again"); return; }

            if (!sdk::hw2::place_killstreak(pawn, where)) { logger::error("[ arena ] the place call could not be made"); return; }

            logger::success("[ arena ] killstreak placed");
        });
    }

    void arena_domain::grant_streaks(bool is_target) {
        const int mask = streak_setup.ready_mask;
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([mask, target, is_target]() {
            sdk::UObject* component = nullptr;
            std::string who = "you";

            if (is_target) {
                if (!detail::require_host("granting someone else streaks")) return;

                sdk::APlayerState* member = detail::chosen_member(target);
                if (!member) return;

                component = sdk::hw2::streak_component_of({ member, sdk::hw2::controller_of(member), member->PawnPrivate() });
                who = detail::name_of(member);
            } else {
                component = detail::own_streaks_now();
            }

            if (!component) { logger::error("[ arena ] no killstreak component on " + who + " - spawn in first"); return; }
            if (!sdk::hw2::restore_killstreaks(component, mask)) { logger::error("[ arena ] HW2RestoreMigratedKillstreaks could not be called"); return; }

            char line[96];
            std::snprintf(line, sizeof(line), "[ arena ] ready mask 0x%02X restored for %s", mask, who.c_str());
            logger::success(line);
        });
    }

    void arena_domain::equip_streaks() {
        const int mask = streak_setup.equip_mask;

        game::dispatch::post([mask]() {
            sdk::UObject* component = detail::own_streaks_now();
            if (!component) { logger::error("[ arena ] no killstreak component on you -> spawn in first"); return; }

            if (!sdk::hw2::set_equipped_streaks(component, static_cast<std::uint8_t>(mask))) { logger::error("[ arena ] ServerSetEquipped could not be called"); return; }

            char line[64];
            std::snprintf(line, sizeof(line), "[ arena ] equipped mask 0x%02X requested", mask);
            logger::success(line);
        });
    }

    void arena_domain::use_streak() {
        const sdk::hw2::killstreak streak = static_cast<sdk::hw2::killstreak>(streak_setup.streak_slot);

        game::dispatch::post([streak]() {
            sdk::UObject* component = detail::own_streaks_now();
            if (!component) { logger::error("[ arena ] no killstreak component on you -> spawn in first"); return; }

            if (!sdk::hw2::use_streak(component, streak)) { logger::error("[ arena ] ServerUse could not be called"); return; }

            logger::success(std::string("[ arena ] ServerUse sent for ") + sdk::hw2::killstreak_name(streak) + " -> the component decides if it is ready");
        });
    }

    void arena_domain::cluster_strike() {
        game::dispatch::post([]() {
            if (!detail::require_host("a cluster strike")) return;

            sdk::APawn* pawn = detail::own_character();
            if (!pawn) { logger::error("[ arena ] no pawn -> spawn in first"); return; }

            sdk::UObject* component = sdk::hw2::old_streaks_of(detail::own_state());
            if (!component) { logger::error("[ arena ] no AC_KillStreak component on your player state"); return; }

            sdk::FVector where;
            if (!detail::streak_point(pawn, where)) { logger::error("[ arena ] no camera this frame -> open the overlay in a match and try again"); return; }

            if (!sdk::hw2::spawn_cluster_strike(component, where)) { logger::error("[ arena ] SpawnClusterStrike could not be called"); return; }

            logger::success("[ arena ] cluster strike called in");
        });
    }

    void arena_domain::set_streak_count() {
        const int count = streak_setup.streak_count;

        game::dispatch::post([count]() {
            sdk::UObject* component = sdk::hw2::old_streaks_of(detail::own_state());
            if (!component) { logger::error("[ arena ] no AC_KillStreak component on your player state"); return; }

            if (!sdk::hw2::set_kill_streak(component, count)) { logger::error("[ arena ] SetKillStreak could not be called"); return; }

            logger::success("[ arena ] kill streak counter set to " + std::to_string(count));
        });
    }

    void arena_domain::team_uav() {
        const double seconds = static_cast<double>(streak_setup.uav_seconds);

        game::dispatch::post([seconds]() {
            if (!detail::require_host("a uav")) return;

            sdk::APlayerState* mine = detail::own_state();
            if (!mine) { logger::error("[ arena ] no player state -> join a match first"); return; }

            const int team = sdk::hw2::team_of(mine);
            if (!sdk::hw2::activate_uav(team, mine, seconds)) { logger::error("[ arena ] ActivateUAV could not be called"); return; }

            logger::success("[ arena ] uav up for team " + std::to_string(team) + " for " + std::to_string(static_cast<int>(seconds)) + "s");
        });
    }

    void arena_domain::drop_protection() {
        const std::uintptr_t target = host_setup.target;

        game::dispatch::post([target]() {
            if (!detail::require_host("dropping spawn protection")) return;

            sdk::APlayerState* member = detail::chosen_member(target);
            if (!member) return;

            sdk::APawn* pawn = member->PawnPrivate();
            if (!pawn || sdk::hw2::kind_of(pawn) != sdk::hw2::actor_kind::character) { logger::error("[ arena ] " + detail::name_of(member) + " is not alive"); return; }

            if (!sdk::hw2::drop_spawn_protection(pawn)) { logger::error("[ arena ] DisableSpawnProtection could not be called"); return; }

            logger::success("[ arena ] spawn protection dropped on " + detail::name_of(member));
        });
    }

    void arena_domain::hunt_once() {
        const std::uintptr_t target = host_setup.target;
        const bool is_enemies_only = aggro_setup.is_enemies_only;

        game::dispatch::post([target, is_enemies_only]() {
            if (!detail::require_host("sending bots after someone")) return;
            if (!detail::chosen_member(target)) return;

            const int told = detail::hunt_with_bots(target, is_enemies_only);
            if (told < 0) { logger::error("[ arena ] that player has no live pawn to hunt"); return; }

            logger::success("[ arena ] " + std::to_string(told) + " bots told the picked player shot them");
        });
    }

    void arena_domain::summons_to_team() {
        const int team = streak_setup.summon_team;

        game::dispatch::post([team]() {
            if (!detail::require_host("moving summoned bots")) return;

            const int moved = sdk::hw2::set_summoned_team(team);
            if (moved == 0) { logger::warning("[ arena ] no summoned homies or bombers are out right now"); return; }

            logger::success("[ arena ] " + std::to_string(moved) + " summoned bots now fight for team " + std::to_string(team));
        });
    }

    void arena_domain::report() {
        game::dispatch::post([]() {
            sdk::hw2::dev_mode mode;
            if (!sdk::hw2::read_dev_mode(mode)) logger::error("[ arena ] no dev settings object");
            else logger::info(std::string("[ arena ] dev mode ") + (mode.is_enabled ? "on" : "off")
                + ", library says " + (sdk::hw2::is_dev_mode_active() ? "active" : "inactive")
                + ", esp " + (mode.is_esp ? "on" : "off")
                + ", team size " + std::to_string(mode.team_size)
                + ", max players " + std::to_string(mode.max_players));

            const int tiers = sdk::hw2::bot_tier_count();
            logger::info("[ arena ] " + std::to_string(tiers) + " bot tiers:");

            for (int index = 0; index < tiers; ++index) {
                sdk::hw2::bot_tier tier;
                if (!sdk::hw2::read_bot_tier(index, tier)) continue;

                char line[192];
                std::snprintf(line, sizeof(line), "[ arena ] %d %s -> turn %.1f, reaction %.2fs, settled error %.2f, spread %.2fx, engage %.0f",
                    index, sdk::hw2::bot_tier_name(index).c_str(), tier.aim_turn_rate, tier.reaction_time,
                    tier.aim_error_settled, tier.spread_multiplier, tier.engage_range);
                logger::info(line);
            }

            sdk::hw2::bot_brain brain;
            if (!sdk::hw2::read_bot_brain(brain)) return;

            char line[192];
            std::snprintf(line, sizeof(line), "[ arena ] brain -> interp %.1f, error interval %.2fs, hearing %.0f, memory %.1fs, perceived aim %s",
                brain.aim_interp_speed, brain.aim_error_interval, brain.hearing_radius, brain.memory_seconds,
                brain.is_perceived_aim ? "on" : "off");
            logger::info(line);
        });
    }

    void arena_domain::restore() {
        game::dispatch::post([]() {
            dev_setup.is_hold = false;
            bot_setup.is_hold = false;

            if (detail::is_dev_saved) sdk::hw2::write_dev_mode(detail::original_dev);
            if (detail::is_brain_saved) sdk::hw2::write_bot_brain(detail::original_brain);

            for (const auto& [index, tier] : detail::original_tiers)
                sdk::hw2::write_bot_tier(index, tier);

            logger::success("[ arena ] dev mode, every touched tier and the bot brain put back as they shipped");
        });
    }

}
