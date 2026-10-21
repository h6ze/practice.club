#pragma once
#include <string>
#include <vector>
#include "host.hh"

namespace features {

    struct friend_view {
        std::string name;
        std::string status;
        bool is_joinable = false;
        int index = 0;
    };

    struct network_snapshot {
        std::vector<friend_view> friends;
        bool has_invite = false;
        std::string inviter;
        bool has_migration = false;
        int phase = 0;
        bool is_migrating = false;
        bool is_migration_host = false;
        std::string successor;
    };

    struct network_options {
        char reason[64] = "removed by the host";
        char announcement[96] = "";
        char team_0_text[96] = "";
        char team_1_text[96] = "";

        int public_connections = 12;
        bool is_join_in_progress = true;
        bool is_allow_invites = true;

        int friend_index = 0;
        char match_id[32] = "practice";
    };

    inline network_options network_setup;

    struct network_domain {
        void tick();
        void watch();
        [[nodiscard]] network_snapshot snapshot();

        void kick();
        void ban();

        void lobby_access();
        void open_browser();
        void refresh_browser();
        void join_selected();

        void refresh_friends();
        void join_friend();
        void invite_friend();
        void open_invites();
        void answer_invite(bool is_accept);

        void hand_over_and_leave();
        void leave(bool is_to_desktop);

        void announce();
        void announce_teams();
        void objective_message();

        void save_report();
        void dump_report();
    };

    inline network_domain network;

}
