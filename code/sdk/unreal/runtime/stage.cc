#include "stage.hh"
#include <string>
#include <sdk/notes.hh>
#include <sdk/globals.hh>

namespace game::detail {

    struct tracker {
        game::loading_stage current = game::loading_stage::uninitialized;
        std::string map;
    };

    tracker& state() {
        static tracker value;
        return value;
    }

    [[nodiscard]] game::loading_stage read_stage() {
        if (!sdk::globals::is_ready()) return game::loading_stage::halted;

        sdk::UWorld* world = sdk::globals::world();
        if (!world) return game::loading_stage::booting;

        detail::state().map = world->name();

        if (!world->OwningGameInstance()) return game::loading_stage::loaded;

        const bool is_networked = world->NetDriver() != nullptr;
        if (!world->GameState()) return is_networked ? game::loading_stage::connecting : game::loading_stage::main_menu;

        sdk::AController* controller = world->local_controller();
        if (!controller) return is_networked ? game::loading_stage::connecting : game::loading_stage::main_menu;

        return controller->Pawn() ? game::loading_stage::in_game : game::loading_stage::connecting;
    }

}

game::loading_stage game::stage() { return detail::state().current; }

const char* game::stage_name(loading_stage value) {
    switch (value) {
    case loading_stage::uninitialized: return "uninitialized";
    case loading_stage::booting: return "booting";
    case loading_stage::halted: return "halted";
    case loading_stage::loaded: return "loaded";
    case loading_stage::main_menu: return "main menu";
    case loading_stage::connecting: return "connecting";
    case loading_stage::in_game: return "in game";
    }

    return "unknown";
}

void game::set_stage(loading_stage next) {
    detail::tracker& current = detail::state();
    if (current.current == next) return;

    const loading_stage previous = current.current;
    current.current = next;

    sdk::say(sdk::note::info, std::string("[ game ] ") + stage_name(previous) + " -> " + stage_name(next)
        + (current.map.empty() ? std::string{} : " on " + current.map));
}

void game::refresh_stage() { set_stage(detail::read_stage()); }

const char* game::map_name() { return detail::state().map.c_str(); }
