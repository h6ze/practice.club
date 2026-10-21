#pragma once
#include <string>
#include <vector>
#include <sdk/unreal/engine.hh>

namespace sdk::hw2 {

    [[nodiscard]] int team_of(const APlayerState* player_state) noexcept;
    [[nodiscard]] int kills_of(const APlayerState* player_state) noexcept;
    [[nodiscard]] int deaths_of(const APlayerState* player_state) noexcept;

    [[nodiscard]] int level_of(const APlayerState* player_state) noexcept;
    [[nodiscard]] int experience_of(const APlayerState* player_state) noexcept;
    [[nodiscard]] int experience_to_level_of(const APlayerState* player_state) noexcept;
    [[nodiscard]] int max_level_of(const APlayerState* player_state) noexcept;

    bool set_level(APlayerState* player_state, int level) noexcept;
    bool set_experience(APlayerState* player_state, int experience) noexcept;

    [[nodiscard]] double health_of(const APawn* pawn) noexcept;
    [[nodiscard]] double max_health_of(const APawn* pawn) noexcept;
    [[nodiscard]] bool is_dead(const APawn* pawn) noexcept;

    [[nodiscard]] int pending_unlocks(const APlayerController* controller) noexcept;
    [[nodiscard]] bool is_progression_loaded(const APlayerController* controller) noexcept;

    bool apply_unlocks_for_level(APlayerController* controller, int level);
    bool save_progression(APlayerController* controller);
    bool load_progression(APlayerController* controller);
    [[nodiscard]] bool is_weapon_unlocked(APlayerController* controller, int unlock_level);

    bool raise_stat_to(APlayerController* controller, const char* key, int value);
    bool add_stat(APlayerController* controller, const char* key, int amount);

    struct stat_entry {
        std::string key;
        int value = 0;
    };

    [[nodiscard]] std::vector<stat_entry> stats_of(const APlayerController* controller);

    [[nodiscard]] std::vector<std::string> weapon_names();

    bool call_set_level(APlayerState* player_state, int level);
    bool call_set_experience(APlayerState* player_state, int experience);

}
