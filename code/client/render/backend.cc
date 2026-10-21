#include "backend.hh"
#include <string>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx12.h>
#include <imgui/imgui_impl_win32.h>
#include <client/diag/log/logger.hh>
#include <client/render/dx12/device.hh>
#include <client/render/fonts/fonts.hh>
#include <client/render/ui/style/theme.hh>

namespace {

    struct stage {
        bool is_context = false;
        bool is_platform = false;
        bool is_renderer = false;

        [[nodiscard]] bool is_ready() const noexcept { return is_context && is_platform && is_renderer; }
    };

    stage& state() {
        static stage value;
        return value;
    }

    void configure() {
        ImGuiIO& io = ImGui::GetIO();

        io.IniFilename = nullptr;
        io.LogFilename = nullptr;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigWindowsMoveFromTitleBarOnly = true;
    }

}

bool render::backend::ensure(ID3D12Device* device, ID3D12CommandQueue* queue, ID3D12DescriptorHeap* srv_heap, HWND window,
    DXGI_FORMAT rtv_format, UINT frames_in_flight) {
    stage& current = state();
    if (current.is_ready()) return true;
    if (!device || !queue || !srv_heap || !window) return false;
    if (rtv_format == DXGI_FORMAT_UNKNOWN || !frames_in_flight) return false;

    if (!current.is_context) {
        IMGUI_CHECKVERSION();
        if (!ImGui::CreateContext()) { logger::error("[ imgui ] could not create a context"); return false; }

        configure();
        theme::apply();
        fonts::load();

        current.is_context = true;
    }

    if (!current.is_platform) {
        if (!ImGui_ImplWin32_Init(window)) { logger::error("[ imgui ] the win32 platform backend refused to start"); return false; }
        current.is_platform = true;
    }

    if (!current.is_renderer) {
        ImGui_ImplDX12_InitInfo info{};
        info.Device = device;
        info.CommandQueue = queue;
        info.NumFramesInFlight = static_cast<UINT>(frames_in_flight);
        info.RTVFormat = rtv_format;
        info.DSVFormat = DXGI_FORMAT_UNKNOWN;
        info.SrvDescriptorHeap = srv_heap;

        info.SrvDescriptorAllocFn = [](ImGui_ImplDX12_InitInfo*, D3D12_CPU_DESCRIPTOR_HANDLE* cpu, D3D12_GPU_DESCRIPTOR_HANDLE* gpu) {
            if (!device::srv_alloc(cpu, gpu)) logger::error("[ imgui ] the srv descriptor heap ran out of room");
        };

        info.SrvDescriptorFreeFn = [](ImGui_ImplDX12_InitInfo*, D3D12_CPU_DESCRIPTOR_HANDLE cpu, D3D12_GPU_DESCRIPTOR_HANDLE gpu) {
            device::srv_free(cpu, gpu);
        };

        if (!ImGui_ImplDX12_Init(&info)) { logger::error("[ imgui ] the dx12 renderer backend refused to start"); return false; }

        if (!ImGui_ImplDX12_CreateDeviceObjects()) {
            logger::error("[ imgui ] the dx12 pipeline objects could not be created -> format " + std::to_string(static_cast<int>(rtv_format)) + " may be unsupported");
            ImGui_ImplDX12_Shutdown();
            return false;
        }

        current.is_renderer = true;
    }

    logger::success("[ imgui ] overlay backend ready");

    return true;
}

void render::backend::stop() {
    stage& current = state();

    if (current.is_renderer) { ImGui_ImplDX12_Shutdown(); current.is_renderer = false; }
    if (current.is_platform) { ImGui_ImplWin32_Shutdown(); current.is_platform = false; }
    if (current.is_context) { ImGui::DestroyContext(); current.is_context = false; }
}

bool render::backend::is_ready() { return state().is_ready(); }

void render::backend::begin() {
    ImGui_ImplDX12_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void render::backend::end(ID3D12GraphicsCommandList* cmd_list) {
    ImGui::Render();
    if (!cmd_list) return;
    ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cmd_list);
}
