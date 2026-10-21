#pragma once
#include <cstdint>
#include <vector>
#include <sdk/unreal/engine.hh>

namespace sdk::hw2 {

    enum class objective_kind : std::uint8_t { other, capture_point, snd_site, rush_site };
    enum class match_mode : std::uint8_t { other, conquest, rush, search_and_destroy, free_for_all, team_deathmatch };

    [[nodiscard]] objective_kind objective_kind_of(const AActor* objective);
    [[nodiscard]] match_mode mode_of_match();

    [[nodiscard]] std::vector<AActor*> objectives();
    [[nodiscard]] FName objective_id(const AActor* objective) noexcept;

    bool capture_point(AActor* point, std::uint8_t state);
    bool secure_point(AActor* point);
    bool recover_point(AActor* point);
    bool give_objective_points(AActor* point, bool is_team, double score, std::uint8_t reason);
    bool set_point_holder(bool is_holder_team, std::uint8_t point);

    bool plant_bomb(AActor* site, APawn* by);
    bool disarm_bomb(AActor* site, APawn* by);
    bool explode_bomb(AActor* site);
    bool defuse_bomb(AActor* site);

    [[nodiscard]] AActor* snd_bomb();
    [[nodiscard]] AActor* bomb_carrier(const AActor* bomb) noexcept;
    bool give_bomb(AActor* bomb, APawn* character);
    bool drop_bomb(AActor* bomb);
    bool reset_bomb(AActor* bomb);

    bool reset_reinforcements();
    bool rush_phase_spawns(int phase, int team);
    bool choose_attack_site();
    bool pick_round_sites();
    bool force_spawn();
    bool refresh_rosters();
    bool check_ffa_winner();

    [[nodiscard]] std::vector<AActor*> spawn_points();
    bool set_spawn_active(AActor* spawn, bool is_active);

    bool spawn_at_point(AActor* spawn, APlayerController* controller, int team);
    bool spawn_with_team(APlayerController* controller);

    bool spawn_player_pawn(AController* controller, AActor* spawn_point, const UObject* operator_info);

    [[nodiscard]] AActor* preview_spawn(int team, bool is_ffa, AController* for_player);

    bool request_spawn(APlayerController* controller, bool is_force);

    bool simulate_resume(float clock, int team_a, int team_b);

}
