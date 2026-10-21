#pragma once
#include <string>
#include <client/util/handle.hh>
#include <client/diag/log/sink.hh>

namespace logger {

    class file_sink final : public sink {
        win::unique_handle file;
        std::wstring location;

    public:
        [[nodiscard]] bool open(const std::wstring& directory);
        void write(const record& value) override;
        void flush() override;

        [[nodiscard]] const std::wstring& path() const noexcept { return location; }
    };

}
