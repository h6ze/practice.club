#include "rules.hh"
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/offsets.generated.hh>
#include <sdk/globals.hh>
#include <sdk/unreal/query/lookup.hh>
#include <sdk/unreal/runtime/strings.hh>

namespace sdk::hw2::detail {

    inline lookup::held team_capacity_library;
    inline lookup::held funny_mode_library;

    [[nodiscard]] inline std::uint32_t part_offset(match_part part) noexcept {
        switch (part) {
        case match_part::match_state: return offsets::hw2_game_state::match_state_system;
        case match_part::match_settings: return offsets::hw2_game_state::match_settings;
        case match_part::bot_manager: return offsets::hw2_game_state::bot_manager;
        case match_part::spawn_system: return offsets::hw2_game_state::spawn_system;
        case match_part::host_migration: return offsets::hw2_game_state::host_migration;
        case match_part::match_report: return offsets::hw2_game_state::match_report;
        }

        return 0;
    }

    [[nodiscard]] inline UObject* info_component(const APlayerState* player_state) noexcept {
        return mem::pointer<UObject>(player_state, offsets::hw2_player_state::state_info);
    }

    [[nodiscard]] inline UObject* team_part(const APlayerState* player_state) noexcept {
        return mem::pointer<UObject>(player_state, offsets::hw2_player_state::team_component);
    }

}

sdk::AGameStateBase* sdk::hw2::match_game_state() {
    UWorld* world = globals::world();
    AGameStateBase* state = world ? world->GameState() : nullptr;

    return lookup::derives_from(state, "BP_Base_GS_C") ? state : nullptr;
}

sdk::UObject* sdk::hw2::match_component(match_part part) {
    const AGameStateBase* state = match_game_state();
    if (!state) return nullptr;

    return mem::pointer<UObject>(state, detail::part_offset(part));
}

sdk::UObject* sdk::hw2::game_mode() {
    UWorld* world = globals::world();
    UObject* mode = world ? world->AuthorityGameMode() : nullptr;

    return lookup::derives_from(mode, "GameMode") ? mode : nullptr;
}

sdk::UObject* sdk::hw2::lobby_instance() {
    UWorld* world = globals::world();
    UObject* instance = world ? static_cast<UObject*>(world->OwningGameInstance()) : nullptr;

    return lookup::derives_from(instance, "BP_GameInstance_C") ? instance : nullptr;
}

bool sdk::hw2::read_scoreboard(scoreboard& board) noexcept {
    const UObject* system = match_component(match_part::match_state);
    if (!system) return false;

    namespace field = offsets::hw2_match_state;

    board.team_a = mem::read<int>(system, field::team_a_points);
    board.team_b = mem::read<int>(system, field::team_b_points);
    board.rounds_a = mem::read<int>(system, field::rounds_won_a);
    board.rounds_b = mem::read<int>(system, field::rounds_won_b);
    board.winner = mem::read<int>(system, field::winner_team);
    board.match_state = mem::read<std::uint8_t>(system, field::match_state);
    board.round_state = mem::read<std::uint8_t>(system, field::round_state);
    board.clock = mem::read<float>(system, field::match_time);
    board.time_to_start = mem::read<double>(system, field::time_left_to_start);

    return true;
}

bool sdk::hw2::set_team_points(int side, int points) {
    UObject* system = match_component(match_part::match_state);

    if (side == 0) return call::fire_with<int>(system, "SetTeamAPoints", offsets::params::set_team_a_points::points, points);

    return call::fire_with<int>(system, "SetTeamBPoints", offsets::params::set_team_b_points::points, points);
}

bool sdk::hw2::add_point(int team) {
    return call::fire_with<int>(match_component(match_part::match_state), "AddPoints", offsets::params::add_points::team, team);
}

bool sdk::hw2::add_round_won(int team, bool& is_game_over) {
    call::invocation entry(match_component(match_part::match_state), "AddRoundsWon");
    if (!entry.is_valid()) return false;

    entry.set<int>(offsets::params::add_rounds_won::team, team);
    if (!entry.fire()) return false;

    is_game_over = entry.get<bool>(offsets::params::add_rounds_won::is_game_over);

    return true;
}

bool sdk::hw2::set_winner(int team) {
    return call::fire_with<int>(match_component(match_part::match_state), "SetWinnerTeam", offsets::params::set_winner_team::winner, team);
}

bool sdk::hw2::end_round(int winner) {
    return call::fire_with<int>(match_component(match_part::match_state), "EndRound", offsets::params::end_round::winner, winner);
}

bool sdk::hw2::end_game() {
    return call::fire(match_component(match_part::match_state), "EndGame");
}

bool sdk::hw2::reset_scores() {
    return call::fire(match_component(match_part::match_state), "ResetScores");
}

bool sdk::hw2::flip_rounds() {
    return call::fire(match_component(match_part::match_state), "FlipRoundsWon");
}

bool sdk::hw2::set_match_state(std::uint8_t state) {
    return call::fire_with<std::uint8_t>(match_component(match_part::match_state), "SetMatchState", offsets::params::set_match_state::state, state);
}

bool sdk::hw2::set_round_state(std::uint8_t state) {
    return call::fire_with<std::uint8_t>(match_component(match_part::match_state), "SetRoundState", offsets::params::set_round_state::state, state);
}

bool sdk::hw2::start_match_timer() {
    return call::fire(match_component(match_part::match_state), "StartMatchTimer");
}

bool sdk::hw2::time_out() {
    return call::fire(match_component(match_part::match_state), "Timeout");
}

bool sdk::hw2::activate_uav(int team, APlayerState* instigator, double seconds) {
    call::invocation entry(match_component(match_part::match_state), "ActivateUAV");
    if (!entry.is_valid()) return false;

    namespace parm = offsets::params::activate_uav;

    entry.set<int>(parm::team, team);
    entry.set<APlayerState*>(parm::instigator, instigator);
    entry.set<double>(parm::seconds, seconds);

    return entry.fire();
}

bool sdk::hw2::apply_funny_match_settings() {
    UObject* settings = match_component(match_part::match_settings);
    if (!settings) return false;

    UObject* library = lookup::class_default(detail::funny_mode_library, "HW2FunnyModeLibrary");

    return call::fire_with<UObject*>(library, "ApplyFunnyMatchSettings", offsets::params::apply_funny_match_settings::match_settings, settings);
}

bool sdk::hw2::restart_player(AController* controller) {
    if (!controller) return false;

    return call::fire_with<AController*>(game_mode(), "RestartPlayer", offsets::params::restart_player::new_player, controller);
}

bool sdk::hw2::restart_game() {
    return call::fire(game_mode(), "RestartGame");
}

bool sdk::hw2::start_match() {
    return call::fire(game_mode(), "StartMatch");
}

bool sdk::hw2::end_match() {
    return call::fire(game_mode(), "EndMatch");
}

bool sdk::hw2::change_name(AController* controller, const char* name) {
    if (!controller || !name || !*name) return false;

    call::invocation entry(game_mode(), "ChangeName");
    if (!entry.is_valid()) return false;

    const FString text = strings::make(name);
    if (!text.Data) return false;

    namespace parm = offsets::params::change_name;

    entry.set<AController*>(parm::controller, controller);
    entry.set<FString>(parm::new_name, text);
    entry.set<bool>(parm::is_name_change, true);

    return entry.fire();
}

bool sdk::hw2::server_travel(const char* level) {
    if (!level || !*level) return false;

    const FString text = strings::make(level);
    if (!text.Data) return false;

    return call::fire_with<FString>(lobby_instance(), "ServerTravelToMap", offsets::params::server_travel_to_map::level, text);
}

bool sdk::hw2::create_new_match(const char* mode) {
    if (!mode || !*mode) return false;

    const FString text = strings::make(mode);
    if (!text.Data) return false;

    return call::fire_with<FString>(lobby_instance(), "CreateNewMatch", offsets::params::create_new_match::game_mode, text);
}

bool sdk::hw2::is_bot(const APlayerState* player_state) noexcept {
    return mem::read_bit(player_state, offsets::aplayer_state::is_bot, offsets::aplayer_state::is_bot_bit);
}

sdk::AController* sdk::hw2::controller_of(const APlayerState* player_state) noexcept {
    AActor* owner = player_state ? player_state->Owner() : nullptr;

    return lookup::derives_from(owner, "Controller") ? static_cast<AController*>(owner) : nullptr;
}

bool sdk::hw2::set_team(APlayerState* player_state, int team) {
    return call::fire_with<int>(detail::team_part(player_state), "SetTeam", offsets::params::team_set::team, team);
}

bool sdk::hw2::request_team(APlayerController* controller, int team) {
    return call::fire_with<int>(controller, "ControllerSetTeam", offsets::params::controller_set_team::team, team);
}

bool sdk::hw2::toggle_team(APlayerController* controller) {
    return call::fire(controller, "ToggleTeam");
}

bool sdk::hw2::flip_teams() {
    return call::fire(match_game_state(), "FlipTeams");
}

bool sdk::hw2::balance_teams() {
    return call::fire(match_game_state(), "BalanceTeams");
}

bool sdk::hw2::can_join_team(UObject* player, int team) {
    call::invocation entry(lookup::class_default(detail::team_capacity_library, "HW2TeamCapacityLibrary"), "HW2CanJoinTeam");
    if (!entry.is_valid()) return false;

    namespace parm = offsets::params::can_join_team;

    entry.set<UObject*>(parm::context, match_game_state());
    entry.set<UObject*>(parm::player, player);
    entry.set<int>(parm::team, team);
    if (!entry.fire()) return false;

    return entry.get<bool>(parm::return_value);
}

bool sdk::hw2::create_bots(int team_a, int team_b) {
    call::invocation entry(match_component(match_part::bot_manager), "CreateBots");
    if (!entry.is_valid()) return false;

    entry.set<int>(offsets::params::create_bots::team_a, team_a);
    entry.set<int>(offsets::params::create_bots::team_b, team_b);

    return entry.fire();
}

bool sdk::hw2::create_bots_ffa(int count) {
    return call::fire_with<int>(match_component(match_part::bot_manager), "CreateBotsFFA", offsets::params::create_bots_ffa::count, count);
}

bool sdk::hw2::remove_bot(APlayerState* player_state) {
    if (!player_state) return false;

    return call::fire_with<APlayerState*>(match_component(match_part::bot_manager), "RemoveBot", offsets::params::remove_bot::player_state, player_state);
}

bool sdk::hw2::remove_all_bots() {
    return call::fire(match_component(match_part::bot_manager), "RemoveAllBots");
}

bool sdk::hw2::respawn_bot(AController* controller) {
    if (!controller) return false;

    return call::fire_with<AController*>(match_component(match_part::bot_manager), "RespawnBot", offsets::params::respawn_bot::controller, controller);
}

bool sdk::hw2::remove_one_bot(int team) {
    return call::fire_with<int>(match_game_state(), "RemoveOneBotFromTeam", offsets::params::remove_one_bot::team, team);
}

int sdk::hw2::assists_of(const APlayerState* player_state) noexcept {
    return mem::read<int>(detail::info_component(player_state), offsets::hw2_scoreboard::assist, 0);
}

double sdk::hw2::score_of(const APlayerState* player_state) noexcept {
    return mem::read<double>(detail::info_component(player_state), offsets::hw2_scoreboard::player_score, 0.0);
}

bool sdk::hw2::set_player_score(APlayerState* player_state, double score) {
    return call::fire_with<double>(detail::info_component(player_state), "SetPlayerScore", offsets::params::set_player_score::score, score);
}

bool sdk::hw2::set_kills(APlayerState* player_state, int kills) {
    return call::fire_with<int>(detail::info_component(player_state), "SetKills", offsets::params::set_kills::kills, kills);
}

bool sdk::hw2::set_deaths(APlayerState* player_state, int deaths) {
    return call::fire_with<int>(detail::info_component(player_state), "SetDeaths", offsets::params::set_deaths::deaths, deaths);
}

bool sdk::hw2::set_assists(APlayerState* player_state, int assists) {
    return call::fire_with<int>(detail::info_component(player_state), "SetAssists", offsets::params::set_assists::assists, assists);
}
