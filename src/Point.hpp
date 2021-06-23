#pragma once

#include "Utilities.hpp"
#include "Vector.hpp"

#include <algorithm>
#include <array>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <ostream>

template<std::size_t size>
class Vector;
template<std::size_t size>
class Point
{
    public:
        Point<size>() = default;
        explicit Point<size>(std::initializer_list<float> values);
        ~Point<size>() = default;

        Point<size>(const Point<size>& rhs) = default;
        auto operator=(const Point<size>& rhs) -> Point<size>& = default;
        Point<size>(Point<size>&& rhs) = default;
        auto operator=(Point<size>&& rhs) -> Point<size>& = default;

        auto operator==(const Point<size>& rhs) const -> bool;
        auto operator+(const Vector<size>& rhs) const -> Vector<size>;
        auto operator-(const Point<size>& rhs) -> Vector<size>; 
        auto operator-=(const Vector<size>& rhs) -> Point<size>&;
        auto operator-(const Vector<size>& rhs) -> Point<size>;
        auto at(std::size_t position) const -> const float&;
        auto at(std::size_t position) -> float&;

        template<std::size_t p_size>
        friend auto operator<<(std::ostream& ost, const Point<p_size>& p) -> std::ostream&;
    private:
        std::array<float, size> _coordinates{};
};

using Point2 = Point<2>;
using Point3 = Point<3>;
using Point4 = Point<4>;

template<std::size_t size>
Point<size>::Point(std::initializer_list<float> values)
{
    if (values.size() > size) {
        throw std::runtime_error("Too many elements");
    }
    std::copy(values.begin(), values.end(), _coordinates.begin());
}

template<std::size_t size>
auto Point<size>::operator==(const Point<size>& rhs) const -> bool
{
    bool result{true};
    for (std::size_t i{0}; i < size; ++i) {
        result &= relativelyEqual(at(i), rhs.at(i));
    }
    return result;
}

template<std::size_t size>
auto Point<size>::operator+(const Vector<size>& rhs) const -> Vector<size>
{
    Vector<size> tmp;
    for (std::size_t i{0}; i < size; ++i) {
        tmp.at(i) = rhs.at(i) + at(i);
    }
    return tmp;
}

template<std::size_t size>
auto Point<size>::operator-(const Point<size>& rhs) -> Vector<size>
{
    Vector<size> tmp;
    for (std::size_t i{0}; i < size; ++i) {
        tmp.at(i) = at(i) - rhs.at(i);
    }
    return tmp;
}

template<std::size_t size>
auto Point<size>::operator-=(const Vector<size>& rhs) -> Point<size>&
{
    for (std::size_t i{0}; i < size; ++i) {
        _coordinates[i] -= rhs.at(i);
    }
    return *this;
}

template<std::size_t size>
auto Point<size>::operator-(const Vector<size>& rhs) -> Point<size>
{
    return Point<size>{*this} -= rhs;
}

template<std::size_t size>
auto Point<size>::at(std::size_t position) const -> const float&
{
    if (position >= size) {
        throw std::runtime_error("Index if out of bounds");
    }
    return _coordinates[position];
}

template<std::size_t size>
auto Point<size>::at(std::size_t position) -> float&
{
    if (position >= size) {
        throw std::runtime_error("Index if out of bounds");
    }
    return _coordinates[position];
}

template<std::size_t size>
inline auto operator<<(std::ostream& ost, const Point<size>& p) -> std::ostream&
{
    ost << "(";
    for (std::size_t i{0}; i < size-1; ++i) {
        ost << p.at(i) << ",";
    }
    ost << p.at(size-1) << ")";
    return ost;
}
