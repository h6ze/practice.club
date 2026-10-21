#include "encoding.hh"
#include <Windows.h>

std::string sdk::narrow(const wchar_t* value, int length) {
    if (!value || length <= 0) return std::string{};

    const int bytes = WideCharToMultiByte(CP_UTF8, 0, value, length, nullptr, 0, nullptr, nullptr);
    if (bytes <= 0) return std::string{};

    std::string out(static_cast<size_t>(bytes), '\0');
    WideCharToMultiByte(CP_UTF8, 0, value, length, out.data(), bytes, nullptr, nullptr);

    return out;
}

std::string sdk::narrow(const FString& value) {
    return narrow(value.Data, value.NumElements > 0 ? value.NumElements : 0);
}

std::wstring sdk::widen(const char* value) {
    if (!value || !*value) return std::wstring{};

    const int chars = MultiByteToWideChar(CP_UTF8, 0, value, -1, nullptr, 0);
    if (chars <= 1) return std::wstring{};

    std::wstring out(static_cast<size_t>(chars - 1), 0);
    MultiByteToWideChar(CP_UTF8, 0, value, -1, out.data(), chars);

    return out;
}
