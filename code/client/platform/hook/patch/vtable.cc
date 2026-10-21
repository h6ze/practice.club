#include "vtable.hh"
#include <Windows.h>

void* hook::vtable_slot(void* instance, size_t index) noexcept {
    if (!instance) return nullptr;

    __try {
        void** table = *reinterpret_cast<void***>(instance);
        return table ? table[index] : nullptr;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return nullptr;
    }
}
