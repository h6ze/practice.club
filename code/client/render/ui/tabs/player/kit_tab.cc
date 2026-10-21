#include <client/render/ui/tabs/panels.hh>
#include <cstdio>
#include <vector>
#include <imgui/imgui.h>
#include <features/data/boards.hh>

namespace render::panels::detail {

    constexpr float kit_number_width = 110.0f;

    void draw_choice(const char* label, const std::vector<features::kit_choice>& list, int& pick, bool is_with_keep) {
        const char* shown = list.empty() ? "none loaded" : "pick one";
        if (is_with_keep && pick == -1) shown = "keep";
        else if (is_with_keep && pick == -2) shown = "default";
        else if (pick >= 0 && pick < static_cast<int>(list.size())) shown = list[static_cast<size_t>(pick)].name.c_str();

        if (!ImGui::BeginCombo(label, shown)) return;

        if (is_with_keep) {
            if (ImGui::Selectable("keep", pick == -1)) pick = -1;
            if (ImGui::Selectable("default", pick == -2)) pick = -2;
        }

        for (int i = 0; i < static_cast<int>(list.size()); ++i) {
            char entry[96];
            std::snprintf(entry, sizeof(entry), "%s##%d", list[static_cast<size_t>(i)].name.c_str(), i);

            if (ImGui::Selectable(entry, pick == i)) pick = i;
        }

        ImGui::EndCombo();
    }

    void draw_who(const features::match_snapshot& seen) {
        features::kit_options& options = features::kit_setup;

        if (ImGui::RadioButton("me", !options.is_on_picked)) options.is_on_picked = false;
        ImGui::SameLine();
        if (ImGui::RadioButton("picked player", options.is_on_picked)) options.is_on_picked = true;

        if (options.is_on_picked) draw_player_pick(seen);

    }

    void draw_give(const features::kit_catalog& list) {
        if (!ImGui::CollapsingHeader("weapons and ammo", ImGuiTreeNodeFlags_DefaultOpen)) return;

        features::kit_options& options = features::kit_setup;

        draw_choice("weapon", list.weapons, options.weapon, false);

        ImGui::SetNextItemWidth(kit_number_width);
        ImGui::InputInt("ammo", &options.give_ammo);
        ImGui::Checkbox("full mag", &options.is_full_mag);
        ImGui::SameLine();
        ImGui::Checkbox("with the attachment picks", &options.is_with_parts);

        if (ImGui::Button("give")) features::kit.give_weapon();
        ImGui::SameLine();
        if (ImGui::Button("refill ammo")) features::kit.refill_ammo();
        ImGui::SameLine();
        if (ImGui::Button("refresh lists")) features::kit.refresh_catalog();

        if (ImGui::Button("to primary")) features::kit.switch_weapon(true);
        ImGui::SameLine();
        if (ImGui::Button("to secondary")) features::kit.switch_weapon(false);
        ImGui::SameLine();
        if (ImGui::Button("drop held gun")) features::kit.drop_weapon();
        ImGui::SameLine();
        if (ImGui::Button("disarm")) features::kit.disarm();

        ImGui::Checkbox("infinite reserve ammo", &options.is_infinite_reserve);
        ImGui::SameLine();
        ImGui::Checkbox("infinite lethals", &options.is_infinite_lethals);
    }

    void draw_held_gun() {
        if (!ImGui::CollapsingHeader("gun in your hands")) return;

        features::kit_options& options = features::kit_setup;

        draw_board(features::boards::held_weapon);

        ImGui::SetNextItemWidth(kit_number_width);
        ImGui::InputInt("##fire mode", &options.firing_mode);
        ImGui::SameLine();
        if (ImGui::Button("set fire mode")) features::kit.set_firing_mode();

        ImGui::SetNextItemWidth(kit_number_width);
        ImGui::InputInt("##mag ammo", &options.mag_ammo);
        ImGui::SameLine();
        if (ImGui::Button("set magazine")) features::kit.set_mag_ammo();

        if (ImGui::Button("cancel bolt")) features::kit.cancel_bolt();
        ImGui::SameLine();
        if (ImGui::Button("stock off")) features::kit.set_stock(true);
        ImGui::SameLine();
        if (ImGui::Button("stock on")) features::kit.set_stock(false);

        if (ImGui::TreeNode("its model's settings")) {
            draw_board(features::boards::held_weapon_data);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("magazine and optic")) {
            draw_board(features::boards::held_magazine);
            draw_board(features::boards::held_optic);
            ImGui::TreePop();
        }
    }

    void draw_attachments(const features::kit_catalog& list) {
        if (!ImGui::CollapsingHeader("attachments")) return;

        features::kit_options& options = features::kit_setup;
        const char* slots[features::attachment_slot_count] = { "optic", "muzzle", "stock", "magazine", "accessory", "underbarrel", "canted sight" };

        for (int slot = 0; slot < features::attachment_slot_count; ++slot)
            draw_choice(slots[slot], list.attachments[slot], options.parts[slot], true);

        if (ImGui::Button("apply to the gun in hand")) features::kit.apply_attachments();
    }

    void draw_loadout(const features::kit_catalog& list) {
        if (!ImGui::CollapsingHeader("loadout")) return;

        features::kit_options& options = features::kit_setup;

        draw_board(features::boards::own_loadout);

        if (ImGui::Button("set as primary")) features::kit.loadout_weapon(true);
        ImGui::SameLine();
        if (ImGui::Button("set as secondary")) features::kit.loadout_weapon(false);

        draw_choice("lethal", list.lethals, options.lethal, false);
        if (ImGui::Button("set lethal")) features::kit.loadout_lethal();

        draw_choice("character", list.operators, options.operator_pick, false);
        ImGui::SetNextItemWidth(kit_number_width);
        ImGui::InputInt("for team", &options.operator_team);
        if (ImGui::Button("set character")) features::kit.loadout_operator();

        ImGui::SetNextItemWidth(kit_number_width);
        ImGui::InputInt("##perk", &options.perk);
        ImGui::SameLine();
        if (ImGui::Button("set perk")) features::kit.set_perk();

        ImGui::SetNextItemWidth(kit_number_width);
        ImGui::InputInt("##field upgrade", &options.field_upgrade);
        ImGui::SameLine();
        if (ImGui::Button("set field upgrade")) features::kit.set_field_upgrade();
    }

    void draw_health() {
        if (!ImGui::CollapsingHeader("health")) return;

        features::kit_options& options = features::kit_setup;

        if (ImGui::TreeNode("your health")) {
            draw_board(features::boards::own_vitals);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("picked player's health")) {
            draw_board(features::boards::picked_vitals);
            ImGui::TreePop();
        }


        ImGui::SliderFloat("##heal", &options.heal_amount, 1.0f, 500.0f, "%.0f");
        ImGui::SameLine();
        if (ImGui::Button("heal")) features::kit.heal();

        ImGui::SliderFloat("##max health", &options.max_health, 1.0f, 1000.0f, "%.0f");
        ImGui::SameLine();
        if (ImGui::Button("set max health")) features::kit.set_max_health();

        ImGui::SliderFloat("##damage", &options.damage_amount, 1.0f, 500.0f, "%.0f");
        ImGui::SameLine();
        if (ImGui::Button("damage")) features::kit.damage();

        if (ImGui::Button("kill")) features::kit.kill();
    }

    void draw_body() {
        if (!ImGui::CollapsingHeader("body and skills")) return;

        draw_board(features::boards::own_body);
        draw_board(features::boards::own_interaction);

        if (ImGui::Button("use skill")) features::kit.use_skill();
        ImGui::SameLine();
        if (ImGui::Button("reset skill")) features::kit.reset_skill();
        ImGui::SameLine();
        if (ImGui::Button("apply perk")) features::kit.apply_perk();

        if (ImGui::Button("block firing")) features::kit.set_fire(false);
        ImGui::SameLine();
        if (ImGui::Button("allow firing")) features::kit.set_fire(true);
        ImGui::SameLine();
        if (ImGui::Button("stand up")) features::kit.uncrouch();
    }

    void draw_throwables() {
        if (!ImGui::CollapsingHeader("lethals and pickups")) return;

        if (ImGui::TreeNode("your lethal")) {
            draw_board(features::boards::own_lethal);
            ImGui::TreePop();
        }


        features::field_board* defaults[] = {
            &features::boards::frag_defaults, &features::boards::claymore_defaults,
            &features::boards::pickup_defaults, &features::boards::medkit_defaults,
        };

        for (features::field_board* board : defaults) {
            if (!ImGui::TreeNode(board->title)) continue;

            draw_board(*board);
            ImGui::TreePop();
        }

        if (ImGui::Button("set off every claymore")) features::kit.detonate_claymores();
        ImGui::SameLine();
        if (ImGui::Button("set off every grenade")) features::kit.explode_grenades();
        if (ImGui::Button("refill every ammo box")) features::kit.refill_ammo_boxes();
    }

    void draw_damage_types(const features::kit_catalog& list) {
        if (!ImGui::CollapsingHeader("damage types")) return;

        draw_choice("type", list.damage_types, features::boards::damage_type_board.element, false);
        draw_board(features::boards::damage_type_board);
    }

}

void render::panels::draw_kit_tab() {
    const features::kit_catalog list = features::kit.catalog();
    const features::match_snapshot seen = features::host.snapshot();

    if (list.weapons.empty()) features::kit.refresh_catalog();

    detail::draw_who(seen);

    ImGui::Separator();

    detail::draw_give(list);
    detail::draw_held_gun();
    detail::draw_attachments(list);
    detail::draw_loadout(list);
    detail::draw_health();
    detail::draw_body();
    detail::draw_throwables();
    detail::draw_damage_types(list);
}
