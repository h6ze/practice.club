#pragma once
#include <string>

namespace text {

    [[nodiscard]] std::string narrow(const std::wstring& value);
    [[nodiscard]] std::wstring widen(const std::string& value);

    [[nodiscard]] std::string last_error();
    [[nodiscard]] std::string hex(unsigned long long value, int digits = 16);

}
