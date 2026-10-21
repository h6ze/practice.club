#pragma once
#include <cstdint>
#include <string>

namespace sdk {

    enum class note : std::uint8_t { info, success, warning, error };

    using note_sink = void(*)(note level, const std::string& text);

    void bind_notes(note_sink sink);
    void say(note level, const std::string& text);

    [[nodiscard]] std::string hex(std::uintptr_t value);

}
