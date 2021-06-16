#include "Point.hpp"
#include "Vector.hpp"

#include <cmath>
#include <algorithm>

Vec3::Vec3(float x, float y, float z) :
    _coordinates{x, y, z, 0}
{
}

auto Vec3::relativelyEqual(float a,
                           float b,
                           float maxRelativeDiff) const -> bool
{
    const auto diff = std::abs(a - b);
    a = std::abs(a);
    b = std::abs(b);
    const auto scaledEps = maxRelativeDiff * std::max(a, b);
    return diff <= scaledEps;
}

auto Vec3::operator==(const Vec3& rhs) const -> bool
{
    return relativelyEqual(x(), rhs.x()) &&
           relativelyEqual(y(), rhs.y()) &&
           relativelyEqual(z(), rhs.z());
}

auto Vec3::operator+(const Point& rhs) -> Vec3&
{
    _coordinates[0] += rhs.x();
    _coordinates[1] += rhs.y();
    _coordinates[2] += rhs.z();
    return *this;
}
auto Vec3::x() const -> const float&
{
    return _coordinates[0];
}

auto Vec3::y() const -> const float&
{
    return _coordinates[1];
}

auto Vec3::z() const -> const float&
{
    return _coordinates[2];
}
