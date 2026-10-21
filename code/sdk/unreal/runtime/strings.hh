#pragma once
#include <sdk/core/container.hh>
#include <sdk/core/reflect/object.hh>

namespace sdk::strings {

    [[nodiscard]] FString make(const char* text);

    [[nodiscard]] bool is_ready();

}
