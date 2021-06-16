#pragma once

#include <array>
#include <limits>

class Point;

class Vec3
{
    public:
        Vec3() = default;
        explicit Vec3(float x, float y, float z);
        ~Vec3() = default;
    
        Vec3(const Vec3& vector) = default;
        auto operator=(const Vec3& rhs) -> Vec3& = default;
        Vec3(Vec3&& vector) = default;
        auto operator=(Vec3&& rhs) -> Vec3& = default;
    
        auto operator==(const Vec3& rhs) const -> bool;
        auto operator+(const Point& rhs) -> Vec3&;
        auto x() const -> const float&;
        auto y() const -> const float&;
        auto z() const -> const float&;

    private:
        auto relativelyEqual(float a,
                             float b,
                             float maxRelativeDiff =
                                 std::numeric_limits<float>::epsilon()) const -> bool;
        std::array<float, 4> _coordinates;
};
