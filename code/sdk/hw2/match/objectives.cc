#include "objectives.hh"
#include <cstring>
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/core/container.hh>
#include <sdk/offsets.generated.hh>
#include <sdk/unreal/query/lookup.hh>
#include "rules.hh"

namespace sdk::hw2::detail {

    inline lookup::held player_spawn_library;
    inline lookup::held spawn_choice_library;

    struct soft_class {
        std::uint8_t bytes[0x28] = {};
    };

    constexpr std::uint32_t soft_sub_path = 0x18;
    constexpr std::int32_t list_cap = 512;

    [[nodiscard]] inline std::vector<AActor*> actor_list(const void* owner, std::uint32_t offset) {
        std::vector<AActor*> found;

        const TArray<AActor*> items = mem::read<TArray<AActor*>>(owner, offset, TArray<AActor*>{});
        if (!items.Data || items.num() <= 0 || items.num() > list_cap) return found;

        for (std::int32_t i = 0; i < items.num(); ++i) {
            AActor* actor = mem::read<AActor*>(items.Data, static_cast<std::uint32_t>(i) * sizeof(void*), nullptr);
            if (actor) found.push_back(actor);
        }

        return found;
    }

    [[nodiscard]] inline UObject* mode_state(const char* class_name) {
        AGameStateBase* state = match_game_state();

        return lookup::derives_from(state, class_name) ? state : nullptr;
    }

}

sdk::hw2::objective_kind sdk::hw2::objective_kind_of(const AActor* objective) {
    if (lookup::derives_from(objective, "BP_ConquestCapturePoint_C")) return objective_kind::capture_point;
    if (lookup::derives_from(objective, "BP_SearchAndDestroyObjective_C")) return objective_kind::snd_site;
    if (lookup::derives_from(objective, "BP_RushObjective_C")) return objective_kind::rush_site;

    return objective_kind::other;
}

sdk::hw2::match_mode sdk::hw2::mode_of_match() {
    const AGameStateBase* state = match_game_state();
    if (!state) return match_mode::other;

    if (lookup::derives_from(state, "BP_Conquest_GS_C")) return match_mode::conquest;
    if (lookup::derives_from(state, "BP_Rush_GS_C")) return match_mode::rush;
    if (lookup::derives_from(state, "BP_SearchAndDestroy_GS_C")) return match_mode::search_and_destroy;
    if (lookup::derives_from(state, "BP_FreeForAll_GS_C")) return match_mode::free_for_all;
    if (lookup::derives_from(state, "BP_TeamDeathmatch_GS_C")) return match_mode::team_deathmatch;

    return match_mode::other;
}

std::vector<sdk::AActor*> sdk::hw2::objectives() {
    return detail::actor_list(match_game_state(), offsets::hw2_game_state::objectives);
}

sdk::FName sdk::hw2::objective_id(const AActor* objective) noexcept {
    return mem::read<FName>(objective, offsets::hw2_objective_base::id, FName{});
}

bool sdk::hw2::capture_point(AActor* point, std::uint8_t state) {
    if (objective_kind_of(point) != objective_kind::capture_point) return false;

    return call::fire_with<std::uint8_t>(point, "CapturePoint", offsets::params::capture_point::state, state);
}

bool sdk::hw2::secure_point(AActor* point) {
    if (objective_kind_of(point) != objective_kind::capture_point) return false;

    return call::fire(point, "SecurePoint");
}

bool sdk::hw2::recover_point(AActor* point) {
    if (objective_kind_of(point) != objective_kind::capture_point) return false;

    return call::fire(point, "RecoverLastState");
}

bool sdk::hw2::give_objective_points(AActor* point, bool is_team, double score, std::uint8_t reason) {
    if (objective_kind_of(point) != objective_kind::capture_point) return false;

    call::invocation entry(point, "Server_GivePoints");
    if (!entry.is_valid()) return false;

    namespace parm = offsets::params::give_objective_points;

    entry.set<bool>(parm::is_team, is_team);
    entry.set<double>(parm::score, score);
    entry.set<std::uint8_t>(parm::reason, reason);

    return entry.fire();
}

bool sdk::hw2::set_point_holder(bool is_holder_team, std::uint8_t point) {
    call::invocation entry(detail::mode_state("BP_Conquest_GS_C"), "SetCapturePointHolder");
    if (!entry.is_valid()) return false;

    entry.set<bool>(offsets::params::set_point_holder::holder_team, is_holder_team);
    entry.set<std::uint8_t>(offsets::params::set_point_holder::point, point);

    return entry.fire();
}

bool sdk::hw2::plant_bomb(AActor* site, APawn* by) {
    const objective_kind kind = objective_kind_of(site);
    if (kind == objective_kind::snd_site) return call::fire_with<APawn*>(site, "Server_ActivateBomb", offsets::params::snd_activate_bomb::pawn, by);
    if (kind == objective_kind::rush_site) return call::fire_with<APawn*>(site, "Server_ActivateBomb", offsets::params::rush_activate_bomb::pawn, by);

    return false;
}

bool sdk::hw2::disarm_bomb(AActor* site, APawn* by) {
    const objective_kind kind = objective_kind_of(site);
    if (kind == objective_kind::snd_site) return call::fire_with<APawn*>(site, "Deactivate_Bomb", offsets::params::snd_deactivate_bomb::pawn, by);
    if (kind == objective_kind::rush_site) return call::fire_with<APawn*>(site, "Deactivate_Bomb", offsets::params::rush_deactivate_bomb::pawn, by);

    return false;
}

bool sdk::hw2::explode_bomb(AActor* site) {
    const objective_kind kind = objective_kind_of(site);
    if (kind != objective_kind::snd_site && kind != objective_kind::rush_site) return false;

    return call::fire(site, "ExplodeBomb");
}

bool sdk::hw2::defuse_bomb(AActor* site) {
    const objective_kind kind = objective_kind_of(site);
    if (kind != objective_kind::snd_site && kind != objective_kind::rush_site) return false;

    return call::fire(site, "Defuse_Bomb");
}

sdk::AActor* sdk::hw2::snd_bomb() {
    AActor* bomb = mem::pointer<AActor>(detail::mode_state("BP_SearchAndDestroy_GS_C"), offsets::hw2_snd_state::bomb);
    if (lookup::derives_from(bomb, "BP_SearchAndDestroy_Bomb_C")) return bomb;

    return nullptr;
}

sdk::AActor* sdk::hw2::bomb_carrier(const AActor* bomb) noexcept {
    return mem::pointer<AActor>(bomb, offsets::hw2_snd_bomb::carrier);
}

bool sdk::hw2::give_bomb(AActor* bomb, APawn* character) {
    if (!character) return false;

    return call::fire_with<APawn*>(bomb, "AttachToCharacter", offsets::params::attach_bomb::character, character);
}

bool sdk::hw2::drop_bomb(AActor* bomb) {
    return call::fire(bomb, "DropBomb");
}

bool sdk::hw2::reset_bomb(AActor* bomb) {
    return call::fire(bomb, "ResetBomb");
}

bool sdk::hw2::reset_reinforcements() {
    return call::fire(detail::mode_state("BP_Rush_GS_C"), "ResetReinforcements");
}

bool sdk::hw2::rush_phase_spawns(int phase, int team) {
    call::invocation entry(detail::mode_state("BP_Rush_GS_C"), "ActivateSpawnsForTheNewPhase");
    if (!entry.is_valid()) return false;

    entry.set<int>(offsets::params::rush_phase_spawns::phase, phase);
    entry.set<int>(offsets::params::rush_phase_spawns::team, team);

    return entry.fire();
}

bool sdk::hw2::choose_attack_site() {
    return call::fire(detail::mode_state("BP_SearchAndDestroy_GS_C"), "ChooseAttackSiteRandom");
}

bool sdk::hw2::pick_round_sites() {
    return call::fire(detail::mode_state("BP_SearchAndDestroy_GS_C"), "PickRoundSites");
}

bool sdk::hw2::force_spawn() {
    return call::fire(detail::mode_state("BP_SearchAndDestroy_GS_C"), "ForceSpawn");
}

bool sdk::hw2::refresh_rosters() {
    return call::fire(detail::mode_state("BP_SearchAndDestroy_GS_C"), "RefreshRosters");
}

bool sdk::hw2::check_ffa_winner() {
    return call::fire(detail::mode_state("BP_FreeForAll_GS_C"), "CheckWinnerPoints");
}

std::vector<sdk::AActor*> sdk::hw2::spawn_points() {
    return detail::actor_list(match_component(match_part::spawn_system), offsets::hw2_spawn_system::spawns);
}

bool sdk::hw2::set_spawn_active(AActor* spawn, bool is_active) {
    if (!lookup::derives_from(spawn, "BP_PlayerSpawn_C")) return false;

    return call::fire_with<bool>(spawn, "SetActive", offsets::params::set_spawn_active::is_active, is_active);
}

bool sdk::hw2::spawn_at_point(AActor* spawn, APlayerController* controller, int team) {
    if (!controller || !lookup::derives_from(spawn, "BP_PlayerSpawn_C")) return false;

    call::invocation entry(match_component(match_part::spawn_system), "SpawnPlayer");
    if (!entry.is_valid()) return false;

    namespace parm = offsets::params::spawn_at_point;

    entry.set<AActor*>(parm::spawn, spawn);
    entry.set<APlayerController*>(parm::controller, controller);
    entry.set<int>(parm::team, team);

    return entry.fire();
}

bool sdk::hw2::spawn_with_team(APlayerController* controller) {
    if (!controller) return false;

    return call::fire_with<APlayerController*>(match_component(match_part::spawn_system), "Server_SpawnPlayerWithTeam",
        offsets::params::spawn_with_team::controller, controller);
}

bool sdk::hw2::spawn_player_pawn(AController* controller, AActor* spawn_point, const UObject* operator_info) {
    if (!controller || !spawn_point || !lookup::derives_from(operator_info, "PDA_Operator_Info_C")) return false;

    detail::soft_class pawn_class;
    if (!mem::copy(pawn_class.bytes, reinterpret_cast<const std::uint8_t*>(operator_info) + offsets::hw2_operator_info::operator_class, sizeof(pawn_class.bytes))) return false;

    void* sub_path = nullptr;
    std::memcpy(&sub_path, pawn_class.bytes + detail::soft_sub_path, sizeof(sub_path));
    if (sub_path) return false;

    call::invocation entry(lookup::class_default(detail::player_spawn_library, "HW2PlayerSpawnLibrary"), "HW2SpawnPlayerPawn");
    if (!entry.is_valid()) return false;

    namespace parm = offsets::params::spawn_player_pawn;

    entry.set<AController*>(parm::controller, controller);
    entry.set<AActor*>(parm::spawn_point, spawn_point);
    entry.set<detail::soft_class>(parm::pawn_class, pawn_class);

    return entry.fire();
}

sdk::AActor* sdk::hw2::preview_spawn(int team, bool is_ffa, AController* for_player) {
    UObject* system = match_component(match_part::spawn_system);
    if (!system) return nullptr;

    call::invocation entry(lookup::class_default(detail::spawn_choice_library, "HW2BotLibrary"), "HW2ChooseSpawn");
    if (!entry.is_valid()) return nullptr;

    namespace parm = offsets::params::choose_spawn;

    entry.set<UObject*>(parm::spawn_system, system);
    entry.set<int>(parm::team, team);
    entry.set<bool>(parm::is_ffa, is_ffa);
    entry.set<AController*>(parm::for_player, for_player);
    if (!entry.fire()) return nullptr;

    return entry.get<AActor*>(parm::return_value);
}

bool sdk::hw2::request_spawn(APlayerController* controller, bool is_force) {
    return call::fire_with<bool>(controller, "Spawn", offsets::params::controller_spawn::is_force, is_force);
}

bool sdk::hw2::simulate_resume(float clock, int team_a, int team_b) {
    call::invocation entry(match_component(match_part::host_migration), "DebugSimulateResume");
    if (!entry.is_valid()) return false;

    namespace parm = offsets::params::simulate_resume;

    entry.set<float>(parm::clock, clock);
    entry.set<int>(parm::team_a, team_a);
    entry.set<int>(parm::team_b, team_b);

    return entry.fire();
}
