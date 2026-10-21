#include "minidump.hh"
#include <DbgHelp.h>

namespace {

    constexpr MINIDUMP_TYPE dump_flags = static_cast<MINIDUMP_TYPE>(
        MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory | MiniDumpWithThreadInfo | MiniDumpWithUnloadedModules);

}

bool crash::write_minidump(const char* path, EXCEPTION_POINTERS* pointers) noexcept {
    const HANDLE file = CreateFileA(path, GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) return false;

    MINIDUMP_EXCEPTION_INFORMATION description{};
    description.ThreadId = GetCurrentThreadId();
    description.ExceptionPointers = pointers;
    description.ClientPointers = FALSE;

    const BOOL written = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), file, dump_flags,
        pointers ? &description : nullptr, nullptr, nullptr);

    CloseHandle(file);

    return written != FALSE;
}
