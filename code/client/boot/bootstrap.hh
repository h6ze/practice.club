#pragma once
#include <Windows.h>

namespace boot {

    [[nodiscard]] bool run(HMODULE owner);
    void unwind();

    [[nodiscard]] HMODULE owner();
    [[nodiscard]] bool is_loaded();

}
