#pragma once
#include <utility>

namespace win {

    template <class action>
    class scope_guard {
        action leave;
        bool is_armed = true;

    public:
        explicit scope_guard(action&& value) noexcept : leave(std::move(value)) {}
        ~scope_guard() { if (is_armed) leave(); }

        scope_guard(const scope_guard&) = delete;
        scope_guard& operator=(const scope_guard&) = delete;

        void dismiss() noexcept { is_armed = false; }
    };

    template <class action> [[nodiscard]] scope_guard<action> on_scope_exit(action&& value) noexcept {
        return scope_guard<action>(std::forward<action>(value));
    }

}
