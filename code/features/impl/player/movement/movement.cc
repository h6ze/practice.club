#include <features/features.hh>
#include <string>
#include <sdk/unreal/runtime/stage.hh>
#include <features/impl/helpers.hh>

namespace features {

    void movement_domain::tick() {
        if (detail::is_movement_pass_queued.exchange(true)) return;

        game::dispatch::post([this]() {
            if (game::stage() != game::loading_stage::in_game) { detail::is_movement_pass_queued = false; return; }

            detail::forget_stale_movement();

            tune_movement();
            speeds();
            flight();
            character();
            spin();

            detail::is_movement_pass_queued = false;
        });
    }

    void movement_domain::tune_movement() {
        sdk::APawn* pawn = detail::own_character();
        const detail::movement_original* original = detail::original_movement(pawn);
        if (!original) return;

        sdk::hw2::write_movement(pawn, detail::tuned_movement(original->stats));
    }

    void movement_domain::speeds() {
        const movement_options& options = movement_setup;

        sdk::APawn* pawn = detail::own_character();
        detail::movement_original* original = detail::original_movement(pawn);
        if (!original) return;

        const float walk = detail::scaled_speed(original->walk, sdk::hw2::max_walk_speed_of(pawn), options.is_speed, options.speed);
        const float crouch = detail::scaled_speed(original->crouch, sdk::hw2::max_crouch_speed_of(pawn), options.is_speed, options.speed);
        const float fly = detail::scaled_speed(original->fly, sdk::hw2::max_fly_speed_of(pawn), options.is_fly, options.fly_speed);

        sdk::hw2::set_max_walk_speed(pawn, walk);
        sdk::hw2::set_max_crouch_speed(pawn, crouch);
        sdk::hw2::set_max_fly_speed(pawn, fly);
    }

    void movement_domain::flight() {
        sdk::APawn* pawn = detail::own_character();
        detail::movement_original* original = detail::original_movement(pawn);
        if (!original) return;

        if (movement_setup.is_fly) {
            if (sdk::hw2::movement_mode_of(pawn) != sdk::hw2::movement_mode::flying) sdk::hw2::set_movement_mode(pawn, sdk::hw2::movement_mode::flying);
            if (!sdk::hw2::is_cheat_flying(pawn)) sdk::hw2::set_cheat_flying(pawn, true);

            original->is_flying = true;
            return;
        }

        if (!original->is_flying) return;

        sdk::hw2::set_cheat_flying(pawn, false);
        sdk::hw2::set_movement_mode(pawn, sdk::hw2::movement_mode::falling);
        original->is_flying = false;
    }

    void movement_domain::character() {
        if (!movement_setup.is_endless_sprint) return;

        sdk::APawn* pawn = detail::own_character();
        if (!sdk::hw2::is_sprint_ready(pawn)) sdk::hw2::set_sprint_ready(pawn, true);
    }

    void movement_domain::spin() {
        detail::spin_memory& memory = detail::spin_state;

        sdk::APawn* pawn = detail::own_character();

        if (memory.is_saved && memory.pawn != pawn) memory.forget();

        const bool is_wanted = movement_setup.is_spin && aim_status.is_host;

        if (!is_wanted || !pawn) {
            if (!memory.is_saved) return;

            game::dispatch::watch(nullptr, nullptr);

            const sdk::APlayerController* controller = detail::own_controller();
            if (controller) sdk::hw2::set_body_rotation(memory.pawn, sdk::FRotator{ 0.0, controller->ControlRotation().Yaw, 0.0 });

            sdk::hw2::set_yaw_from_controller(memory.pawn, memory.was_yaw_from_controller);
            sdk::hw2::set_orient_to_movement(memory.pawn, memory.was_orient_to_movement);
            sdk::hw2::set_arm_flags(sdk::hw2::spring_arm_of(memory.pawn), memory.was_arm_on_control, memory.was_arm_inheriting_yaw);
            sdk::hw2::set_camera_on_control(sdk::hw2::camera_of(memory.pawn), memory.was_camera_on_control);

            memory.forget();
            logger::info("[ movement ] spin off, the body follows where you look again");

            return;
        }

        if (!memory.is_saved) {
            memory.pawn = pawn;
            memory.was_yaw_from_controller = sdk::hw2::is_yaw_from_controller(pawn);
            memory.was_orient_to_movement = sdk::hw2::is_orient_to_movement(pawn);

            const sdk::UObject* arm = sdk::hw2::spring_arm_of(pawn);
            memory.was_arm_on_control = sdk::hw2::is_arm_on_control(arm);
            memory.was_arm_inheriting_yaw = sdk::hw2::is_arm_inheriting_yaw(arm);
            memory.was_camera_on_control = sdk::hw2::is_camera_on_control(sdk::hw2::camera_of(pawn));

            const sdk::APlayerController* controller = detail::own_controller();
            memory.yaw = controller ? controller->ControlRotation().Yaw : 0.0;
            memory.is_saved = true;

            detail::take_movement_thunks(pawn);

            logger::success("[ movement ] spin on, wasd follows the camera");
        }

        sdk::hw2::set_yaw_from_controller(pawn, false);
        sdk::hw2::set_orient_to_movement(pawn, false);
        sdk::hw2::set_arm_flags(sdk::hw2::spring_arm_of(pawn), true, false);

        sdk::hw2::set_camera_on_control(sdk::hw2::camera_of(pawn), true);

        const double turned = detail::spin_step(memory, movement_setup.spin_speed);
        if (turned == 0.0) return;

        memory.yaw = std::fmod(memory.yaw + turned, 360.0);
        sdk::hw2::set_body_rotation(pawn, sdk::FRotator{ 0.0, memory.yaw, 0.0 });
    }

    void movement_domain::report() {
        game::dispatch::post([]() {
            sdk::APawn* pawn = detail::own_character();
            const detail::movement_original* original = detail::original_movement(pawn);
            if (!original) { logger::error("[ movement ] no pawn with a readable movement component -> spawn in first"); return; }

            sdk::hw2::movement_stats live;
            if (!sdk::hw2::read_movement(pawn, live)) { logger::error("[ movement ] the movement component went away mid pass"); return; }

            const sdk::hw2::movement_stats& base = original->stats;

            logger::info("[ movement ] original -> live:");
            logger::info(detail::stride_line("walk speed", original->walk.base, sdk::hw2::max_walk_speed_of(pawn)));
            logger::info(detail::stride_line("crouch speed", original->crouch.base, sdk::hw2::max_crouch_speed_of(pawn)));
            logger::info(detail::stride_line("fly speed", original->fly.base, sdk::hw2::max_fly_speed_of(pawn)));
            logger::info(detail::stride_line("acceleration", base.max_acceleration, live.max_acceleration));
            logger::info(detail::stride_line("braking", base.braking_deceleration_walking, live.braking_deceleration_walking));
            logger::info(detail::stride_line("friction", base.ground_friction, live.ground_friction));
            logger::info(detail::stride_line("jump velocity", base.jump_z_velocity, live.jump_z_velocity));
            logger::info(detail::stride_line("jump count", base.jump_max_count, live.jump_max_count));
            logger::info(detail::stride_line("gravity", base.gravity_scale, live.gravity_scale));
            logger::info(detail::stride_line("air control", base.air_control, live.air_control));
            logger::info(detail::stride_line("step height", base.max_step_height, live.max_step_height));
            logger::info(detail::stride_line("floor angle", base.walkable_floor_angle, live.walkable_floor_angle));
            logger::info(detail::stride_line("ads speed extra", base.ads_speed_extra, live.ads_speed_extra));

            const sdk::UWorld* world = sdk::globals::world();
            const bool is_host = world && world->AuthorityGameMode() != nullptr;
            if (is_host) logger::success("[ movement ]   authority is this client");
            else logger::error("[ movement ] authority is the server, not this client");

            logger::info(std::string("[ movement ]   mode ") + sdk::hw2::mode_name(sdk::hw2::movement_mode_of(pawn))
                + ", fall damage " + (live.is_fall_damage ? "on" : "off")
                + ", walks off ledges " + (live.is_walk_off_ledges ? "yes" : "no")
                + ", correction " + (live.is_ignore_correction ? "ignored" : "on"));
        });
    }

    void movement_domain::restore() {
        movement_setup = movement_options{};

        logger::success("[ movement ] every movement option reset -> the originals go back on the next pass in a match");
    }

}
