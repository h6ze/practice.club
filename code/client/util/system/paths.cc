#include "paths.hh"
#include <filesystem>
#include <client/util/brand.hh>
#include <client/util/string/text.hh>

namespace {

    struct location {
        HMODULE owner = nullptr;
        std::wstring module_file;
        std::wstring module_name;
        std::wstring process_name;
        std::wstring root;
        std::wstring logs;
        std::wstring crashes;
        std::string crashes_narrow;
    };

    location& state() {
        static location value;
        return value;
    }

    [[nodiscard]] std::wstring image_of(HMODULE owner) {
        wchar_t buffer[MAX_PATH] = {};
        const DWORD length = GetModuleFileNameW(owner, buffer, MAX_PATH);
        return std::wstring(buffer, length);
    }

    [[nodiscard]] std::wstring local_appdata() {
        wchar_t buffer[MAX_PATH] = {};
        const DWORD length = GetEnvironmentVariableW(L"LOCALAPPDATA", buffer, MAX_PATH);
        if (length > 0 && length < MAX_PATH) return std::wstring(buffer, length);

        return std::filesystem::temp_directory_path().wstring();
    }

    [[nodiscard]] bool make_directory(const std::wstring& value) {
        std::error_code error;
        std::filesystem::create_directories(value, error);
        return !error;
    }

}

#pragma region binding

void paths::bind(HMODULE value) {
    location& current = state();

    current.owner = value;
    current.module_file = image_of(value);
    current.module_name = std::filesystem::path(current.module_file).filename().wstring();
    current.process_name = std::filesystem::path(image_of(nullptr)).filename().wstring();

    const std::filesystem::path root = std::filesystem::path(local_appdata()) / brand::wide_name;

    current.root = root.wstring();
    current.logs = (root / L"logs").wstring();
    current.crashes = (root / L"crashes").wstring();
    current.crashes_narrow = text::narrow(current.crashes);
}

bool paths::ensure() {
    const location& current = state();
    if (current.root.empty()) return false;

    return make_directory(current.logs) && make_directory(current.crashes);
}

#pragma endregion

#pragma region locations

HMODULE paths::owner() { return state().owner; }
const std::wstring& paths::module_file() { return state().module_file; }
const std::wstring& paths::module_name() { return state().module_name; }
const std::wstring& paths::process_name() { return state().process_name; }
const std::wstring& paths::root() { return state().root; }
const std::wstring& paths::logs() { return state().logs; }
const std::wstring& paths::crashes() { return state().crashes; }
const char* paths::crashes_narrow() { return state().crashes_narrow.c_str(); }

#pragma endregion
