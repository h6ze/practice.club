#pragma once
#include <Windows.h>

namespace crash {

    struct reason { const char* name; const char* detail; };

    [[nodiscard]] reason reason_of(DWORD code) noexcept;
    [[nodiscard]] const char* access_kind(ULONG_PTR operation) noexcept;

}
