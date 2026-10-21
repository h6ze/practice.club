#include "device.hh"
#include <algorithm>
#include <array>
#include <vector>
#include <client/diag/log/logger.hh>
#include <client/util/handle.hh>
#include <client/util/string/text.hh>
#include <client/render/dx12/frame/queue.hh>

namespace {

    constexpr UINT max_frames = 8;

    constexpr UINT srv_descriptors = 64;

    struct frame_ctx {
        win::com_ptr<ID3D12CommandAllocator> allocator;
        win::com_ptr<ID3D12Resource> render_target;
        D3D12_CPU_DESCRIPTOR_HANDLE rtv{};
        UINT64 fence_value = 0;
    };

    struct pipeline {
        win::com_ptr<ID3D12Device> device;
        ID3D12CommandQueue* queue = nullptr;
        win::com_ptr<ID3D12Fence> fence;
        win::com_ptr<ID3D12DescriptorHeap> rtv_heap;
        win::com_ptr<ID3D12DescriptorHeap> srv_heap;
        win::com_ptr<ID3D12GraphicsCommandList> cmd_list;
        std::array<frame_ctx, max_frames> frames;
        HWND window = nullptr;
        DXGI_FORMAT rtv_format = DXGI_FORMAT_UNKNOWN;
        UINT buffers = 0;
        UINT rtv_stride = 0;
        UINT srv_stride = 0;
        std::vector<UINT> srv_free;
        UINT64 fence_ctr = 0;
        win::unique_handle fence_event;
        bool is_ready = false;
    };

    pipeline& state() {
        static pipeline value;
        return value;
    }

    void flush_gpu() {
        pipeline& p = state();
        if (!p.queue || !p.fence || !p.fence_event.get()) return;
        const UINT64 v = ++p.fence_ctr;
        p.queue->Signal(p.fence.get(), v);
        if (p.fence->GetCompletedValue() < v) {
            p.fence->SetEventOnCompletion(v, p.fence_event.get());
            WaitForSingleObject(p.fence_event.get(), INFINITE);
        }
    }

    void reset_pipeline(pipeline& p) {
        for (auto& f : p.frames) { f.render_target.reset(); f.allocator.reset(); f.rtv = {}; f.fence_value = 0; }
        p.cmd_list.reset();
        p.srv_heap.reset();
        p.rtv_heap.reset();
        p.fence_event.reset();
        p.fence.reset();
        p.queue = nullptr;
        p.device.reset();
        p.window = nullptr;
        p.rtv_format = DXGI_FORMAT_UNKNOWN;
        p.buffers = 0;
        p.rtv_stride = 0;
        p.srv_stride = 0;
        p.srv_free.clear();
        p.fence_ctr = 0;
        p.is_ready = false;
    }

}

bool render::device::bind(IDXGISwapChain* swap_chain) {
    pipeline& p = state();
    if (p.is_ready) return true;
    if (!swap_chain) return false;

    ID3D12Device* raw_device = nullptr;
    if (FAILED(swap_chain->GetDevice(IID_PPV_ARGS(&raw_device)))) {
        logger::error("[ render ] the swapchain is not backed by a d3d12 device");
        return false;
    }
    p.device = win::adopt_com(raw_device);

    if (!queue::ensure(p.device.get())) { reset_pipeline(p); return false; }

    ID3D12CommandQueue* lent = queue::borrowed();
    if (!lent) { reset_pipeline(p); return false; }

    ID3D12Device* raw_owner = nullptr;
    if (FAILED(lent->GetDevice(IID_PPV_ARGS(&raw_owner)))) {
        logger::error("[ render ] the borrowed command queue would not name its device");
        reset_pipeline(p); return false;
    }
    const auto owner = win::adopt_com(raw_owner);

    if (owner.get() != p.device.get()) {
        logger::error("[ render ] the borrowed command queue belongs to another device -> the overlay stays hidden");
        reset_pipeline(p); return false;
    }
    p.queue = lent;

    DXGI_SWAP_CHAIN_DESC desc{};
    if (FAILED(swap_chain->GetDesc(&desc)) || !desc.OutputWindow) {
        logger::error("[ render ] the swapchain reported no output window");
        reset_pipeline(p); return false;
    }
    p.window = desc.OutputWindow;
    p.rtv_format = desc.BufferDesc.Format;
    p.buffers = std::clamp(desc.BufferCount, 1u, max_frames);

    logger::info("[ render ] swapchain is " + std::to_string(desc.BufferDesc.Width) + "x" + std::to_string(desc.BufferDesc.Height)
        + ", format " + std::to_string(static_cast<int>(desc.BufferDesc.Format))
        + ", " + std::to_string(desc.BufferCount) + " buffers, flags " + text::hex(desc.Flags, 4));

    ID3D12Fence* raw_fence = nullptr;
    if (FAILED(p.device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&raw_fence)))) {
        logger::error("[ render ] could not create a fence");
        reset_pipeline(p); return false;
    }
    p.fence = win::adopt_com(raw_fence);

    HANDLE event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (!event) { logger::error("[ render ] could not create a fence event"); reset_pipeline(p); return false; }
    p.fence_event = win::adopt(event);

    D3D12_DESCRIPTOR_HEAP_DESC rtv_hd{};
    rtv_hd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtv_hd.NumDescriptors = p.buffers;
    rtv_hd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    ID3D12DescriptorHeap* raw_rtv = nullptr;
    if (FAILED(p.device->CreateDescriptorHeap(&rtv_hd, IID_PPV_ARGS(&raw_rtv)))) {
        logger::error("[ render ] could not create the rtv heap");
        reset_pipeline(p); return false;
    }
    p.rtv_heap = win::adopt_com(raw_rtv);
    p.rtv_stride = p.device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    D3D12_DESCRIPTOR_HEAP_DESC srv_hd{};
    srv_hd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    srv_hd.NumDescriptors = srv_descriptors;
    srv_hd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

    ID3D12DescriptorHeap* raw_srv = nullptr;
    if (FAILED(p.device->CreateDescriptorHeap(&srv_hd, IID_PPV_ARGS(&raw_srv)))) {
        logger::error("[ render ] could not create the srv heap");
        reset_pipeline(p); return false;
    }
    p.srv_heap = win::adopt_com(raw_srv);
    p.srv_stride = p.device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    p.srv_free.clear();
    p.srv_free.reserve(srv_descriptors);
    for (UINT i = srv_descriptors; i > 0; --i) p.srv_free.push_back(i - 1);

    for (UINT i = 0; i < p.buffers; ++i) {
        ID3D12CommandAllocator* raw_alloc = nullptr;
        if (FAILED(p.device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&raw_alloc)))) {
            logger::error("[ render ] could not create a command allocator");
            reset_pipeline(p); return false;
        }
        p.frames[i].allocator = win::adopt_com(raw_alloc);
    }

    ID3D12GraphicsCommandList* raw_list = nullptr;
    if (FAILED(p.device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
            p.frames[0].allocator.get(), nullptr, IID_PPV_ARGS(&raw_list)))) {
        logger::error("[ render ] could not create a command list");
        reset_pipeline(p); return false;
    }
    p.cmd_list = win::adopt_com(raw_list);
    p.cmd_list->Close();

    if (!create_targets(swap_chain)) { reset_pipeline(p); return false; }

    p.is_ready = true;
    logger::success("[ render ] bound to the d3d12 device on window " + text::hex(reinterpret_cast<uintptr_t>(p.window)));
    return true;
}

void render::device::release() {
    pipeline& p = state();
    flush_gpu();
    reset_pipeline(p);
}

bool render::device::create_targets(IDXGISwapChain* swap_chain) {
    pipeline& p = state();
    if (!p.device || !swap_chain || !p.rtv_heap || !p.buffers) return false;

    D3D12_CPU_DESCRIPTOR_HANDLE h = p.rtv_heap->GetCPUDescriptorHandleForHeapStart();

    for (UINT i = 0; i < p.buffers; ++i) {
        ID3D12Resource* raw_buffer = nullptr;
        if (FAILED(swap_chain->GetBuffer(i, IID_PPV_ARGS(&raw_buffer)))) {
            logger::error("[ render ] back buffer " + std::to_string(i) + " could not be read -> the overlay stays hidden");
            return false;
        }

        D3D12_RENDER_TARGET_VIEW_DESC rtv_desc{};
        rtv_desc.Format = p.rtv_format;
        rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

        p.frames[i].render_target = win::adopt_com(raw_buffer);
        p.frames[i].rtv = h;
        p.device->CreateRenderTargetView(raw_buffer, &rtv_desc, h);
        h.ptr += p.rtv_stride;
    }

    return true;
}

void render::device::release_targets() {
    flush_gpu();
    for (auto& f : state().frames) f.render_target.reset();
}

ID3D12Device* render::device::handle() { return state().device.get(); }
ID3D12CommandQueue* render::device::queue() { return state().queue; }
ID3D12DescriptorHeap* render::device::srv_heap() { return state().srv_heap.get(); }
HWND render::device::window() { return state().window; }
bool render::device::is_ready() { return state().is_ready; }
DXGI_FORMAT render::device::format() { return state().rtv_format; }

bool render::device::srv_alloc(D3D12_CPU_DESCRIPTOR_HANDLE* cpu, D3D12_GPU_DESCRIPTOR_HANDLE* gpu) {
    pipeline& p = state();
    if (!cpu || !gpu || !p.srv_heap || p.srv_free.empty()) return false;

    const UINT slot = p.srv_free.back();
    p.srv_free.pop_back();

    cpu->ptr = p.srv_heap->GetCPUDescriptorHandleForHeapStart().ptr + slot * p.srv_stride;
    gpu->ptr = p.srv_heap->GetGPUDescriptorHandleForHeapStart().ptr + slot * p.srv_stride;

    return true;
}

void render::device::srv_free(D3D12_CPU_DESCRIPTOR_HANDLE cpu, D3D12_GPU_DESCRIPTOR_HANDLE) {
    pipeline& p = state();
    if (!p.srv_heap || !p.srv_stride) return;

    const SIZE_T start = p.srv_heap->GetCPUDescriptorHandleForHeapStart().ptr;
    if (cpu.ptr < start) return;

    const UINT slot = static_cast<UINT>((cpu.ptr - start) / p.srv_stride);
    if (slot < srv_descriptors) p.srv_free.push_back(slot);
}
UINT render::device::buffers() { return state().buffers; }

ID3D12GraphicsCommandList* render::device::begin_frame(UINT index) {
    pipeline& p = state();
    if (!p.is_ready || !p.buffers) return nullptr;

    frame_ctx& f = p.frames[index % p.buffers];
    if (!f.render_target) return nullptr;

    if (p.fence->GetCompletedValue() < f.fence_value) {
        p.fence->SetEventOnCompletion(f.fence_value, p.fence_event.get());
        WaitForSingleObject(p.fence_event.get(), INFINITE);
    }

    f.allocator->Reset();
    p.cmd_list->Reset(f.allocator.get(), nullptr);

    D3D12_RESOURCE_BARRIER barrier{};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = f.render_target.get();
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    p.cmd_list->ResourceBarrier(1, &barrier);

    p.cmd_list->OMSetRenderTargets(1, &f.rtv, FALSE, nullptr);

    ID3D12DescriptorHeap* heaps[] = { p.srv_heap.get() };
    p.cmd_list->SetDescriptorHeaps(1, heaps);

    return p.cmd_list.get();
}

void render::device::end_frame(UINT index) {
    pipeline& p = state();
    if (!p.is_ready || !p.buffers) return;

    frame_ctx& f = p.frames[index % p.buffers];

    D3D12_RESOURCE_BARRIER barrier{};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = f.render_target.get();
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    p.cmd_list->ResourceBarrier(1, &barrier);

    p.cmd_list->Close();

    ID3D12CommandList* lists[] = { p.cmd_list.get() };
    p.queue->ExecuteCommandLists(1, lists);

    f.fence_value = ++p.fence_ctr;
    p.queue->Signal(p.fence.get(), p.fence_ctr);

    const HRESULT lost = p.device->GetDeviceRemovedReason();
    if (FAILED(lost)) logger::error("[ render ] the d3d12 device was removed, reason " + text::hex(static_cast<unsigned long>(lost), 8));
}
