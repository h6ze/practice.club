#include "text.hh"
#include <Windows.h>
#include <cstdio>
#include <iterator>

std::string text::narrow(const std::wstring& value) {
    if (value.empty()) return {};

    const int length = WideCharToMultiByte(CP_UTF8, 0, value.c_str(), static_cast<int>(value.size()), nullptr, 0, nullptr, nullptr);
    if (length <= 0) return {};

    std::string result(static_cast<size_t>(length), '\0');
    WideCharToMultiByte(CP_UTF8, 0, value.c_str(), static_cast<int>(value.size()), result.data(), length, nullptr, nullptr);

    return result;
}

std::wstring text::widen(const std::string& value) {
    if (value.empty()) return {};

    const int length = MultiByteToWideChar(CP_UTF8, 0, value.c_str(), static_cast<int>(value.size()), nullptr, 0);
    if (length <= 0) return {};

    std::wstring result(static_cast<size_t>(length), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, value.c_str(), static_cast<int>(value.size()), result.data(), length);

    return result;
}

std::string text::last_error() {
    const DWORD code = GetLastError();

    char buffer[512] = {};
    const DWORD length = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, code, 0, buffer, static_cast<DWORD>(std::size(buffer)), nullptr);

    std::string message(buffer, length);
    while (!message.empty() && (message.back() == '\n' || message.back() == '\r' || message.back() == '.')) message.pop_back();

    return message.empty() ? "win32 error " + std::to_string(code) : "win32 error " + std::to_string(code) + " -> " + message;
}

std::string text::hex(unsigned long long value, int digits) {
    char buffer[32] = {};
    std::snprintf(buffer, sizeof(buffer), "0x%0*llX", digits, value);
    return buffer;
}
