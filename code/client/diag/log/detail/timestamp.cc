#include "timestamp.hh"
#include <Windows.h>
#include <cstdio>

std::string logger::stamp_clock() {
    SYSTEMTIME now{};
    GetLocalTime(&now);

    char buffer[32] = {};
    std::snprintf(buffer, sizeof(buffer), "%02u:%02u:%02u.%03u", now.wHour, now.wMinute, now.wSecond, now.wMilliseconds);

    return buffer;
}

std::string logger::stamp_full() {
    SYSTEMTIME now{};
    GetLocalTime(&now);

    char buffer[32] = {};
    std::snprintf(buffer, sizeof(buffer), "%04u-%02u-%02u %02u:%02u:%02u",
        now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);

    return buffer;
}

std::string logger::stamp_compact() {
    SYSTEMTIME now{};
    GetLocalTime(&now);

    char buffer[32] = {};
    std::snprintf(buffer, sizeof(buffer), "%04u%02u%02u-%02u%02u%02u",
        now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);

    return buffer;
}
