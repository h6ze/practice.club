#pragma once
#include <imgui/imgui.h>
#include <sdk/core/math.hh>

namespace render::draw {

    void box(const sdk::box& frame, ImU32 color, float thickness = 1.0f);
    void corner_box(const sdk::box& frame, ImU32 color, float thickness = 1.6f);

    void health_bar(const sdk::box& frame, float fraction, ImU32 color);
    void snapline(const sdk::box& frame, ImU32 color);

    void label_above(const sdk::box& frame, ImU32 color, const char* format, ...);
    void label_below(const sdk::box& frame, ImU32 color, const char* format, ...);

    void circle(ImVec2 centre, float radius, ImU32 color, float thickness = 1.2f);

}
