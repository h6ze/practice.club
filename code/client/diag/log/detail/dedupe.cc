#include "dedupe.hh"
#include <Windows.h>

bool logger::dedupe::observe(level severity, const std::string& text, repeat_run& closed) {
    closed = {};

    if (seen > 0 && severity == held_severity && text == held_text) {
        ++seen;
        latest_tick = GetTickCount64();
        return false;
    }

    if (seen > 1) closed = { held_severity, seen - 1, latest_tick - opened_tick };

    held_severity = severity;
    held_text = text;
    seen = 1;
    opened_tick = GetTickCount64();
    latest_tick = opened_tick;

    return true;
}

bool logger::dedupe::drain(repeat_run& closed) {
    closed = {};

    if (seen > 1) closed = { held_severity, seen - 1, latest_tick - opened_tick };

    seen = 0;
    held_text.clear();

    return closed.is_present();
}
