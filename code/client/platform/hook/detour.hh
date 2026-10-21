#pragma once
#include <cstdint>
#include "binding.hh"

namespace hook {

    template <class signature> class detour;

#pragma region native convention

    template <class result, class... args>
    class detour<result(*)(args...)> : detail::binding {
        using function = result(*)(args...);

    public:
        [[nodiscard]] bool attach(void* address, function handler, const char* name) {
            return detail::binding::attach(address, reinterpret_cast<void*>(handler), name);
        }

        [[nodiscard]] bool attach(uintptr_t address, function handler, const char* name) {
            return attach(reinterpret_cast<void*>(address), handler, name);
        }

        result original(args... arguments) const {
            const auto resume = reinterpret_cast<function>(detail::binding::trampoline());
            return resume ? resume(arguments...) : result();
        }

        using detail::binding::detach;
        using detail::binding::is_active;
        using detail::binding::address;
    };

#pragma endregion

#pragma region vectorcall

    template <class result, class... args>
    class detour<result(__vectorcall*)(args...)> : detail::binding {
        using function = result(__vectorcall*)(args...);

    public:
        [[nodiscard]] bool attach(void* address, function handler, const char* name) {
            return detail::binding::attach(address, reinterpret_cast<void*>(handler), name);
        }

        [[nodiscard]] bool attach(uintptr_t address, function handler, const char* name) {
            return attach(reinterpret_cast<void*>(address), handler, name);
        }

        result original(args... arguments) const {
            const auto resume = reinterpret_cast<function>(detail::binding::trampoline());
            return resume ? resume(arguments...) : result();
        }

        using detail::binding::detach;
        using detail::binding::is_active;
        using detail::binding::address;
    };

#pragma endregion

#if defined(_M_IX86)

#pragma region stdcall

    template <class result, class... args>
    class detour<result(__stdcall*)(args...)> : detail::binding {
        using function = result(__stdcall*)(args...);

    public:
        [[nodiscard]] bool attach(void* address, function handler, const char* name) {
            return detail::binding::attach(address, reinterpret_cast<void*>(handler), name);
        }

        [[nodiscard]] bool attach(uintptr_t address, function handler, const char* name) {
            return attach(reinterpret_cast<void*>(address), handler, name);
        }

        result original(args... arguments) const {
            const auto resume = reinterpret_cast<function>(detail::binding::trampoline());
            return resume ? resume(arguments...) : result();
        }

        using detail::binding::detach;
        using detail::binding::is_active;
        using detail::binding::address;
    };

#pragma endregion

#pragma region fastcall

    template <class result, class... args>
    class detour<result(__fastcall*)(args...)> : detail::binding {
        using function = result(__fastcall*)(args...);

    public:
        [[nodiscard]] bool attach(void* address, function handler, const char* name) {
            return detail::binding::attach(address, reinterpret_cast<void*>(handler), name);
        }

        [[nodiscard]] bool attach(uintptr_t address, function handler, const char* name) {
            return attach(reinterpret_cast<void*>(address), handler, name);
        }

        result original(args... arguments) const {
            const auto resume = reinterpret_cast<function>(detail::binding::trampoline());
            return resume ? resume(arguments...) : result();
        }

        using detail::binding::detach;
        using detail::binding::is_active;
        using detail::binding::address;
    };

#pragma endregion

#pragma region thiscall

    template <class result, class... args>
    class detour<result(__thiscall*)(args...)> : detail::binding {
        using function = result(__thiscall*)(args...);

    public:
        [[nodiscard]] bool attach(void* address, function handler, const char* name) {
            return detail::binding::attach(address, reinterpret_cast<void*>(handler), name);
        }

        [[nodiscard]] bool attach(uintptr_t address, function handler, const char* name) {
            return attach(reinterpret_cast<void*>(address), handler, name);
        }

        result original(args... arguments) const {
            const auto resume = reinterpret_cast<function>(detail::binding::trampoline());
            return resume ? resume(arguments...) : result();
        }

        using detail::binding::detach;
        using detail::binding::is_active;
        using detail::binding::address;
    };

#pragma endregion

#endif

}
