#include <features/features.hh>
#include <features/impl/helpers.hh>

namespace features {

    void aim_domain::guard() {
        detail::guard_memory& memory = detail::guard_state;

        if (!memory.is_saved) memory.is_saved = sdk::hw2::read_guard(memory.original);
        if (!memory.is_saved) return;

        const bool is_all_off = aim_setup.is_guard_off && aim_status.is_open;
        const bool is_shots_off = weapon_setup.is_rapid_fire && aim_status.is_host;

        if (is_all_off || is_shots_off) {
            sdk::hw2::guard_switches wanted = is_all_off ? sdk::hw2::guard_switches{} : memory.original;
            if (!is_all_off) wanted.is_check_shots = false;

            sdk::hw2::write_guard(wanted);

            if (!memory.is_written) logger::success(is_all_off
                ? "[ aim ] server guard switched off for this hosted match"
                : "[ aim ] guard shot check off for this hosted match, the rest left on");

            memory.is_written = true;
            return;
        }

        if (!memory.is_written) return;

        sdk::hw2::write_guard(memory.original);
        memory.is_written = false;
        logger::info("[ aim ] server guard back to its shipped settings");
    }

    void aim_domain::limits() {
        detail::guard_memory& memory = detail::guard_state;

        if (!memory.is_limits_saved) memory.is_limits_saved = sdk::hw2::read_limits(memory.original_limits);
        if (!memory.is_limits_saved) return;

        if (!guard_setup.is_seeded) detail::seed_guard_options(memory.original_limits);

        if (guard_setup.is_enabled && aim_status.is_host) {
            sdk::hw2::write_limits(detail::wanted_limits());

            if (!memory.is_limits_written) logger::success("[ guard ] tolerances applied for this hosted match");

            memory.is_limits_written = true;
            return;
        }

        if (!memory.is_limits_written) return;

        sdk::hw2::write_limits(memory.original_limits);
        memory.is_limits_written = false;
        logger::info("[ guard ] tolerances back to their shipped values");
    }

    void aim_domain::wallbang() {
        if (!aim_setup.is_wallbang) { detail::wallbang_cadence.forget(); return; }

        sdk::APawn* pawn = detail::own_character();
        if (!pawn || !sdk::hw2::wants_to_fire_of(pawn)) { detail::wallbang_cadence.forget(); return; }

        sdk::AActor* weapon = detail::held_weapon_of(pawn);
        if (!weapon) { detail::wallbang_cadence.forget(); return; }

        const detail::aim_view eye = detail::view_of(detail::own_controller());
        if (!eye.is_valid) { detail::wallbang_cadence.forget(); return; }

        const detail::aim_target target = detail::best_target(eye, aim_setup.wallbang_fov, false);
        if (!target.pawn) return;

        aim_status.has_target = true;

        const int shots = detail::wallbang_cadence.owed_shots(aim_setup.wallbang_rate);
        if (shots <= 0) return;

        const sdk::FVector delta = target.point - eye.location;
        const double distance = delta.length();
        if (distance < 2.0) return;

        const sdk::FVector forward = { delta.X / distance, delta.Y / distance, delta.Z / distance };
        const double push = std::min(static_cast<double>(aim_setup.wallbang_push), distance - 1.0);

        const sdk::FVector start = {
            target.point.X - forward.X * push,
            target.point.Y - forward.Y * push,
            target.point.Z - forward.Z * push,
        };

        for (int shot = 0; shot < shots; ++shot)
            if (!sdk::hw2::fire_shot_from(weapon, pawn, start, forward, 0.0)) break;
    }

    void aim_domain::aimbot() {
        if (!aim_setup.is_aimbot || !aim_status.is_open || !detail::is_aim_key_held()) return;

        sdk::APlayerController* controller = detail::own_controller();
        const detail::aim_view eye = detail::view_of(controller);

        const detail::aim_target target = detail::best_target(eye, aim_setup.fov, aim_setup.is_visible_only);
        if (!target.pawn) return;

        aim_status.has_target = true;

        const sdk::FRotator current = controller->ControlRotation();
        const sdk::FRotator wanted = detail::rotation_to(eye.location, target.point);
        const double step = 1.0 / std::max(1.0f, aim_setup.smooth);

        const sdk::FRotator next = {
            current.Pitch + detail::normalized_axis(wanted.Pitch - current.Pitch) * step,
            current.Yaw + detail::normalized_axis(wanted.Yaw - current.Yaw) * step,
            current.Roll,
        };

        sdk::hw2::set_control_rotation(controller, next);
    }

    void aim_domain::silent() {
        if (!aim_setup.is_silent || !aim_status.is_open || detail::sweep.bullets.empty()) return;

        const detail::aim_view eye = detail::view_of(detail::own_controller());

        const detail::aim_target target = detail::best_target(eye, aim_setup.silent_fov, aim_setup.is_visible_only);
        if (!target.pawn) return;

        aim_status.has_target = true;

        for (sdk::AActor* bullet : detail::sweep.bullets) {
            const sdk::FVector velocity = sdk::hw2::bullet_velocity_of(bullet);
            const double speed = velocity.length();
            if (speed < 1.0) continue;

            const sdk::FVector delta = target.point - bullet->origin();
            const double distance = delta.length();
            if (distance < 1.0) continue;

            const double scale = speed / distance;
            sdk::hw2::set_bullet_velocity(bullet, { delta.X * scale, delta.Y * scale, delta.Z * scale });
            sdk::hw2::set_bullet_drop(bullet, 0.0);
        }
    }

    void aim_domain::teleport() {
        if (!aim_setup.is_bullet_tp || detail::sweep.bullets.empty()) return;

        const detail::aim_view eye = detail::view_of(detail::own_controller());
        if (!eye.is_valid) return;

        const detail::aim_target target = detail::best_target(eye, aim_setup.bullet_tp_fov, false);
        if (!target.pawn) return;

        aim_status.has_target = true;

        for (sdk::AActor* bullet : detail::sweep.bullets) {
            sdk::hw2::set_bullet_drop(bullet, 0.0);
            sdk::hw2::move_bullet(bullet, target.point, aim_setup.is_bullet_tp_hit);
        }
    }

    void aim_domain::circles() {
        if (!aim_status.is_open) return;

        if (aim_setup.is_aimbot && aim_setup.is_aimbot_circle) paint::fov_circle(aim_setup.fov, aim_setup.aimbot_circle);
        if (aim_setup.is_silent && aim_setup.is_silent_circle) paint::fov_circle(aim_setup.silent_fov, aim_setup.silent_circle);
    }

}
