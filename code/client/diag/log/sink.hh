#pragma once
#include "record.hh"

namespace logger {

    struct sink {
        virtual ~sink() = default;

        virtual void write(const record& value) = 0;
        virtual void flush() {}
    };

}
