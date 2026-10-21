#include "theme.hh"
#include <imgui/imgui.h>

namespace {

    constexpr ImVec4 ink = { 0.06f, 0.06f, 0.07f, 0.94f };
    constexpr ImVec4 panel = { 0.11f, 0.11f, 0.13f, 1.00f };
    constexpr ImVec4 raised = { 0.16f, 0.16f, 0.19f, 1.00f };
    constexpr ImVec4 hovered = { 0.22f, 0.22f, 0.26f, 1.00f };
    constexpr ImVec4 active = { 0.28f, 0.28f, 0.34f, 1.00f };
    constexpr ImVec4 accent = { 0.45f, 0.53f, 0.98f, 1.00f };
    constexpr ImVec4 accent_dim = { 0.45f, 0.53f, 0.98f, 0.55f };
    constexpr ImVec4 label = { 0.90f, 0.90f, 0.93f, 1.00f };
    constexpr ImVec4 muted = { 0.48f, 0.48f, 0.54f, 1.00f };
    constexpr ImVec4 edge = { 0.24f, 0.24f, 0.28f, 1.00f };
    constexpr ImVec4 nothing = { 0.00f, 0.00f, 0.00f, 0.00f };

}

void render::theme::apply() {
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowPadding = { 12.0f, 12.0f };
    style.FramePadding = { 8.0f, 4.0f };
    style.ItemSpacing = { 8.0f, 6.0f };
    style.ItemInnerSpacing = { 6.0f, 4.0f };
    style.ScrollbarSize = 12.0f;
    style.GrabMinSize = 10.0f;

    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;

    style.WindowRounding = 6.0f;
    style.ChildRounding = 4.0f;
    style.FrameRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 4.0f;
    style.TabRounding = 4.0f;

    style.WindowTitleAlign = { 0.5f, 0.5f };

    ImVec4* colours = style.Colors;

    colours[ImGuiCol_Text] = label;
    colours[ImGuiCol_TextDisabled] = muted;
    colours[ImGuiCol_WindowBg] = ink;
    colours[ImGuiCol_ChildBg] = nothing;
    colours[ImGuiCol_PopupBg] = panel;
    colours[ImGuiCol_Border] = edge;
    colours[ImGuiCol_BorderShadow] = nothing;
    colours[ImGuiCol_FrameBg] = panel;
    colours[ImGuiCol_FrameBgHovered] = raised;
    colours[ImGuiCol_FrameBgActive] = hovered;
    colours[ImGuiCol_TitleBg] = panel;
    colours[ImGuiCol_TitleBgActive] = raised;
    colours[ImGuiCol_TitleBgCollapsed] = panel;
    colours[ImGuiCol_MenuBarBg] = panel;
    colours[ImGuiCol_ScrollbarBg] = nothing;
    colours[ImGuiCol_ScrollbarGrab] = raised;
    colours[ImGuiCol_ScrollbarGrabHovered] = hovered;
    colours[ImGuiCol_ScrollbarGrabActive] = active;
    colours[ImGuiCol_CheckMark] = accent;
    colours[ImGuiCol_SliderGrab] = accent_dim;
    colours[ImGuiCol_SliderGrabActive] = accent;
    colours[ImGuiCol_Button] = raised;
    colours[ImGuiCol_ButtonHovered] = hovered;
    colours[ImGuiCol_ButtonActive] = active;
    colours[ImGuiCol_Header] = raised;
    colours[ImGuiCol_HeaderHovered] = hovered;
    colours[ImGuiCol_HeaderActive] = active;
    colours[ImGuiCol_Separator] = edge;
    colours[ImGuiCol_SeparatorHovered] = accent_dim;
    colours[ImGuiCol_SeparatorActive] = accent;
    colours[ImGuiCol_ResizeGrip] = nothing;
    colours[ImGuiCol_ResizeGripHovered] = accent_dim;
    colours[ImGuiCol_ResizeGripActive] = accent;
    colours[ImGuiCol_Tab] = panel;
    colours[ImGuiCol_TabHovered] = hovered;
    colours[ImGuiCol_TabSelected] = raised;
    colours[ImGuiCol_TabSelectedOverline] = accent;
    colours[ImGuiCol_TabDimmed] = panel;
    colours[ImGuiCol_TabDimmedSelected] = raised;
    colours[ImGuiCol_PlotLines] = accent;
    colours[ImGuiCol_PlotHistogram] = accent;
    colours[ImGuiCol_TextSelectedBg] = accent_dim;
    colours[ImGuiCol_NavCursor] = accent;
}
