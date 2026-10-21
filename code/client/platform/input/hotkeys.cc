#include "hotkeys.hh"

namespace {

    bool is_open = true;

}

bool input::hotkeys::is_overlay_open() { return is_open; }

void input::hotkeys::toggle_overlay() { is_open = !is_open; }

void input::hotkeys::set_overlay_open(bool value) { is_open = value; }
