#include "draw.hh"
#include <cstdarg>
#include <cstdio>

namespace render::draw::detail {

    constexpr float outline_alpha = 0.60f;
    constexpr float bar_width = 3.0f;
    constexpr float bar_gap = 4.0f;
    constexpr float label_gap = 3.0f;

    constexpr float ring_shadow_spread = 1.5f;

    [[nodiscard]] ImDrawList* surface() { return ImGui::GetBackgroundDrawList(); }

    [[nodiscard]] ImU32 shadow_of(ImU32 color) {
        ImVec4 parts = ImGui::ColorConvertU32ToFloat4(color);
        parts.x *= 0.1f;
        parts.y *= 0.1f;
        parts.z *= 0.1f;
        parts.w *= outline_alpha;

        return ImGui::ColorConvertFloat4ToU32(parts);
    }

    void centered_text(float center_x, float y, ImU32 color, const char* text) {
        const ImVec2 size = ImGui::CalcTextSize(text);
        const ImVec2 at = { center_x - size.x * 0.5f, y };

        surface()->AddText({ at.x + 1.0f, at.y + 1.0f }, shadow_of(IM_COL32_WHITE), text);
        surface()->AddText(at, color, text);
    }

    void formatted(const sdk::box& frame, ImU32 color, bool is_above, const char* format, va_list args) {
        if (!frame.is_valid) return;

        char text[128] = {};
        vsnprintf(text, sizeof(text), format, args);
        if (!text[0]) return;

        const float line = ImGui::GetTextLineHeight();
        const float y = is_above ? frame.top() - line - label_gap : frame.bottom() + label_gap;

        centered_text(frame.center_x(), y, color, text);
    }

}

void render::draw::box(const sdk::box& frame, ImU32 color, float thickness) {
    if (!frame.is_valid) return;

    const ImVec2 low = { frame.left(), frame.top() };
    const ImVec2 high = { frame.right(), frame.bottom() };

    detail::surface()->AddRect({ low.x - 1.0f, low.y - 1.0f }, { high.x + 1.0f, high.y + 1.0f }, detail::shadow_of(color), 0.0f, 0, thickness);
    detail::surface()->AddRect(low, high, color, 0.0f, 0, thickness);
}

void render::draw::corner_box(const sdk::box& frame, ImU32 color, float thickness) {
    if (!frame.is_valid) return;

    const float span_x = frame.width * 0.25f;
    const float span_y = frame.height * 0.2f;

    const float l = frame.left(), r = frame.right(), t = frame.top(), b = frame.bottom();

    ImDrawList* list = detail::surface();
    const ImU32 edge = detail::shadow_of(color);

    const auto stroke = [&](ImVec2 from, ImVec2 to) {
        list->AddLine({ from.x + 1.0f, from.y + 1.0f }, { to.x + 1.0f, to.y + 1.0f }, edge, thickness);
        list->AddLine(from, to, color, thickness);
    };

    stroke({ l, t }, { l + span_x, t });
    stroke({ l, t }, { l, t + span_y });
    stroke({ r, t }, { r - span_x, t });
    stroke({ r, t }, { r, t + span_y });
    stroke({ l, b }, { l + span_x, b });
    stroke({ l, b }, { l, b - span_y });
    stroke({ r, b }, { r - span_x, b });
    stroke({ r, b }, { r, b - span_y });
}

void render::draw::health_bar(const sdk::box& frame, float fraction, ImU32 color) {
    if (!frame.is_valid) return;

    const float clamped = fraction < 0.0f ? 0.0f : (fraction > 1.0f ? 1.0f : fraction);

    const float right = frame.left() - detail::bar_gap;
    const float left = right - detail::bar_width;
    const float filled = frame.bottom() - frame.height * clamped;

    detail::surface()->AddRectFilled({ left - 1.0f, frame.top() - 1.0f }, { right + 1.0f, frame.bottom() + 1.0f }, detail::shadow_of(IM_COL32_WHITE));
    detail::surface()->AddRectFilled({ left, filled }, { right, frame.bottom() }, color);
}

void render::draw::snapline(const sdk::box& frame, ImU32 color) {
    if (!frame.is_valid) return;

    const ImVec2 from = { ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y };
    const ImVec2 to = { frame.center_x(), frame.bottom() };

    detail::surface()->AddLine(from, to, color, 1.0f);
}

void render::draw::label_above(const sdk::box& frame, ImU32 color, const char* format, ...) {
    va_list args;
    va_start(args, format);
    detail::formatted(frame, color, true, format, args);
    va_end(args);
}

void render::draw::label_below(const sdk::box& frame, ImU32 color, const char* format, ...) {
    va_list args;
    va_start(args, format);
    detail::formatted(frame, color, false, format, args);
    va_end(args);
}

void render::draw::circle(ImVec2 centre, float radius, ImU32 color, float thickness) {
    if (radius < 1.0f) return;

    detail::surface()->AddCircle(centre, radius, detail::shadow_of(color), 0, thickness + detail::ring_shadow_spread);
    detail::surface()->AddCircle(centre, radius, color, 0, thickness);
}
