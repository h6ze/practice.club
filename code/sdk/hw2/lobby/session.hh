#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <sdk/unreal/engine.hh>

namespace sdk::hw2 {

    bool kick_player(APlayerController* target, const char* reason);
    bool ban_player(APlayerController* target, const char* reason);

    bool update_lobby(UObject* context, int public_connections, bool is_join_in_progress, bool is_allow_invites);

    [[nodiscard]] UObject* open_server_browser(APlayerController* controller);
    bool refresh_server_browser(UObject* browser, bool is_quiet);
    bool join_selected_server(UObject* browser);

    struct friend_entry {
        std::string name;
        std::string status;
        bool is_joinable = false;
        int index = 0;
    };

    [[nodiscard]] UObject* friends_system(const UObject* context);
    [[nodiscard]] std::vector<friend_entry> friends(const UObject* context);
    bool refresh_friends(const UObject* context);
    bool join_friend(const UObject* context, int index);
    bool invite_friend(const UObject* context, int index);
    bool open_invite_screen(const UObject* context);

    struct invite_status {
        bool is_found = false;
        bool has_invite = false;
        std::string inviter;
    };

    [[nodiscard]] invite_status pending_invite(const UObject* context);
    bool answer_invite(const UObject* context, bool is_accept);

    struct migration_status {
        bool is_found = false;
        int phase = 0;
        bool is_migrating = false;
        bool is_host = false;
        std::string successor;
    };

    [[nodiscard]] migration_status read_migration();
    bool leave_match(bool is_to_desktop);
    bool announce_host_leaving();

    [[nodiscard]] std::string match_report_json(const char* match_id);
    bool dump_match_report();

    bool announce_all(const char* text);
    bool announce_teams(const char* team_0, const char* team_1);
    bool show_objective_message(const char* text);

}
