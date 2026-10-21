#pragma once
#include <sdk/unreal/engine.hh>
#include <sdk/globals.hh>
#include <sdk/hw2/hw2.hh>

namespace features::detail {

    [[nodiscard]] inline sdk::APlayerController* own_controller() {
        sdk::UWorld* world = sdk::globals::world();

        return world ? world->local_controller() : nullptr;
    }

    [[nodiscard]] inline sdk::APlayerState* own_state() {
        sdk::APlayerController* controller = own_controller();

        return controller ? controller->PlayerState() : nullptr;
    }

}
