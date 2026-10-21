#pragma once
#include <atomic>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <string>
#include <utility>
#include <features/features.hh>
#include <sdk/hw2/studio/capture.hh>
#include <sdk/hw2/hw2.hh>
#include <sdk/unreal/query/lookup.hh>
#include <sdk/hw2/lobby/session.hh>
#include <client/diag/log/logger.hh>
#include <features/impl/progress.hh>

namespace features::detail {

    inline std::mutex network_lock;
    inline network_snapshot latest_network;
    inline std::atomic<bool> is_network_pass_queued{ false };
    inline std::chrono::steady_clock::time_point network_watched_until;
    inline std::chrono::steady_clock::time_point next_network_refresh;

    inline std::mutex studio_lock;
    inline studio_snapshot latest_studio;
    inline std::atomic<bool> is_studio_pass_queued{ false };
    inline std::chrono::steady_clock::time_point studio_watched_until;
    inline std::chrono::steady_clock::time_point next_studio_refresh;
    inline std::chrono::steady_clock::time_point next_highlight_check;
    inline std::vector<std::string> known_replays;

    inline constexpr std::chrono::seconds panel_refresh_every{ 1 };
    inline constexpr std::chrono::seconds panel_watch_window{ 1 };
    inline constexpr std::chrono::milliseconds highlight_check_every{ 500 };

    inline sdk::lookup::held open_browser;

    inline int highlight_kills = -1;

    [[nodiscard]] inline network_snapshot take_network_snapshot() {
        network_snapshot fresh;

        const sdk::APlayerController* controller = own_controller();
        for (const sdk::hw2::friend_entry& entry : sdk::hw2::friends(controller))
            fresh.friends.push_back({ entry.name, entry.status, entry.is_joinable, entry.index });

        const sdk::hw2::invite_status invite = sdk::hw2::pending_invite(controller);
        fresh.has_invite = invite.has_invite;
        fresh.inviter = invite.inviter;

        const sdk::hw2::migration_status migration = sdk::hw2::read_migration();
        fresh.has_migration = migration.is_found;
        fresh.phase = migration.phase;
        fresh.is_migrating = migration.is_migrating;
        fresh.is_migration_host = migration.is_host;
        fresh.successor = migration.successor;

        return fresh;
    }

    [[nodiscard]] inline studio_snapshot take_studio_snapshot() {
        studio_snapshot fresh;

        const sdk::hw2::cine_status cine = sdk::hw2::read_cine();
        fresh.has_cine = cine.is_found;
        fresh.is_recording = cine.is_recording;
        fresh.is_god_mode = cine.is_god_mode;
        fresh.seconds = cine.seconds;
        fresh.cine_status = cine.status;

        const sdk::hw2::replay_status replay = sdk::hw2::read_replay();
        fresh.has_replay = replay.is_found;
        fresh.is_replay_recording = replay.is_recording;
        fresh.is_replay_playing = replay.is_playing;
        fresh.replay_status = replay.status;
        fresh.replays = known_replays;

        return fresh;
    }

    inline void check_kill_highlight() {
        const int kills = sdk::hw2::kills_of(own_state());
        const bool is_new_kill = highlight_kills >= 0 && kills > highlight_kills;
        highlight_kills = kills;

        if (!is_new_kill || !sdk::hw2::read_replay().is_recording) return;

        (void)sdk::hw2::replay_highlight("kill");
    }

    [[nodiscard]] inline std::string write_report(const std::string& json) {
        const std::time_t now = std::time(nullptr);
        std::tm local{};
        localtime_s(&local, &now);

        char stamp[32];
        std::strftime(stamp, sizeof(stamp), "%Y%m%d-%H%M%S", &local);

        const std::filesystem::path folder = std::filesystem::path(logger::file()).parent_path();
        const std::filesystem::path target = folder / (std::string("match-report-") + stamp + ".json");

        std::ofstream out(target, std::ios::binary);
        if (!out) return std::string{};

        out << json;

        return target.string();
    }

    inline void say_net(bool is_called, const std::string& done, const char* function_name) {
        if (is_called) { logger::success("[ network ] " + done); return; }

        logger::error(std::string("[ network ] ") + function_name + " could not be called, or answered no -> read the call line above");
    }

    inline void say_studio(bool is_called, const std::string& done, const char* function_name) {
        if (is_called) { logger::success("[ studio ] " + done); return; }

        logger::error(std::string("[ studio ] ") + function_name + " could not be called, or answered no -> read the call line above");
    }

}
