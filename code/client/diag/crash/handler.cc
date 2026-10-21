#include "handler.hh"
#include <Windows.h>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <client/platform/hook/detour.hh>
#include <client/diag/log/logger.hh>
#include <client/util/system/paths.hh>
#include <client/util/string/text.hh>
#include <client/diag/crash/report/minidump.hh>
#include <client/diag/crash/report/report.hh>

namespace {

    constexpr DWORD code_terminate = 0xE0000001;
    constexpr DWORD code_purecall = 0xE0000002;
    constexpr DWORD code_parameter = 0xE0000003;
    constexpr DWORD code_abort = 0xE0000004;

    using set_filter = LPTOP_LEVEL_EXCEPTION_FILTER(WINAPI*)(LPTOP_LEVEL_EXCEPTION_FILTER);

    struct guard_state {
        crash::options settings;
        hook::detour<set_filter> lock;
        LPTOP_LEVEL_EXCEPTION_FILTER previous = nullptr;
        _purecall_handler previous_purecall = nullptr;
        _invalid_parameter_handler previous_parameter = nullptr;
        std::terminate_handler previous_terminate = nullptr;
        unsigned long long started_tick = 0;
        LONG is_reporting = 0;
        bool is_installed = false;
    };

    guard_state& state() {
        static guard_state value;
        return value;
    }

    void stamp_file(char* buffer, size_t size) {
        SYSTEMTIME now{};
        GetLocalTime(&now);
        std::snprintf(buffer, size, "%04u%02u%02u-%02u%02u%02u",
            now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);
    }

    void stamp_readable(char* buffer, size_t size) {
        SYSTEMTIME now{};
        GetLocalTime(&now);
        std::snprintf(buffer, size, "%04u-%02u-%02u %02u:%02u:%02u",
            now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);
    }

    void report(EXCEPTION_POINTERS* pointers) {
        guard_state& current = state();
        if (InterlockedExchange(&current.is_reporting, 1) != 0) return;

        char stamp[32] = {};
        char readable[32] = {};
        stamp_file(stamp, sizeof(stamp));
        stamp_readable(readable, sizeof(readable));

        char dump_path[MAX_PATH] = {};
        char report_path[MAX_PATH] = {};
        std::snprintf(dump_path, sizeof(dump_path), "%s\\%s.dmp", paths::crashes_narrow(), stamp);
        std::snprintf(report_path, sizeof(report_path), "%s\\%s.txt", paths::crashes_narrow(), stamp);

        const bool is_dumped = current.settings.is_minidump && crash::write_minidump(dump_path, pointers);

        crash::details facts;
        facts.pointers = pointers;
        facts.stamp = readable;
        facts.dump = is_dumped ? dump_path : nullptr;
        facts.uptime_ms = GetTickCount64() - current.started_tick;

        crash::write_report(report_path, facts);

        logger::error(std::string("[ crash ] the process faulted -> report written to ") + report_path);
        logger::flush();
    }

    void report_synthetic(DWORD code) {
        CONTEXT context{};
        RtlCaptureContext(&context);

        EXCEPTION_RECORD record{};
        record.ExceptionCode = code;
#if defined(_M_X64)
        record.ExceptionAddress = reinterpret_cast<PVOID>(context.Rip);
#else
        record.ExceptionAddress = reinterpret_cast<PVOID>(context.Eip);
#endif

        EXCEPTION_POINTERS pointers{ &record, &context };
        report(&pointers);
    }

    LONG CALLBACK on_unhandled(EXCEPTION_POINTERS* pointers) {
        report(pointers);
        return EXCEPTION_EXECUTE_HANDLER;
    }

    LPTOP_LEVEL_EXCEPTION_FILTER WINAPI on_set_filter(LPTOP_LEVEL_EXCEPTION_FILTER) {
        return nullptr;
    }

    void on_terminate() {
        report_synthetic(code_terminate);
        std::_Exit(EXIT_FAILURE);
    }

    void on_purecall() {
        report_synthetic(code_purecall);
        std::_Exit(EXIT_FAILURE);
    }

    void on_parameter(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t) {
        report_synthetic(code_parameter);
        std::_Exit(EXIT_FAILURE);
    }

    void on_abort(int) {
        report_synthetic(code_abort);
        std::_Exit(EXIT_FAILURE);
    }

}

bool crash::install(const options& settings) {
    guard_state& current = state();
    if (current.is_installed) return true;

    current.settings = settings;
    current.started_tick = GetTickCount64();

    current.previous = SetUnhandledExceptionFilter(on_unhandled);
    current.previous_purecall = _set_purecall_handler(on_purecall);
    current.previous_parameter = _set_invalid_parameter_handler(on_parameter);
    current.previous_terminate = std::set_terminate(on_terminate);
    std::signal(SIGABRT, on_abort);

    if (settings.is_exclusive) {
        const auto entry = GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "SetUnhandledExceptionFilter");
        if (!entry) logger::warning("[ crash ] could not resolve SetUnhandledExceptionFilter -> the game may replace our filter");
        else if (!current.lock.attach(reinterpret_cast<void*>(entry), on_set_filter, "SetUnhandledExceptionFilter"))
            logger::warning("[ crash ] could not lock the exception filter -> the game may replace ours");
    }

    current.is_installed = true;
    logger::debug("[ crash ] handler armed, reports land in " + text::narrow(paths::crashes()));

    return true;
}

void crash::remove() {
    guard_state& current = state();
    if (!current.is_installed) return;

    current.lock.detach();

    SetUnhandledExceptionFilter(current.previous);
    _set_purecall_handler(current.previous_purecall);
    _set_invalid_parameter_handler(current.previous_parameter);
    std::set_terminate(current.previous_terminate);
    std::signal(SIGABRT, SIG_DFL);

    current.previous = nullptr;
    current.is_installed = false;
}
