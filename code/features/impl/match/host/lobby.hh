#pragma once
#include <atomic>
#include <cstdint>
#include <mutex>
#include <string>
#include <utility>
#include <features/features.hh>
#include <sdk/hw2/hw2.hh>
#include <sdk/hw2/match/rules.hh>
#include <client/diag/log/logger.hh>
#include <features/impl/progress.hh>

namespace features::detail {

    inline std::mutex snapshot_lock;
    inline match_snapshot latest_snapshot;
    inline std::atomic<bool> is_host_pass_queued{ false };

    inline constexpr std::int32_t lobby_cap = 128;

    [[nodiscard]] inline bool is_hosting() {
        return sdk::hw2::game_mode() != nullptr;
    }

    [[nodiscard]] inline sdk::APlayerState* lobby_member(std::uintptr_t id) {
        if (!id) return nullptr;

        const sdk::AGameStateBase* state = sdk::hw2::match_game_state();
        if (!state) return nullptr;

        const sdk::TArray<sdk::APlayerState*> players = state->PlayerArray();
        if (players.num() <= 0 || players.num() > lobby_cap) return nullptr;

        for (std::int32_t i = 0; i < players.num(); ++i) {
            sdk::APlayerState* member = players.at(i);
            if (reinterpret_cast<std::uintptr_t>(member) == id) return member;
        }

        return nullptr;
    }

    [[nodiscard]] inline bool require_host(const char* what) {
        if (is_hosting()) return true;

        logger::error(std::string("[ host ] ") + what + " needs you to host -> on a client the match components are replicated copies");

        return false;
    }

    [[nodiscard]] inline sdk::APlayerState* chosen_member(std::uintptr_t id) {
        if (!id) { logger::error("[ host ] pick a player in the list first"); return nullptr; }

        sdk::APlayerState* member = lobby_member(id);
        if (!member) logger::error("[ host ] that player is no longer in the match -> pick again");

        return member;
    }

    inline void say_call(bool is_called, const std::string& done, const char* function_name) {
        if (is_called) { logger::success("[ host ] " + done); return; }

        logger::error(std::string("[ host ] ") + function_name + " could not be called -> load into a match, or read the call line above nigger");
    }

    [[nodiscard]] inline std::string name_of(const sdk::APlayerState* member) {
        std::string name = member ? member->PlayerNamePrivate() : std::string{};

        return name.empty() ? std::string("unnamed") : name;
    }

    [[nodiscard]] inline match_snapshot take_snapshot() {
        match_snapshot fresh;
        fresh.is_host = is_hosting();

        sdk::hw2::scoreboard board;
        fresh.has_match = sdk::hw2::read_scoreboard(board);
        fresh.team_a = board.team_a;
        fresh.team_b = board.team_b;
        fresh.rounds_a = board.rounds_a;
        fresh.rounds_b = board.rounds_b;
        fresh.winner = board.winner;
        fresh.match_state = board.match_state;
        fresh.round_state = board.round_state;
        fresh.clock = board.clock;
        fresh.time_to_start = board.time_to_start;

        const sdk::AGameStateBase* state = sdk::hw2::match_game_state();
        if (!state) return fresh;

        const sdk::TArray<sdk::APlayerState*> players = state->PlayerArray();
        if (players.num() <= 0 || players.num() > lobby_cap) return fresh;

        const sdk::APlayerState* mine = own_state();
        fresh.players.reserve(static_cast<size_t>(players.num()));

        for (std::int32_t i = 0; i < players.num(); ++i) {
            const sdk::APlayerState* member = players.at(i);
            if (!member) continue;

            lobby_entry entry;
            entry.id = reinterpret_cast<std::uintptr_t>(member);
            entry.name = member->PlayerNamePrivate();
            entry.team = sdk::hw2::team_of(member);
            entry.kills = sdk::hw2::kills_of(member);
            entry.deaths = sdk::hw2::deaths_of(member);
            entry.assists = sdk::hw2::assists_of(member);
            entry.score = sdk::hw2::score_of(member);
            entry.is_bot = sdk::hw2::is_bot(member);
            entry.is_local = member == mine;

            const sdk::APawn* pawn = member->PawnPrivate();
            entry.is_alive = pawn && !sdk::hw2::is_dead(pawn);

            fresh.players.push_back(std::move(entry));
        }

        return fresh;
    }

}
