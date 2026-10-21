#pragma once
#include <sdk/core/math.hh>

namespace game::camera {

    struct view {
        sdk::FVector location;
        sdk::FRotator rotation;
        float fov = 90.0f;
        float width = 0.0f;
        float height = 0.0f;
        bool is_valid = false;
    };

    void refresh(float viewport_width, float viewport_height);

    [[nodiscard]] const view& current();

    [[nodiscard]] double yaw();

    [[nodiscard]] bool to_screen(const sdk::FVector& world, sdk::vec2& out);

    [[nodiscard]] sdk::box box_for(const sdk::FVector& feet, const sdk::FVector& head);

}
