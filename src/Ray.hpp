#pragma once

#include "Point.hpp"
#include "Vector.hpp"

class Ray
{
    public:
        Ray(const Point4& origin, const Vec4& direction);

        auto position(float time) const -> Point4;
        auto direction() const -> const Vec4&;
        auto origin() const -> const Point4&;

    private:
        Vec4 _direction;
        Point4 _origin;
};
