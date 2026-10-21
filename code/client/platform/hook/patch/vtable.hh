#pragma once
#include <cstddef>

namespace hook {

    [[nodiscard]] void* vtable_slot(void* instance, size_t index) noexcept;

}
