#pragma once

namespace features {

    struct enforcement_options {
        bool is_enabled = false;
        int level = 55;
    };

    inline enforcement_options enforcement_setup;

    struct enforcement_domain {
        void tick();
    };

    inline enforcement_domain enforcement;

}
