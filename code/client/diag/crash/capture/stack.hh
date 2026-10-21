#pragma once
#include <Windows.h>
#include <cstdint>

namespace crash {

    struct frame_list {
        static constexpr size_t capacity = 64;

        uintptr_t frames[capacity] = {};
        size_t count = 0;
    };

    void walk(const CONTEXT& start, frame_list& out) noexcept;

}
