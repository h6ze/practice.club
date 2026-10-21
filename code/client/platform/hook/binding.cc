#include "binding.hh"
#include <Windows.h>
#include <detours/detours.h>
#include <client/diag/log/logger.hh>
#include <client/util/string/text.hh>
#include <client/platform/hook/patch/transaction.hh>

namespace {

    [[nodiscard]] std::string tag(const char* name) {
        return std::string("[ hook ] ") + (name ? name : "unnamed");
    }

}

hook::detail::binding::~binding() {
    detach();
}

bool hook::detail::binding::attach(void* address, void* hook, const char* name) {
    if (is_active()) return true;
    if (!address) { logger::error(tag(name) + " has no target address -> resolve it before attaching"); return false; }
    if (!hook) { logger::error(tag(name) + " has no replacement"); return false; }

    entry = address;
    replacement = hook;

    transaction pending;
    if (!pending.is_active()) { logger::error(tag(name) + " could not open a detours transaction"); entry = nullptr; replacement = nullptr; return false; }

    const LONG status = DetourAttach(&entry, replacement);
    if (status != NO_ERROR) {
        pending.abort();
        entry = nullptr;
        replacement = nullptr;
        logger::error(tag(name) + " was rejected by detours with status " + std::to_string(status));
        return false;
    }

    if (!pending.commit()) { entry = nullptr; replacement = nullptr; return false; }

    target = address;
    logger::debug(tag(name) + " attached at " + text::hex(reinterpret_cast<uintptr_t>(address)));

    return true;
}

void hook::detail::binding::detach() {
    if (!is_active()) return;

    transaction pending;
    if (pending.is_active()) {
        if (DetourDetach(&entry, replacement) != NO_ERROR) pending.abort();
        else if (!pending.commit()) logger::error("[ hook ] a detour could not be removed cleanly -> unloading now may crash the game");
    }

    entry = nullptr;
    replacement = nullptr;
    target = nullptr;
}
