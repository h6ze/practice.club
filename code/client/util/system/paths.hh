#pragma once
#include <Windows.h>
#include <string>

namespace paths {

#pragma region binding

    void bind(HMODULE value);
    [[nodiscard]] bool ensure();

#pragma endregion

#pragma region locations

    [[nodiscard]] HMODULE owner();
    [[nodiscard]] const std::wstring& module_file();
    [[nodiscard]] const std::wstring& module_name();
    [[nodiscard]] const std::wstring& process_name();

    [[nodiscard]] const std::wstring& root();
    [[nodiscard]] const std::wstring& logs();
    [[nodiscard]] const std::wstring& crashes();

    [[nodiscard]] const char* crashes_narrow();

#pragma endregion

}
