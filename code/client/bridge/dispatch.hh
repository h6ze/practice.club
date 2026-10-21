#pragma once
#include <cstddef>
#include <functional>

namespace game::dispatch {

    [[nodiscard]] bool install();
    void remove();

    void post(std::function<void()> work);

    void bind_game_thread(unsigned long id);

    [[nodiscard]] bool is_ready();
    [[nodiscard]] std::size_t pending();
    [[nodiscard]] unsigned long thread_id();

    using intercept = void (*)(void* object, void* params);

    void watch(const void* function, intercept on_call);

}
