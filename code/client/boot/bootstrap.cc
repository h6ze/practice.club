#include "bootstrap.hh"
#include <cstdio>
#include <string>
#include <client/diag/log/logger.hh>
#include "stage.hh"

namespace {

    struct progress {
        HMODULE owner = nullptr;
        size_t entered = 0;
        bool is_loaded = false;
    };

    progress& state() {
        static progress value;
        return value;
    }

    void announce(const char* text) {
        char buffer[256] = {};
        std::snprintf(buffer, sizeof(buffer), "[ boot ] %s\n", text);
        OutputDebugStringA(buffer);
    }

}

bool boot::run(HMODULE owner) {
    progress& current = state();
    if (current.is_loaded) return true;

    current.owner = owner;

    const stage* steps = plan();
    const size_t total = plan_size();

    for (size_t index = 0; index < total; ++index) {
        const stage& step = steps[index];
        const unsigned long long started = GetTickCount64();

        if (!step.enter()) {
            announce((std::string("stage ") + step.name + " failed, rolling back").c_str());
            logger::error(std::string("[ boot ] stage ") + step.name + " failed, rolling back");
            unwind();
            return false;
        }

        current.entered = index + 1;
        logger::debug(std::string("[ boot ] ") + step.name + " ready in " + std::to_string(GetTickCount64() - started) + "ms");
    }

    current.is_loaded = true;
    logger::success("[ boot ] every stage is up");

    return true;
}

void boot::unwind() {
    progress& current = state();

    const stage* steps = plan();

    while (current.entered > 0) {
        const stage& step = steps[--current.entered];

        logger::debug(std::string("[ boot ] ") + step.name + " down");
        if (step.leave) step.leave();
    }

    current.is_loaded = false;
}

HMODULE boot::owner() { return state().owner; }
bool boot::is_loaded() { return state().is_loaded; }
