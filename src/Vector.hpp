#pragma once

#include <array>
#include <ostream>
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
        auto operator+=(const Vec3& rhs) -> Vec3&;
        auto operator+(const Vec3& rhs) const -> Vec3;
        auto operator+=(const Point& rhs) const -> Point;
        auto operator+(const Point& rhs) const -> Point;
        auto operator-=(const Vec3& rhs) -> Vec3&;
        auto operator-(const Vec3& rhs) const -> Vec3;
        auto operator-() -> Vec3;
        auto operator*=(float scalar) -> Vec3&;
        auto operator*(float scalar) -> Vec3;
        auto operator/=(float scalar) -> Vec3&;
        auto operator/(float scalar) -> Vec3;
        friend auto operator<<(std::ostream& str, const Vec3& vec) -> std::ostream&;

        auto magnitude() const -> float;
        auto normalize() -> Vec3&;
        auto dot(const Vec3& rhs) const -> float;
        auto cross(const Vec3& rhs) -> Vec3&;
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

inline auto operator<<(std::ostream& str, const Vec3& vec) -> std::ostream&
{
    str << "[";
    str << vec.x() << ",";
    str << vec.y() << ",";
    str << vec.z() << "]";
    return str;
}
