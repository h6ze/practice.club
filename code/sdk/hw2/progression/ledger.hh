#pragma once
#include <cstdint>
#include <vector>
#include <sdk/unreal/engine.hh>

namespace sdk::hw2 {

    [[nodiscard]] UObject* online_settings();

    struct cloud_status {
        bool is_found = false;
        bool is_authenticated = false;
        int level = 0;
        int total_xp = 0;
        int pending = 0;
    };

    [[nodiscard]] cloud_status read_cloud(const APlayerController* controller);
    bool fetch_profile(APlayerController* controller);

    bool give_exp(APlayerState* player_state, int amount);
    bool add_experience(APlayerState* player_state, int amount);
    bool add_score(APlayerState* player_state, double score, std::uint8_t reason);
    bool increase_level(APlayerState* player_state);
    bool save_level(APlayerState* player_state);
    bool load_level(APlayerState* player_state);

    struct mission_entry {
        int id = 0;
        int progress = 0;
        int target = 0;
        int reward = 0;
        bool is_completed = false;
    };

    [[nodiscard]] UObject* missions_of(const APlayerState* player_state);
    [[nodiscard]] std::vector<mission_entry> missions(const APlayerState* player_state);

    [[nodiscard]] int complete_missions(APlayerState* player_state, int only_index);
    bool save_missions(APlayerState* player_state);
    bool missions_game_won(APlayerState* player_state, std::uint8_t mode);
    bool missions_player_killed(APlayerState* player_state, std::uint8_t weapon_type);

    [[nodiscard]] UObject* progression_of(const APlayerController* controller);
    bool notify_match_end(APlayerController* controller, bool is_won);
    bool record_kill(APlayerController* controller, bool is_headshot);
    bool notify_local_kill(APlayerController* controller, const char* kind);
    bool bump_weapon_stat(APlayerController* controller, const char* suffix);

}
