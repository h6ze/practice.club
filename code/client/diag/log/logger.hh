#pragma once
#include <string>
#include "level.hh"

namespace logger {

#pragma region lifetime

    struct options {
        bool is_console = false;
        bool is_file = true;
        level floor = level::debug;
        size_t keep_files = 10;
    };

    [[nodiscard]] bool startup(const options& settings);
    void shutdown();
    void flush();

    [[nodiscard]] std::wstring file();

#pragma endregion

#pragma region levels

    void write(level severity, const std::string& text);

    inline void debug(const std::string& text) { write(level::debug, text); }
    inline void info(const std::string& text) { write(level::info, text); }
    inline void success(const std::string& text) { write(level::success, text); }
    inline void warning(const std::string& text) { write(level::warning, text); }
    inline void error(const std::string& text) { write(level::error, text); }

#pragma endregion

}
