#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <sdk/core/text/name.hh>

namespace sdk {

    struct UField;
    struct UStruct;
    struct UClass;
    struct UFunction;

    struct UObject {
        [[nodiscard]] FName fname() const noexcept;
        [[nodiscard]] std::string name() const;
        [[nodiscard]] std::string full_name() const;
        [[nodiscard]] std::int32_t index() const noexcept;
        [[nodiscard]] UClass* klass() const noexcept;
        [[nodiscard]] UObject* outer() const noexcept;
        [[nodiscard]] bool is_a(const UClass* type) const noexcept;
        [[nodiscard]] bool is_named(const char* value) const;
    };

    struct UField : UObject {
        [[nodiscard]] UField* next() const noexcept;
    };

    struct UStruct : UField {
        [[nodiscard]] UStruct* super() const noexcept;
        [[nodiscard]] UField* children() const noexcept;

        [[nodiscard]] std::int32_t size() const noexcept;

        [[nodiscard]] UFunction* find_function(const char* name) const;
    };

    struct UFunction : UStruct {};

    struct UClass : UStruct {
        [[nodiscard]] UObject* default_object() const noexcept;
    };

    namespace objects {

        [[nodiscard]] bool bind(void* array_address);
        [[nodiscard]] bool is_ready();

        [[nodiscard]] std::int32_t count();
        [[nodiscard]] UObject* at(std::int32_t index);

        [[nodiscard]] UClass* find_class(const char* name);

        [[nodiscard]] UObject* find_by_name(const char* name);
        [[nodiscard]] UObject* find_instance(const UClass* type);

        [[nodiscard]] UObject* find_live_instance(const UClass* type);

        [[nodiscard]] std::vector<UClass*> subclasses_of(const UClass* base);

    }

}
