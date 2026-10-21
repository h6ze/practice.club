#include "logger.hh"
#include <cstdio>
#include <memory>
#include <mutex>
#include <vector>
#include <client/util/system/paths.hh>
#include <client/diag/log/sinks/archive.hh>
#include <client/diag/log/sinks/console_sink.hh>
#include <client/diag/log/detail/dedupe.hh>
#include <client/diag/log/sinks/file_sink.hh>
#include <client/diag/log/detail/timestamp.hh>

namespace {

    struct channel {
        std::mutex guard;
        std::vector<std::unique_ptr<logger::sink>> sinks;
        logger::file_sink* journal = nullptr;
        logger::dedupe filter;
        logger::level floor = logger::level::debug;
        bool is_open = false;
    };

    channel& state() {
        static channel value;
        return value;
    }

    [[nodiscard]] std::string span_of(unsigned long long milliseconds) {
        if (milliseconds < 1000) return std::to_string(milliseconds) + "ms";

        char buffer[32] = {};
        std::snprintf(buffer, sizeof(buffer), "%.1fs", static_cast<double>(milliseconds) / 1000.0);

        return buffer;
    }

    void deliver(channel& current, const logger::record& entry) {
        for (auto& target : current.sinks) target->write(entry);
    }

    void close_run(channel& current, const logger::repeat_run& run) {
        logger::record entry;
        entry.severity = run.severity;
        entry.stamp = logger::stamp_clock();
        entry.text = "repeated " + std::to_string(run.count) + (run.count == 1 ? " more time in " : " more times in ")
            + span_of(run.span_ms);

        deliver(current, entry);
    }

}

#pragma region lifetime

bool logger::startup(const options& settings) {
    channel& current = state();

    const std::lock_guard lock(current.guard);
    if (current.is_open) return true;

    current.floor = settings.floor;

    if (settings.is_console) {
        auto console = std::make_unique<console_sink>();
        if (console->open()) current.sinks.push_back(std::move(console));
    }

    if (settings.is_file) {
        prune(paths::logs(), L".log", settings.keep_files);

        auto journal = std::make_unique<file_sink>();
        if (journal->open(paths::logs())) {
            current.journal = journal.get();
            current.sinks.push_back(std::move(journal));
        }
    }

    current.is_open = !current.sinks.empty();

    return current.is_open;
}

void logger::shutdown() {
    channel& current = state();

    const std::lock_guard lock(current.guard);
    if (!current.is_open) return;

    repeat_run closed;
    if (current.filter.drain(closed)) close_run(current, closed);

    for (auto& target : current.sinks) target->flush();

    current.journal = nullptr;
    current.sinks.clear();
    current.is_open = false;
}

void logger::flush() {
    channel& current = state();

    const std::lock_guard lock(current.guard);
    if (!current.is_open) return;

    repeat_run closed;
    if (current.filter.drain(closed)) close_run(current, closed);

    for (auto& target : current.sinks) target->flush();
}

std::wstring logger::file() {
    channel& current = state();

    const std::lock_guard lock(current.guard);

    return current.journal ? current.journal->path() : std::wstring{};
}

#pragma endregion

#pragma region levels

void logger::write(level severity, const std::string& text) {
    channel& current = state();

    const std::lock_guard lock(current.guard);
    if (!current.is_open) return;
    if (severity < current.floor) return;

    repeat_run closed;
    const bool is_fresh = current.filter.observe(severity, text, closed);

    if (closed.is_present()) close_run(current, closed);
    if (!is_fresh) return;

    record entry;
    entry.severity = severity;
    entry.stamp = stamp_clock();
    entry.text = text;

    deliver(current, entry);
}

#pragma endregion
