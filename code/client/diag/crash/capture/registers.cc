#include "registers.hh"
#include <iterator>

namespace {

#if defined(_M_X64)

    struct register_slot { const char* name; DWORD64 CONTEXT::* field; };

    constexpr register_slot slots[] = {
        { "rax", &CONTEXT::Rax }, { "rbx", &CONTEXT::Rbx }, { "rcx", &CONTEXT::Rcx }, { "rdx", &CONTEXT::Rdx },
        { "rsi", &CONTEXT::Rsi }, { "rdi", &CONTEXT::Rdi }, { "rbp", &CONTEXT::Rbp }, { "rsp", &CONTEXT::Rsp },
        { "r8 ", &CONTEXT::R8 }, { "r9 ", &CONTEXT::R9 }, { "r10", &CONTEXT::R10 }, { "r11", &CONTEXT::R11 },
        { "r12", &CONTEXT::R12 }, { "r13", &CONTEXT::R13 }, { "r14", &CONTEXT::R14 }, { "r15", &CONTEXT::R15 },
        { "rip", &CONTEXT::Rip },
    };

    constexpr size_t per_line = 4;

#endif

}

void crash::write_registers(writer& out, const CONTEXT& context) {
#if defined(_M_X64)
    for (size_t index = 0; index < std::size(slots); ++index) {
        if (index % per_line == 0) out.text("  ");

        out.text(slots[index].name);
        out.character(' ');
        out.hex(context.*slots[index].field);

        const bool is_last = index + 1 == std::size(slots);
        if (is_last || (index + 1) % per_line == 0) out.line();
        else out.text("   ");
    }

    out.text("  eflags ");
    out.hex(context.EFlags, 8);
    out.line();
#else
    out.text("  register dump is x64 only");
    out.line();
#endif
}
