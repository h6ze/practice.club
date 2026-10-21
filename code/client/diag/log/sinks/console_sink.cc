#include "console_sink.hh"
#include <cstdio>
#include <client/util/brand.hh>

namespace {

    constexpr WORD dim = FOREGROUND_INTENSITY;
    constexpr WORD plain = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    constexpr WORD marker_colours[] = {
        FOREGROUND_INTENSITY,
        FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        FOREGROUND_RED | FOREGROUND_INTENSITY,
    };

    void paint(HANDLE output, WORD attribute) {
        if (output) SetConsoleTextAttribute(output, attribute);
    }

}

logger::console_sink::~console_sink() {
    paint(output, restored);
    if (is_allocated) FreeConsole();
}

bool logger::console_sink::open() {
    if (!GetConsoleWindow()) {
        if (!AllocConsole()) return false;
        is_allocated = true;
    }

    FILE* stream = nullptr;
    freopen_s(&stream, "CONOUT$", "w", stdout);
    freopen_s(&stream, "CONOUT$", "w", stderr);

    output = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen{};
    restored = GetConsoleScreenBufferInfo(output, &screen) ? screen.wAttributes : plain;

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitleA(brand::name);

    return true;
}

void logger::console_sink::write(const record& value) {
    const level_label& label = label_of(value.severity);

    paint(output, dim);
    std::fputs(value.stamp.c_str(), stdout);

    paint(output, marker_colours[static_cast<size_t>(value.severity)]);
    std::printf(" [%c] ", label.marker);

    paint(output, value.severity == level::error ? marker_colours[static_cast<size_t>(level::error)] : plain);
    std::fputs(value.text.c_str(), stdout);

    paint(output, plain);
    std::fputc('\n', stdout);
    std::fflush(stdout);
}
