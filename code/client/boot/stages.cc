#include "stage.hh"
#include <Windows.h>
#include <iterator>
#include <string>
#include <client/diag/crash/handler.hh>
//#include <client/platform/guard/hyprv.hxx>
#include <client/diag/log/logger.hh>
#include <client/render/dx12/frame/queue.hh>
#include <client/render/dx12/swapchain.hh>
#include <sdk/notes.hh>
#include <sdk/globals.hh>
#include <sdk/unreal/runtime/stage.hh>
#include <client/bridge/dispatch.hh>
#include <client/bridge/natives.hh>
#include <client/util/brand.hh>
#include <client/util/system/paths.hh>
#include <client/util/string/text.hh>
#include "bootstrap.hh"

namespace {

    [[nodiscard]] bool enter_paths() {
        paths::bind(boot::owner());
        if (paths::ensure()) return true;

        OutputDebugStringA("[ boot ] could not create the practice.club data directories\n");

        return false;
    }

    [[nodiscard]] bool enter_logging() {
        logger::options settings;

#if defined(PRACTICE_DEV)
        settings.is_console = true;
        settings.floor = logger::level::debug;
#else
        settings.is_console = false;
        settings.floor = logger::level::info;
#endif

        if (!logger::startup(settings)) { OutputDebugStringA("[ boot ] no logging sink could be opened\n"); return false; }

        logger::success(std::string("[ boot ] ") + brand::name + " " + brand::version
            + " attached to " + text::narrow(paths::process_name()));
        logger::info("[ boot ] journal at " + text::narrow(logger::file()));

        return true;
    }

    [[nodiscard]] bool enter_hyprv() {

        return true;
    }

    [[nodiscard]] bool enter_crash() {
        const crash::options settings;
        return crash::install(settings);
    }

    void forward_note(sdk::note level, const std::string& text) {
        switch (level) {
        case sdk::note::success: logger::success(text); return;
        case sdk::note::warning: logger::warning(text); return;
        case sdk::note::error: logger::error(text); return;
        case sdk::note::info: break;
        }

        logger::info(text);
    }

    [[nodiscard]] bool enter_sdk() {
        sdk::bind_notes(&forward_note);

        if (!sdk::globals::resolve()) {
            game::set_stage(game::loading_stage::halted);
            logger::error("[ sdk ] the game globals could not be resolved -> game state is unavailable");
            return false;
        }

        game::set_stage(game::loading_stage::booting);

        return true;
    }

    [[nodiscard]] bool enter_dispatch() {
        if (!game::dispatch::install())
            logger::warning("[ dispatch ] the game thread pump is unavailable -> anything that calls into the game is off");

        return true;
    }

    [[nodiscard]] bool enter_graphics() {
        return render::swapchain::hook();
    }

    void leave_dispatch() {
        game::natives::restore_all();
        game::dispatch::remove();
    }

    void leave_graphics() {
        render::swapchain::unhook();
        render::queue::unhook();
    }

    constexpr boot::stage plan_table[] = {
        { "paths", enter_paths, nullptr },
        { "logging", enter_logging, logger::shutdown },
        { "hyprv", enter_hyprv, nullptr },
        { "crash", enter_crash, crash::remove },
        { "sdk", enter_sdk, nullptr },
        { "dispatch", enter_dispatch, leave_dispatch },
        { "graphics", enter_graphics, leave_graphics },
    };

}

const boot::stage* boot::plan() { return plan_table; }

size_t boot::plan_size() { return std::size(plan_table); }
