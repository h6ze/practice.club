#pragma once
#include <Windows.h>

namespace input::window {

    [[nodiscard]] bool ensure(HWND target);
    void release();

    [[nodiscard]] bool is_hooked();

}
