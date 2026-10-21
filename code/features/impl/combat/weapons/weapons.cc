#include <features/features.hh>
#include <string>
#include <sdk/unreal/runtime/stage.hh>
#include <features/impl/helpers.hh>

namespace features {

    void weapons_domain::tick() {
        if (detail::is_weapon_pass_queued.exchange(true)) return;

        game::dispatch::post([this]() {
            if (game::stage() != game::loading_stage::in_game) { detail::is_weapon_pass_queued = false; return; }

            detail::forget_stale();
            detail::refresh_sweep();
            detail::refresh_aim_status();

            aim.guard();
            aim.limits();
            aim.aimbot();
            aim.silent();
            aim.wallbang();
            aim.teleport();

            tune_stats();
            rechamber();
            auto_fire();
            bot_damage();
            ammo();
            recolor();
            bullet_drop();
            throwables();

            detail::is_weapon_pass_queued = false;
        });
    }

    void weapons_domain::tune_stats() {
        for (sdk::AActor* weapon : detail::own_weapons())
            static_cast<void>(detail::original_stats(sdk::hw2::settings_of(weapon)));

        const bool is_interval = detail::is_fire_rate_an_interval();

        for (auto entry = detail::stats_originals.begin(); entry != detail::stats_originals.end();) {
            if (!detail::is_same_object(entry->first, entry->second.index)) {
                entry = detail::stats_originals.erase(entry);
                continue;
            }

            sdk::hw2::write_stats(entry->first, detail::tuned_stats(entry->second.stats, is_interval));
            ++entry;
        }
    }

    void weapons_domain::rechamber() {
        if (!weapon_setup.is_rapid_fire) return;

        for (sdk::AActor* weapon : detail::own_weapons()) {
            if (sdk::hw2::needs_pump_of(weapon)) sdk::hw2::set_needs_pump(weapon, false);
            if (sdk::hw2::bolt_cycling_of(weapon)) sdk::hw2::set_bolt_cycling(weapon, false);
        }

        sdk::APawn* pawn = detail::own_character();
        if (pawn && !sdk::hw2::can_shoot_of(pawn)) sdk::hw2::set_can_shoot(pawn, true);
    }

    void weapons_domain::auto_fire() {
        const weapon_options& options = weapon_setup;

        if (!options.is_auto_fire) { detail::auto_fire_cadence.forget(); return; }

        sdk::APawn* pawn = detail::own_character();
        if (!pawn || !sdk::hw2::wants_to_fire_of(pawn)) { detail::auto_fire_cadence.forget(); return; }

        sdk::AActor* weapon = detail::held_weapon_of(pawn);
        sdk::UObject* settings = sdk::hw2::settings_of(weapon);
        if (!settings) { detail::auto_fire_cadence.forget(); return; }

        const int shots = detail::auto_fire_cadence.owed_shots(options.auto_fire_rate);
        if (shots <= 0) return;

        const bool is_hit_scan = sdk::hw2::hit_scan_of(settings);
        const double spread = static_cast<double>(options.auto_fire_spread);

        for (int shot = 0; shot < shots; ++shot)
            if (!sdk::hw2::fire_shot(weapon, pawn, is_hit_scan, spread)) break;
    }

    void weapons_domain::bot_damage() {
        const weapon_options& options = weapon_setup;

        for (sdk::AActor* weapon : detail::sweep.other_guns) {
            const detail::gun_original* original = detail::original_gun(weapon);
            if (!original) continue;

            const double wanted = options.is_bot_damage ? original->bot_damage * options.bot_damage : original->bot_damage;
            if (sdk::hw2::bot_damage_of(weapon) != wanted) sdk::hw2::set_bot_damage(weapon, wanted);
        }
    }

    void weapons_domain::ammo() {
        const weapon_options& options = weapon_setup;

        for (sdk::AActor* weapon : detail::own_weapons()) {
            const detail::gun_original* original = detail::original_gun(weapon);
            if (!original) continue;

            const int magazine = options.is_mag_size ? options.mag_size : original->ammo_per_mag;
            if (sdk::hw2::ammo_per_mag_of(weapon) != magazine) sdk::hw2::set_ammo_per_mag(weapon, magazine);

            if (options.is_infinite_ammo && sdk::hw2::current_ammo_of(weapon) < magazine) sdk::hw2::set_current_ammo(weapon, magazine);
        }
    }

    void weapons_domain::recolor() {
        const weapon_options& options = weapon_setup;

        const detail::skin_colors wanted = detail::wanted_colors();
        const sdk::FLinearColor color_a = wanted.a;
        const sdk::FLinearColor color_b = wanted.b;

        for (sdk::AActor* weapon : detail::own_weapons()) {
            detail::gun_original* original = detail::original_gun(weapon);
            if (!original) continue;

            if (options.is_recolor) {
                const bool is_current = sdk::hw2::skin_color_a_of(weapon) == color_a && sdk::hw2::skin_color_b_of(weapon) == color_b;
                if (original->is_painted && is_current) continue;

                original->is_painted = sdk::hw2::apply_skin_colors(weapon, color_a, color_b);
                continue;
            }

            if (!original->is_painted) continue;

            sdk::hw2::apply_skin_colors(weapon, original->color_a, original->color_b);
            original->is_painted = false;
        }
    }

    void weapons_domain::bullet_drop() {
        if (!weapon_setup.is_no_drop) return;

        for (sdk::AActor* bullet : detail::sweep.bullets)
            sdk::hw2::set_bullet_drop(bullet, 0.0);
    }

    void weapons_domain::throwables() {
        const throwable_options& options = throwable_setup;
        if (!options.is_enabled) return;

        for (const detail::thrown_item& item : detail::sweep.throwables) {
            if (detail::is_launched(item.actor)) continue;

            sdk::UObject* projectile = sdk::hw2::projectile_movement_of(item.actor, item.kind);
            if (!projectile) continue;

            const sdk::FVector velocity = sdk::hw2::movement_velocity_of(projectile);
            if (velocity.is_zero()) continue;

            sdk::hw2::set_movement_velocity(projectile, { velocity.X * options.speed, velocity.Y * options.speed, velocity.Z * options.speed });
            sdk::hw2::set_gravity_scale(projectile, sdk::hw2::gravity_scale_of(projectile) * options.gravity);
            sdk::hw2::set_bounciness(projectile, sdk::hw2::bounciness_of(projectile) * options.bounce);

            detail::launched[item.actor] = item.actor->index();
        }
    }

    void weapons_domain::report() {
        game::dispatch::post([]() {
            const sdk::APawn* pawn = detail::own_pawn();
            if (!pawn) { logger::error("[ weapons ] no pawn -> spawn in first"); return; }

            sdk::AActor* weapon = sdk::hw2::weapon_of(pawn, sdk::hw2::weapon_slot::current);
            sdk::UObject* settings = sdk::hw2::settings_of(weapon);

            const detail::stats_original* original = detail::original_stats(settings);
            sdk::hw2::weapon_stats live;
            if (!original || !sdk::hw2::read_stats(settings, live)) { logger::error("[ weapons ] the gun in hand has no readable settings asset"); return; }

            const sdk::hw2::weapon_stats& base = original->stats;
            const sdk::UClass* type = weapon->klass();

            logger::info("[ weapons ] " + (type ? type->name() : std::string("unknown gun")) + " via " + settings->name() + ", original -> live:");
            logger::info(detail::stat_line("damage", base.damage, live.damage));
            logger::info(detail::stat_line("headshot", base.headshot, live.headshot));
            logger::info(detail::stat_line("fire rate", base.fire_rate, live.fire_rate));
            logger::info(detail::stat_line("burst rate", base.burst_fire_rate, live.burst_fire_rate));
            logger::info(detail::stat_line("vertical min", base.vertical_recoil_min, live.vertical_recoil_min));
            logger::info(detail::stat_line("vertical max", base.vertical_recoil_max, live.vertical_recoil_max));
            logger::info(detail::stat_line("horizontal min", base.horizontal_recoil_min, live.horizontal_recoil_min));
            logger::info(detail::stat_line("horizontal max", base.horizontal_recoil_max, live.horizontal_recoil_max));
            logger::info(detail::stat_line("bullet velocity", base.bullet_velocity, live.bullet_velocity));
            logger::info(detail::stat_line("range", base.range, live.range));
            logger::info(detail::stat_line("falloff floor", base.falloff_min, live.falloff_min));
            logger::info(detail::stat_line("magazine", base.ammo_per_mag, live.ammo_per_mag));
            logger::info(detail::stat_line("pellets", base.projectiles_per_shot, live.projectiles_per_shot));

            logger::info(std::string("[ weapons ]   hitscan ") + (live.is_hit_scan ? "on" : "off")
                + ", client hit reg " + (live.is_client_hit_reg ? "on" : "off")
                + ", shotgun " + (live.is_shotgun ? "yes" : "no"));

            logger::info(std::string("[ weapons ]   fire rate read as ")
                + (detail::is_fire_rate_an_interval() ? "seconds between shots" : "shots per unit of time"));
        });
    }

    void weapons_domain::restore() {
        weapon_setup = weapon_options{};
        throwable_setup = throwable_options{};

        logger::success("[ weapons ] every weapon option reset -> the originals go back on the next pass in a match");
    }

}
