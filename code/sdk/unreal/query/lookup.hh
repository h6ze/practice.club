#pragma once
#include <cstdint>
#include <initializer_list>
#include <vector>
#include <sdk/core/reflect/object.hh>

namespace sdk::lookup {

    struct held {
        UObject* object = nullptr;
        std::int32_t index = -1;
    };

    [[nodiscard]] bool is_live(const held& slot);

    [[nodiscard]] UObject* class_default(held& slot, const char* class_name);

    [[nodiscard]] bool derives_from(const UObject* object, const char* class_name);

    [[nodiscard]] UObject* find_owned(const char* class_name, std::initializer_list<const UObject*> outers);

    [[nodiscard]] std::vector<UObject*> live_instances(const char* class_name);

}
