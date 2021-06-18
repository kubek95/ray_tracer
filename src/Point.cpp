#include "Point.hpp"
#include "Vector.hpp"
#include "Utilities.hpp"

#include <cmath>
#include <algorithm>

Point::Point(float x, float y, float z) :
    _coordinates{x, y, z, 1}
{
}

auto Point::operator==(const Point& rhs) const -> bool
{
    return relativelyEqual(x(), rhs.x()) &&
           relativelyEqual(y(), rhs.y()) &&
           relativelyEqual(z(), rhs.z());
}

auto Point::operator+=(const Vec3& rhs) const -> Vec3
{
    return Vec3{x()+rhs.x(), y()+rhs.y(), z()+rhs.z()};
}

auto Point::operator+(const Vec3& rhs) const -> Vec3
{
    return Point{*this} += rhs;
}

auto Point::operator-(const Point& rhs) -> Vec3
{
    const auto x = _coordinates[0] - rhs.x();
    const auto y = _coordinates[1] - rhs.y();
    const auto z = _coordinates[2] - rhs.z();
    return Vec3{x, y, z};
}

auto Point::operator-=(const Vec3& rhs) -> Point&
{
    _coordinates[0] -= rhs.x();
    _coordinates[1] -= rhs.y();
    _coordinates[2] -= rhs.z();
    return *this;
}

auto Point::operator-(const Vec3& rhs) -> Point
{
    return Point{*this} -= rhs;
}

auto Point::x() const -> const float&
{
    return _coordinates[0];
}

auto Point::y() const -> const float&
{
    return _coordinates[1];
}

auto Point::z() const -> const float&
{
    return _coordinates[2];
}

