#pragma once
#include <Windows.h>
#include <memory>
#include <type_traits>
#include <utility>

namespace win {

#pragma region owned kernel handle

    struct handle_deleter {
        void operator()(HANDLE value) const noexcept {
            if (value && value != INVALID_HANDLE_VALUE) CloseHandle(value);
        }
    };

    using unique_handle = std::unique_ptr<std::remove_pointer_t<HANDLE>, handle_deleter>;

    [[nodiscard]] inline unique_handle adopt(HANDLE value) noexcept {
        return unique_handle(value == INVALID_HANDLE_VALUE ? nullptr : value);
    }

#pragma endregion

#pragma region owned com interface

    struct com_deleter {
        template <class T> void operator()(T* value) const noexcept { if (value) value->Release(); }
    };

    template <class T> using com_ptr = std::unique_ptr<T, com_deleter>;

    template <class T> [[nodiscard]] com_ptr<T> adopt_com(T* value) noexcept { return com_ptr<T>(value); }

#pragma endregion

}
