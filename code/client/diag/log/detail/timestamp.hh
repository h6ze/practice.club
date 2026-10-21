#pragma once
#include <string>

namespace logger {

    [[nodiscard]] std::string stamp_clock();
    [[nodiscard]] std::string stamp_full();
    [[nodiscard]] std::string stamp_compact();

}
