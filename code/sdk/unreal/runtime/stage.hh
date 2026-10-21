#pragma once
#include <cstdint>

namespace game {

    enum class loading_stage : std::uint8_t {
        uninitialized,
        booting,
        halted,
        loaded,
        main_menu,
        connecting,
        in_game,
    };

    loading_stage stage();
    void set_stage(loading_stage next);
    const char* stage_name(loading_stage value);

    void refresh_stage();

    const char* map_name();

}
