#pragma once
#include <Windows.h>

namespace input::hotkeys {

    inline constexpr unsigned overlay_key = VK_DELETE;

    [[nodiscard]] bool is_overlay_open();
    void toggle_overlay();
    void set_overlay_open(bool value);

}
