#pragma once
#include <Windows.h>
#include <cstdint>

namespace crash::modules {

    struct span {
        uintptr_t base = 0;
        size_t size = 0;
        char name[64] = {};

        [[nodiscard]] bool contains(uintptr_t address) const noexcept {
            return address >= base && address < base + size;
        }
    };

    void collect() noexcept;

    [[nodiscard]] size_t count() noexcept;
    [[nodiscard]] const span& at(size_t index) noexcept;
    [[nodiscard]] const span* owner_of(uintptr_t address) noexcept;

}
