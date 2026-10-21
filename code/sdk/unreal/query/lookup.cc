#include "lookup.hh"
#include <string>
#include <unordered_map>
#include <sdk/core/access.hh>
#include <sdk/offsets.generated.hh>

namespace sdk::lookup::detail {

    struct verdict {
        std::int32_t index = -1;
        bool is_derived = false;
    };

    inline std::unordered_map<std::string, std::unordered_map<const UClass*, verdict>> verdicts;

    constexpr std::int32_t template_flags = 0x10 | 0x20;

    [[nodiscard]] inline bool is_template(const UObject* object) {
        return (mem::read<std::int32_t>(object, offsets::uobject::flags) & template_flags) != 0;
    }

}

bool sdk::lookup::is_live(const held& slot) {
    return slot.object && slot.index >= 0 && objects::at(slot.index) == slot.object;
}

sdk::UObject* sdk::lookup::class_default(held& slot, const char* class_name) {
    if (is_live(slot)) return slot.object;

    UClass* type = objects::find_class(class_name);
    slot.object = type ? type->default_object() : nullptr;
    slot.index = slot.object ? slot.object->index() : -1;

    return slot.object;
}

bool sdk::lookup::derives_from(const UObject* object, const char* class_name) {
    if (!object || !class_name) return false;

    const UClass* type = object->klass();
    if (!type) return false;

    std::unordered_map<const UClass*, detail::verdict>& known = detail::verdicts[class_name];

    const auto found = known.find(type);
    if (found != known.end() && objects::at(found->second.index) == type) return found->second.is_derived;

    detail::verdict answer;
    answer.index = type->index();

    for (const UStruct* step = type; step; step = step->super()) {
        if (!step->is_named(class_name)) continue;

        answer.is_derived = true;
        break;
    }

    known[type] = answer;

    return answer.is_derived;
}

sdk::UObject* sdk::lookup::find_owned(const char* class_name, std::initializer_list<const UObject*> outers) {
    const UClass* type = objects::find_class(class_name);
    if (!type) return nullptr;

    const std::int32_t total = objects::count();
    for (std::int32_t i = 0; i < total; ++i) {
        UObject* object = objects::at(i);
        if (!object) continue;

        const UObject* outer = object->outer();
        bool is_owned = false;
        for (const UObject* candidate : outers) is_owned |= candidate && outer == candidate;

        if (is_owned && object->is_a(type)) return object;
    }

    return nullptr;
}

std::vector<sdk::UObject*> sdk::lookup::live_instances(const char* class_name) {
    std::vector<UObject*> found;

    const UClass* type = objects::find_class(class_name);
    if (!type) return found;

    const std::int32_t total = objects::count();
    for (std::int32_t i = 0; i < total; ++i) {
        UObject* object = objects::at(i);
        if (object && object->is_a(type) && !detail::is_template(object)) found.push_back(object);
    }

    return found;
}
