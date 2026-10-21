#include "object.hh"
#include <string>
#include <unordered_map>
#include <utility>
#include <sdk/offsets.generated.hh>
#include <sdk/core/access.hh>
#include <sdk/notes.hh>

namespace sdk::objects::detail {

    void* array_base = nullptr;
    UClass* class_type = nullptr;
    std::unordered_map<std::string, UClass*> class_index;
    std::unordered_map<std::string, UObject*> name_cache;

    std::int32_t indexed_total = 0;
    ULONGLONG next_reindex = 0;
    constexpr ULONGLONG reindex_every_ms = 2000;

    [[nodiscard]] inline std::int32_t stored_count() noexcept {
        return mem::read<std::int32_t>(array_base, offsets::object_array::num, 0);
    }

    [[nodiscard]] inline std::int32_t stored_chunks() noexcept {
        return mem::read<std::int32_t>(array_base, offsets::object_array::chunks, 0);
    }

    [[nodiscard]] UClass* resolve_class_type() {
        if (class_type) return class_type;

        const std::int32_t total = count();
        for (std::int32_t i = 0; i < total; ++i) {
            UObject* object = at(i);
            if (object && object->klass() == reinterpret_cast<UClass*>(object)) {
                class_type = static_cast<UClass*>(object);
                break;
            }
        }

        return class_type;
    }

    void build_class_index(UClass* type) {
        class_index.clear();

        const std::int32_t total = count();
        for (std::int32_t i = 0; i < total; ++i) {
            UObject* object = at(i);
            if (!object || !object->is_a(type)) continue;

            std::string label = object->name();
            if (!label.empty()) class_index.emplace(std::move(label), static_cast<UClass*>(object));
        }

        indexed_total = total;
        say(note::info, "[ sdk ] indexed " + std::to_string(class_index.size()) + " classes");
    }

}

sdk::FName sdk::UObject::fname() const noexcept {
    return mem::read<FName>(this, offsets::uobject::name, FName{});
}

std::string sdk::UObject::name() const { return fname().text(); }

std::string sdk::UObject::full_name() const {
    std::string out = name();
    if (out.empty()) return out;

    for (UObject* above = outer(); above != nullptr; above = above->outer()) {
        const std::string part = above->name();
        if (part.empty()) break;

        out = part + "." + out;
    }

    const UClass* type = klass();

    return type ? type->name() + " " + out : out;
}

std::int32_t sdk::UObject::index() const noexcept {
    return mem::read<std::int32_t>(this, offsets::uobject::index, -1);
}

sdk::UClass* sdk::UObject::klass() const noexcept {
    return mem::pointer<UClass>(this, offsets::uobject::klass);
}

sdk::UObject* sdk::UObject::outer() const noexcept {
    return mem::pointer<UObject>(this, offsets::uobject::outer);
}

bool sdk::UObject::is_a(const UClass* type) const noexcept {
    if (!type) return false;

    for (const UStruct* walk = klass(); walk != nullptr; walk = walk->super())
        if (static_cast<const void*>(walk) == static_cast<const void*>(type)) return true;

    return false;
}

bool sdk::UObject::is_named(const char* value) const {
    return value && name() == value;
}

sdk::UField* sdk::UField::next() const noexcept {
    return mem::pointer<UField>(this, offsets::ufield::next);
}

sdk::UStruct* sdk::UStruct::super() const noexcept {
    return mem::pointer<UStruct>(this, offsets::ustruct::super);
}

sdk::UField* sdk::UStruct::children() const noexcept {
    return mem::pointer<UField>(this, offsets::ustruct::children);
}

std::int32_t sdk::UStruct::size() const noexcept {
    return mem::read<std::int32_t>(this, offsets::ustruct::size, 0);
}

sdk::UFunction* sdk::UStruct::find_function(const char* name) const {
    if (!name) return nullptr;

    int guard = 0;
    for (const UStruct* type = this; type != nullptr && guard < 64; type = type->super(), ++guard) {
        int step = 0;
        for (UField* child = type->children(); child != nullptr && step < 4096; child = child->next(), ++step)
            if (child->is_named(name)) return static_cast<UFunction*>(child);
    }

    return nullptr;
}

sdk::UObject* sdk::UClass::default_object() const noexcept {
    return mem::pointer<UObject>(this, offsets::uclass::default_object);
}

bool sdk::objects::bind(void* array_address) {
    detail::array_base = array_address;
    detail::class_type = nullptr;
    detail::class_index.clear();

    const std::int32_t total = detail::stored_count();
    const std::int32_t chunks = detail::stored_chunks();

    if (total <= 0 || total > 50'000'000 || chunks <= 0 || chunks > 0x1000) {
        detail::array_base = nullptr;
        return false;
    }

    return at(0) != nullptr;
}

bool sdk::objects::is_ready() { return detail::array_base != nullptr; }

std::int32_t sdk::objects::count() { return detail::stored_count(); }

sdk::UObject* sdk::objects::at(std::int32_t index) {
    if (!detail::array_base || index < 0 || index >= detail::stored_count()) return nullptr;

    const std::int32_t per_chunk = static_cast<std::int32_t>(offsets::object_array::per_chunk);
    const std::int32_t chunk = index / per_chunk;
    const std::int32_t slot = index % per_chunk;
    if (chunk >= detail::stored_chunks()) return nullptr;

    auto* table = mem::pointer<std::uint8_t*>(detail::array_base, offsets::object_array::objects);
    if (!table) return nullptr;

    std::uint8_t* items = mem::read<std::uint8_t*>(table, static_cast<std::uint32_t>(chunk) * sizeof(void*), nullptr);
    if (!items) return nullptr;

    const std::uint32_t at_slot = static_cast<std::uint32_t>(slot) * offsets::object_array::item_stride;

    return mem::pointer<UObject>(items, at_slot + offsets::object_array::item_object);
}

sdk::UClass* sdk::objects::find_class(const char* name) {
    if (!name || !detail::array_base) return nullptr;

    UClass* class_type = detail::resolve_class_type();
    if (!class_type) return nullptr;

    if (detail::class_index.empty()) detail::build_class_index(class_type);

    auto found = detail::class_index.find(name);
    if (found != detail::class_index.end()) return found->second;

    const ULONGLONG now = GetTickCount64();
    if (count() == detail::indexed_total || now < detail::next_reindex) return nullptr;

    detail::next_reindex = now + detail::reindex_every_ms;
    detail::build_class_index(class_type);

    found = detail::class_index.find(name);

    return found != detail::class_index.end() ? found->second : nullptr;
}

std::vector<sdk::UClass*> sdk::objects::subclasses_of(const UClass* base) {
    std::vector<UClass*> found;

    UClass* class_type = detail::resolve_class_type();
    if (!base || !class_type) return found;

    const std::int32_t total = count();
    for (std::int32_t i = 0; i < total; ++i) {
        UObject* object = at(i);
        if (!object || !object->is_a(class_type)) continue;

        for (const UStruct* step = static_cast<UStruct*>(object); step; step = step->super()) {
            if (step != base) continue;

            found.push_back(static_cast<UClass*>(object));
            break;
        }
    }

    return found;
}

sdk::UObject* sdk::objects::find_instance(const UClass* type) {
    if (!type || !detail::array_base) return nullptr;

    const std::int32_t total = count();
    for (std::int32_t i = 0; i < total; ++i) {
        UObject* object = at(i);
        if (object && object->is_a(type)) return object;
    }

    return nullptr;
}

sdk::UObject* sdk::objects::find_live_instance(const UClass* type) {
    if (!type || !detail::array_base) return nullptr;

    constexpr std::int32_t template_flags = 0x10 | 0x20;

    const std::int32_t total = count();
    for (std::int32_t i = 0; i < total; ++i) {
        UObject* object = at(i);
        if (!object || !object->is_a(type)) continue;
        if (mem::read<std::int32_t>(object, offsets::uobject::flags) & template_flags) continue;

        return object;
    }

    return nullptr;
}

sdk::UObject* sdk::objects::find_by_name(const char* name) {
    if (!name || !detail::array_base) return nullptr;

    const auto cached = detail::name_cache.find(name);
    if (cached != detail::name_cache.end()) return cached->second;

    const std::int32_t total = count();
    for (std::int32_t i = 0; i < total; ++i) {
        UObject* object = at(i);
        if (!object || !object->is_named(name)) continue;

        detail::name_cache.emplace(name, object);

        return object;
    }

    detail::name_cache.emplace(name, nullptr);

    return nullptr;
}
