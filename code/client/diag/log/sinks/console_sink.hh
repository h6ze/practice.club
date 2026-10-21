#pragma once
#include <Windows.h>
#include <client/diag/log/sink.hh>

namespace logger {

    class console_sink final : public sink {
        HANDLE output = nullptr;
        WORD restored = 0;
        bool is_allocated = false;

    public:
        ~console_sink() override;

        [[nodiscard]] bool open();
        void write(const record& value) override;
    };

}
