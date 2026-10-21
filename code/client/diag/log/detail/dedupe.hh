#pragma once
#include <string>
#include <client/diag/log/level.hh>

namespace logger {

    struct repeat_run {
        level severity = level::debug;
        unsigned count = 0;
        unsigned long long span_ms = 0;

        [[nodiscard]] bool is_present() const noexcept { return count > 0; }
    };

    class dedupe {
        level held_severity = level::info;
        std::string held_text;
        unsigned seen = 0;
        unsigned long long opened_tick = 0;
        unsigned long long latest_tick = 0;

    public:
        [[nodiscard]] bool observe(level severity, const std::string& text, repeat_run& closed);
        [[nodiscard]] bool drain(repeat_run& closed);
    };

}
