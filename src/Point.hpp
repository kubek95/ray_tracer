#pragma once

#include "Utilities.hpp"
#include "Vector.hpp"

#include <algorithm>
#include <array>
#include <initializer_list>
#include <stdexcept>
#include <ostream>

template<std::size_t size>
class Vector;

template<std::size_t size>
class Point
{
    public:
        constexpr Point<size>() noexcept
        {
            static_assert(size <= 4, "Point with size greater than 4 is not supported");
        }

        constexpr Point<size>(std::initializer_list<float> values) :
            Point<size>()
        {
            if (values.size() > size) {
                throw std::runtime_error("Too many elements");
            }
            std::copy(values.begin(), values.end(), _coordinates.begin());
        }

        auto& operator-=(const Vector<size>& rhs)
        {
            for (std::size_t i{0}; i < size; ++i) {
                _coordinates[i] -= rhs.at(i);
            }
            return *this;
        }

        auto& at(std::size_t position) const
        {
            if (position >= size) {
                throw std::runtime_error("Index if out of bounds");
            }
            return _coordinates[position];
        }
        
        auto& at(std::size_t position)
        {
            if (position >= size) {
                throw std::runtime_error("Index if out of bounds");
            }
            return _coordinates[position];
        }

    private:
        std::array<float, size> _coordinates{};
};

using Point2 = Point<2>;
using Point3 = Point<3>;
using Point4 = Point<4>;

template<std::size_t size>
inline auto operator==(const Point<size>& lhs, const Point<size>& rhs)
{
    auto result = true;
    for (std::size_t i{0}; i < size; ++i) {
        result &= relativelyEqual(lhs.at(i), rhs.at(i));
    }
    return result;
}

template<std::size_t size>
inline auto operator+(const Point<size>& lhs, const Vector<size>& rhs)
{
    Vector<size> tmp;
    for (std::size_t i{0}; i < size; ++i) {
        tmp.at(i) = rhs.at(i) + lhs.at(i);
    }
    return tmp;
}

template<std::size_t size>
inline auto operator-(const Point<size>& lhs, const Point<size>& rhs)
{
    Vector<size> tmp;
    for (std::size_t i{0}; i < size; ++i) {
        tmp.at(i) = lhs.at(i) - rhs.at(i);
    }
    return tmp;
}

template<std::size_t size>
inline auto operator-(Point<size> lhs, const Vector<size>& rhs)
{
    return lhs -= rhs;
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
