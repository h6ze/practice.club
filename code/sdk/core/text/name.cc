#include "name.hh"
#include <Windows.h>
#include <cwchar>
#include <sdk/core/container.hh>
#include "encoding.hh"

namespace sdk::detail {

    constexpr std::int32_t name_buffer_chars = 1024;

    using append_call = void(*)(const FName*, FString&);

    append_call append_string = nullptr;

    [[nodiscard]] inline bool append(const FName& name, FString& view) noexcept {
        __try { append_string(&name, view); return true; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
    }

}

void sdk::bind_append_string(void* address) {
    detail::append_string = reinterpret_cast<detail::append_call>(address);
}

std::string sdk::FName::text() const {
    if (!detail::append_string || is_none()) return std::string{};

    wchar_t buffer[detail::name_buffer_chars] = {};
    FString view(buffer, 0, detail::name_buffer_chars);

    if (!detail::append(*this, view)) return std::string{};
    if (view.NumElements <= 0 || view.NumElements > detail::name_buffer_chars) return std::string{};

    const std::int32_t used = static_cast<std::int32_t>(wcsnlen(buffer, static_cast<size_t>(view.NumElements)));

    std::string out = narrow(buffer, used);
    if (Number > 0) out += "_" + std::to_string(Number - 1);

    return out;
}
