#pragma once
#include <cmath>
#include <imgui/imgui.h>
#include <features/data/tune.hh>
#include <sdk/unreal/view/camera.hh>
#include <sdk/unreal/view/players.hh>
#include <client/render/ui/draw.hh>

namespace features::paint {

    [[nodiscard]] inline ImU32 tint_of(const game::player& subject) {
        if (!subject.is_alive) return tune::downed;

        return subject.is_enemy ? tune::enemy : tune::friendly;
    }

    [[nodiscard]] inline ImU32 health_tint(float fraction) {
        const float clamped = fraction < 0.0f ? 0.0f : (fraction > 1.0f ? 1.0f : fraction);
        const float red = clamped < 0.5f ? 1.0f : (1.0f - clamped) * 2.0f;
        const float green = clamped < 0.5f ? clamped * 2.0f : 1.0f;

        return ImGui::ColorConvertFloat4ToU32({ red, green, 0.25f, 1.0f });
    }

    inline void corner_box(const game::player& subject) {
        render::draw::corner_box(subject.frame, tint_of(subject));
    }

    inline void name(const game::player& subject) {
        if (subject.name.empty()) return;

        render::draw::label_above(subject.frame, tint_of(subject), "%s", subject.name.c_str());
    }

    inline void health(const game::player& subject) {
        render::draw::health_bar(subject.frame, subject.health_fraction(), health_tint(subject.health_fraction()));
    }

    inline void distance(const game::player& subject) {
        render::draw::label_below(subject.frame, tint_of(subject), "%.0f m  lvl %d", subject.distance, subject.level);
    }

    inline void snapline(const game::player& subject) {
        render::draw::snapline(subject.frame, tint_of(subject));
    }

    inline void head_dot(const game::player& subject) {
        sdk::vec2 at;
        if (!game::camera::to_screen(subject.head, at)) return;

        ImGui::GetBackgroundDrawList()->AddCircleFilled({ at.x, at.y }, tune::head_dot_radius, tint_of(subject));
    }

    inline void fov_circle(float cone, const float colour[4]) {
        const game::camera::view& active = game::camera::current();
        if (!active.is_valid || cone <= 0.0f || cone >= tune::widest_circle_cone) return;

        constexpr double radians_per_degree = 3.14159265358979323846 / 180.0;
        const double scale = (active.width * 0.5) / std::tan(active.fov * 0.5 * radians_per_degree);
        const float radius = static_cast<float>(scale * std::tan(cone * radians_per_degree));

        const float corner = std::sqrt(active.width * active.width + active.height * active.height) * 0.5f;
        if (radius > corner) return;

        const ImU32 tint = ImGui::ColorConvertFloat4ToU32({ colour[0], colour[1], colour[2], colour[3] });
        render::draw::circle({ active.width * 0.5f, active.height * 0.5f }, radius, tint);
    }

}
