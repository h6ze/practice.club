#include "modules.hh"
#include <Psapi.h>
#include <cstring>

namespace {

    constexpr size_t capacity = 320;

    crash::modules::span table[capacity];
    size_t found = 0;

}

void crash::modules::collect() noexcept {
    found = 0;

    HMODULE handles[capacity] = {};
    DWORD needed = 0;

    const HANDLE process = GetCurrentProcess();
    if (!EnumProcessModules(process, handles, sizeof(handles), &needed)) return;

    const size_t listed = needed / sizeof(HMODULE);

    for (size_t index = 0; index < listed && found < capacity; ++index) {
        MODULEINFO info{};
        if (!GetModuleInformation(process, handles[index], &info, sizeof(info))) continue;

        span& entry = table[found];
        entry.base = reinterpret_cast<uintptr_t>(info.lpBaseOfDll);
        entry.size = info.SizeOfImage;

        if (!GetModuleBaseNameA(process, handles[index], entry.name, sizeof(entry.name)))
            std::strncpy(entry.name, "unknown", sizeof(entry.name) - 1);

        ++found;
    }
}

size_t crash::modules::count() noexcept { return found; }

const crash::modules::span& crash::modules::at(size_t index) noexcept { return table[index]; }

const crash::modules::span* crash::modules::owner_of(uintptr_t address) noexcept {
    for (size_t index = 0; index < found; ++index)
        if (table[index].contains(address)) return &table[index];

    return nullptr;
}
