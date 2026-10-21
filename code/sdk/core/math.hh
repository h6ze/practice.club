#pragma once
#include <cmath>

namespace sdk {

    struct FVector {
        double X = 0.0;
        double Y = 0.0;
        double Z = 0.0;

        [[nodiscard]] FVector operator+(const FVector& other) const noexcept { return { X + other.X, Y + other.Y, Z + other.Z }; }
        [[nodiscard]] FVector operator-(const FVector& other) const noexcept { return { X - other.X, Y - other.Y, Z - other.Z }; }

        [[nodiscard]] double dot(const FVector& other) const noexcept { return X * other.X + Y * other.Y + Z * other.Z; }
        [[nodiscard]] double length() const noexcept { return std::sqrt(dot(*this)); }
        [[nodiscard]] bool is_zero() const noexcept { return X == 0.0 && Y == 0.0 && Z == 0.0; }
    };

    struct FRotator {
        double Pitch = 0.0;
        double Yaw = 0.0;
        double Roll = 0.0;
    };

    struct FLinearColor {
        float R = 1.0f;
        float G = 1.0f;
        float B = 1.0f;
        float A = 1.0f;

        [[nodiscard]] bool operator==(const FLinearColor& other) const noexcept { return R == other.R && G == other.G && B == other.B && A == other.A; }
        [[nodiscard]] bool operator!=(const FLinearColor& other) const noexcept { return !(*this == other); }
    };

    struct vec2 {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct box {
        vec2 top_left;
        float width = 0.0f;
        float height = 0.0f;
        bool is_valid = false;

        [[nodiscard]] float left() const noexcept { return top_left.x; }
        [[nodiscard]] float right() const noexcept { return top_left.x + width; }
        [[nodiscard]] float top() const noexcept { return top_left.y; }
        [[nodiscard]] float bottom() const noexcept { return top_left.y + height; }
        [[nodiscard]] float center_x() const noexcept { return top_left.x + width * 0.5f; }
    };

}
