#pragma once
#include <Windows.h>
#include <cstdint>
#include <cstring>

namespace sdk::mem {

    template <class T> [[nodiscard]] inline T read(const void* base, std::uint32_t offset, T fallback = T{}) noexcept {
        if (!base) return fallback;

        __try { return *reinterpret_cast<const T*>(reinterpret_cast<const std::uint8_t*>(base) + offset); }
        __except (EXCEPTION_EXECUTE_HANDLER) { return fallback; }
    }

    template <class T> [[nodiscard]] inline T* pointer(const void* base, std::uint32_t offset) noexcept {
        return reinterpret_cast<T*>(read<std::uintptr_t>(base, offset, 0));
    }

    inline bool copy(void* destination, const void* source, std::size_t bytes) noexcept {
        if (!destination || !source || !bytes) return false;

        __try { memcpy(destination, source, bytes); return true; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
    }

    template <class T> inline bool write(void* base, std::uint32_t offset, T value) noexcept {
        if (!base) return false;

        __try { *reinterpret_cast<T*>(reinterpret_cast<std::uint8_t*>(base) + offset) = value; return true; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
    }

    [[nodiscard]] inline bool read_bit(const void* base, std::uint32_t offset, std::uint32_t bit) noexcept {
        return ((read<std::uint8_t>(base, offset) >> bit) & 1u) != 0u;
    }

    inline bool write_bit(void* base, std::uint32_t offset, std::uint32_t bit, bool is_set) noexcept {
        if (!base) return false;

        const std::uint8_t mask = static_cast<std::uint8_t>(1u << bit);
        const std::uint8_t byte = read<std::uint8_t>(base, offset);

        return write<std::uint8_t>(base, offset, is_set ? byte | mask : byte & static_cast<std::uint8_t>(~mask));
    }

}
