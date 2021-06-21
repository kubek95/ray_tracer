#pragma once

#include "Point.hpp"
#include "Utilities.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <limits>
#include <initializer_list>
#include <stdexcept>

template<std::size_t size>
class Point;
template<std::size_t size>
class Vector
{
    public:
        Vector<size>() = default;
        explicit Vector<size>(std::initializer_list<float> values);
        ~Vector<size>() = default;
    
        Vector<size>(const Vector<size>& vector) = default;
        auto operator=(const Vector<size>& rhs) -> Vector<size>& = default;
        Vector<size>(Vector<size>&& vector) = default;
        auto operator=(Vector<size>&& rhs) -> Vector<size>& = default;
    
        auto operator==(const Vector<size>& rhs) const -> bool;
        auto operator+=(const Vector<size>& rhs) -> Vector<size>&;
        auto operator+(const Vector<size>& rhs) const -> Vector<size>;
        auto operator+=(const Point<size>& rhs) const -> Point<size>;
        auto operator+(const Point<size>& rhs) const -> Point<size>;
        auto operator-=(const Vector<size>& rhs) -> Vector<size>&;
        auto operator-(const Vector<size>& rhs) const -> Vector<size>;
        auto operator-() -> Vector<size>;
        auto operator*=(float scalar) -> Vector<size>&;
        auto operator*(float scalar) -> Vector<size>;
        auto operator/=(float scalar) -> Vector<size>&;
        auto operator/(float scalar) -> Vector<size>;
        template<std::size_t vec_size>
        friend auto operator<<(std::ostream& str, const Vector<vec_size>& vec) -> std::ostream&;

        auto magnitude() const -> float;
        auto normalize() -> Vector<size>&;
        auto dot(const Vector<size>& rhs) const -> float;
        auto cross(const Vector<size>& rhs) -> Vector<size>&;
        auto at(const std::size_t position) const -> const float&;
        auto at(std::size_t position) -> float&;

    private:
        std::array<float, size> _coordinates{};
};

using Vec2 = Vector<2>;
using Vec3 = Vector<3>;
using Vec4 = Vector<4>;

template<std::size_t size>
Vector<size>::Vector(std::initializer_list<float> values)
{
    if(values.size() > size) {
        throw std::runtime_error("Too many elements");
    }
    std::copy(values.begin(), values.end(), _coordinates.begin());
}

template<std::size_t size>
auto Vector<size>::operator==(const Vector<size>& rhs) const -> bool
{
    bool result{true};
    for (std::size_t i{0}; i < size; ++i) {
        result &= relativelyEqual(_coordinates[i], rhs._coordinates[i]);
    }
    return result;
}

template<std::size_t size>
auto Vector<size>::operator+=(const Vector<size>& rhs) -> Vector<size>&
{
    for (std::size_t i{0}; i < size; ++i) {
        _coordinates[i] += rhs._coordinates[i];
    }
    return *this;
}

template<std::size_t size>
auto Vector<size>::operator+(const Vector<size>& rhs) const -> Vector<size>
{
    return Vector<size>{*this} += rhs;
}

template<std::size_t size>
auto Vector<size>::operator+=(const Point<size>& rhs) const -> Point<size>
{
    Point<size> tmp;
    for(std::size_t i{0}; i < size; ++i) {
        tmp.at(i) = at(i)+rhs.at(i);
    }
    return tmp;
}

template<std::size_t size>
auto Vector<size>::operator+(const Point<size>& rhs) const -> Point<size>
{
    return Vector<size>{*this} += rhs;
}

template<std::size_t size>
auto Vector<size>::operator-=(const Vector<size>& rhs) -> Vector<size>&
{
    for (std::size_t i{0}; i < size; ++i) {
        _coordinates[i] -= rhs._coordinates[i];
    }
    return *this;
}

template<std::size_t size>
auto Vector<size>::operator-(const Vector<size>& rhs) const -> Vector<size>
{
    return Vector<size>{*this} -= rhs;
}

template<std::size_t size>
auto Vector<size>::operator-() -> Vector<size>
{
    Vector<size> tmp{*this};
    for (std::size_t i{0}; i < size; ++i) {
        tmp._coordinates[i] = -_coordinates[i];
    }
    return tmp;
}

template<std::size_t size>
auto Vector<size>::operator*=(float scalar) -> Vector<size>&
{
    for (std::size_t i{0}; i < size; ++i) {
        _coordinates[i] *= scalar;
    }
    return *this;
}

template<std::size_t size>
auto Vector<size>::operator*(float scalar) -> Vector<size>
{
    return Vector<size>{*this} *= scalar;
}

template<std::size_t size>
auto Vector<size>::operator/=(float scalar) -> Vector<size>&
{
    return *this *= 1/scalar;
}

template<std::size_t size>
auto Vector<size>::operator/(float scalar) -> Vector<size>
{
    return Vector<size>{*this}/=scalar;
}

template<std::size_t size>
auto Vector<size>::magnitude() const -> float
{
    float sumOfSquares;
    for (std::size_t i{0}; i < size; ++i) {
        sumOfSquares += std::pow(at(i), 2.f);
    }
    return std::sqrt(sumOfSquares);
}

template<std::size_t size>
auto Vector<size>::normalize() -> Vector<size>&
{
    const auto mag = magnitude();
    for (std::size_t i{0}; i < size; ++i) {
        _coordinates[i] /= mag;
    }
    return *this;
}

template<std::size_t size>
auto Vector<size>::dot(const Vector<size>& rhs) const -> float
{
    float dotProduct;
    for (std::size_t i{0}; i < size; ++i) {
        dotProduct += _coordinates[i]*rhs._coordinates[i];
    }
    return dotProduct;
}

//TODO: expand to more sizes
template<std::size_t size>
auto Vector<size>::cross(const Vector<size>& rhs) -> Vector<size>&
{
    if (size != 3) {
        throw std::runtime_error("implementation does not support cross product"
                                 "for vectors with size different than 3");
    }
    const float x{this->at(0)};
    const float y{this->at(1)};
    const float z{this->at(2)};
    _coordinates[0] = y*rhs.at(2) - z*rhs.at(1);
    _coordinates[1] = z*rhs.at(0) - x*rhs.at(2);
    _coordinates[2] = x*rhs.at(1) - y*rhs.at(0);
    return *this;
}

template<std::size_t size>
auto Vector<size>::at(std::size_t position) const -> const float&
{
    if (position >= size) {
        throw std::runtime_error("Index out of bounds");
    }
    return _coordinates[position];
}

template<std::size_t size>
auto Vector<size>::at(const std::size_t position) -> float&
{
    if (position >= size) {
        throw std::runtime_error("Index out of bounds");
    }
    return _coordinates[position];
}

template<std::size_t size>
inline auto operator<<(std::ostream& str, const Vector<size>& vec) -> std::ostream&
{
    str << "[";
    for (std::size_t i{0}; i < size-1; ++i) {
        str << vec.at(i) << ",";
    }
    str << vec.at(size-1) << "]";
    return str;
}
