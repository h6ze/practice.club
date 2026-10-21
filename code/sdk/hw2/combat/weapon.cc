#include "weapon.hh"
#include <string>
#include <unordered_map>
#include <sdk/core/access.hh>
#include <sdk/core/reflect/call.hh>
#include <sdk/offsets.generated.hh>

namespace sdk::hw2::detail {

    struct known_kind {
        std::int32_t index = -1;
        actor_kind kind = actor_kind::other;
    };

    inline std::unordered_map<const UClass*, known_kind> kind_by_class;

    [[nodiscard]] inline actor_kind kind_named(const std::string& name) {
        if (name == "BP_Bullet_C") return actor_kind::bullet;
        if (name == "BP_FragGrenade_C") return actor_kind::frag;
        if (name == "BP_Medkit_C") return actor_kind::medkit;
        if (name == "BP_SmallAmmoBox_C") return actor_kind::ammo_box;
        if (name == "BP_SmallExplosiveAmmoBox_C") return actor_kind::explosive_box;
        if (name == "BP_BaseWeapon_C") return actor_kind::weapon;
        if (name == "BP_PlayerCharacter_C") return actor_kind::character;
        if (name == "PlayerController") return actor_kind::player_controller;

        return actor_kind::other;
    }

    [[nodiscard]] inline actor_kind classify(const UClass* type) {
        int guard = 0;
        for (const UStruct* walk = type; walk != nullptr && guard < 32; walk = walk->super(), ++guard) {
            const actor_kind kind = kind_named(walk->name());
            if (kind != actor_kind::other) return kind;
        }

        return actor_kind::other;
    }

}

sdk::AActor* sdk::hw2::weapon_of(const APawn* pawn, weapon_slot slot) noexcept {
    const void* inventory = mem::pointer<void>(pawn, offsets::hw2_character::inventory);

    switch (slot) {
    case weapon_slot::primary: return mem::pointer<AActor>(inventory, offsets::hw2_inventory::primary);
    case weapon_slot::secondary: return mem::pointer<AActor>(inventory, offsets::hw2_inventory::secondary);
    case weapon_slot::current: return mem::pointer<AActor>(inventory, offsets::hw2_inventory::current);
    }

    return nullptr;
}

sdk::UObject* sdk::hw2::settings_of(const AActor* weapon) noexcept {
    return mem::pointer<UObject>(weapon, offsets::hw2_weapon::settings);
}

bool sdk::hw2::read_stats(const UObject* settings, weapon_stats& stats) noexcept {
    if (!settings) return false;

    namespace field = offsets::hw2_weapon_settings;

    stats.damage = mem::read<double>(settings, field::damage);
    stats.fire_rate = mem::read<double>(settings, field::fire_rate);
    stats.burst_fire_rate = mem::read<double>(settings, field::burst_fire_rate);
    stats.range = mem::read<double>(settings, field::range);
    stats.headshot = mem::read<double>(settings, field::headshot);
    stats.vertical_recoil_min = mem::read<double>(settings, field::vertical_recoil_min);
    stats.vertical_recoil_max = mem::read<double>(settings, field::vertical_recoil_max);
    stats.horizontal_recoil_min = mem::read<double>(settings, field::horizontal_recoil_min);
    stats.horizontal_recoil_max = mem::read<double>(settings, field::horizontal_recoil_max);
    stats.bullet_velocity = mem::read<double>(settings, field::bullet_velocity);
    stats.falloff_start = mem::read<double>(settings, field::falloff_start);
    stats.falloff_end = mem::read<double>(settings, field::falloff_end);
    stats.falloff_min = mem::read<double>(settings, field::falloff_min);
    stats.ammo_per_mag = mem::read<int>(settings, field::ammo_per_mag);
    stats.projectiles_per_shot = mem::read<int>(settings, field::projectiles_per_shot);
    stats.is_hit_scan = mem::read<bool>(settings, field::is_hit_scan);
    stats.is_shotgun = mem::read<bool>(settings, field::is_shotgun);
    stats.is_client_hit_reg = mem::read<bool>(settings, field::is_client_hit_reg);
    stats.is_pump_action = mem::read<bool>(settings, field::is_pump_action);

    return stats.damage > 0.0;
}

bool sdk::hw2::write_stats(UObject* settings, const weapon_stats& stats) noexcept {
    if (!settings) return false;

    namespace field = offsets::hw2_weapon_settings;

    bool is_written = mem::write<double>(settings, field::damage, stats.damage);
    is_written &= mem::write<double>(settings, field::fire_rate, stats.fire_rate);
    is_written &= mem::write<double>(settings, field::burst_fire_rate, stats.burst_fire_rate);
    is_written &= mem::write<double>(settings, field::range, stats.range);
    is_written &= mem::write<double>(settings, field::headshot, stats.headshot);
    is_written &= mem::write<double>(settings, field::vertical_recoil_min, stats.vertical_recoil_min);
    is_written &= mem::write<double>(settings, field::vertical_recoil_max, stats.vertical_recoil_max);
    is_written &= mem::write<double>(settings, field::horizontal_recoil_min, stats.horizontal_recoil_min);
    is_written &= mem::write<double>(settings, field::horizontal_recoil_max, stats.horizontal_recoil_max);
    is_written &= mem::write<double>(settings, field::bullet_velocity, stats.bullet_velocity);
    is_written &= mem::write<double>(settings, field::falloff_start, stats.falloff_start);
    is_written &= mem::write<double>(settings, field::falloff_end, stats.falloff_end);
    is_written &= mem::write<double>(settings, field::falloff_min, stats.falloff_min);
    is_written &= mem::write<int>(settings, field::ammo_per_mag, stats.ammo_per_mag);
    is_written &= mem::write<int>(settings, field::projectiles_per_shot, stats.projectiles_per_shot);
    is_written &= mem::write<bool>(settings, field::is_hit_scan, stats.is_hit_scan);
    is_written &= mem::write<bool>(settings, field::is_client_hit_reg, stats.is_client_hit_reg);
    is_written &= mem::write<bool>(settings, field::is_pump_action, stats.is_pump_action);

    return is_written;
}

bool sdk::hw2::fire_shot(AActor* weapon, APawn* instigator, bool is_hit_scan, double spread) {
    if (!weapon || !instigator) return false;

    if (is_hit_scan) {
        call::invocation look(weapon, "GetLineTraceInfo");
        if (!look.is_valid() || !look.fire()) return false;

        namespace from = offsets::params::line_trace_info;

        return fire_shot_from(weapon, instigator, look.get<FVector>(from::trace_start),
                              look.get<FVector>(from::forward), spread);
    }

    call::invocation spawn(weapon, "GetSpawnBulletInfo");
    if (!spawn.is_valid() || !spawn.fire()) return false;

    namespace from = offsets::params::spawn_bullet_info;
    const FVector location = spawn.get<FVector>(from::spawn_location);
    const FVector velocity = spawn.get<FVector>(from::velocity);
    const FRotator rotation = spawn.get<FRotator>(from::spawn_rotation);

    call::invocation shot(weapon, "Server_FireBullet");
    if (!shot.is_valid()) return false;

    namespace field = offsets::params::server_fire_bullet;
    shot.set<FVector>(field::spawn_location, location);
    shot.set<FVector>(field::bullet_velocity, velocity);
    shot.set<APawn*>(field::instigator, instigator);
    shot.set<FRotator>(field::spawn_rotation, rotation);
    shot.set<double>(field::spread, spread);

    return shot.fire();
}

bool sdk::hw2::fire_shot_from(AActor* weapon, APawn* instigator, const FVector& start,
                             const FVector& forward, double spread) {
    if (!weapon || !instigator) return false;

    call::invocation shot(weapon, "Server_FireInstantBullet");
    if (!shot.is_valid()) return false;

    namespace field = offsets::params::server_fire_instant;
    shot.set<FVector>(field::trace_start, start);
    shot.set<FVector>(field::forward, forward);
    shot.set<APawn*>(field::instigator, instigator);
    shot.set<double>(field::spread, spread);

    return shot.fire();
}

bool sdk::hw2::can_shoot_of(const APawn* pawn) noexcept {
    return mem::read<bool>(pawn, offsets::hw2_character::can_shoot, false);
}

bool sdk::hw2::set_can_shoot(APawn* pawn, bool is_ready) noexcept {
    return mem::write<bool>(pawn, offsets::hw2_character::can_shoot, is_ready);
}

bool sdk::hw2::wants_to_fire_of(const APawn* pawn) noexcept {
    return mem::read<bool>(pawn, offsets::hw2_character::wants_to_fire, false);
}

bool sdk::hw2::hit_scan_of(const UObject* settings) noexcept {
    return mem::read<bool>(settings, offsets::hw2_weapon_settings::is_hit_scan, false);
}

bool sdk::hw2::needs_pump_of(const AActor* weapon) noexcept {
    return mem::read<bool>(weapon, offsets::hw2_weapon::is_needs_pump, false);
}

bool sdk::hw2::bolt_cycling_of(const AActor* weapon) noexcept {
    return mem::read<bool>(weapon, offsets::hw2_weapon::is_bolt_cycling, false);
}

bool sdk::hw2::set_needs_pump(AActor* weapon, bool is_needed) noexcept {
    return mem::write<bool>(weapon, offsets::hw2_weapon::is_needs_pump, is_needed);
}

bool sdk::hw2::set_bolt_cycling(AActor* weapon, bool is_cycling) noexcept {
    return mem::write<bool>(weapon, offsets::hw2_weapon::is_bolt_cycling, is_cycling);
}

int sdk::hw2::current_ammo_of(const AActor* weapon) noexcept {
    return mem::read<int>(weapon, offsets::hw2_weapon::current_ammo, 0);
}

int sdk::hw2::ammo_per_mag_of(const AActor* weapon) noexcept {
    return mem::read<int>(weapon, offsets::hw2_weapon::ammo_per_mag, 0);
}

bool sdk::hw2::set_current_ammo(AActor* weapon, int ammo) noexcept {
    return mem::write<int>(weapon, offsets::hw2_weapon::current_ammo, ammo);
}

bool sdk::hw2::set_ammo_per_mag(AActor* weapon, int ammo) noexcept {
    return mem::write<int>(weapon, offsets::hw2_weapon::ammo_per_mag, ammo);
}

double sdk::hw2::bot_damage_of(const AActor* weapon) noexcept {
    return mem::read<double>(weapon, offsets::hw2_weapon::bot_damage, 1.0);
}

bool sdk::hw2::set_bot_damage(AActor* weapon, double scale) noexcept {
    return mem::write<double>(weapon, offsets::hw2_weapon::bot_damage, scale);
}

sdk::FLinearColor sdk::hw2::skin_color_a_of(const AActor* weapon) noexcept {
    return mem::read<FLinearColor>(weapon, offsets::hw2_weapon::skin_color_a, FLinearColor{});
}

sdk::FLinearColor sdk::hw2::skin_color_b_of(const AActor* weapon) noexcept {
    return mem::read<FLinearColor>(weapon, offsets::hw2_weapon::skin_color_b, FLinearColor{});
}

bool sdk::hw2::apply_skin_colors(AActor* weapon, const FLinearColor& color_a, const FLinearColor& color_b) {
    if (!weapon) return false;

    mem::write<FLinearColor>(weapon, offsets::hw2_weapon::skin_color_a, color_a);
    mem::write<FLinearColor>(weapon, offsets::hw2_weapon::skin_color_b, color_b);

    const std::uint32_t meshes[] = { offsets::hw2_weapon::mesh_fpp, offsets::hw2_weapon::mesh_tpp };

    bool is_painted = false;
    for (const std::uint32_t mesh_at : meshes) {
        UObject* mesh = mem::pointer<UObject>(weapon, mesh_at);
        if (!mesh) continue;

        call::invocation entry(weapon, "HW2_ApplySkinColors");
        if (!entry.is_valid()) return false;

        entry.set<UObject*>(offsets::params::apply_skin_colors::target_mesh, mesh);
        entry.set<FLinearColor>(offsets::params::apply_skin_colors::color_a, color_a);
        entry.set<FLinearColor>(offsets::params::apply_skin_colors::color_b, color_b);

        if (entry.fire()) is_painted = true;
    }

    return is_painted;
}

sdk::hw2::actor_kind sdk::hw2::kind_of(const AActor* actor) {
    const UClass* type = actor ? actor->klass() : nullptr;
    if (!type) return actor_kind::other;

    const std::int32_t index = type->index();

    const auto found = detail::kind_by_class.find(type);
    if (found != detail::kind_by_class.end() && found->second.index == index) return found->second.kind;

    const actor_kind kind = detail::classify(type);
    detail::kind_by_class[type] = { index, kind };

    return kind;
}

bool sdk::hw2::is_throwable(actor_kind kind) noexcept {
    return kind == actor_kind::frag || kind == actor_kind::medkit
        || kind == actor_kind::ammo_box || kind == actor_kind::explosive_box;
}

bool sdk::hw2::set_bullet_drop(AActor* bullet, double z_velocity) noexcept {
    return mem::write<double>(bullet, offsets::hw2_bullet::z_velocity, z_velocity);
}

sdk::FVector sdk::hw2::bullet_start_of(const AActor* bullet) noexcept {
    return mem::read<FVector>(bullet, offsets::hw2_bullet::start_location, FVector{});
}

bool sdk::hw2::set_bullet_start(AActor* bullet, const FVector& location) noexcept {
    return mem::write<FVector>(bullet, offsets::hw2_bullet::start_location, location);
}

bool sdk::hw2::move_bullet(AActor* bullet, const FVector& location, bool is_blocking_hit) {
    if (!bullet) return false;

    call::invocation move(bullet, "MoveBullet");
    if (!move.is_valid()) return false;

    namespace field = offsets::params::move_bullet;
    move.set<FVector>(field::new_location, location);
    move.set<bool>(field::is_blocking_hit, is_blocking_hit);

    return move.fire();
}

sdk::FVector sdk::hw2::bullet_velocity_of(const AActor* bullet) noexcept {
    return mem::read<FVector>(bullet, offsets::hw2_bullet::velocity, FVector{});
}

bool sdk::hw2::set_bullet_velocity(AActor* bullet, const FVector& velocity) noexcept {
    return mem::write<FVector>(bullet, offsets::hw2_bullet::velocity, velocity);
}

sdk::UObject* sdk::hw2::projectile_movement_of(const AActor* actor, actor_kind kind) noexcept {
    switch (kind) {
    case actor_kind::frag: return mem::pointer<UObject>(actor, offsets::hw2_throwable::frag_movement);
    case actor_kind::medkit: return mem::pointer<UObject>(actor, offsets::hw2_throwable::medkit_movement);
    case actor_kind::ammo_box: return mem::pointer<UObject>(actor, offsets::hw2_throwable::ammo_box_movement);
    case actor_kind::explosive_box: return mem::pointer<UObject>(actor, offsets::hw2_throwable::explosive_box_movement);
    default: return nullptr;
    }
}

sdk::FVector sdk::hw2::movement_velocity_of(const UObject* movement) noexcept {
    return mem::read<FVector>(movement, offsets::uprojectile_movement::velocity, FVector{});
}

bool sdk::hw2::set_movement_velocity(UObject* movement, const FVector& velocity) noexcept {
    return mem::write<FVector>(movement, offsets::uprojectile_movement::velocity, velocity);
}

float sdk::hw2::gravity_scale_of(const UObject* movement) noexcept {
    return mem::read<float>(movement, offsets::uprojectile_movement::gravity_scale, 1.0f);
}

bool sdk::hw2::set_gravity_scale(UObject* movement, float scale) noexcept {
    return mem::write<float>(movement, offsets::uprojectile_movement::gravity_scale, scale);
}

float sdk::hw2::bounciness_of(const UObject* movement) noexcept {
    return mem::read<float>(movement, offsets::uprojectile_movement::bounciness, 0.0f);
}

bool sdk::hw2::set_bounciness(UObject* movement, float bounciness) noexcept {
    return mem::write<float>(movement, offsets::uprojectile_movement::bounciness, bounciness);
}
