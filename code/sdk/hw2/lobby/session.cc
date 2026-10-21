#include "session.hh"
#include <Windows.h>
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/core/container.hh>
#include <sdk/core/text/encoding.hh>
#include <sdk/offsets.generated.hh>
#include <sdk/unreal/query/lookup.hh>
#include <sdk/hw2/match/rules.hh>
#include <sdk/unreal/runtime/strings.hh>

namespace sdk::hw2::detail {

    inline lookup::held text_library;
    inline lookup::held sessions_library;
    inline lookup::held update_proxy_default;
    inline lookup::held browser_default;
    inline lookup::held friends_default;
    inline lookup::held invite_default;

    inline lookup::held migration_system;
    inline ULONGLONG next_migration_search = 0;
    constexpr ULONGLONG instance_search_every_ms = 3000;
    constexpr std::int32_t friend_cap = 512;

    struct text_value {
        std::uint8_t bytes[0x18] = {};
    };

    [[nodiscard]] inline bool make_text(const char* text, text_value& value) {
        if (!text) return false;

        const FString source = strings::make(*text ? text : " ");
        if (!source.Data) return false;

        call::invocation entry(lookup::class_default(text_library, "KismetTextLibrary"), "Conv_StringToText");
        if (!entry.is_valid()) return false;

        entry.set<FString>(offsets::params::string_to_text::in_string, source);
        if (!entry.fire()) return false;

        value = entry.get<text_value>(offsets::params::string_to_text::return_value);

        return true;
    }

    [[nodiscard]] inline std::string get_text(UObject* object, const char* function_name, std::uint32_t offset) {
        call::invocation entry(object, function_name);
        if (!entry.is_valid() || !entry.fire()) return std::string{};

        return narrow(entry.get<FString>(offset));
    }

    template <class T> [[nodiscard]] inline T get_value(UObject* object, const char* function_name, std::uint32_t offset) {
        call::invocation entry(object, function_name);
        if (!entry.is_valid() || !entry.fire()) return T{};

        return entry.get<T>(offset);
    }

    [[nodiscard]] inline UObject* subsystem_from(lookup::held& slot, const char* class_name, const UObject* context, std::uint32_t context_at, std::uint32_t return_at) {
        call::invocation entry(lookup::class_default(slot, class_name), "Get");
        if (!entry.is_valid()) return nullptr;

        entry.set<const UObject*>(context_at, context);
        if (!entry.fire()) return nullptr;

        return entry.get<UObject*>(return_at);
    }

    [[nodiscard]] inline UObject* invite_system(const UObject* context) {
        return subsystem_from(invite_default, "HW2InviteSubsystem", context, offsets::params::invite_get::context, offsets::params::invite_get::return_value);
    }

    [[nodiscard]] inline UObject* migration_subsystem() {
        if (lookup::is_live(migration_system)) return migration_system.object;

        const ULONGLONG now = GetTickCount64();
        if (now < next_migration_search) return nullptr;
        next_migration_search = now + instance_search_every_ms;

        UObject* found = objects::find_live_instance(objects::find_class("HW2HostMigrationSubsystem"));
        migration_system = { found, found ? found->index() : -1 };

        return found;
    }

    [[nodiscard]] inline bool admin_call(const char* function_name, std::uint32_t context_at, std::uint32_t controller_at, std::uint32_t reason_at,
        std::uint32_t return_at, APlayerController* target, const char* reason) {
        if (!target) return false;

        text_value text;
        if (!make_text(reason, text)) return false;

        call::invocation entry(lookup::class_default(sessions_library, "AdvancedSessionsLibrary"), function_name);
        if (!entry.is_valid()) return false;

        entry.set<UObject*>(context_at, match_game_state());
        entry.set<APlayerController*>(controller_at, target);
        entry.set<text_value>(reason_at, text);
        if (!entry.fire()) return false;

        return entry.get<bool>(return_at);
    }

}

bool sdk::hw2::kick_player(APlayerController* target, const char* reason) {
    namespace parm = offsets::params::kick_player;

    return detail::admin_call("KickPlayer", parm::context, parm::controller, parm::reason, parm::return_value, target, reason);
}

bool sdk::hw2::ban_player(APlayerController* target, const char* reason) {
    namespace parm = offsets::params::ban_player;

    return detail::admin_call("BanPlayer", parm::context, parm::controller, parm::reason, parm::return_value, target, reason);
}

bool sdk::hw2::update_lobby(UObject* context, int public_connections, bool is_join_in_progress, bool is_allow_invites) {
    if (!context) return false;

    call::invocation entry(lookup::class_default(detail::update_proxy_default, "UpdateSessionCallbackProxyAdvanced"), "UpdateSession");
    if (!entry.is_valid()) return false;

    namespace parm = offsets::params::update_session;

    entry.set<UObject*>(parm::context, context);
    entry.set<int>(parm::public_connections, public_connections);
    entry.set<int>(parm::private_connections, 0);
    entry.set<bool>(parm::is_lan, false);
    entry.set<bool>(parm::is_allow_invites, is_allow_invites);
    entry.set<bool>(parm::is_join_in_progress, is_join_in_progress);
    entry.set<bool>(parm::is_refresh, true);
    entry.set<bool>(parm::is_dedicated, false);
    entry.set<bool>(parm::is_advertise, true);
    entry.set<bool>(parm::is_join_presence, true);
    entry.set<bool>(parm::is_join_friends_only, false);
    if (!entry.fire()) return false;

    return call::fire(entry.get<UObject*>(parm::return_value), "Activate");
}

sdk::UObject* sdk::hw2::open_server_browser(APlayerController* controller) {
    if (!controller) return nullptr;

    call::invocation entry(lookup::class_default(detail::browser_default, "HW2ServerBrowserWidget"), "Open");
    if (!entry.is_valid()) return nullptr;

    entry.set<APlayerController*>(offsets::params::browser_open::controller, controller);
    if (!entry.fire()) return nullptr;

    return entry.get<UObject*>(offsets::params::browser_open::return_value);
}

bool sdk::hw2::refresh_server_browser(UObject* browser, bool is_quiet) {
    return call::fire_with<bool>(browser, "Refresh", offsets::params::browser_refresh::is_quiet, is_quiet);
}

bool sdk::hw2::join_selected_server(UObject* browser) {
    return call::fire(browser, "JoinSelected");
}

sdk::UObject* sdk::hw2::friends_system(const UObject* context) {
    return detail::subsystem_from(detail::friends_default, "HW2FriendsSubsystem", context,
        offsets::params::friends_get::context, offsets::params::friends_get::return_value);
}

std::vector<sdk::hw2::friend_entry> sdk::hw2::friends(const UObject* context) {
    std::vector<friend_entry> found;

    const UObject* system = friends_system(context);
    const TArray<std::uint8_t> list = mem::read<TArray<std::uint8_t>>(system, offsets::hw2_friends::friends, TArray<std::uint8_t>{});
    if (!list.Data || list.num() <= 0 || list.num() > detail::friend_cap) return found;

    for (std::int32_t i = 0; i < list.num(); ++i) {
        const std::uint8_t* item = list.Data + offsets::hw2_friend_entry::byte_size * static_cast<std::uint32_t>(i);

        friend_entry entry;
        entry.name = narrow(mem::read<FString>(item, offsets::hw2_friend_entry::display_name, FString{}));
        entry.status = narrow(mem::read<FString>(item, offsets::hw2_friend_entry::status_text, FString{}));
        entry.is_joinable = mem::read<bool>(item, offsets::hw2_friend_entry::is_joinable);
        entry.index = mem::read<int>(item, offsets::hw2_friend_entry::friend_index);

        found.push_back(std::move(entry));
    }

    return found;
}

bool sdk::hw2::refresh_friends(const UObject* context) {
    return call::fire(friends_system(context), "RefreshFriends");
}

bool sdk::hw2::join_friend(const UObject* context, int index) {
    call::invocation entry(friends_system(context), "JoinFriend");
    if (!entry.is_valid()) return false;

    entry.set<int>(offsets::params::join_friend::index, index);
    if (!entry.fire()) return false;

    return entry.get<bool>(offsets::params::join_friend::return_value);
}

bool sdk::hw2::invite_friend(const UObject* context, int index) {
    call::invocation entry(friends_system(context), "InviteFriend");
    if (!entry.is_valid()) return false;

    entry.set<int>(offsets::params::invite_friend::index, index);
    if (!entry.fire()) return false;

    return entry.get<bool>(offsets::params::invite_friend::return_value);
}

bool sdk::hw2::open_invite_screen(const UObject* context) {
    return call::fire(friends_system(context), "OpenInviteScreen");
}

sdk::hw2::invite_status sdk::hw2::pending_invite(const UObject* context) {
    invite_status status;

    UObject* system = detail::invite_system(context);
    if (!system) return status;

    status.is_found = true;
    status.has_invite = detail::get_value<bool>(system, "HasPendingInvite", offsets::params::has_pending_invite::return_value);
    if (status.has_invite) status.inviter = detail::get_text(system, "GetPendingInviterName", offsets::params::pending_inviter::return_value);

    return status;
}

bool sdk::hw2::answer_invite(const UObject* context, bool is_accept) {
    return call::fire(detail::invite_system(context), is_accept ? "AcceptPendingInvite" : "DeclinePendingInvite");
}

sdk::hw2::migration_status sdk::hw2::read_migration() {
    migration_status status;

    UObject* system = detail::migration_subsystem();
    if (!system) return status;

    status.is_found = true;
    status.phase = detail::get_value<std::uint8_t>(system, "GetPhase", offsets::params::migration_phase::return_value);
    status.is_migrating = detail::get_value<bool>(system, "IsMigrating", 0);
    status.is_host = detail::get_value<bool>(system, "IsMigrationHost", 0);
    status.successor = detail::get_text(system, "GetSuccessorName", offsets::params::migration_successor::return_value);

    return status;
}

bool sdk::hw2::leave_match(bool is_to_desktop) {
    return call::fire_with<bool>(detail::migration_subsystem(), "LeaveMatch", offsets::params::leave_match::is_to_desktop, is_to_desktop);
}

bool sdk::hw2::announce_host_leaving() {
    call::invocation entry(match_component(match_part::host_migration), "AnnounceHostLeaving");
    if (!entry.is_valid() || !entry.fire()) return false;

    return entry.get<bool>(offsets::params::announce_leaving::return_value);
}

std::string sdk::hw2::match_report_json(const char* match_id) {
    call::invocation entry(match_component(match_part::match_report), "BuildReportJson");
    if (!entry.is_valid()) return std::string{};

    const FString id = strings::make(match_id && *match_id ? match_id : "practice");
    if (!id.Data) return std::string{};

    entry.set<FString>(offsets::params::report_json::match_id, id);
    if (!entry.fire()) return std::string{};

    return narrow(entry.get<FString>(offsets::params::report_json::return_value));
}

bool sdk::hw2::dump_match_report() {
    return call::fire(match_component(match_part::match_report), "DebugDumpReport");
}

bool sdk::hw2::announce_all(const char* text) {
    detail::text_value message;
    if (!detail::make_text(text, message)) return false;

    call::invocation entry(match_game_state(), "SendMessageToAll");
    if (!entry.is_valid()) return false;

    entry.set<detail::text_value>(offsets::params::send_message_all::message, message);
    entry.set<bool>(offsets::params::send_message_all::is_reliable, true);

    return entry.fire();
}

bool sdk::hw2::announce_teams(const char* team_0, const char* team_1) {
    detail::text_value first;
    detail::text_value second;
    if (!detail::make_text(team_0, first) || !detail::make_text(team_1, second)) return false;

    call::invocation entry(match_game_state(), "SendMessageTeam");
    if (!entry.is_valid()) return false;

    entry.set<detail::text_value>(offsets::params::send_message_team::team_0, first);
    entry.set<detail::text_value>(offsets::params::send_message_team::team_1, second);
    entry.set<bool>(offsets::params::send_message_team::is_reliable, true);

    return entry.fire();
}

bool sdk::hw2::show_objective_message(const char* text) {
    detail::text_value message;
    if (!detail::make_text(text, message)) return false;

    return call::fire_with<detail::text_value>(match_game_state(), "ShowObjectiveMessage", offsets::params::show_objective_message::text, message);
}
