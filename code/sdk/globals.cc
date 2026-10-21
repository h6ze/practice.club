#include "globals.hh"
#include <Windows.h>
#include <string>
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/core/text/name.hh>
#include "notes.hh"
#include "offsets.generated.hh"

namespace sdk::globals::detail {

    struct resolved {
        std::uintptr_t image = 0;
        void** gworld = nullptr;
        bool is_ready = false;
        bool is_matched = false;
    };

    resolved& state() {
        static resolved value;
        return value;
    }

    [[nodiscard]] std::uint32_t image_size_of(std::uintptr_t image) noexcept {
        const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(image);
        if (!dos || dos->e_magic != IMAGE_DOS_SIGNATURE) return 0;

        const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS64*>(image + dos->e_lfanew);

        return nt->Signature == IMAGE_NT_SIGNATURE ? nt->OptionalHeader.SizeOfImage : 0;
    }

}

bool sdk::globals::resolve() {
    detail::resolved& current = detail::state();
    if (current.is_ready) return true;

    current.image = reinterpret_cast<std::uintptr_t>(GetModuleHandleW(nullptr));
    if (!current.image) { say(note::error, "[ sdk ] the game module could not be located"); return false; }

    const std::uint32_t live = detail::image_size_of(current.image);
    current.is_matched = live == offsets::image_size;

    if (!current.is_matched)
        say(note::warning, "[ sdk ] this exe is " + hex(live) + " but the offsets came from "
            + hex(offsets::image_size));

    bind_append_string(reinterpret_cast<void*>(current.image + offsets::global::append_string));
    bind_process_event(reinterpret_cast<void*>(current.image + offsets::global::process_event));

    if (!objects::bind(reinterpret_cast<void*>(current.image + offsets::global::gobjects))) {
        say(note::error, "[ sdk ] gobjects did not validate at " + hex(offsets::global::gobjects) + " -> the offsets are broken, go back to ooga booga coding");
        return false;
    }

    const UObject* first = objects::at(0);
    const std::string probe = first ? first->name() : std::string{};
    if (probe.empty()) { say(note::error, "[ sdk ] no fname could be read -> appendstring is wrong"); return false; }

    current.gworld = reinterpret_cast<void**>(current.image + offsets::global::gworld);
    current.is_ready = true;

    say(note::success, "[ sdk ] " + std::to_string(objects::count()) + " objects, first is " + probe
        + ", dump " + offsets::dump_tag);

    return true;
}

bool sdk::globals::is_ready() { return detail::state().is_ready; }

bool sdk::globals::is_build_matched() { return detail::state().is_matched; }

std::uintptr_t sdk::globals::base() { return detail::state().image; }

sdk::UWorld* sdk::globals::world() {
    const detail::resolved& current = detail::state();
    if (!current.is_ready || !current.gworld) return nullptr;

    return mem::read<UWorld*>(current.gworld, 0, nullptr);
}
