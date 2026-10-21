#pragma once
#include <string>
#include "level.hh"

namespace logger {

    struct record {
        level severity = level::info;
        std::string stamp;
        std::string text;
    };

}
