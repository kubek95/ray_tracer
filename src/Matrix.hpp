#pragma once

#include "Utilities.hpp"

#include <array>
#include <cstring>
#include <stdexcept>
#include <utility>
#include <ostream>

#include <iostream>

template<std::size_t mat_size>
class Matrix
{
    public:
        Matrix<mat_size>() = default;
        Matrix<mat_size>(std::initializer_list<float> list);
        ~Matrix<mat_size>() = default;

        Matrix<mat_size>(const Matrix<mat_size>&) = default;
        Matrix<mat_size>(Matrix<mat_size>&&) = default;

        auto operator==(const Matrix<mat_size>& rhs) const -> bool;
        auto operator!=(const Matrix<mat_size>& rhs) const -> bool;
        auto operator*=(const Matrix<mat_size>& rhs) -> Matrix<mat_size>&;
        auto operator*(const Matrix<mat_size>& rhs) const -> Matrix<mat_size>;
        auto at(std::size_t row, std::size_t column) -> float&;
        auto at(std::size_t row, std::size_t column) const -> const float&;

        template<std::size_t size>
        friend auto operator<<(std::ostream&, const Matrix<size>&) -> std::ostream&;
    private:
        auto indexToCoord(std::size_t index) const -> std::pair<std::size_t, std::size_t>;
        std::array<float, mat_size*mat_size> _matrix{};
};

using Mat4 = Matrix<4>;
using Mat3 = Matrix<3>;
using Mat2 = Matrix<2>;

template<std::size_t mat_size>
Matrix<mat_size>::Matrix(std::initializer_list<float> list)
{
    if (list.size() > mat_size*mat_size) {
        throw std::runtime_error("Too many elements in initializer list");
    }
    std::memcpy(_matrix.data(), std::data(list), list.size()*sizeof(float));
}

template<std::size_t mat_size>
auto Matrix<mat_size>::indexToCoord(std::size_t index) const -> std::pair<std::size_t, std::size_t>
{
    return {index/mat_size, index%mat_size};
}

template<std::size_t mat_size>
auto Matrix<mat_size>::operator==(const Matrix<mat_size>& rhs) const -> bool
{
    for(std::size_t i{0}; i < mat_size*mat_size; ++i) {
        const auto [row, column] = indexToCoord(i);
        if (!relativelyEqual(_matrix[i], rhs.at(row, column))) {
            return false;
        }
    }
    return true;
}

template<std::size_t mat_size>
auto Matrix<mat_size>::operator!=(const Matrix<mat_size>& rhs) const -> bool
{
    return (!(*this == rhs));
}

template<std::size_t mat_size>
auto Matrix<mat_size>::operator*=(const Matrix<mat_size>& rhs) -> Matrix<mat_size>&
{
    std::array<float, mat_size*mat_size> tmp{};
    for(unsigned int row{0}; row < mat_size; ++row){
        for(unsigned int column{0}; column < mat_size; ++column) {
            for(unsigned int k{0}; k < mat_size; ++k) {
                tmp[row*mat_size+column] += at(row, k)*rhs.at(k, column);
            }
        }
    }
    std::memcpy(_matrix.data(), tmp.data(), mat_size*mat_size*sizeof(float));
    return *this;
}

template<std::size_t mat_size>
auto Matrix<mat_size>::operator*(const Matrix<mat_size>& rhs) const -> Matrix<mat_size>
{
    return Matrix<mat_size>{*this} *= rhs;
}

template<std::size_t mat_size>
auto Matrix<mat_size>::at(std::size_t row, std::size_t column) -> float&
{
    if (row > mat_size-1 || column > mat_size-1) {
        throw std::runtime_error("out of bounds");
    }
    return _matrix[mat_size*row+column];
}

template<std::size_t mat_size>
auto Matrix<mat_size>::at(std::size_t row, std::size_t column) const -> const float&
{
    if (row > mat_size-1 || column > mat_size-1) {
        throw std::runtime_error("out of bounds");
    }
    return _matrix[mat_size*row+column];
}

template<std::size_t mat_size>
auto operator<<(std::ostream& os, const Matrix<mat_size>& mat) -> std::ostream&
{
    for(const auto el: mat._matrix) {
        os << el << " ";
    }
    return os;
}
