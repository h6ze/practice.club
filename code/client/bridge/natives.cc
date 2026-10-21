#include "natives.hh"
#include <vector>
#include <sdk/core/access.hh>
#include <sdk/offsets.generated.hh>
#include <client/diag/log/logger.hh>

namespace game::natives::detail {

    struct swapped {
        sdk::UFunction* function = nullptr;
        thunk original = nullptr;
    };

    std::vector<swapped> taken;

    [[nodiscard]] swapped* already_taken(const sdk::UFunction* function) {
        for (swapped& entry : taken)
            if (entry.function == function) return &entry;

        return nullptr;
    }

}

game::natives::thunk game::natives::swap(sdk::UFunction* function, thunk replacement) {
    if (!function || !replacement) return nullptr;

    if (detail::swapped* entry = detail::already_taken(function)) return entry->original;

    const thunk original = sdk::mem::read<thunk>(function, sdk::offsets::ufunction::exec_function, nullptr);
    if (!original) { logger::error("[ natives ] no exec thunk on that function -> nothing swapped"); return nullptr; }

    if (!sdk::mem::write<thunk>(function, sdk::offsets::ufunction::exec_function, replacement)) {
        logger::error("[ natives ] could not write the exec thunk");
        return nullptr;
    }

    detail::taken.push_back({ function, original });

    return original;
}

void game::natives::restore_all() {
    for (const detail::swapped& entry : detail::taken)
        sdk::mem::write<thunk>(entry.function, sdk::offsets::ufunction::exec_function, entry.original);

    if (!detail::taken.empty()) logger::info("[ natives ] exec thunks put back");

    detail::taken.clear();
}
