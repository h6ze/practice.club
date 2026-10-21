#pragma once
#include <cstddef>

namespace boot {

    struct stage {
        const char* name;
        bool (*enter)();
        void (*leave)();
    };

    [[nodiscard]] const stage* plan();
    [[nodiscard]] size_t plan_size();

}
