#pragma once

#include <array>
#include <ostream>

class Color
{
    public:
        Color() = default;
        explicit Color(float r, float g, float b);
        ~Color() = default;

        Color(const Color& rhs) = default;
        auto operator=(const Color& rhs) -> Color& = default;
        Color(Color&& rhs) = default;
        auto operator=(Color&& rhs) -> Color& = default;

        auto operator==(const Color& rhs) const -> bool;
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

        friend auto operator<<(std::ostream& os, const Color& c) -> std::ostream&;
    private:
        std::array<float, 3> _rgb;
};

inline auto operator<<(std::ostream& os, const Color& c) -> std::ostream&
{
    os << "[";
    os << c.r() << ",";
    os << c.g() << ",";
    os << c.b() << "]";
    return os;
}
