#include "file_sink.hh"
#include <filesystem>
#include <client/util/brand.hh>
#include <client/util/string/text.hh>
#include <client/diag/log/detail/timestamp.hh>

namespace {

    constexpr char byte_order_mark[] = "\xEF\xBB\xBF";

    void emit(HANDLE file, const char* data, size_t size) {
        DWORD written = 0;
        WriteFile(file, data, static_cast<DWORD>(size), &written, nullptr);
    }

}

bool logger::file_sink::open(const std::wstring& directory) {
    const std::wstring name = std::wstring(brand::wide_name) + L"-" + text::widen(stamp_compact()) + L".log";
    location = (std::filesystem::path(directory) / name).wstring();

    file = win::adopt(CreateFileW(location.c_str(), FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_DELETE,
        nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr));

    if (!file) return false;

    emit(file.get(), byte_order_mark, sizeof(byte_order_mark) - 1);

    return true;
}

void logger::file_sink::write(const record& value) {
    if (!file) return;

    const level_label& label = label_of(value.severity);

    std::string line;
    line.reserve(value.stamp.size() + value.text.size() + 8);
    line += value.stamp;
    line += " [";
    line += label.marker;
    line += "] ";
    line += value.text;
    line += "\r\n";

    emit(file.get(), line.data(), line.size());
}

void logger::file_sink::flush() {
    if (file) FlushFileBuffers(file.get());
}
