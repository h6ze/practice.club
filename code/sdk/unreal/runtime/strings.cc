#include "strings.hh"
#include <string>
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/core/text/encoding.hh>
#include <sdk/notes.hh>
#include <sdk/offsets.generated.hh>

namespace sdk::strings::detail {

    constexpr int seed_number = 1000000000;
    constexpr int join_ceiling = 12;

    UObject* library = nullptr;

    [[nodiscard]] UObject* kismet() {
        if (library) return library;

        UClass* type = objects::find_class("KismetStringLibrary");
        if (!type) { say(note::error, "[ strings ] KismetStringLibrary is not in the object array"); return nullptr; }

        library = type->default_object();
        if (!library) say(note::error, "[ strings ] KismetStringLibrary has no default object");

        return library;
    }

    [[nodiscard]] FString from_int(int value) {
        UObject* owner = kismet();
        if (!owner) return FString{};

        call::invocation entry(owner, "Conv_IntToString");
        if (!entry.is_valid()) return FString{};

        entry.set<int>(offsets::params::conv_int_to_string::in_int, value);
        if (!entry.fire()) return FString{};

        return entry.get<FString>(offsets::params::conv_int_to_string::return_value);
    }

    [[nodiscard]] FString joined(const FString& first, const FString& second) {
        UObject* owner = kismet();
        if (!owner) return FString{};

        call::invocation entry(owner, "Concat_StrStr");
        if (!entry.is_valid()) return FString{};

        entry.set<FString>(offsets::params::concat_str_str::a, first);
        entry.set<FString>(offsets::params::concat_str_str::b, second);
        if (!entry.fire()) return FString{};

        return entry.get<FString>(offsets::params::concat_str_str::return_value);
    }

}

bool sdk::strings::is_ready() { return detail::kismet() != nullptr; }

sdk::FString sdk::strings::make(const char* text) {
    if (!text) return FString{};

    const std::wstring wide = widen(text);
    const std::int32_t needed = static_cast<std::int32_t>(wide.size()) + 1;

    FString buffer = detail::from_int(detail::seed_number);
    if (!buffer.Data) { say(note::error, "[ strings ] the game would not hand back a string"); return FString{}; }

    for (int round = 0; buffer.MaxElements < needed && round < detail::join_ceiling; ++round) {
        const FString more = detail::from_int(detail::seed_number);
        if (!more.Data) return FString{};

        buffer = detail::joined(buffer, more);
        if (!buffer.Data) return FString{};
    }

    if (buffer.MaxElements < needed) {
        say(note::error, "[ strings ] could not grow a game string to " + std::to_string(needed) + " characters");
        return FString{};
    }

    if (!mem::copy(buffer.Data, wide.c_str(), (wide.size() + 1) * sizeof(wchar_t))) return FString{};

    buffer.NumElements = needed;

    return buffer;
}
