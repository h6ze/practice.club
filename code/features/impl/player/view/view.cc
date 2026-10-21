#include <features/features.hh>
#include <string>
#include <sdk/unreal/runtime/stage.hh>
#include <features/impl/helpers.hh>

namespace features {

    void view_domain::tick() {
        if (detail::is_view_pass_queued.exchange(true)) return;

        game::dispatch::post([this]() {
            if (game::stage() != game::loading_stage::in_game) { detail::is_view_pass_queued = false; return; }

            detail::forget_stale_view();

            tune_view();
            field_of_view();
            settings();
            steady();

            detail::is_view_pass_queued = false;
        });
    }

    void view_domain::tune_view() {
        const view_options& options = view_setup;

        sdk::APawn* pawn = detail::own_character();
        detail::view_original* original = detail::original_view(pawn);
        if (!original) return;

        sdk::hw2::write_view(pawn, detail::tuned_view(original->stats));

        sdk::hw2::set_default_fov(pawn, detail::held_fov(original->default_fov, sdk::hw2::default_fov_of(pawn), options.is_fov, options.fov));

        sdk::hw2::set_current_fov(pawn, detail::held_fov(original->current_fov, sdk::hw2::current_fov_of(pawn), options.is_fov, options.fov));
    }

    void view_domain::field_of_view() {
        const view_options& options = view_setup;

        sdk::UObject* subsystem = detail::input_subsystem();
        if (!subsystem) return;

        const float live = sdk::hw2::input_fov_of(subsystem);
        if (live <= 0.0f) return;

        sdk::hw2::set_input_fov(subsystem, static_cast<float>(detail::held_fov(detail::held_input_fov, live, options.is_fov, options.fov)));
    }

    void view_domain::settings() {
        const view_options& options = view_setup;

        sdk::APlayerController* controller = detail::own_controller();
        detail::view_settings_original* original = detail::original_view_settings(sdk::hw2::view_settings_of(controller));
        if (!original) return;

        sdk::hw2::set_settings_fov(controller, detail::held_fov(original->fov, sdk::hw2::settings_fov_of(controller), options.is_fov, options.fov));

        if (options.is_third_person) {
            if (!sdk::hw2::is_third_person(controller)) {
                sdk::hw2::set_third_person(controller, true);
                sdk::hw2::update_perspective(detail::own_character());
            }

            original->is_tpp_forced = true;
            return;
        }

        if (!original->is_tpp_forced) return;

        sdk::hw2::set_third_person(controller, original->is_tpp);
        sdk::hw2::update_perspective(detail::own_character());
        original->is_tpp_forced = false;
    }

    void view_domain::steady() {
        const view_options& options = view_setup;

        sdk::APawn* pawn = detail::own_character();
        if (!pawn) return;

        if (options.is_no_recoil) sdk::hw2::clear_view_recoil(pawn);
        if (options.is_fixed_ads_fov) sdk::hw2::set_target_fov(pawn, options.ads_fov);
        if (options.is_no_spread) sdk::hw2::set_target_spread(pawn, 0.0);
        if (options.is_clean_screen) sdk::hw2::set_saturation(pawn, options.saturation);
        if (options.is_hold_breath) sdk::hw2::set_hold_breath(pawn, options.hold_breath);
        if (options.is_lean) sdk::hw2::set_leaning(pawn, options.lean);
    }

    void view_domain::report() {
        game::dispatch::post([]() {
            sdk::APawn* pawn = detail::own_character();
            const detail::view_original* original = detail::original_view(pawn);
            if (!original) { logger::error("[ view ] no pawn with a readable camera -> spawn in first"); return; }

            sdk::hw2::view_stats live;
            if (!sdk::hw2::read_view(pawn, live)) { logger::error("[ view ] the camera or the spring arm went away mid pass"); return; }

            sdk::APlayerController* controller = detail::own_controller();
            const detail::view_settings_original* settings = detail::original_view_settings(sdk::hw2::view_settings_of(controller));
            const sdk::hw2::view_stats& base = original->stats;

            logger::info("[ view ] original -> live:");
            logger::info(detail::optics_line("default fov", original->default_fov.base, sdk::hw2::default_fov_of(pawn)));
            if (settings) logger::info(detail::optics_line("settings fov", settings->fov.base, sdk::hw2::settings_fov_of(controller)));
            logger::info(detail::optics_line("breathing strength", base.breathing_strength, live.breathing_strength));
            logger::info(detail::optics_line("breathing yaw", base.breathing_yaw, live.breathing_yaw));
            logger::info(detail::optics_line("breathing pitch", base.breathing_pitch, live.breathing_pitch));
            logger::info(detail::optics_line("post process blend", base.post_process_blend, live.post_process_blend));
            logger::info(detail::optics_line("tpp arm length", base.tpp_arm_length, live.tpp_arm_length));
            logger::info(detail::optics_line("spring arm length", base.arm_length, live.arm_length));
            logger::info(detail::optics_line("arm side offset", base.socket_offset.Y, live.socket_offset.Y));
            logger::info(detail::optics_line("arm pivot rise", base.target_offset.Z, live.target_offset.Z));

            logger::info(detail::optics_value("input subsystem fov", sdk::hw2::input_fov_of(detail::input_subsystem())));
            logger::info(detail::optics_value("camera manager fov", sdk::hw2::manager_fov_of(detail::own_controller())));
            logger::info(detail::optics_value("component fov", sdk::hw2::camera_fov_of(pawn)));
            logger::info(detail::optics_value("first person fov", sdk::hw2::first_person_fov_of(pawn)));
            logger::info(detail::optics_value("current fov", sdk::hw2::current_fov_of(pawn)));

            logger::info(detail::optics_value("rendered fov", sdk::hw2::rendered_fov_of(detail::own_controller())));
            logger::info(detail::optics_value("target fov", sdk::hw2::target_fov_of(pawn)));
            logger::info(detail::optics_value("target spread", sdk::hw2::target_spread_of(pawn)));
            logger::info(detail::optics_value("saturation", sdk::hw2::saturation_of(pawn)));
            logger::info(detail::optics_value("lean", sdk::hw2::leaning_of(pawn)));
            logger::info(detail::optics_value("camera lean", sdk::hw2::camera_leaning_of(pawn)));

            logger::info(std::string("[ view ]   first person fov ") + (sdk::hw2::is_first_person_fov_on(pawn) ? "on" : "off")
                + " -> when on, the arms and gun render on their own fov and the world does not follow it");
            logger::info(std::string("[ view ]   perspective ") + (sdk::hw2::is_third_person(controller) ? "third" : "first")
                + ", arm collision " + (live.is_arm_collision ? "on" : "off")
                + ", breathing " + (live.is_breathing ? "on" : "off")
                + ", hold breath " + (live.is_hold_breath_allowed ? "allowed" : "blocked")
                + ", run shake " + (live.run_camera_shake ? "set" : "none"));
        });
    }

    void view_domain::probe() {
        game::dispatch::post([]() {
            const sdk::UClass* type = sdk::objects::find_class("HW2FieldOfViewSubsystem");
            if (!type) { logger::error("[ view ] no HW2FieldOfViewSubsystem class in the object array"); return; }

            sdk::UObject* subsystem = sdk::objects::find_instance(type);
            if (!subsystem) { logger::error("[ view ] the fov subsystem class is registered but no instance is live -> get into a match first"); return; }

            const std::uintptr_t base = sdk::globals::base();
            logger::info("[ view ] fov subsystem " + subsystem->full_name());
            logger::info(detail::rva_line("module base", base, base));

            for (std::uint32_t at = 0; at < 0x60; at += 8) {
                const std::uintptr_t vtable = sdk::mem::read<std::uintptr_t>(subsystem, at, 0);
                if (!detail::is_in_image(vtable, base)) continue;

                logger::success(detail::rva_line(detail::slot_label(at, 0).c_str(), vtable, base));

                for (std::uint32_t slot = 0; slot < 12; ++slot) {
                    const std::uintptr_t entry = sdk::mem::read<std::uintptr_t>(reinterpret_cast<const void*>(vtable), slot * 8, 0);
                    if (!detail::is_in_image(entry, base)) continue;

                    logger::info(detail::rva_line(detail::slot_label(at, slot).c_str(), entry, base));
                }
            }

            const sdk::AActor* manager = detail::own_controller() ? detail::own_controller()->PlayerCameraManager() : nullptr;
            const sdk::UClass* manager_type = manager ? manager->klass() : nullptr;
            logger::info("[ view ] camera manager is " + (manager_type ? manager_type->name() : std::string("none")));
        });
    }

    void view_domain::restore() {
        view_setup = view_options{};

        logger::success("[ view ] every view option reset -> the originals go back on the next pass in a match");
    }

}
