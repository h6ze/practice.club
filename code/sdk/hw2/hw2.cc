#include "hw2.hh"
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/notes.hh>
#include <sdk/unreal/runtime/strings.hh>
#include <sdk/core/text/encoding.hh>
#include <sdk/offsets.generated.hh>

namespace sdk::hw2::detail {

    [[nodiscard]] inline UObject* state_info(const APlayerState* player_state) noexcept {
        return mem::pointer<UObject>(player_state, offsets::hw2_player_state::state_info);
    }

    [[nodiscard]] inline void* team_component(const APlayerState* player_state) noexcept {
        return mem::pointer<void>(player_state, offsets::hw2_player_state::team_component);
    }

    [[nodiscard]] inline void* health_component(const APawn* pawn) noexcept {
        return mem::pointer<void>(pawn, offsets::hw2_character::health_component);
    }

    [[nodiscard]] inline UObject* progression(const APlayerController* controller) noexcept {
        return mem::pointer<UObject>(controller, offsets::hw2_controller::progression_component);
    }

}

int sdk::hw2::team_of(const APlayerState* player_state) noexcept {
    return mem::read<int>(detail::team_component(player_state), offsets::hw2_team::team, -1);
}

int sdk::hw2::kills_of(const APlayerState* player_state) noexcept {
    return mem::read<int>(detail::state_info(player_state), offsets::hw2_state_info::kills, 0);
}

int sdk::hw2::deaths_of(const APlayerState* player_state) noexcept {
    return mem::read<int>(detail::state_info(player_state), offsets::hw2_state_info::deaths, 0);
}

int sdk::hw2::level_of(const APlayerState* player_state) noexcept {
    return mem::read<int>(detail::state_info(player_state), offsets::hw2_state_info::level, 0);
}

int sdk::hw2::experience_of(const APlayerState* player_state) noexcept {
    return mem::read<int>(detail::state_info(player_state), offsets::hw2_state_info::experience, 0);
}

int sdk::hw2::experience_to_level_of(const APlayerState* player_state) noexcept {
    return mem::read<int>(detail::state_info(player_state), offsets::hw2_state_info::experience_to_level, 0);
}

int sdk::hw2::max_level_of(const APlayerState* player_state) noexcept {
    return mem::read<int>(detail::state_info(player_state), offsets::hw2_state_info::max_level, 0);
}

bool sdk::hw2::set_level(APlayerState* player_state, int level) noexcept {
    return mem::write<int>(detail::state_info(player_state), offsets::hw2_state_info::level, level);
}

bool sdk::hw2::set_experience(APlayerState* player_state, int experience) noexcept {
    return mem::write<int>(detail::state_info(player_state), offsets::hw2_state_info::experience, experience);
}

double sdk::hw2::health_of(const APawn* pawn) noexcept {
    return mem::read<double>(detail::health_component(pawn), offsets::hw2_health::health, 0.0);
}

double sdk::hw2::max_health_of(const APawn* pawn) noexcept {
    return mem::read<double>(detail::health_component(pawn), offsets::hw2_health::max_health, 0.0);
}

bool sdk::hw2::is_dead(const APawn* pawn) noexcept {
    return mem::read<bool>(detail::health_component(pawn), offsets::hw2_health::is_dead, true);
}

int sdk::hw2::pending_unlocks(const APlayerController* controller) noexcept {
    const void* component = detail::progression(controller);

    return mem::read<TArray<void*>>(component, offsets::hw2_progression::pending_unlocks, TArray<void*>{}).num();
}

bool sdk::hw2::is_progression_loaded(const APlayerController* controller) noexcept {
    return mem::read<bool>(detail::progression(controller), offsets::hw2_progression::is_loaded, false);
}

bool sdk::hw2::apply_unlocks_for_level(APlayerController* controller, int level) {
    call::invocation entry(detail::progression(controller), "CheckUnlocksForLevel");
    if (!entry.is_valid()) return false;

    entry.set<int>(offsets::params::check_unlocks_for_level::new_level, level);

    return entry.fire();
}

bool sdk::hw2::save_progression(APlayerController* controller) {
    call::invocation entry(detail::progression(controller), "SaveProgression");

    return entry.is_valid() && entry.fire();
}

bool sdk::hw2::load_progression(APlayerController* controller) {
    call::invocation entry(detail::progression(controller), "LoadProgression");

    return entry.is_valid() && entry.fire();
}

bool sdk::hw2::is_weapon_unlocked(APlayerController* controller, int unlock_level) {
    call::invocation entry(detail::progression(controller), "IsWeaponUnlocked");
    if (!entry.is_valid()) return false;

    entry.set<int>(offsets::params::is_weapon_unlocked::unlock_level, unlock_level);
    if (!entry.fire()) return false;

    return entry.get<bool>(offsets::params::is_weapon_unlocked::is_unlocked);
}

bool sdk::hw2::raise_stat_to(APlayerController* controller, const char* key, int value) {
    UObject* component = detail::progression(controller);
    if (!component) return false;

    call::invocation entry(component, "RaiseStatTo");
    if (!entry.is_valid()) return false;

    const FString name = strings::make(key);
    if (!name.Data) return false;

    entry.set<FString>(offsets::params::raise_stat_to::key, name);
    entry.set<int>(offsets::params::raise_stat_to::value, value);

    return entry.fire();
}

bool sdk::hw2::add_stat(APlayerController* controller, const char* key, int amount) {
    UObject* component = detail::progression(controller);
    if (!component) return false;

    call::invocation entry(component, "AddStat");
    if (!entry.is_valid()) return false;

    const FString name = strings::make(key);
    if (!name.Data) return false;

    entry.set<FString>(offsets::params::add_stat::key, name);
    entry.set<int>(offsets::params::add_stat::amount, amount);

    return entry.fire();
}

std::vector<sdk::hw2::stat_entry> sdk::hw2::stats_of(const APlayerController* controller) {
    std::vector<stat_entry> found;

    const UObject* component = detail::progression(controller);
    if (!component) return found;

    const std::uint32_t at = offsets::hw2_progression::stats;
    auto* data = mem::pointer<std::uint8_t>(component, at + 0x00);
    const int total = mem::read<int>(component, at + 0x08, 0);
    if (!data || total <= 0 || total > 4096) return found;

    found.reserve(static_cast<size_t>(total));

    for (int i = 0; i < total; ++i) {
        const std::uint32_t slot = static_cast<std::uint32_t>(i) * 0x20;

        const FString key = mem::read<FString>(data, slot, FString{});

        if (!key.Data || key.NumElements <= 1 || key.NumElements > 512) continue;
        if (key.MaxElements < key.NumElements) continue;

        stat_entry entry;
        entry.key = narrow(key);
        entry.value = mem::read<int>(data, slot + 0x10, 0);

        if (!entry.key.empty()) found.push_back(std::move(entry));
    }

    return found;
}

bool sdk::hw2::call_set_level(APlayerState* player_state, int level) {
    UObject* component = detail::state_info(player_state);
    if (!component) return false;

    call::invocation entry(component, "SetLevel");
    if (!entry.is_valid()) return false;

    entry.set<int>(offsets::params::set_level::level, level);

    return entry.fire();
}

bool sdk::hw2::call_set_experience(APlayerState* player_state, int experience) {
    UObject* component = detail::state_info(player_state);
    if (!component) return false;

    call::invocation entry(component, "SetExperience");
    if (!entry.is_valid()) return false;

    entry.set<int>(offsets::params::set_experience::experience, experience);

    return entry.fire();
}

std::vector<std::string> sdk::hw2::weapon_names() {
    std::vector<std::string> found;

    UObject* enum_object = objects::find_by_name("E_WeaponNames");
    if (!enum_object) { say(note::error, "[ hw2 ] E_WeaponNames is not in the object array"); return found; }

    UClass* helper = objects::find_class("KismetNodeHelperLibrary");
    UObject* library = helper ? helper->default_object() : nullptr;
    if (!library) { say(note::error, "[ hw2 ] KismetNodeHelperLibrary has no default object"); return found; }

    for (int value = 0; value < 64; ++value) {
        call::invocation entry(library, "GetEnumeratorUserFriendlyName");
        if (!entry.is_valid()) break;

        entry.set<UObject*>(offsets::params::enumerator_name::enum_object, enum_object);
        entry.set<std::uint8_t>(offsets::params::enumerator_name::value, static_cast<std::uint8_t>(value));
        if (!entry.fire()) break;

        const FString text = entry.get<FString>(offsets::params::enumerator_name::return_value);
        const std::string name = narrow(text);

        if (name.empty()) break;

        found.push_back(name);
    }

    return found;
}
