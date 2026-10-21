#include "notes.hh"
#include <cstdio>

namespace sdk::detail {

    note_sink installed_sink = nullptr;

}

void sdk::bind_notes(note_sink sink) { detail::installed_sink = sink; }

void sdk::say(note level, const std::string& text) {
    if (detail::installed_sink) detail::installed_sink(level, text);
}

std::string sdk::hex(std::uintptr_t value) {
    char buffer[32] = {};
    snprintf(buffer, sizeof(buffer), "0x%llX", static_cast<unsigned long long>(value));

    return buffer;
}
