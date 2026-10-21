#pragma once
#include <cstdint>
#include <sdk/unreal/engine.hh>

namespace sdk::globals {

    [[nodiscard]] bool resolve();
    [[nodiscard]] bool is_ready();

    [[nodiscard]] std::uintptr_t base();
    [[nodiscard]] UWorld* world();

    [[nodiscard]] bool is_build_matched();

}
