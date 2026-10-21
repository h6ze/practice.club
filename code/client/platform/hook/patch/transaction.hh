#pragma once
#include <mutex>
#include <vector>
#include <client/util/handle.hh>

namespace hook {

    class transaction {
        std::unique_lock<std::mutex> gate;
        std::vector<win::unique_handle> enlisted;
        bool is_open = false;

    public:
        transaction();
        ~transaction();

        transaction(const transaction&) = delete;
        transaction& operator=(const transaction&) = delete;

        [[nodiscard]] bool commit();
        void abort();

        [[nodiscard]] bool is_active() const noexcept { return is_open; }
    };

}
