#pragma once
#include <string>
#include <sdk/core/container.hh>

namespace sdk {

    [[nodiscard]] std::string narrow(const wchar_t* value, int length);
    [[nodiscard]] std::string narrow(const FString& value);

    [[nodiscard]] std::wstring widen(const char* value);

}
