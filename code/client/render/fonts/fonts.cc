#include "fonts.hh"
#include <cstddef>
#include <imgui/imgui.h>
#include <client/diag/log/logger.hh>
#include "font_data.hh"

namespace render::fonts::detail {

    constexpr float size = 18.0f;

    ImFont* regular_face = nullptr;
    ImFont* medium_face = nullptr;
    ImFont* bold_face = nullptr;

    ImFont* add(const unsigned char* data, std::size_t length) {
        ImFontConfig config;
        config.FontDataOwnedByAtlas = false;

        return ImGui::GetIO().Fonts->AddFontFromMemoryTTF(const_cast<unsigned char*>(data), static_cast<int>(length), size, &config);
    }

}

void render::fonts::load() {
    detail::regular_face = detail::add(font_data::regular, font_data::regular_size);
    detail::medium_face = detail::add(font_data::medium, font_data::medium_size);
    detail::bold_face = detail::add(font_data::bold, font_data::bold_size);

    if (!detail::regular_face || !detail::medium_face || !detail::bold_face) logger::warning("[ imgui ] an sf pro face did not load");
}

ImFont* render::fonts::regular() { return detail::regular_face; }

ImFont* render::fonts::medium() { return detail::medium_face; }

ImFont* render::fonts::bold() { return detail::bold_face; }
