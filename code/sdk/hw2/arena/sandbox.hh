#pragma once
#include <cstdint>
#include <initializer_list>
#include <string>
#include <sdk/core/math.hh>
#include <sdk/unreal/engine.hh>

namespace sdk::hw2 {

    struct dev_mode {
        bool is_enabled = false;
        bool is_esp = false;
        bool is_esp_overlay = false;
        FLinearColor esp_color;
        float esp_radius = 0.0f;
        float esp_height = 0.0f;
        float esp_distance = 0.0f;
        int team_size = 0;
        int max_players = 0;
    };

    [[nodiscard]] UObject* dev_settings();
    [[nodiscard]] bool read_dev_mode(dev_mode& mode) noexcept;
    bool write_dev_mode(const dev_mode& mode) noexcept;

    [[nodiscard]] bool is_dev_mode_active();

    struct bot_tier {
        float aim_turn_rate = 0.0f;
        float aim_reaction_delay = 0.0f;
        float aim_error_initial = 0.0f;
        float aim_error_settled = 0.0f;
        float aim_settle_time = 0.0f;
        float aim_fire_angle = 0.0f;
        float burst_duration = 0.0f;
        float burst_rest = 0.0f;
        float aim_latency = 0.0f;
        float aim_predict_skill = 0.0f;
        float reaction_time = 0.0f;
        float spread_multiplier = 0.0f;
        float moving_spread_scale = 0.0f;
        int max_bots_per_target = 0;
        float engage_range = 0.0f;
        float max_fire_range = 0.0f;
        float detect_time = 0.0f;
        float flinch_spread = 0.0f;
        float pursuit_scale = 0.0f;
    };

    struct bot_brain {
        float aim_interp_speed = 0.0f;
        float aim_error_interval = 0.0f;
        float aim_target_z_offset = 0.0f;
        float hearing_radius = 0.0f;
        float memory_seconds = 0.0f;
        bool is_perceived_aim = false;
        bool is_movement_spread = false;
    };

    [[nodiscard]] UObject* bot_settings();
    [[nodiscard]] int bot_tier_count() noexcept;
    [[nodiscard]] std::string bot_tier_name(int index);

    [[nodiscard]] bool read_bot_tier(int index, bot_tier& tier) noexcept;
    bool write_bot_tier(int index, const bot_tier& tier) noexcept;
    [[nodiscard]] bool read_bot_brain(bot_brain& brain) noexcept;
    bool write_bot_brain(const bot_brain& brain) noexcept;

    enum class killstreak : std::uint8_t { snitch = 0, homies = 1, suicide_bomber = 2, drive_by = 3 };

    [[nodiscard]] const char* killstreak_name(killstreak streak) noexcept;

    bool activate_killstreak(AActor* context, killstreak streak);
    bool activate_killstreak_slot(AActor* context, int slot);
    bool place_killstreak(AActor* context, const FVector& location);

    [[nodiscard]] UObject* streak_settings();

    [[nodiscard]] UObject* streak_component_of(std::initializer_list<const UObject*> owners);

    bool restore_killstreaks(UObject* component, int ready_mask);
    bool set_equipped_streaks(UObject* component, std::uint8_t mask);
    bool use_streak(UObject* component, killstreak streak);

    [[nodiscard]] UObject* old_streaks_of(const APlayerState* player_state);
    bool spawn_cluster_strike(UObject* component, const FVector& location);
    bool set_kill_streak(UObject* component, int count);

    bool bot_on_damaged(AController* bot, APawn* shooter);

    bool drop_spawn_protection(APawn* pawn);

    [[nodiscard]] AActor* drive_by_car();

    [[nodiscard]] int set_summoned_team(int team);

}
