#include "window.hh"
#include <imgui/imgui.h>
#include <client/diag/log/logger.hh>
#include <client/util/string/text.hh>
#include "hotkeys.hh"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND window, UINT message, WPARAM first, LPARAM second);

namespace {

    struct binding {
        HWND target = nullptr;
        WNDPROC previous = nullptr;
        bool is_unicode = true;
    };

    binding& state() {
        static binding value;
        return value;
    }

    [[nodiscard]] bool is_mouse_message(UINT message) {
        return (message >= WM_MOUSEFIRST && message <= WM_MOUSELAST) || message == WM_MOUSEHOVER || message == WM_MOUSELEAVE;
    }

    [[nodiscard]] bool is_keyboard_message(UINT message) {
        return (message >= WM_KEYFIRST && message <= WM_KEYLAST) || message == WM_SETFOCUS || message == WM_KILLFOCUS;
    }

    [[nodiscard]] LRESULT forward(HWND window, UINT message, WPARAM first, LPARAM second) {
        const binding& current = state();
        if (!current.previous) return DefWindowProcW(window, message, first, second);

        return current.is_unicode ? CallWindowProcW(current.previous, window, message, first, second)
                                  : CallWindowProcA(current.previous, window, message, first, second);
    }

    LRESULT CALLBACK on_message(HWND window, UINT message, WPARAM first, LPARAM second) {
        if (message == WM_KEYUP && first == input::hotkeys::overlay_key) {
            input::hotkeys::toggle_overlay();
            return TRUE;
        }

        if (input::hotkeys::is_overlay_open() && ImGui::GetCurrentContext()) {
            ImGui_ImplWin32_WndProcHandler(window, message, first, second);

            const ImGuiIO& io = ImGui::GetIO();
            if (io.WantCaptureMouse && is_mouse_message(message)) return TRUE;
            if (io.WantCaptureKeyboard && is_keyboard_message(message)) return TRUE;
            if (io.WantTextInput && message == WM_CHAR) return TRUE;
        }

        return forward(window, message, first, second);
    }

}

bool input::window::ensure(HWND target) {
    binding& current = state();
    if (current.previous) return true;
    if (!target || !IsWindow(target)) return false;

    current.target = target;
    current.is_unicode = IsWindowUnicode(target) != FALSE;

    const auto replacement = reinterpret_cast<LONG_PTR>(on_message);
    const LONG_PTR installed = current.is_unicode ? SetWindowLongPtrW(target, GWLP_WNDPROC, replacement)
                                                  : SetWindowLongPtrA(target, GWLP_WNDPROC, replacement);

    if (!installed) { logger::error("[ input ] could not replace the window procedure -> " + text::last_error()); current.target = nullptr; return false; }

    current.previous = reinterpret_cast<WNDPROC>(installed);
    logger::success("[ input ] window procedure hooked, press delete to toggle the overlay");

    return true;
}

void input::window::release() {
    binding& current = state();
    if (!current.previous || !current.target) return;

    if (IsWindow(current.target)) {
        const auto restored = reinterpret_cast<LONG_PTR>(current.previous);
        if (current.is_unicode) SetWindowLongPtrW(current.target, GWLP_WNDPROC, restored);
        else SetWindowLongPtrA(current.target, GWLP_WNDPROC, restored);
    }

    current.previous = nullptr;
    current.target = nullptr;
}

bool input::window::is_hooked() { return state().previous != nullptr; }
