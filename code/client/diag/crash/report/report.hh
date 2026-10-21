#pragma once
#include <Windows.h>

namespace crash {

    struct details {
        EXCEPTION_POINTERS* pointers = nullptr;
        const char* stamp = nullptr;
        const char* dump = nullptr;
        unsigned long long uptime_ms = 0;
    };

    void write_report(const char* path, const details& facts) noexcept;

}
