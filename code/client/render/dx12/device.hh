#pragma once
#include <d3d12.h>
#include <dxgi.h>

namespace render::device {

    [[nodiscard]] bool bind(IDXGISwapChain* swap_chain);
    void release();

    [[nodiscard]] bool create_targets(IDXGISwapChain* swap_chain);
    void release_targets();

    [[nodiscard]] ID3D12Device* handle();
    [[nodiscard]] ID3D12CommandQueue* queue();
    [[nodiscard]] ID3D12DescriptorHeap* srv_heap();
    [[nodiscard]] ID3D12GraphicsCommandList* begin_frame(UINT index);
    void end_frame(UINT index);
    [[nodiscard]] HWND window();
    [[nodiscard]] bool is_ready();
    [[nodiscard]] DXGI_FORMAT format();
    [[nodiscard]] UINT buffers();

    [[nodiscard]] bool srv_alloc(D3D12_CPU_DESCRIPTOR_HANDLE* cpu, D3D12_GPU_DESCRIPTOR_HANDLE* gpu);
    void srv_free(D3D12_CPU_DESCRIPTOR_HANDLE cpu, D3D12_GPU_DESCRIPTOR_HANDLE gpu);

}
