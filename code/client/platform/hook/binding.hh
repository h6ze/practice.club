#pragma once

namespace hook::detail {

    class binding {
        void* entry = nullptr;
        void* replacement = nullptr;
        void* target = nullptr;

    public:
        binding() = default;
        ~binding();

        binding(const binding&) = delete;
        binding& operator=(const binding&) = delete;

        [[nodiscard]] bool attach(void* address, void* hook, const char* name);
        void detach();

        [[nodiscard]] bool is_active() const noexcept { return target != nullptr; }
        [[nodiscard]] void* trampoline() const noexcept { return entry; }
        [[nodiscard]] void* address() const noexcept { return target; }
    };

}
