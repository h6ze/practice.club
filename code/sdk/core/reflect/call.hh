#pragma once
#include <cstdint>
#include <vector>
#include "object.hh"

namespace sdk {

    void bind_process_event(void* address);

    namespace call {

        [[nodiscard]] bool is_ready();

        class invocation {
            UObject* target = nullptr;
            UFunction* entry = nullptr;
            std::vector<std::uint8_t> frame;

        public:
            invocation(UObject* object, const char* function_name);

            [[nodiscard]] bool is_valid() const noexcept { return target != nullptr && entry != nullptr; }
            [[nodiscard]] std::int32_t frame_size() const noexcept { return static_cast<std::int32_t>(frame.size()); }

            template <class T> void set(std::uint32_t offset, const T& value) noexcept {
                if (offset + sizeof(T) > frame.size()) return;

                *reinterpret_cast<T*>(frame.data() + offset) = value;
            }

            template <class T> [[nodiscard]] T get(std::uint32_t offset) const noexcept {
                if (offset + sizeof(T) > frame.size()) return T{};

                return *reinterpret_cast<const T*>(frame.data() + offset);
            }

            [[nodiscard]] bool fire();
        };

        [[nodiscard]] inline bool fire(UObject* object, const char* function_name) {
            invocation entry(object, function_name);

            return entry.is_valid() && entry.fire();
        }

        template <class T> [[nodiscard]] inline bool fire_with(UObject* object, const char* function_name, std::uint32_t offset, const T& value) {
            invocation entry(object, function_name);
            if (!entry.is_valid()) return false;

            entry.set<T>(offset, value);

            return entry.fire();
        }

    }

}
