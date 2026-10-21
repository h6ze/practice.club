#pragma once
#include <Windows.h>
#include <cstddef>

namespace crash {

    class writer {
        HANDLE file = nullptr;
        char buffer[4096] = {};
        size_t used = 0;
        size_t column = 0;

    public:
        explicit writer(const char* path) noexcept;
        ~writer();

        writer(const writer&) = delete;
        writer& operator=(const writer&) = delete;

        [[nodiscard]] bool is_open() const noexcept { return file != nullptr; }

        void text(const char* value) noexcept;
        void character(char value) noexcept;
        void decimal(unsigned long long value) noexcept;
        void hex(unsigned long long value, int digits = 16) noexcept;
        void pad(size_t target) noexcept;
        void label(const char* name) noexcept;
        void line() noexcept;
        void rule(char glyph, size_t width) noexcept;
        void flush() noexcept;
    };

}
