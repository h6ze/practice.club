#pragma once
#include <cstdint>
#include <string>

namespace sdk {

    struct FName {
        std::int32_t ComparisonIndex = 0;
        std::int32_t Number = 0;

        [[nodiscard]] bool is_none() const noexcept { return !ComparisonIndex && !Number; }
        [[nodiscard]] std::string text() const;
    };

    void bind_append_string(void* address);

}
