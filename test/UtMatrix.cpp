#include "Matrix.hpp"
#include "Utilities.hpp"

#include "gtest/gtest.h"

TEST(matrix, should_support_4x4_matrices)
{
    Mat4 mat;
    for(std::size_t row{0}; row < 4; ++row) {
        for(std::size_t column{0}; column < 4; ++column) {
            mat.at(row, column) = static_cast<float>(row+column);
        }
    }
    for(std::size_t row{0}; row < 4; ++row) {
        for(std::size_t column{0}; column < 4; ++column) {
            ASSERT_TRUE(relativelyEqual(mat.at(row, column),
                                        static_cast<float>(row+column)));
        }
    }
    ASSERT_THROW(mat.at(1, 4), std::runtime_error);
    ASSERT_THROW(mat.at(4, 1), std::runtime_error);
    ASSERT_THROW(mat.at(4, 4), std::runtime_error);
}

TEST(matrix, should_support_3x3_matrices)
{
    Mat3 mat;
    for(std::size_t row{0}; row < 3; ++row) {
        for(std::size_t column{0}; column < 3; ++column) {
            mat.at(row, column) = static_cast<float>(row+column);
        }
    }
    for(std::size_t row{0}; row < 3; ++row) {
        for(std::size_t column{0}; column < 3; ++column) {
            ASSERT_TRUE(relativelyEqual(mat.at(row, column),
                                        static_cast<float>(row+column)));
        }
    }
    ASSERT_THROW(mat.at(1, 3), std::runtime_error);
    ASSERT_THROW(mat.at(3, 1), std::runtime_error);
    ASSERT_THROW(mat.at(3, 3), std::runtime_error);
}

TEST(matrix, should_support_2x2_matrices)
{
    Mat2 mat;
    for(std::size_t row{0}; row < 2; ++row) {
        for(std::size_t column{0}; column < 2; ++column) {
            mat.at(row, column) = static_cast<float>(row+column);
        }
    }
    for(std::size_t row{0}; row < 2; ++row) {
        for(std::size_t column{0}; column < 2; ++column) {
            ASSERT_TRUE(relativelyEqual(mat.at(row, column),
                                        static_cast<float>(row+column)));
        }
    }
    ASSERT_THROW(mat.at(0, 2), std::runtime_error);
    ASSERT_THROW(mat.at(2, 0), std::runtime_error);
    ASSERT_THROW(mat.at(2, 2), std::runtime_error);
}

TEST(matrix, check_equality_of_two_matrices)
{
    Mat2 mat1;
    mat1.at(0,0) = 1.f;
    mat1.at(0,1) = 2.f;
    mat1.at(1,0) = 3.f;
    mat1.at(1,1) = 4.f;
    Mat2 mat2;
    mat2.at(0,0) = 1.1f;
    mat2.at(0,1) = 2.f;
    mat2.at(1,0) = 3.f;
    mat2.at(1,1) = 4.f;
    ASSERT_EQ(mat1, mat1);
    ASSERT_NE(mat1, mat2);
}

TEST(matrix, check_multiplication)
{
    Mat4 mat1{1.f, 2.f, 3.f, 4.f,
              5.f, 6.f, 7.f, 8.f,
              9.f, 8.f, 7.f, 6.f,
              5.f, 4.f, 3.f, 2.f};
    Mat4 mat2{-2.f, 1.f, 2.f, 3.f,
              3.f, 2.f, 1.f, -1.f,
              4.f, 3.f, 6.f, 5.f,
              1.f, 2.f, 7.f, 8.f};
    Mat4 expectedResult{20.f, 22.f, 50.f, 48.f,
                        44.f, 54.f, 114.f, 108.f,
                        40.f, 58.f, 110.f, 102.f,
                        16.f, 26.f, 46.f, 42.f};
    ASSERT_EQ(mat1*mat2, expectedResult);
}
