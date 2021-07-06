#pragma once

#include "Utilities.hpp"
#include <array>
#include <ostream>

class Color
{
    public:
        Color() = default;
        explicit Color(float r, float g, float b);

        auto operator+=(const Color& rhs) -> Color&;
        auto operator+(const Color& rhs) const -> Color;
        auto operator-=(const Color& rhs) -> Color&;
        auto operator-(const Color& rhs) const -> Color;
        auto operator*=(const Color& rhs) -> Color&;
        auto operator*(const Color& rhs) -> Color;
        auto operator*=(float scalar) -> Color&;
        auto operator*(float scalar) const -> Color;
        auto r() const -> const float&;
        auto g() const -> const float&;
        auto b() const -> const float&;

    private:
        std::array<float, 3> _rgb{};
};

inline auto operator==(const Color& lhs, const Color& rhs)
{
    return relativelyEqual(lhs.r(), rhs.r()) &&
           relativelyEqual(lhs.g(), rhs.g()) &&
           relativelyEqual(lhs.b(), rhs.b());
}

inline auto operator<<(std::ostream& os, const Color& c) -> std::ostream&
{
    os << "[";
    os << c.r() << ",";
    os << c.g() << ",";
    os << c.b() << "]";
    return os;
}
