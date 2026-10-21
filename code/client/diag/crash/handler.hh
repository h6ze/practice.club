#pragma once

namespace crash {

    struct options {
        bool is_exclusive = true;
        bool is_minidump = true;
    };

    [[nodiscard]] bool install(const options& settings);
    void remove();

}
