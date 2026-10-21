#pragma once
#include <cstdint>
#include <sdk/core/math.hh>
#include <sdk/unreal/engine.hh>

namespace sdk::hw2 {

    struct weapon_stats {
        double damage = 0.0;
        double fire_rate = 0.0;
        double burst_fire_rate = 0.0;
        double range = 0.0;
        double headshot = 0.0;
        double vertical_recoil_min = 0.0;
        double vertical_recoil_max = 0.0;
        double horizontal_recoil_min = 0.0;
        double horizontal_recoil_max = 0.0;
        double bullet_velocity = 0.0;
        double falloff_start = 0.0;
        double falloff_end = 0.0;
        double falloff_min = 0.0;
        int ammo_per_mag = 0;
        int projectiles_per_shot = 0;
        bool is_hit_scan = false;
        bool is_shotgun = false;
        bool is_client_hit_reg = false;
        bool is_pump_action = false;
    };

    enum class weapon_slot { primary, secondary, current };

    [[nodiscard]] AActor* weapon_of(const APawn* pawn, weapon_slot slot) noexcept;
    [[nodiscard]] UObject* settings_of(const AActor* weapon) noexcept;

    [[nodiscard]] bool read_stats(const UObject* settings, weapon_stats& stats) noexcept;
    bool write_stats(UObject* settings, const weapon_stats& stats) noexcept;

    [[nodiscard]] int current_ammo_of(const AActor* weapon) noexcept;
    [[nodiscard]] int ammo_per_mag_of(const AActor* weapon) noexcept;
    bool set_current_ammo(AActor* weapon, int ammo) noexcept;
    bool set_ammo_per_mag(AActor* weapon, int ammo) noexcept;

    bool fire_shot(AActor* weapon, APawn* instigator, bool is_hit_scan, double spread);
    bool fire_shot_from(AActor* weapon, APawn* instigator, const FVector& start, const FVector& forward,
                        double spread);

    [[nodiscard]] bool can_shoot_of(const APawn* pawn) noexcept;
    bool set_can_shoot(APawn* pawn, bool is_ready) noexcept;

    [[nodiscard]] bool wants_to_fire_of(const APawn* pawn) noexcept;

    [[nodiscard]] bool hit_scan_of(const UObject* settings) noexcept;

    [[nodiscard]] bool needs_pump_of(const AActor* weapon) noexcept;
    [[nodiscard]] bool bolt_cycling_of(const AActor* weapon) noexcept;
    bool set_needs_pump(AActor* weapon, bool is_needed) noexcept;
    bool set_bolt_cycling(AActor* weapon, bool is_cycling) noexcept;

    [[nodiscard]] double bot_damage_of(const AActor* weapon) noexcept;
    bool set_bot_damage(AActor* weapon, double scale) noexcept;

    [[nodiscard]] FLinearColor skin_color_a_of(const AActor* weapon) noexcept;
    [[nodiscard]] FLinearColor skin_color_b_of(const AActor* weapon) noexcept;

    bool apply_skin_colors(AActor* weapon, const FLinearColor& color_a, const FLinearColor& color_b);

    enum class actor_kind { other, weapon, bullet, frag, medkit, ammo_box, explosive_box, character, player_controller };

    [[nodiscard]] actor_kind kind_of(const AActor* actor);
    [[nodiscard]] bool is_throwable(actor_kind kind) noexcept;

    bool set_bullet_drop(AActor* bullet, double z_velocity) noexcept;
    [[nodiscard]] FVector bullet_start_of(const AActor* bullet) noexcept;
    bool set_bullet_start(AActor* bullet, const FVector& location) noexcept;
    bool move_bullet(AActor* bullet, const FVector& location, bool is_blocking_hit);
    [[nodiscard]] FVector bullet_velocity_of(const AActor* bullet) noexcept;
    bool set_bullet_velocity(AActor* bullet, const FVector& velocity) noexcept;

    [[nodiscard]] UObject* projectile_movement_of(const AActor* actor, actor_kind kind) noexcept;
    [[nodiscard]] FVector movement_velocity_of(const UObject* movement) noexcept;
    bool set_movement_velocity(UObject* movement, const FVector& velocity) noexcept;
    [[nodiscard]] float gravity_scale_of(const UObject* movement) noexcept;
    bool set_gravity_scale(UObject* movement, float scale) noexcept;
    [[nodiscard]] float bounciness_of(const UObject* movement) noexcept;
    bool set_bounciness(UObject* movement, float bounciness) noexcept;

}
