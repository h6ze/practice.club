#pragma once
#include <cstdint>

namespace logger {

    enum class level : uint8_t { debug, info, success, warning, error };

    struct level_label { char marker; const char* name; };

    inline constexpr level_label labels[] = {
        { '~', "debug" },
        { '*', "info" },
        { '+', "ok" },
        { '!', "warn" },
        { '-', "error" },
    };

    [[nodiscard]] inline const level_label& label_of(level value) { return labels[static_cast<size_t>(value)]; }

}
