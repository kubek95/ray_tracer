#include "Ray.hpp"

Ray::Ray(const Point4& origin, const Vec4& direction):
    _origin{origin},
    _direction{direction}
{
}

auto Ray::position(float time) const -> Point4
{
    return _direction*time + _origin;
}

auto Ray::direction() const -> const Vec4&
{
    return _direction;
}

auto Ray::origin() const -> const Point4&
{
    return _origin;
}

