#include "call.hh"
#include <Windows.h>
#include <sdk/notes.hh>

namespace sdk::call::detail {

    constexpr std::int32_t frame_ceiling = 0x4000;

    using process_event_call = void(__fastcall*)(void*, void*, void*);

    process_event_call process_event = nullptr;

    [[nodiscard]] inline bool guarded(void* object, void* entry, void* params) noexcept {
        __try { process_event(object, entry, params); return true; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
    }

}

void sdk::bind_process_event(void* address) {
    call::detail::process_event = reinterpret_cast<call::detail::process_event_call>(address);
}

bool sdk::call::is_ready() { return detail::process_event != nullptr; }

sdk::call::invocation::invocation(UObject* object, const char* function_name) {
    if (!object || !function_name) return;

    UClass* type = object->klass();
    if (!type) return;

    UFunction* found = type->find_function(function_name);
    if (!found) { say(note::error, std::string("[ call ] ") + function_name + " is not a function on this object"); return; }

    const std::int32_t wanted = found->size();
    if (wanted < 0 || wanted > detail::frame_ceiling) {
        say(note::error, std::string("[ call ] ") + function_name + " reports an implausible frame of " + std::to_string(wanted) + " bytes");
        return;
    }

    target = object;
    entry = found;
    frame.assign(static_cast<size_t>(wanted), 0);
}

bool sdk::call::invocation::fire() {
    if (!is_valid()) return false;
    if (!detail::process_event) { say(note::error, "[ call ] processevent has not been resolved"); return false; }

    void* params = frame.empty() ? nullptr : frame.data();

    if (detail::guarded(target, entry, params)) return true;

    say(note::error, "[ call ] " + entry->name() + " faulted -> the frame or the target was wrong");

    return false;
}
