#pragma once

struct ImFont;

namespace render::fonts {

    void load();

    [[nodiscard]] ImFont* regular();
    [[nodiscard]] ImFont* medium();
    [[nodiscard]] ImFont* bold();

}
