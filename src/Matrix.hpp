#pragma once

#include "Point.hpp"
#include "Utilities.hpp"
#include "Vector.hpp"

#include <algorithm>
#include <array>
#include <cstring>
#include <stdexcept>
#include <utility>
#include <ostream>

template<std::size_t size>
class Matrix
{
    public:
        Matrix<size>() = default;
        Matrix<size>(std::initializer_list<float> list);

        auto operator==(const Matrix<size>& rhs) const -> bool;
        auto operator!=(const Matrix<size>& rhs) const -> bool;
        auto operator*=(const Matrix<size>& rhs) -> Matrix<size>&;
        auto operator*(const Matrix<size>& rhs) const -> Matrix<size>;
        auto operator*(const Vector<size>& rhs) const -> Vector<size>;
        auto operator*(const Point<size>& rhs) const -> Point<size>;
        auto operator/=(float scalar) -> Matrix<size>&;
        auto operator/(float scalar) const -> Matrix<size>;
        auto transpose() -> Matrix<size>&;
        auto determinant() const -> float;
        auto submatrix(std::size_t row, std::size_t column) const -> Matrix<size-1>;
        auto cofactor(std::size_t row, std::size_t column) const -> float;
        auto minor(std::size_t row, std::size_t column) const -> float;
        auto isInvertible() const -> bool;
        auto inverse() -> Matrix<size>&;
        auto at(std::size_t row, std::size_t column) -> float&;
        auto at(std::size_t row, std::size_t column) const -> const float&;

        template<std::size_t mat_size>
        friend auto operator<<(std::ostream&, const Matrix<mat_size>&) -> std::ostream&;
    private:
        auto indexToCoord(std::size_t index) const -> std::pair<std::size_t, std::size_t>;
        auto coordToIndex(std::size_t row, std::size_t column) const -> std::size_t;

        std::array<float, size*size> _matrix{};
};

using Mat4 = Matrix<4>;
using Mat3 = Matrix<3>;
using Mat2 = Matrix<2>;
using Mat1 = Matrix<1>;

namespace matrix {
inline const Mat1 identity1{1.f};
inline const Mat2 identity2{1.f, 0.f,
                            0.f, 1.f};
inline const Mat3 identity3{1.f, 0.f, 0.f,
                            0.f, 1.f, 0.f,
                            0.f, 0.f, 1.f};
inline const Mat4 identity4{1.f, 0.f, 0.f, 0.f,
                            0.f, 1.f, 0.f, 0.f,
                            0.f, 0.f, 1.f, 0.f,
                            0.f, 0.f, 0.f, 1.f};
}

template<std::size_t size>
Matrix<size>::Matrix(std::initializer_list<float> list)
{
    if (list.size() > size*size) {
        throw std::runtime_error("Too many elements in initializer list");
    }
    if (size > 4) {
        throw std::runtime_error("Matrices with size above 4 are not supported");
    }
    std::memcpy(_matrix.data(), std::data(list), list.size()*sizeof(float));
}

template<std::size_t size>
auto Matrix<size>::indexToCoord(std::size_t index) const -> std::pair<std::size_t, std::size_t>
{
    return {index/size, index%size};
}

template<std::size_t size>
auto Matrix<size>::coordToIndex(std::size_t row, std::size_t column) const -> std::size_t
{
    return size*row + column;
}

template<std::size_t size>
auto Matrix<size>::operator==(const Matrix<size>& rhs) const -> bool
{
    for(std::size_t i{0}; i < size*size; ++i) {
        const auto [row, column] = indexToCoord(i);
        if (!relativelyEqual(_matrix[i], rhs.at(row, column))) {
            return false;
        }
    }
    return true;
}

template<std::size_t size>
auto Matrix<size>::operator!=(const Matrix<size>& rhs) const -> bool
{
    return (!(*this == rhs));
}

template<std::size_t size>
auto Matrix<size>::operator*=(const Matrix<size>& rhs) -> Matrix<size>&
{
    std::array<float, size*size> tmp{};
    for(unsigned int row{0}; row < size; ++row){
        for(unsigned int column{0}; column < size; ++column) {
            for(unsigned int k{0}; k < size; ++k) {
                tmp[row*size+column] += at(row, k)*rhs.at(k, column);
            }
        }
    }
    std::memcpy(_matrix.data(), tmp.data(), size*size*sizeof(float));
    return *this;
}

template<std::size_t size>
auto Matrix<size>::operator*(const Matrix<size>& rhs) const -> Matrix<size>
{
    return Matrix<size>{*this} *= rhs;
}

template<std::size_t size>
auto Matrix<size>::operator*(const Vector<size>& rhs) const -> Vector<size>
{
    Vector<size> temp;
    for (std::size_t row{0}; row < size; ++row) {
        for (std::size_t k{0}; k < size; ++k) {
            temp.at(row) += at(row, k) * rhs.at(k);
        }
    }
    return temp;
}

template<std::size_t size>
auto Matrix<size>::operator*(const Point<size>& rhs) const -> Point<size>
{
    Point<size> temp;
    for (std::size_t row{0}; row < size; ++row) {
        for (std::size_t k{0}; k < size; ++k) {
            temp.at(row) += at(row, k) * rhs.at(k);
        }
    }
    return temp;
}

template<std::size_t size>
auto Matrix<size>::operator/=(float scalar) -> Matrix<size>&
{
    std::for_each(_matrix.begin(),
                  _matrix.end(),
                  [scalar](float& el){el/=scalar;});
    return *this;
}

template<std::size_t size>
auto Matrix<size>::operator/(float scalar) const -> Matrix<size>
{
    return Matrix{*this} /= scalar;
}

template<std::size_t size>
auto Matrix<size>::at(std::size_t row, std::size_t column) -> float&
{
    if (row > size-1 || column > size-1) {
        throw std::runtime_error("out of bounds");
    }
    return _matrix[coordToIndex(row, column)];
}

template<std::size_t size>
auto Matrix<size>::transpose() -> Matrix<size>&
{
    for (std::size_t row{0}; row < size; ++row) {
        for (std::size_t column{row}; column < size; ++column) {
            if (row != column) {
                std::swap(_matrix[coordToIndex(row, column)],
                          _matrix[coordToIndex(column, row)]);
            }
        }
    }
    return *this;
}

template<std::size_t size>
auto Matrix<size>::determinant() const -> float
{
    float determinant{};
    for(std::size_t column{0}; column < size; ++column) {
        determinant += at(0, column) * cofactor(0, column);
    }
    return determinant;
}

template<>
inline auto Matrix<1>::determinant() const -> float
{
    return at(0,0);
}

template<std::size_t size>
auto Matrix<size>::submatrix(std::size_t rowToDelete, std::size_t columnToDelete) const -> Matrix<size-1>
{
    Matrix<size-1> temp;
    for (std::size_t row{0}; row < size; ++row) {
        for (std::size_t column{0}; column < size; ++column) {
            if (row != rowToDelete && column != columnToDelete) {
                const auto rowToInsert = row > rowToDelete ? row-1 : row;
                const auto columnToInsert = column > columnToDelete ? column-1 : column;
                temp.at(rowToInsert, columnToInsert) = at(row, column);
            }
        }
    }
    return temp;
}

template<>
inline auto Matrix<2>::submatrix(std::size_t row, std::size_t column) const -> Matrix<1>
{
    return Mat1{at(1-row, 1-column)};
}

template<std::size_t size>
auto Matrix<size>::minor(std::size_t row, std::size_t column) const -> float
{
    return submatrix(row, column).determinant();
}

template<std::size_t size>
auto Matrix<size>::cofactor(std::size_t row, std::size_t column) const -> float
{
    return (row+column)&1 ? -minor(row, column) : minor(row, column);
}

template<std::size_t size>
auto Matrix<size>::isInvertible() const -> bool
{
    return determinant() != 0;
}

template<std::size_t size>
auto Matrix<size>::inverse() -> Matrix<size>&
{
    Matrix<size> matOfCofactors;
    for (std::size_t row{0}; row < size; ++row) {
        for (std::size_t column{0}; column < size; ++column) {
            matOfCofactors.at(row, column) = cofactor(row, column);
        }
    }
    matOfCofactors.transpose();
    matOfCofactors /= determinant();
    _matrix = matOfCofactors._matrix;
    return *this;
}

template<std::size_t size>
auto Matrix<size>::at(std::size_t row, std::size_t column) const -> const float&
{
    if (row > size-1 || column > size-1) {
        throw std::runtime_error("out of bounds");
    }
    return _matrix[size*row+column];
}

template<std::size_t size>
auto operator<<(std::ostream& os, const Matrix<size>& mat) -> std::ostream&
{
    for (std::size_t row{0}; row < size; ++row) {
        os << "|";
        for(std::size_t column{0}; column < size; ++column) {
            os << mat.at(row, column) << " ";
        }
        os << "|\n";
    }
    return os;
}
