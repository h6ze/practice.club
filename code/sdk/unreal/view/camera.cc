#include "camera.hh"
#include <sdk/core/access.hh>
#include <sdk/offsets.generated.hh>
#include <sdk/globals.hh>

namespace game::camera::detail {

    constexpr double degrees_to_radians = 3.14159265358979323846 / 180.0;

    constexpr float box_aspect = 0.45f;

    constexpr float min_fov = 1.0f;
    constexpr float max_fov = 170.0f;

    view& state() {
        static view value;
        return value;
    }

    struct basis {
        sdk::FVector forward;
        sdk::FVector right;
        sdk::FVector up;
    };

    [[nodiscard]] basis axes_of(const sdk::FRotator& rotation) noexcept {
        const double pitch = rotation.Pitch * degrees_to_radians;
        const double yaw = rotation.Yaw * degrees_to_radians;
        const double roll = rotation.Roll * degrees_to_radians;

        const double cp = std::cos(pitch), sp = std::sin(pitch);
        const double cy = std::cos(yaw), sy = std::sin(yaw);
        const double cr = std::cos(roll), sr = std::sin(roll);

        basis out;
        out.forward = { cp * cy, cp * sy, sp };
        out.right = { sr * sp * cy - cr * sy, sr * sp * sy + cr * cy, -sr * cp };
        out.up = { -(cr * sp * cy + sr * sy), cy * sr - cr * sp * sy, cr * cp };

        return out;
    }

}

void game::camera::refresh(float viewport_width, float viewport_height) {
    view& active = detail::state();
    active = view{};

    active.width = viewport_width;
    active.height = viewport_height;
    if (viewport_width <= 0.0f || viewport_height <= 0.0f) return;

    sdk::UWorld* world = sdk::globals::world();
    if (!world) return;

    sdk::APlayerController* controller = world->local_controller();
    if (!controller) return;

    const sdk::AActor* manager = controller->PlayerCameraManager();
    if (!manager) return;

    const std::uint32_t pov = sdk::offsets::acamera_manager::camera_cache + sdk::offsets::view::pov;

    active.location = sdk::mem::read<sdk::FVector>(manager, pov + sdk::offsets::view::location, sdk::FVector{});
    active.rotation = sdk::mem::read<sdk::FRotator>(manager, pov + sdk::offsets::view::rotation, sdk::FRotator{});
    active.fov = sdk::mem::read<float>(manager, pov + sdk::offsets::view::fov, 0.0f);

    if (active.fov < detail::min_fov || active.fov > detail::max_fov) return;
    if (active.location.is_zero()) return;

    active.is_valid = true;
}

const game::camera::view& game::camera::current() { return detail::state(); }

double game::camera::yaw() { return detail::state().rotation.Yaw; }

bool game::camera::to_screen(const sdk::FVector& world, sdk::vec2& out) {
    const view& active = detail::state();
    if (!active.is_valid) return false;

    const detail::basis axes = detail::axes_of(active.rotation);
    const sdk::FVector delta = world - active.location;

    const double depth = delta.dot(axes.forward);
    if (depth < 1.0) return false;

    const double across = delta.dot(axes.right);
    const double rise = delta.dot(axes.up);
    const double scale = (active.width * 0.5) / std::tan(active.fov * 0.5 * detail::degrees_to_radians);

    out.x = static_cast<float>(active.width * 0.5 + across * scale / depth);
    out.y = static_cast<float>(active.height * 0.5 - rise * scale / depth);

    return true;
}

sdk::box game::camera::box_for(const sdk::FVector& feet, const sdk::FVector& head) {
    sdk::box frame;

    sdk::vec2 low{};
    sdk::vec2 high{};
    if (!to_screen(feet, low) || !to_screen(head, high)) return frame;

    const float height = low.y - high.y;
    if (height <= 1.0f) return frame;

    const float width = height * detail::box_aspect;

    frame.top_left = { high.x - width * 0.5f, high.y };
    frame.width = width;
    frame.height = height;
    frame.is_valid = true;

    return frame;
}
