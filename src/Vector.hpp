#pragma once

#include "Point.hpp"
#include "Utilities.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <numeric>
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
        constexpr Vector<size>() noexcept
        {
            static_assert(size <= 4, "Vector with size greater than 4 is not supported");
        }

        constexpr Vector<size>(std::initializer_list<float> values):
            Vector<size>{}
        {
            if(values.size() > size) {
                throw std::runtime_error("Too many elements");
            }
            std::copy(values.begin(), values.end(), _coordinates.begin());
        }
    
        auto& operator+=(const Vector<size>& rhs)
        {
            for (std::size_t i{0}; i < size; ++i) {
                _coordinates[i] += rhs._coordinates[i];
            }
            return *this;
        }

        auto& operator-=(const Vector<size>& rhs)
        {
            for (std::size_t i{0}; i < size; ++i) {
                _coordinates[i] -= rhs._coordinates[i];
            }
            return *this;
        }

        auto& operator*=(float scalar)
        {
            std::for_each(_coordinates.begin(), _coordinates.end(),
                          [scalar](auto& el){ el*=scalar; });
            return *this;
        }

        auto& operator/=(float scalar)
        {
            return *this *= 1/scalar;
        }

        auto& at(const std::size_t position) const
        {
            if (position >= size) {
                throw std::runtime_error("Index out of bounds");
            }
            return _coordinates[position];
        }

        auto& at(std::size_t position)
        {
            if (position >= size) {
                throw std::runtime_error("Index out of bounds");
            }
            return _coordinates[position];
        }

        auto cross(const Vector<size>& rhs) -> Vector<size>&;

    private:
        std::array<float, size> _coordinates{};
};

using Vec2 = Vector<2>;
using Vec3 = Vector<3>;
using Vec4 = Vector<4>;

template<std::size_t size>
inline auto operator==(const Vector<size>& lhs, const Vector<size>& rhs)
{
    auto result = true;
    for (std::size_t i{0}; i < size; ++i) {
        result &= relativelyEqual(lhs.at(i), rhs.at(i));
    }
    return result;
}

template<std::size_t size>
inline auto operator+(Vector<size> lhs, const Vector<size>& rhs)
{
    return lhs += rhs;
}

template<std::size_t size>
inline auto operator+(const Vector<size>& lhs, Point<size> rhs)
{
    for(std::size_t i{0}; i < size; ++i) {
        rhs.at(i) += lhs.at(i);
    }
    return rhs;
}

template<std::size_t size>
inline auto operator-(Vector<size> lhs, const Vector<size>& rhs)
{
    return lhs -= rhs;
}

template<std::size_t size>
inline auto operator-(Vector<size> vec)
{
    for(std::size_t i{0}; i < size; ++i) {
        vec.at(i) = -vec.at(i);
    }
    return vec;
}

template<std::size_t size>
inline auto operator*(Vector<size> lhs, float scalar)
{
    return lhs *= scalar;
}

template<std::size_t size>
inline auto operator/(Vector<size> lhs, float scalar)
{
    return lhs /= scalar;
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

template<std::size_t size>
inline auto magnitude(const Vector<size>& vec)
{
    auto sumOfSquares{0.f};
    for (std::size_t i{0}; i < size; ++i) {
        sumOfSquares += std::pow(vec.at(i), 2.f);
    }
    return std::sqrt(sumOfSquares);
}

template<std::size_t size>
inline auto normalize(Vector<size> vec)
{
    const auto mag = magnitude(vec);
    for (std::size_t i{0}; i < size; ++i) {
        vec.at(i) /= mag;
    }
    return vec;
}

template<std::size_t size>
inline auto dotProduct(const Vector<size>& lhs, const Vector<size>& rhs)
{
    auto dotProduct = 0.f;
    for (std::size_t i{0}; i < size; ++i) {
        dotProduct += lhs.at(i) * rhs.at(i);
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
    const auto x=this->at(0);
    const auto y=this->at(1);
    const auto z=this->at(2);
    _coordinates[0] = y*rhs.at(2) - z*rhs.at(1);
    _coordinates[1] = z*rhs.at(0) - x*rhs.at(2);
    _coordinates[2] = x*rhs.at(1) - y*rhs.at(0);
    return *this;
}
