#pragma once

#include <array>
#include <limits>
#include <ostream>

class Vec3;

class Point
{
    public:
        Point() = default;
        explicit Point(float x, float y, float z);
        ~Point() = default;

        Point(const Point& rhs) = default;
        auto operator=(const Point& rhs) -> Point& = default;
        Point(Point&& rhs) = default;
        auto operator=(Point&& rhs) -> Point& = default;

        auto operator==(const Point& rhs) const -> bool;
        auto operator+=(const Vec3& rhs) const -> Vec3;
        auto operator+(const Vec3& rhs) const -> Vec3;
        auto operator-(const Point& rhs) -> Vec3; 
        auto operator-=(const Vec3& rhs) -> Point&;
        auto operator-(const Vec3& rhs) -> Point;
        auto x() const -> const float&;
        auto y() const -> const float&;
        auto z() const -> const float&;

        friend auto operator<<(std::ostream& ost, const Point& p) -> std::ostream&;
    private:
        auto relativelyEqual(float a,
                             float b,
                             float maxRelativeDiff =
                                 std::numeric_limits<float>::epsilon()) const -> bool;
        std::array<float, 4> _coordinates;
};

inline auto operator<<(std::ostream& ost, const Point& p) -> std::ostream&
{
    ost << "(";
    ost << p.x() << ",";
    ost << p.y() << ",";
    ost << p.z() << ")";
    return ost;
}
