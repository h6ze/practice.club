#include "players.hh"
#include <utility>
#include "camera.hh"
#include <sdk/globals.hh>
#include <sdk/hw2/hw2.hh>

namespace game::players::detail {

    constexpr double capsule_half_height = 88.0;
    constexpr double head_room = 12.0;
    constexpr double units_per_metre = 100.0;
    constexpr std::int32_t sane_player_cap = 128;

    std::vector<player>& roster() {
        static std::vector<player> value;
        return value;
    }

    int& local_slot() {
        static int value = -1;
        return value;
    }

    [[nodiscard]] player build(sdk::APlayerState* player_state) {
        player entry;
        entry.player_state = player_state;
        entry.name = player_state->PlayerNamePrivate();
        entry.team = sdk::hw2::team_of(player_state);
        entry.kills = sdk::hw2::kills_of(player_state);
        entry.deaths = sdk::hw2::deaths_of(player_state);
        entry.level = sdk::hw2::level_of(player_state);

        entry.pawn = player_state->PawnPrivate();
        if (!entry.pawn) return entry;

        entry.health = sdk::hw2::health_of(entry.pawn);
        entry.max_health = sdk::hw2::max_health_of(entry.pawn);
        entry.is_alive = !sdk::hw2::is_dead(entry.pawn) && entry.health > 0.0;

        entry.origin = entry.pawn->origin();
        if (entry.origin.is_zero()) {
            entry.is_alive = false;
            return entry;
        }

        entry.feet = { entry.origin.X, entry.origin.Y, entry.origin.Z - capsule_half_height };
        entry.head = { entry.origin.X, entry.origin.Y, entry.origin.Z + capsule_half_height + head_room };

        const camera::view& view = camera::current();
        entry.distance = static_cast<float>((entry.origin - view.location).length() / units_per_metre);
        entry.frame = camera::box_for(entry.feet, entry.head);

        return entry;
    }

}

void game::players::refresh() {
    std::vector<player>& list = detail::roster();
    list.clear();
    detail::local_slot() = -1;

    sdk::UWorld* world = sdk::globals::world();
    if (!world) return;

    sdk::AGameStateBase* game_state = world->GameState();
    if (!game_state) return;

    sdk::APlayerState* mine = nullptr;
    if (sdk::APlayerController* controller = world->local_controller()) mine = controller->PlayerState();

    const auto states = game_state->PlayerArray();
    const std::int32_t total = states.num();
    if (total <= 0 || total > detail::sane_player_cap) return;

    list.reserve(static_cast<size_t>(total));

    for (std::int32_t i = 0; i < total; ++i) {
        sdk::APlayerState* player_state = states.at(i);
        if (!player_state) continue;

        player entry = detail::build(player_state);
        entry.is_local = player_state == mine;

        if (entry.is_local) detail::local_slot() = static_cast<int>(list.size());

        list.push_back(std::move(entry));
    }

    const player* self = local();
    const int own_team = self ? self->team : -1;

    for (player& entry : list)
        entry.is_enemy = !entry.is_local && (own_team < 0 || entry.team != own_team);
}

const std::vector<game::player>& game::players::all() { return detail::roster(); }

const game::player* game::players::local() {
    const std::vector<player>& list = detail::roster();
    const int slot = detail::local_slot();

    return slot >= 0 && slot < static_cast<int>(list.size()) ? &list[static_cast<size_t>(slot)] : nullptr;
}
