#include "transaction.hh"
#include <TlHelp32.h>
#include <detours/detours.h>
#include <client/diag/log/logger.hh>

namespace {

    constexpr DWORD thread_access = THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_QUERY_INFORMATION;

    std::mutex& transaction_gate() {
        static std::mutex value;
        return value;
    }

    void enlist_others(std::vector<win::unique_handle>& enlisted) {
        const auto snapshot = win::adopt(CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0));
        if (!snapshot) return;

        THREADENTRY32 info{};
        info.dwSize = sizeof(info);

        if (!Thread32First(snapshot.get(), &info)) return;

        const DWORD process_id = GetCurrentProcessId();
        const DWORD current_id = GetCurrentThreadId();

        do {
            if (info.th32OwnerProcessID != process_id) continue;
            if (info.th32ThreadID == current_id) continue;

            auto thread = win::adopt(OpenThread(thread_access, FALSE, info.th32ThreadID));
            if (!thread) continue;

            if (DetourUpdateThread(thread.get()) != NO_ERROR) continue;

            enlisted.push_back(std::move(thread));
        } while (Thread32Next(snapshot.get(), &info));
    }

}

hook::transaction::transaction() : gate(transaction_gate()) {
    if (DetourTransactionBegin() != NO_ERROR) return;

    is_open = true;

    DetourUpdateThread(GetCurrentThread());
    enlist_others(enlisted);
}

hook::transaction::~transaction() {
    abort();
}

bool hook::transaction::commit() {
    if (!is_open) return false;

    const LONG status = DetourTransactionCommit();
    is_open = false;
    enlisted.clear();

    if (status == NO_ERROR) return true;

    logger::error("[ hook ] detours refused the commit with status " + std::to_string(status));

    return false;
}

void hook::transaction::abort() {
    if (!is_open) return;

    DetourTransactionAbort();
    is_open = false;
    enlisted.clear();
}
