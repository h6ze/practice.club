#include "frame.hh"
#include <atomic>
#include <dxgi1_4.h>
#include <imgui/imgui.h>
#include <features/features.hh>
#include <client/bridge/dispatch.hh>
#include <sdk/unreal/runtime/stage.hh>
#include <client/platform/input/hotkeys.hh>
#include <client/platform/input/window.hh>
#include <client/diag/log/logger.hh>
#include <client/util/handle.hh>
#include <client/render/backend.hh>
#include <client/render/dx12/device.hh>
#include <client/render/ui/overlay.hh>

namespace {

    std::atomic<bool> is_drawing{false};

    class draw_lock {
        bool held = false;

    public:
        draw_lock() {
            bool idle = false;
            held = is_drawing.compare_exchange_strong(idle, true);
        }

        ~draw_lock() { if (held) is_drawing.store(false); }

        draw_lock(const draw_lock&) = delete;
        draw_lock& operator=(const draw_lock&) = delete;

        [[nodiscard]] bool is_held() const noexcept { return held; }
    };

}

void render::frame::draw(IDXGISwapChain* swap_chain) {
    const draw_lock lock;
    if (!lock.is_held()) return;

    if (!device::bind(swap_chain)) return;
    if (!backend::ensure(device::handle(), device::queue(), device::srv_heap(), device::window(), device::format(), device::buffers())) return;

    IDXGISwapChain3* sc3 = nullptr;
    if (FAILED(swap_chain->QueryInterface(IID_PPV_ARGS(&sc3)))) return;
    const auto sc3_ptr = win::adopt_com(sc3);

    const UINT index = sc3->GetCurrentBackBufferIndex();

    ID3D12GraphicsCommandList* list = device::begin_frame(index);
    if (!list) return;

    if (!input::window::ensure(device::window()))
        logger::warning("[ input ] the overlay cannot take input until the window procedure is hooked");

    game::dispatch::bind_game_thread(GetWindowThreadProcessId(device::window(), nullptr));

    game::refresh_stage();

    backend::begin();

    features::draw_frame();

    ImGui::GetIO().MouseDrawCursor = input::hotkeys::is_overlay_open();
    if (input::hotkeys::is_overlay_open()) overlay::draw();

    backend::end(list);

    device::end_frame(index);
}
