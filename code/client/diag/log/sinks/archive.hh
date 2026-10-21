#pragma once
#include <string>

namespace logger {

    void prune(const std::wstring& directory, const std::wstring& extension, size_t keep);

}
