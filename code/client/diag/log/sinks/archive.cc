#include "archive.hh"
#include <algorithm>
#include <filesystem>
#include <vector>

namespace {

    struct aged_file {
        std::filesystem::path path;
        std::filesystem::file_time_type written;
    };

}

void logger::prune(const std::wstring& directory, const std::wstring& extension, size_t keep) {
    std::error_code error;

    std::vector<aged_file> found;
    for (const auto& entry : std::filesystem::directory_iterator(directory, error)) {
        if (error) return;
        if (!entry.is_regular_file(error)) continue;
        if (entry.path().extension().wstring() != extension) continue;

        const auto written = entry.last_write_time(error);
        if (error) { error.clear(); continue; }

        found.push_back({ entry.path(), written });
    }

    if (found.size() <= keep) return;

    std::sort(found.begin(), found.end(), [](const aged_file& left, const aged_file& right) {
        return left.written > right.written;
    });

    for (size_t index = keep; index < found.size(); ++index)
        std::filesystem::remove(found[index].path, error);
}
