#include "queue.hh"
#include <atomic>
#include <client/platform/hook/detour.hh>
#include <client/platform/hook/patch/vtable.hh>
#include <client/diag/log/logger.hh>
#include <client/util/handle.hh>
#include <client/util/string/text.hh>

namespace {

    constexpr size_t execute_slot = 10;

    using execute_call = void(__stdcall*)(ID3D12CommandQueue*, UINT, ID3D12CommandList* const*);

    struct entries {
        hook::detour<execute_call> execute;
        std::atomic<ID3D12CommandQueue*> direct{nullptr};
        bool is_hooked = false;
    };

    entries& state() {
        static entries value;
        return value;
    }

    void __stdcall on_execute(ID3D12CommandQueue* command_queue, UINT count, ID3D12CommandList* const* lists) {
        entries& current = state();

        if (command_queue && !current.direct.load(std::memory_order_acquire)
            && command_queue->GetDesc().Type == D3D12_COMMAND_LIST_TYPE_DIRECT) {
            ID3D12CommandQueue* idle = nullptr;
            if (current.direct.compare_exchange_strong(idle, command_queue)) {
                command_queue->AddRef();
                logger::success("[ render ] borrowed the game command queue at " + text::hex(reinterpret_cast<uintptr_t>(command_queue)));
            }
        }

        current.execute.original(command_queue, count, lists);
    }

    [[nodiscard]] void* resolve(ID3D12Device* device) {
        D3D12_COMMAND_QUEUE_DESC qd{};
        qd.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        qd.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

        ID3D12CommandQueue* raw_queue = nullptr;
        if (FAILED(device->CreateCommandQueue(&qd, IID_PPV_ARGS(&raw_queue)))) {
            logger::error("[ render ] could not create a scratch command queue to read its vtable");
            return nullptr;
        }
        const auto scratch = win::adopt_com(raw_queue);

        return hook::vtable_slot(scratch.get(), execute_slot);
    }

}

bool render::queue::ensure(ID3D12Device* device) {
    entries& current = state();
    if (current.is_hooked) return true;
    if (!device) return false;

    void* target = resolve(device);
    if (!target) return false;

    if (!current.execute.attach(target, on_execute, "ID3D12CommandQueue::ExecuteCommandLists")) return false;

    current.is_hooked = true;
    logger::info("[ render ] waiting for the game to submit on its own command queue");

    return true;
}

void render::queue::unhook() {
    entries& current = state();

    current.execute.detach();
    current.is_hooked = false;

    if (ID3D12CommandQueue* lent = current.direct.exchange(nullptr)) lent->Release();
}

ID3D12CommandQueue* render::queue::borrowed() { return state().direct.load(std::memory_order_acquire); }
