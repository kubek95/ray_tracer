#include "Color.hpp"
#include "Utilities.hpp"

Color::Color(float r, float g, float b) :
    _rgb{r,g,b}
{}

auto Color::operator==(const Color& rhs) const -> bool
{
    return relativelyEqual(r(), rhs.r()) &&
           relativelyEqual(g(), rhs.g()) &&
           relativelyEqual(b(), rhs.b());
}

auto Color::operator+=(const Color& rhs) -> Color&
{
    _rgb[0] += rhs.r();
    _rgb[1] += rhs.g();
    _rgb[2] += rhs.b();
    return *this;
}

auto Color::operator+(const Color& rhs) const -> Color
{
    return Color{*this} += rhs;
}

auto Color::operator-=(const Color& rhs) -> Color&
{
    _rgb[0] -= rhs.r();
    _rgb[1] -= rhs.g();
    _rgb[2] -= rhs.b();
    return *this;
}

auto Color::operator-(const Color& rhs) const -> Color
{
    return Color{*this} -= rhs;
}

auto Color::operator*=(float scalar) -> Color&
{
    _rgb[0] *= scalar;
    _rgb[1] *= scalar;
    _rgb[2] *= scalar;
    return *this;
}

auto Color::operator*(float scalar) const -> Color
{
    return Color{*this} *= scalar;
}

auto Color::operator*=(const Color& rhs) -> Color&
{
    _rgb[0] *= rhs.r();
    _rgb[1] *= rhs.g();
    _rgb[2] *= rhs.b();
    return *this;
}

auto Color::operator*(const Color& rhs) -> Color
{
    return Color{*this} *= rhs;
}

auto Color::r() const -> const float&
{
    return _rgb[0];
}

auto Color::g() const -> const float&
{
    return _rgb[1];
}

auto Color::b() const -> const float&
{
    return _rgb[2];
}
