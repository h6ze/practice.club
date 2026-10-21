#include <Windows.h>
#include <client/boot/bootstrap.hh>

namespace {

    DWORD WINAPI load(LPVOID parameter) {
        return boot::run(static_cast<HMODULE>(parameter)) ? 0u : 1u;
    }

}

BOOL APIENTRY DllMain(HMODULE owner, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(owner);

        const HANDLE thread = CreateThread(nullptr, 0, load, owner, 0, nullptr);
        if (!thread) return FALSE;

        CloseHandle(thread);

        return TRUE;
    }

    if (reason == DLL_PROCESS_DETACH && !reserved) boot::unwind();

    return TRUE;
}
