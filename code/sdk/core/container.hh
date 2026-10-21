#pragma once
#include <cstdint>

namespace sdk {

    template <class T> struct TArray {
        T* Data = nullptr;
        std::int32_t NumElements = 0;
        std::int32_t MaxElements = 0;

        [[nodiscard]] std::int32_t num() const noexcept { return NumElements; }
        [[nodiscard]] bool is_valid(std::int32_t index) const noexcept { return Data && index >= 0 && index < NumElements; }
        [[nodiscard]] T at(std::int32_t index) const noexcept { return is_valid(index) ? Data[index] : T{}; }
    };

    struct FString : TArray<wchar_t> {
        FString() = default;

        FString(wchar_t* buffer, std::int32_t used, std::int32_t capacity) {
            Data = buffer;
            NumElements = used;
            MaxElements = capacity;
        }
    };

}
