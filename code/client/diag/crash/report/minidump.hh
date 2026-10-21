#pragma once
#include <Windows.h>

namespace crash {

    [[nodiscard]] bool write_minidump(const char* path, EXCEPTION_POINTERS* pointers) noexcept;

}
