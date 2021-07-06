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
        constexpr Matrix<size>() noexcept
        {
            static_assert(size <= 4, "Matrix with size greater than 4 is not supported");
        }

        constexpr Matrix<size>(std::initializer_list<float> list):
            Matrix<size>{}
        {
            if (list.size() > size*size) {
                throw std::runtime_error("Too many elements in initializer list");
            }
            std::copy(list.begin(), list.end(), _matrix.begin());
        }

        auto& operator*=(const Matrix<size>& rhs)
        {
            std::array<float, size*size> tmp{};
            for(unsigned int row{0}; row < size; ++row){
                for(unsigned int column{0}; column < size; ++column) {
                    for(unsigned int k{0}; k < size; ++k) {
                        tmp[coordToIndex(row, column)] += at(row, k)*rhs.at(k, column);
                    }
                }
            }
            std::copy(tmp.begin(), tmp.end(), _matrix.begin());
            return *this;
        }

        auto& operator/=(float scalar)
        {
            std::for_each(_matrix.begin(),
                          _matrix.end(),
                          [scalar](float& el){el/=scalar;});
            return *this;
        }

        auto at(std::size_t row, std::size_t column) const
        {
            if (row > size-1 || column > size-1) {
                throw std::runtime_error("out of bounds");
            }
            return _matrix[coordToIndex(row, column)];
        }

        auto& at(std::size_t row, std::size_t column)
        {
            if (row > size-1 || column > size-1) {
                throw std::runtime_error("out of bounds");
            }
            return _matrix[coordToIndex(row, column)];
        }

    private:
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
inline auto indexToCoord(std::size_t index) -> std::pair<std::size_t, std::size_t>
{
    return {index/size, index%size};
}

template<std::size_t size>
auto Matrix<size>::coordToIndex(std::size_t row, std::size_t column) const -> std::size_t
{
    return size*row + column;
}

template<std::size_t size>
inline auto operator==(const Matrix<size>& lhs, const Matrix<size>& rhs)
{
    for(std::size_t i{0}; i < size*size; ++i) {
        const auto [row, column] = indexToCoord<size>(i);
        if (!relativelyEqual(lhs.at(row, column), rhs.at(row, column))) {
            return false;
        }
    }
    return true;
}

template<std::size_t size>
inline auto operator!=(const Matrix<size>& lhs, const Matrix<size>& rhs)
{
    return !(lhs == rhs);
}

template<std::size_t size>
inline auto operator*(Matrix<size> lhs, const Matrix<size>& rhs)
{
    lhs *= rhs;
    return lhs;
}

template<std::size_t size>
inline auto operator*(const Matrix<size>& lhs, const Vector<size>& rhs)
{
    Vector<size> temp;
    for (std::size_t row{0}; row < size; ++row) {
        for (std::size_t k{0}; k < size; ++k) {
            temp.at(row) += lhs.at(row, k) * rhs.at(k);
        }
    }
    return temp;
}

template<std::size_t size>
inline auto operator*(const Matrix<size>& lhs, const Point<size>& rhs)
{
    Point<size> temp;
    for (std::size_t row{0}; row < size; ++row) {
        for (std::size_t k{0}; k < size; ++k) {
            temp.at(row) += lhs.at(row, k) * rhs.at(k);
        }
    }
    return temp;
}

template<std::size_t size>
inline auto operator/(Matrix<size> lhs, float scalar)
{
    lhs /= scalar;
    return lhs;
}

template<std::size_t size>
inline auto transpose(Matrix<size> mat)
{
    for (std::size_t row{0}; row < size; ++row) {
        for (std::size_t column{row}; column < size; ++column) {
            if (row != column) {
                std::swap(mat.at(row, column), mat.at(column, row));
            }
        }
    }
    return mat;
}

template<std::size_t size>
inline auto determinant(const Matrix<size>& mat)
{
    auto determinant = 0.f;
    for(std::size_t column{0}; column < size; ++column) {
        determinant += mat.at(0, column) * cofactor(mat, 0, column);
    }
    return determinant;
}

template<>
inline auto determinant(const Matrix<1>& mat)
{
    return mat.at(0,0);
}

template<std::size_t size>
inline auto submatrix(const Matrix<size>& mat, std::size_t rowToDelete, std::size_t columnToDelete)
{
    Matrix<size-1> temp;
    for (std::size_t row{0}; row < size; ++row) {
        for (std::size_t column{0}; column < size; ++column) {
            if (row != rowToDelete && column != columnToDelete) {
                const auto rowToInsert = row > rowToDelete ? row-1 : row;
                const auto columnToInsert = column > columnToDelete ? column-1 : column;
                temp.at(rowToInsert, columnToInsert) = mat.at(row, column);
            }
        }
    }
    return temp;
}

template<std::size_t size>
inline auto minor(const Matrix<size>& mat, std::size_t row, std::size_t column)
{
    return determinant(submatrix(mat, row, column));
}

template<std::size_t size>
inline auto cofactor(const Matrix<size>& mat, std::size_t row, std::size_t column)
{
    return (row+column)&1 ? -minor(mat, row, column) : minor(mat, row, column);
}

template<std::size_t size>
inline auto isInvertible(const Matrix<size>& mat)
{
    return determinant(mat) != 0;
}

template<std::size_t size>
inline auto inverse(const Matrix<size>& mat)
{
    Matrix<size> matOfCofactors;
    for (std::size_t row{0}; row < size; ++row) {
        for (std::size_t column{0}; column < size; ++column) {
            matOfCofactors.at(row, column) = cofactor(mat, row, column);
        }
    }
    matOfCofactors = transpose(std::move(matOfCofactors));
    matOfCofactors /= determinant(mat);
    return matOfCofactors;
}

template<std::size_t size>
inline auto operator<<(std::ostream& os, const Matrix<size>& mat) -> std::ostream&
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
