#include "writer.hh"
#include <cstdio>
#include <cstring>

namespace {

    constexpr size_t label_column = 14;

}

crash::writer::writer(const char* path) noexcept {
    const HANDLE opened = CreateFileA(path, GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (opened != INVALID_HANDLE_VALUE) file = opened;
}

crash::writer::~writer() {
    flush();
    if (file) CloseHandle(file);
}

void crash::writer::flush() noexcept {
    if (!file || used == 0) return;

    DWORD written = 0;
    WriteFile(file, buffer, static_cast<DWORD>(used), &written, nullptr);
    used = 0;
}

void crash::writer::character(char value) noexcept {
    if (!file) return;
    if (used == sizeof(buffer)) flush();

    buffer[used++] = value;
    column = value == '\n' ? 0 : column + 1;
}

void crash::writer::text(const char* value) noexcept {
    if (!value) return;

    for (const char* cursor = value; *cursor; ++cursor) character(*cursor);
}

void crash::writer::decimal(unsigned long long value) noexcept {
    char scratch[32] = {};
    std::snprintf(scratch, sizeof(scratch), "%llu", value);
    text(scratch);
}

void crash::writer::hex(unsigned long long value, int digits) noexcept {
    char scratch[32] = {};
    std::snprintf(scratch, sizeof(scratch), "0x%0*llX", digits, value);
    text(scratch);
}

void crash::writer::pad(size_t target) noexcept {
    while (column < target) character(' ');
}

void crash::writer::label(const char* name) noexcept {
    text(name);
    pad(label_column);
}

void crash::writer::line() noexcept {
    character('\r');
    character('\n');
}

void crash::writer::rule(char glyph, size_t width) noexcept {
    for (size_t index = 0; index < width; ++index) character(glyph);
    line();
}
