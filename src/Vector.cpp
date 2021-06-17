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

auto Vec3::operator+=(const Point& rhs) -> Vec3&
{
    _coordinates[0] += rhs.x();
    _coordinates[1] += rhs.y();
    _coordinates[2] += rhs.z();
    return *this;
}

auto Vec3::operator+(const Point& rhs) const -> Vec3
{
    return Vec3{*this} += rhs;
}

auto Vec3::operator-=(const Vec3& rhs) -> Vec3&
{
    _coordinates[0] -= rhs.x();
    _coordinates[1] -= rhs.y();
    _coordinates[2] -= rhs.z();
    return *this;
}

auto Vec3::operator-(const Vec3& rhs) const -> Vec3
{
    return Vec3{*this} -= rhs;
}

auto Vec3::operator-() -> Vec3
{
    Vec3 tmp{*this};
    tmp._coordinates[0] = -_coordinates[0];
    tmp._coordinates[1] = -_coordinates[1];
    tmp._coordinates[2] = -_coordinates[2];
    return tmp;
}

auto Vec3::operator*=(float scalar) -> Vec3&
{
    _coordinates[0] *= scalar;
    _coordinates[1] *= scalar;
    _coordinates[2] *= scalar;
    return *this;
}

auto Vec3::operator*(float scalar) -> Vec3
{
    return Vec3{*this} *= scalar;
}

auto Vec3::operator/=(float scalar) -> Vec3&
{
    return *this *= 1/scalar;
}

auto Vec3::operator/(float scalar) -> Vec3
{
    return Vec3{*this}/=scalar;
}

auto Vec3::magnitude() const -> float
{
    return std::sqrt(std::pow(x(), 2) + std::pow(y(), 2) + std::pow(z(), 2));
}

auto Vec3::normalize() -> Vec3&
{
    const auto mag = magnitude();
    _coordinates[0] /= mag;
    _coordinates[1] /= mag;
    _coordinates[2] /= mag;
    return *this;
}

auto Vec3::dot(const Vec3& rhs) const -> float
{
    return x()*rhs.x() +
           y()*rhs.y() +
           z()*rhs.z();
}

auto Vec3::cross(const Vec3& rhs) -> Vec3&
{
    const float x{this->x()};
    const float y{this->y()};
    const float z{this->z()};
    _coordinates[0] = y*rhs.z() - z*rhs.y();
    _coordinates[1] = z*rhs.x() - x*rhs.z();
    _coordinates[2] = x*rhs.y() - y*rhs.x();
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
