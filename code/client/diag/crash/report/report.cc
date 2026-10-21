#include "report.hh"
#include <cstdio>
#include <client/util/brand.hh>
#include <client/diag/crash/capture/modules.hh>
#include <client/diag/crash/reason.hh>
#include <client/diag/crash/capture/registers.hh>
#include <client/diag/crash/capture/stack.hh>
#include "writer.hh"

namespace {

    crash::frame_list walked;

    [[nodiscard]] const crash::modules::span* ours() noexcept {
        HMODULE self = nullptr;
        GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            reinterpret_cast<LPCSTR>(&ours), &self);

        return self ? crash::modules::owner_of(reinterpret_cast<uintptr_t>(self)) : nullptr;
    }

    void write_location(crash::writer& out, uintptr_t address) {
        out.hex(address);

        const crash::modules::span* owner = crash::modules::owner_of(address);
        if (!owner) { out.text("  <unmapped>"); return; }

        out.text("  ");
        out.text(owner->name);
        out.character('+');
        out.hex(address - owner->base, 1);
    }

    void write_header(crash::writer& out, const crash::details& facts) {
        out.text(brand::name);
        out.text(" crash report");
        out.line();
        out.rule('=', 60);
        out.line();

        char name[MAX_PATH] = {};
        GetModuleFileNameA(nullptr, name, MAX_PATH);

        out.label("when");
        out.text(facts.stamp);
        out.line();

        out.label("version");
        out.text(brand::version);
        out.line();

        out.label("process");
        out.text(name);
        out.line();

        out.label("pid");
        out.decimal(GetCurrentProcessId());
        out.line();

        out.label("thread");
        out.decimal(GetCurrentThreadId());
        out.line();

        out.label("uptime");
        out.decimal(facts.uptime_ms / 1000);
        out.text("s");
        out.line();

        if (facts.dump) { out.label("minidump"); out.text(facts.dump); out.line(); }

        out.line();
    }

    void write_fault(crash::writer& out, const EXCEPTION_RECORD& record) {
        const crash::reason cause = crash::reason_of(record.ExceptionCode);

        out.text("fault");
        out.line();
        out.rule('-', 60);

        out.label("  code");
        out.hex(record.ExceptionCode, 8);
        out.text("  ");
        out.text(cause.name);
        out.line();

        out.label("  meaning");
        out.text(cause.detail);
        out.line();

        out.label("  at");
        write_location(out, reinterpret_cast<uintptr_t>(record.ExceptionAddress));
        out.line();

        if (record.ExceptionCode == EXCEPTION_ACCESS_VIOLATION && record.NumberParameters >= 2) {
            out.label("  operation");
            out.text(crash::access_kind(record.ExceptionInformation[0]));
            out.character(' ');
            out.hex(record.ExceptionInformation[1]);
            out.line();
        }

        const crash::modules::span* home = ours();
        const crash::modules::span* blamed = crash::modules::owner_of(reinterpret_cast<uintptr_t>(record.ExceptionAddress));

        out.label("  implicated");
        out.text(home && blamed && home->base == blamed->base ? "yes" : "no");
        out.line();
        out.line();
    }

    void write_stack(crash::writer& out, const CONTEXT& context) {
        crash::walk(context, walked);

        out.text("stack");
        out.line();
        out.rule('-', 60);

        if (walked.count == 0) { out.text("  the stack could not be unwound"); out.line(); out.line(); return; }

        for (size_t index = 0; index < walked.count; ++index) {
            char ordinal[8] = {};
            std::snprintf(ordinal, sizeof(ordinal), "  %2zu  ", index);

            out.text(ordinal);
            write_location(out, walked.frames[index]);
            out.line();
        }

        out.line();
    }

    void write_modules(crash::writer& out) {
        out.text("modules");
        out.line();
        out.rule('-', 60);

        for (size_t index = 0; index < crash::modules::count(); ++index) {
            const crash::modules::span& entry = crash::modules::at(index);

            out.text("  ");
            out.hex(entry.base);
            out.text("  ");
            out.hex(entry.size, 8);
            out.text("  ");
            out.text(entry.name);
            out.line();
        }

        out.line();
    }

}

void crash::write_report(const char* path, const details& facts) noexcept {
    if (!facts.pointers || !facts.pointers->ExceptionRecord) return;

    modules::collect();

    writer out(path);
    if (!out.is_open()) return;

    write_header(out, facts);
    write_fault(out, *facts.pointers->ExceptionRecord);

    if (facts.pointers->ContextRecord) {
        out.text("registers");
        out.line();
        out.rule('-', 60);
        write_registers(out, *facts.pointers->ContextRecord);
        out.line();

        write_stack(out, *facts.pointers->ContextRecord);
    }

    write_modules(out);

    out.flush();
}
