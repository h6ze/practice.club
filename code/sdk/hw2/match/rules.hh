#pragma once
#include <cstdint>
#include <sdk/unreal/engine.hh>

namespace sdk::hw2 {

    enum class match_part : std::uint8_t { match_state, match_settings, bot_manager, spawn_system, host_migration, match_report };

    [[nodiscard]] UObject* match_component(match_part part);
    [[nodiscard]] AGameStateBase* match_game_state();

    [[nodiscard]] UObject* game_mode();
    [[nodiscard]] UObject* lobby_instance();

    struct scoreboard {
        int team_a = 0;
        int team_b = 0;
        int rounds_a = 0;
        int rounds_b = 0;
        int winner = 0;
        std::uint8_t match_state = 0;
        std::uint8_t round_state = 0;
        float clock = 0.0f;
        double time_to_start = 0.0;
    };

    [[nodiscard]] bool read_scoreboard(scoreboard& board) noexcept;

    bool set_team_points(int side, int points);
    bool add_point(int team);
    bool add_round_won(int team, bool& is_game_over);
    bool set_winner(int team);
    bool end_round(int winner);
    bool end_game();
    bool reset_scores();
    bool flip_rounds();
    bool set_match_state(std::uint8_t state);
    bool set_round_state(std::uint8_t state);
    bool start_match_timer();
    bool time_out();

    bool activate_uav(int team, APlayerState* instigator, double seconds);

    bool apply_funny_match_settings();

    bool restart_player(AController* controller);
    bool restart_game();
    bool start_match();
    bool end_match();
    bool change_name(AController* controller, const char* name);

    bool server_travel(const char* level);
    bool create_new_match(const char* mode);

    [[nodiscard]] bool is_bot(const APlayerState* player_state) noexcept;
    [[nodiscard]] AController* controller_of(const APlayerState* player_state) noexcept;

    bool set_team(APlayerState* player_state, int team);
    bool request_team(APlayerController* controller, int team);
    bool toggle_team(APlayerController* controller);
    bool flip_teams();
    bool balance_teams();
    [[nodiscard]] bool can_join_team(UObject* player, int team);

    bool create_bots(int team_a, int team_b);
    bool create_bots_ffa(int count);
    bool remove_bot(APlayerState* player_state);
    bool remove_all_bots();
    bool respawn_bot(AController* controller);
    bool remove_one_bot(int team);

    [[nodiscard]] int assists_of(const APlayerState* player_state) noexcept;
    [[nodiscard]] double score_of(const APlayerState* player_state) noexcept;

    bool set_player_score(APlayerState* player_state, double score);
    bool set_kills(APlayerState* player_state, int kills);
    bool set_deaths(APlayerState* player_state, int deaths);
    bool set_assists(APlayerState* player_state, int assists);

}
