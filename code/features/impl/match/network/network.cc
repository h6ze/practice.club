#include <features/features.hh>
#include <string>
#include <utility>
#include <features/impl/helpers.hh>

namespace features {

    void network_domain::tick() {
        const auto now = std::chrono::steady_clock::now();
        if (now > detail::network_watched_until || now < detail::next_network_refresh) return;
        if (detail::is_network_pass_queued.exchange(true)) return;

        detail::next_network_refresh = now + detail::panel_refresh_every;

        game::dispatch::post([]() {
            network_snapshot fresh = detail::take_network_snapshot();

            {
                const std::lock_guard<std::mutex> guard(detail::network_lock);
                detail::latest_network = std::move(fresh);
            }

            detail::is_network_pass_queued = false;
        });
    }

    void network_domain::watch() {
        detail::network_watched_until = std::chrono::steady_clock::now() + detail::panel_watch_window;
    }

    network_snapshot network_domain::snapshot() {
        const std::lock_guard<std::mutex> guard(detail::network_lock);

        return detail::latest_network;
    }

    void network_domain::kick() {
        const std::uintptr_t target = host_setup.target;
        const std::string reason = network_setup.reason;

        game::dispatch::post([target, reason]() {
            if (!detail::require_host("kicking someone")) return;

            sdk::APlayerState* member = detail::chosen_member(target);
            if (!member) return;

            sdk::AController* controller = sdk::hw2::controller_of(member);
            if (!sdk::lookup::derives_from(controller, "PlayerController")) { logger::error("[ network ] that is a bot -> remove it on the match tab"); return; }

            const std::string name = detail::name_of(member);
            detail::say_net(sdk::hw2::kick_player(static_cast<sdk::APlayerController*>(controller), reason.c_str()), name + " kicked", "KickPlayer");
        });
    }

    void network_domain::ban() {
        const std::uintptr_t target = host_setup.target;
        const std::string reason = network_setup.reason;

        game::dispatch::post([target, reason]() {
            if (!detail::require_host("banning someone from your lobby")) return;

            sdk::APlayerState* member = detail::chosen_member(target);
            if (!member) return;

            sdk::AController* controller = sdk::hw2::controller_of(member);
            if (!sdk::lookup::derives_from(controller, "PlayerController")) { logger::error("[ network ] that is a bot -> remove it on the match tab"); return; }

            const std::string name = detail::name_of(member);
            detail::say_net(sdk::hw2::ban_player(static_cast<sdk::APlayerController*>(controller), reason.c_str()), name + " banned from this session", "BanPlayer");
        });
    }

    void network_domain::lobby_access() {
        const network_options chosen = network_setup;

        game::dispatch::post([chosen]() {
            if (!detail::require_host("changing the lobby")) return;

            const bool is_sent = sdk::hw2::update_lobby(sdk::hw2::match_game_state(), chosen.public_connections, chosen.is_join_in_progress, chosen.is_allow_invites);
            detail::say_net(is_sent, std::string("lobby update sent -> joining mid match ") + (chosen.is_join_in_progress ? "open" : "closed")
                + ", " + std::to_string(chosen.public_connections) + " public slots", "UpdateSession");
        });
    }

    void network_domain::open_browser() {
        game::dispatch::post([]() {
            sdk::UObject* browser = sdk::hw2::open_server_browser(detail::own_controller());
            detail::open_browser = { browser, browser ? browser->index() : -1 };

            detail::say_net(browser != nullptr, "server browser opened", "UHW2ServerBrowserWidget::Open");
        });
    }

    void network_domain::refresh_browser() {
        game::dispatch::post([]() {
            if (!sdk::lookup::is_live(detail::open_browser)) { logger::error("[ network ] open the browser first"); return; }

            detail::say_net(sdk::hw2::refresh_server_browser(detail::open_browser.object, false), "server list refreshing", "Refresh");
        });
    }

    void network_domain::join_selected() {
        game::dispatch::post([]() {
            if (!sdk::lookup::is_live(detail::open_browser)) { logger::error("[ network ] open the browser first"); return; }

            detail::say_net(sdk::hw2::join_selected_server(detail::open_browser.object), "joining the server selected in the browser", "JoinSelected");
        });
    }

    void network_domain::refresh_friends() {
        game::dispatch::post([]() {
            detail::say_net(sdk::hw2::refresh_friends(detail::own_controller()), "friends list refreshing", "RefreshFriends");
        });
    }

    void network_domain::join_friend() {
        const int index = network_setup.friend_index;

        game::dispatch::post([index]() {
            detail::say_net(sdk::hw2::join_friend(detail::own_controller(), index), "joining friend " + std::to_string(index), "JoinFriend");
        });
    }

    void network_domain::invite_friend() {
        const int index = network_setup.friend_index;

        game::dispatch::post([index]() {
            detail::say_net(sdk::hw2::invite_friend(detail::own_controller(), index), "invite sent to friend " + std::to_string(index), "InviteFriend");
        });
    }

    void network_domain::open_invites() {
        game::dispatch::post([]() {
            detail::say_net(sdk::hw2::open_invite_screen(detail::own_controller()), "invite screen opened", "OpenInviteScreen");
        });
    }

    void network_domain::answer_invite(bool is_accept) {
        game::dispatch::post([is_accept]() {
            detail::say_net(sdk::hw2::answer_invite(detail::own_controller(), is_accept),
                std::string("pending invite ") + (is_accept ? "accepted" : "declined"), is_accept ? "AcceptPendingInvite" : "DeclinePendingInvite");
        });
    }

    void network_domain::hand_over_and_leave() {
        game::dispatch::post([]() {
            if (!detail::require_host("handing the match over")) return;

            const bool is_announced = sdk::hw2::announce_host_leaving();
            logger::info(std::string("[ network ] AnnounceHostLeaving answered ") + (is_announced ? "yes" : "no"));

            detail::say_net(sdk::hw2::leave_match(false), "leaving the match to the next host", "LeaveMatch");
        });
    }

    void network_domain::leave(bool is_to_desktop) {
        game::dispatch::post([is_to_desktop]() {
            detail::say_net(sdk::hw2::leave_match(is_to_desktop), is_to_desktop ? "leaving to the desktop" : "leaving the match", "LeaveMatch");
        });
    }

    void network_domain::announce() {
        const std::string text = network_setup.announcement;

        game::dispatch::post([text]() {
            if (text.empty()) { logger::error("[ network ] type the announcement first"); return; }
            if (!detail::require_host("announcing")) return;

            detail::say_net(sdk::hw2::announce_all(text.c_str()), "announced to everyone: " + text, "SendMessageToAll");
        });
    }

    void network_domain::announce_teams() {
        const std::string first = network_setup.team_0_text;
        const std::string second = network_setup.team_1_text;

        game::dispatch::post([first, second]() {
            if (first.empty() && second.empty()) { logger::error("[ network ] type at least one team's message"); return; }
            if (!detail::require_host("announcing")) return;

            detail::say_net(sdk::hw2::announce_teams(first.c_str(), second.c_str()), "team messages sent", "SendMessageTeam");
        });
    }

    void network_domain::objective_message() {
        const std::string text = network_setup.announcement;

        game::dispatch::post([text]() {
            if (text.empty()) { logger::error("[ network ] type the message first"); return; }
            if (!detail::require_host("showing an objective message")) return;

            detail::say_net(sdk::hw2::show_objective_message(text.c_str()), "objective banner shown: " + text, "ShowObjectiveMessage");
        });
    }

    void network_domain::save_report() {
        const std::string match_id = network_setup.match_id;

        game::dispatch::post([match_id]() {
            if (!detail::require_host("reading the match report")) return;

            const std::string json = sdk::hw2::match_report_json(match_id.c_str());
            if (json.empty()) { logger::error("[ network ] BuildReportJson gave nothing back -> the ledger fills on the host during a match"); return; }

            const std::string path = detail::write_report(json);
            if (path.empty()) { logger::error("[ network ] the report could not be written next to the journal"); return; }

            logger::success("[ network ] match report, " + std::to_string(json.size()) + " bytes, written to " + path);
        });
    }

    void network_domain::dump_report() {
        game::dispatch::post([]() {
            if (!detail::require_host("dumping the match report")) return;

            detail::say_net(sdk::hw2::dump_match_report(), "DebugDumpReport run -> it writes to the game's own log", "DebugDumpReport");
        });
    }

}
