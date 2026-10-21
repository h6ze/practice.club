#pragma once
#include <d3d12.h>
#include <dxgi.h>
#include <Windows.h>

namespace render::backend {

    [[nodiscard]] bool ensure(ID3D12Device* device, ID3D12CommandQueue* queue, ID3D12DescriptorHeap* srv_heap, HWND window,
        DXGI_FORMAT rtv_format, UINT frames_in_flight);
    void stop();

    [[nodiscard]] bool is_ready();

    void begin();
    void end(ID3D12GraphicsCommandList* cmd_list);

}
