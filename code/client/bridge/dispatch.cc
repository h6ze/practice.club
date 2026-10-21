#include "dispatch.hh"
#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <mutex>
#include <string>
#include <utility>
#include <vector>
#include <sdk/globals.hh>
#include <sdk/offsets.generated.hh>
#include <client/platform/hook/detour.hh>
#include <client/diag/log/logger.hh>

namespace game::dispatch::detail {

    using process_event_call = void(__fastcall*)(void*, void*, void*);
    hook::detour<process_event_call> process_event;

    constexpr std::size_t stalled_queue = 64;

    std::mutex guard;
    std::vector<std::function<void()>> queue;

    std::atomic<std::size_t> waiting{0};
    std::atomic<bool> is_draining{false};
    std::atomic<unsigned long> game_thread{0};

    std::atomic<const void*> watched{nullptr};
    std::atomic<intercept> on_watched{nullptr};

    void drain() {
        std::vector<std::function<void()>> batch;

        {
            const std::lock_guard<std::mutex> lock(guard);
            batch.swap(queue);
            waiting.store(0, std::memory_order_relaxed);
        }

        for (const std::function<void()>& work : batch)
            if (work) work();
    }

    void __fastcall on_process_event(void* object, void* function, void* params) {
        const bool is_game_thread = waiting.load(std::memory_order_relaxed) > 0 && GetCurrentThreadId() == game_thread.load(std::memory_order_relaxed);
        if (is_game_thread && !is_draining.exchange(true, std::memory_order_acquire)) {
            drain();
            is_draining.store(false, std::memory_order_release);
        }

        if (function == watched.load(std::memory_order_relaxed)) {
            const intercept on_call = on_watched.load(std::memory_order_relaxed);
            if (on_call) on_call(object, params);
        }

        process_event.original(object, function, params);
    }

}

void game::dispatch::watch(const void* function, intercept on_call) {
    if (!function || !on_call) {
        detail::watched.store(nullptr, std::memory_order_relaxed);
        detail::on_watched.store(nullptr, std::memory_order_release);
        return;
    }

    detail::on_watched.store(on_call, std::memory_order_relaxed);
    detail::watched.store(function, std::memory_order_release);
}

bool game::dispatch::install() {
    if (detail::process_event.is_active()) return true;

    const std::uintptr_t base = sdk::globals::base();
    if (!base) { logger::error("[ dispatch ] the sdk has not resolved the game module yet"); return false; }

    void* target = reinterpret_cast<void*>(base + sdk::offsets::global::process_event);
    if (!detail::process_event.attach(target, detail::on_process_event, "UObject::ProcessEvent")) return false;

    logger::success("[ dispatch ] game thread pump armed on processevent");

    return true;
}

void game::dispatch::remove() {
    detail::process_event.detach();

    const std::lock_guard<std::mutex> lock(detail::guard);
    detail::queue.clear();
    detail::waiting.store(0, std::memory_order_relaxed);
}

void game::dispatch::post(std::function<void()> work) {
    if (!work) return;

    if (!detail::process_event.is_active()) { logger::error("[ dispatch ] no game thread pump -> the work was dropped"); return; }

    const std::lock_guard<std::mutex> lock(detail::guard);
    detail::queue.push_back(std::move(work));
    detail::waiting.store(detail::queue.size(), std::memory_order_relaxed);

    if (detail::queue.size() == detail::stalled_queue) logger::warning("[ dispatch ] queued work is not draining -> the game thread binding looks wrong");
}

void game::dispatch::bind_game_thread(unsigned long id) {
    if (!id || detail::game_thread.load(std::memory_order_relaxed) == id) return;

    detail::game_thread.store(id, std::memory_order_relaxed);
    logger::info("[ dispatch ] game thread is " + std::to_string(id) + ", queued work runs only there");
}

bool game::dispatch::is_ready() { return detail::process_event.is_active(); }

std::size_t game::dispatch::pending() { return detail::waiting.load(std::memory_order_relaxed); }

unsigned long game::dispatch::thread_id() { return detail::game_thread.load(std::memory_order_relaxed); }
