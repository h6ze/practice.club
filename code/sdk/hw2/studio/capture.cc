#include "capture.hh"
#include <Windows.h>
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/core/container.hh>
#include <sdk/core/text/encoding.hh>
#include <sdk/offsets.generated.hh>
#include <sdk/unreal/query/lookup.hh>
#include <sdk/unreal/runtime/strings.hh>

namespace sdk::hw2::detail {

    inline lookup::held cine_settings_default;
    inline lookup::held replay_settings_default;
    inline lookup::held voice_settings_default;
    inline lookup::held audio_output_default;
    inline lookup::held voice_cue_default;
    inline lookup::held input_settings_default;
    inline lookup::held third_person_default;
    inline lookup::held input_statics_default;
    inline lookup::held voice_library_default;

    constexpr ULONGLONG instance_search_every_ms = 3000;
    constexpr std::int32_t replay_cap = 512;

    struct held_instance {
        lookup::held slot;
        ULONGLONG next_try = 0;
    };

    inline held_instance cine_instance;
    inline held_instance replay_instance;
    inline held_instance voice_instance;

    [[nodiscard]] inline UObject* instance_of(held_instance& held, const char* class_name) {
        if (lookup::is_live(held.slot)) return held.slot.object;

        const ULONGLONG now = GetTickCount64();
        if (now < held.next_try) return nullptr;
        held.next_try = now + instance_search_every_ms;

        UObject* found = objects::find_live_instance(objects::find_class(class_name));
        held.slot = { found, found ? found->index() : -1 };

        return found;
    }

    template <class T> [[nodiscard]] inline T get_value(UObject* object, const char* function_name, std::uint32_t offset) {
        call::invocation entry(object, function_name);
        if (!entry.is_valid() || !entry.fire()) return T{};

        return entry.get<T>(offset);
    }

    [[nodiscard]] inline std::string get_text(UObject* object, const char* function_name, std::uint32_t offset) {
        call::invocation entry(object, function_name);
        if (!entry.is_valid() || !entry.fire()) return std::string{};

        return narrow(entry.get<FString>(offset));
    }

    [[nodiscard]] inline bool named_call(UObject* object, const char* function_name, const char* text, std::uint32_t text_at, std::uint32_t return_at) {
        if (!object || !text || !*text) return false;

        call::invocation entry(object, function_name);
        if (!entry.is_valid()) return false;

        const FString value = strings::make(text);
        if (!value.Data) return false;

        entry.set<FString>(text_at, value);
        if (!entry.fire()) return false;

        return entry.get<bool>(return_at);
    }

    [[nodiscard]] inline UObject* input_statics() {
        return lookup::class_default(input_statics_default, "HW2InputStatics");
    }

}

sdk::UObject* sdk::hw2::cine_settings() { return lookup::class_default(detail::cine_settings_default, "HW2CineSettings"); }
sdk::UObject* sdk::hw2::replay_settings() { return lookup::class_default(detail::replay_settings_default, "HW2ReplaySettings"); }
sdk::UObject* sdk::hw2::voice_settings() { return lookup::class_default(detail::voice_settings_default, "HW2VoiceChatSettings"); }
sdk::UObject* sdk::hw2::audio_output_settings() { return lookup::class_default(detail::audio_output_default, "HW2AudioOutputSettings"); }
sdk::UObject* sdk::hw2::voice_cue_settings() { return lookup::class_default(detail::voice_cue_default, "HW2VoiceCueSettings"); }
sdk::UObject* sdk::hw2::input_settings() { return lookup::class_default(detail::input_settings_default, "HW2InputSettings"); }
sdk::UObject* sdk::hw2::third_person_settings() { return lookup::class_default(detail::third_person_default, "HW2ThirdPersonCameraSettings"); }

sdk::UObject* sdk::hw2::cine_system() { return detail::instance_of(detail::cine_instance, "HW2CineSubsystem"); }
sdk::UObject* sdk::hw2::replay_system() { return detail::instance_of(detail::replay_instance, "HW2ReplaySubsystem"); }

sdk::UObject* sdk::hw2::voice_save() {
    return mem::pointer<UObject>(detail::instance_of(detail::voice_instance, "HW2VoiceChatSubsystem"), offsets::hw2_voice_system::saved_object);
}

sdk::hw2::cine_status sdk::hw2::read_cine() {
    cine_status status;

    UObject* system = cine_system();
    if (!system) return status;

    status.is_found = true;
    status.is_recording = detail::get_value<bool>(system, "IsRecording", offsets::params::cine_is_recording::return_value);
    status.is_god_mode = detail::get_value<bool>(system, "IsGodModeEnabled", offsets::params::cine_is_god_mode::return_value);
    status.seconds = detail::get_value<float>(system, "GetRecordingSeconds", offsets::params::cine_seconds::return_value);
    status.status = detail::get_text(system, "GetStatusString", offsets::params::cine_status::return_value);

    return status;
}

bool sdk::hw2::cine_call(const char* function_name) {
    return call::fire(cine_system(), function_name);
}

bool sdk::hw2::set_god_mode(bool is_enabled) {
    return call::fire_with<bool>(cine_system(), "SetGodMode", offsets::params::cine_god_mode::is_enabled, is_enabled);
}

sdk::hw2::replay_status sdk::hw2::read_replay() {
    replay_status status;

    UObject* system = replay_system();
    if (!system) return status;

    status.is_found = true;
    status.is_recording = detail::get_value<bool>(system, "IsRecording", offsets::params::replay_is_recording::return_value);
    status.is_playing = detail::get_value<bool>(system, "IsPlayingReplay", offsets::params::replay_is_playing::return_value);
    status.status = detail::get_text(system, "GetStatusString", offsets::params::replay_status::return_value);

    return status;
}

std::vector<std::string> sdk::hw2::replay_files() {
    std::vector<std::string> found;

    call::invocation entry(replay_system(), "GetReplays");
    if (!entry.is_valid() || !entry.fire()) return found;

    const TArray<std::uint8_t> files = entry.get<TArray<std::uint8_t>>(offsets::params::replay_list::return_value);
    if (!files.Data || files.num() <= 0 || files.num() > detail::replay_cap) return found;

    for (std::int32_t i = 0; i < files.num(); ++i) {
        const std::uint8_t* item = files.Data + offsets::hw2_replay_file::byte_size * static_cast<std::uint32_t>(i);
        std::string name = narrow(mem::read<FString>(item, offsets::hw2_replay_file::name, FString{}));

        if (!name.empty()) found.push_back(std::move(name));
    }

    return found;
}

bool sdk::hw2::replay_call(const char* function_name) {
    return call::fire(replay_system(), function_name);
}

bool sdk::hw2::replay_record(const char* name) {
    return detail::named_call(replay_system(), "StartRecording", name, offsets::params::replay_record::name, offsets::params::replay_record::return_value);
}

bool sdk::hw2::replay_play(const char* name, float start_seconds) {
    UObject* system = replay_system();
    if (!system || !name || !*name) return false;

    call::invocation entry(system, "PlayReplayFile");
    if (!entry.is_valid()) return false;

    const FString value = strings::make(name);
    if (!value.Data) return false;

    entry.set<FString>(offsets::params::replay_play::name, value);
    entry.set<float>(offsets::params::replay_play::start, start_seconds);
    if (!entry.fire()) return false;

    return entry.get<bool>(offsets::params::replay_play::return_value);
}

bool sdk::hw2::replay_highlight(const char* label) {
    return detail::named_call(replay_system(), "MarkHighlight", label, offsets::params::replay_highlight::label, offsets::params::replay_highlight::return_value);
}

bool sdk::hw2::replay_jump(int direction) {
    call::invocation entry(replay_system(), "JumpToHighlight");
    if (!entry.is_valid()) return false;

    entry.set<int>(offsets::params::replay_jump::direction, direction);
    if (!entry.fire()) return false;

    return entry.get<bool>(offsets::params::replay_jump::return_value);
}

bool sdk::hw2::replay_follow(const char* player_name) {
    return detail::named_call(replay_system(), "FollowPlayer", player_name, offsets::params::replay_follow::name, offsets::params::replay_follow::return_value);
}

sdk::UObject* sdk::hw2::replay_spectator(const APlayerController* controller) {
    return lookup::derives_from(controller, "HW2ReplaySpectator") ? const_cast<APlayerController*>(controller) : nullptr;
}

bool sdk::hw2::spectator_call(const APlayerController* controller, const char* function_name) {
    return call::fire(replay_spectator(controller), function_name);
}

bool sdk::hw2::replay_seek_to(const APlayerController* controller, float seconds) {
    return call::fire_with<float>(replay_spectator(controller), "SeekTo", offsets::params::replay_seek_to::seconds, seconds);
}

bool sdk::hw2::replay_seek(const APlayerController* controller, float delta) {
    return call::fire_with<float>(replay_spectator(controller), "Seek", offsets::params::replay_seek::delta, delta);
}

bool sdk::hw2::replay_speed(const APlayerController* controller, float speed) {
    return call::fire_with<float>(replay_spectator(controller), "SetPlaybackSpeed", offsets::params::replay_speed::speed, speed);
}

bool sdk::hw2::reset_voice(const UObject* context) {
    return call::fire_with<const UObject*>(lookup::class_default(detail::voice_library_default, "HW2VoiceChatLibrary"), "HW2ResetVoiceSettings",
        offsets::params::reset_voice::context, context);
}

bool sdk::hw2::set_aim_assist(const UObject* context, bool is_enabled) {
    call::invocation entry(detail::input_statics(), "HW2SetControllerAimAssist");
    if (!entry.is_valid()) return false;

    entry.set<const UObject*>(offsets::params::set_aim_assist::context, context);
    entry.set<bool>(offsets::params::set_aim_assist::is_enabled, is_enabled);

    return entry.fire();
}

bool sdk::hw2::set_input_fov(const UObject* context, float fov) {
    call::invocation entry(detail::input_statics(), "HW2SetFieldOfView");
    if (!entry.is_valid()) return false;

    entry.set<const UObject*>(offsets::params::set_input_fov::context, context);
    entry.set<float>(offsets::params::set_input_fov::fov, fov);

    return entry.fire();
}

bool sdk::hw2::set_vibration(const UObject* context, bool is_enabled) {
    call::invocation entry(detail::input_statics(), "HW2SetControllerVibration");
    if (!entry.is_valid()) return false;

    entry.set<const UObject*>(offsets::params::set_vibration::context, context);
    entry.set<bool>(offsets::params::set_vibration::is_enabled, is_enabled);

    return entry.fire();
}

bool sdk::hw2::reset_controller(const UObject* context) {
    return call::fire_with<const UObject*>(detail::input_statics(), "HW2ResetControllerSettings", offsets::params::reset_controller::context, context);
}

sdk::UObject* sdk::hw2::voice_of(const APawn* pawn) noexcept {
    return mem::pointer<UObject>(pawn, offsets::hw2_character::generic_voice);
}

bool sdk::hw2::try_voice(const APawn* pawn, int event_id) {
    return call::fire_with<int>(voice_of(pawn), "TryVoice", offsets::params::try_voice::event_id, event_id);
}

bool sdk::hw2::voice_call(const APawn* pawn, const char* function_name) {
    return call::fire(voice_of(pawn), function_name);
}
