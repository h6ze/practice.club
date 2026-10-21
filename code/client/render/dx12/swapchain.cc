#include "swapchain.hh"
#include <d3d11.h>
#include <iterator>
#include <client/platform/hook/detour.hh>
#include <client/platform/hook/patch/vtable.hh>
#include <client/platform/input/window.hh>
#include <client/diag/log/logger.hh>
#include <client/util/handle.hh>
#include <client/render/backend.hh>
#include "device.hh"
#include <client/render/dx12/frame/frame.hh>

namespace {

    constexpr size_t present_slot = 8;
    constexpr size_t resize_buffers_slot = 13;
    constexpr DWORD settle_delay_ms = 64;

    using present_call = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);
    using resize_buffers_call = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

    struct entries {
        hook::detour<present_call> present;
        hook::detour<resize_buffers_call> resize_buffers;
    };

    entries& state() {
        static entries value;
        return value;
    }

#pragma region scratch device

    class scratch_window {
        const wchar_t* registered = nullptr;
        HINSTANCE owner = nullptr;
        HWND handle = nullptr;

    public:
        scratch_window() {
            owner = GetModuleHandleW(nullptr);

            WNDCLASSEXW description{};
            description.cbSize = sizeof(description);
            description.style = CS_HREDRAW | CS_VREDRAW;
            description.lpfnWndProc = DefWindowProcW;
            description.hInstance = owner;
            description.lpszClassName = L"practice.club.scratch";

            if (!RegisterClassExW(&description)) return;

            registered = description.lpszClassName;
            handle = CreateWindowExW(0, registered, L"", WS_OVERLAPPEDWINDOW, 0, 0, 64, 64, nullptr, nullptr, owner, nullptr);
        }

        ~scratch_window() {
            if (handle) DestroyWindow(handle);
            if (registered) UnregisterClassW(registered, owner);
        }

        scratch_window(const scratch_window&) = delete;
        scratch_window& operator=(const scratch_window&) = delete;

        [[nodiscard]] HWND get() const noexcept { return handle; }
    };

    struct slots { void* present = nullptr; void* resize_buffers = nullptr; };

    [[nodiscard]] slots resolve() {
        const scratch_window scratch;
        if (!scratch.get()) { logger::error("[ render ] could not create a scratch window to read the swapchain vtable"); return {}; }

        DXGI_SWAP_CHAIN_DESC description{};
        description.BufferCount = 1;
        description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        description.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        description.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        description.OutputWindow = scratch.get();
        description.SampleDesc.Count = 1;
        description.Windowed = TRUE;
        description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        constexpr D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };

        IDXGISwapChain* raw_chain = nullptr;
        ID3D11Device* raw_device = nullptr;
        ID3D11DeviceContext* raw_context = nullptr;

        const HRESULT created = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
            levels, static_cast<UINT>(std::size(levels)), D3D11_SDK_VERSION,
            &description, &raw_chain, &raw_device, nullptr, &raw_context);

        if (FAILED(created)) { logger::error("[ render ] d3d11 refused a scratch device -> the game may not be rendering through d3d11"); return {}; }

        const auto chain = win::adopt_com(raw_chain);
        const auto device = win::adopt_com(raw_device);
        const auto context = win::adopt_com(raw_context);

        slots found;
        found.present = hook::vtable_slot(chain.get(), present_slot);
        found.resize_buffers = hook::vtable_slot(chain.get(), resize_buffers_slot);

        return found;
    }

#pragma endregion

#pragma region hooks

    HRESULT __stdcall on_present(IDXGISwapChain* swap_chain, UINT sync_interval, UINT flags) {
        render::frame::draw(swap_chain);

        return state().present.original(swap_chain, sync_interval, flags);
    }

    HRESULT __stdcall on_resize_buffers(IDXGISwapChain* swap_chain, UINT count, UINT width, UINT height, DXGI_FORMAT format, UINT flags) {
        render::device::release_targets();

        const HRESULT result = state().resize_buffers.original(swap_chain, count, width, height, format, flags);

        if (SUCCEEDED(result) && !render::device::create_targets(swap_chain))
            logger::error("[ render ] the render target did not survive the resize -> the overlay stays hidden until the next one");

        return result;
    }

#pragma endregion

}

bool render::swapchain::hook() {
    const slots found = resolve();
    if (!found.present) { logger::error("[ render ] the swapchain vtable could not be read"); return false; }

    entries& current = state();
    if (!current.present.attach(found.present, on_present, "IDXGISwapChain::Present")) return false;

    if (!found.resize_buffers || !current.resize_buffers.attach(found.resize_buffers, on_resize_buffers, "IDXGISwapChain::ResizeBuffers"))
        logger::warning("[ render ] resizebuffers is unhooked -> the overlay will go blank after a resolution change");

    logger::success("[ render ] present hooked, waiting for the first frame");

    return true;
}

void render::swapchain::unhook() {
    entries& current = state();

    current.resize_buffers.detach();
    current.present.detach();

    Sleep(settle_delay_ms);

    input::window::release();
    backend::stop();
    device::release();
}
