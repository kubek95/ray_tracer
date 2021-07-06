#include "Matrix.hpp"
#include "Utilities.hpp"

#include "gtest/gtest.h"
#include <iostream>

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

TEST(matrix, should_support_multiplication_with_vector)
{
    Mat4 mat{1.f, 2.f, 3.f, 4.f,
             2.f, 4.f, 4.f, 2.f,
             8.f, 6.f, 4.f, 1.f,
             0.f, 0.f, 0.f, 1.f};
    Vec4 vec{1.f, 2.f, 3.f, 1.f};
    Vec4 expectedResult{18.f, 24.f, 33.f, 1};
    ASSERT_EQ(mat*vec, expectedResult);
}

TEST(matrix, should_support_multiplication_by_point)
{
    Mat4 mat{1.f, 2.f, 3.f, 4.f,
             2.f, 4.f, 4.f, 2.f,
             8.f, 6.f, 4.f, 1.f,
             0.f, 0.f, 0.f, 1.f};
    Point4 p{1.f, 2.f, 3.f, 1.f};
    Point4 expectedResult{18.f, 24.f, 33.f, 1};
    ASSERT_EQ(mat*p, expectedResult);
}

TEST(matrix, should_not_change_after_mulitplication_by_identity_matrix)
{
    Mat4 mat{1.f, 2.f, 3.f, 4.f,
             2.f, 4.f, 4.f, 2.f,
             8.f, 6.f, 4.f, 1.f,
             0.f, 0.f, 0.f, 1.f};
    ASSERT_EQ(mat*matrix::identity4, mat);
}

TEST(matrix, should_support_transposition)
{
    Mat3 mat{0.f, 2.f, 3.f,
             9.f, 8.f, 0.f,
             1.f, 8.f, 5.f};
    Mat3 transposed{0.f, 9.f, 1.f,
                    2.f, 8.f, 8.f,
                    3.f, 0.f, 5.f};
    auto cpOfIdMatrix{matrix::identity4};
    ASSERT_EQ(transpose(std::move(mat)), transposed);
    ASSERT_EQ(transpose(std::move(cpOfIdMatrix)), matrix::identity4);
}

TEST(matrix, calculate_determinant_of_2D_matrix)
{
    Mat2 m{1.f, 5.f,
           -3.f, 2.f};
    const float expectedResult{17};
    ASSERT_EQ(determinant(std::move(m)), expectedResult);
}

TEST(matrix, produce_submatrix)
{
    Mat3 m{1.f, 5.f, 0.f,
           -3.f, 2.f, 7.f,
           0.f, 6.f, -3.f};
    Mat2 expectedResult{-3.f, 2.f,
                        0.f, 6.f};
    ASSERT_EQ(submatrix(m,0,2), expectedResult);
    Mat4 m2{-6.f, 1.f, 1.f, 6.f,
            -8.f, 5.f, 8.f, 6.f,
            -1.f, 0.f, 8.f, 2.f,
            -7.f, 1.f, -1.f, 1.f};
    Mat3 result{-6.f, 1.f, 6.f,
                -8.f, 8.f, 6.f,
                -7.f, -1.f, 1.f};
    ASSERT_EQ(submatrix(m2,2,1), result);
}

TEST(matrix, calculate_minor)
{
    Mat3 m{3.f, 5.f, 0.f,
           2.f, -1.f, -7.f,
           6.f, -1.f, 5.f};
    const float expectedMinor{25};
    ASSERT_EQ(minor(m,1,0), expectedMinor);
}

TEST(matrix, calculate_cofactor)
{
    Mat3 m{3.f, 5.f, 0.f,
           2.f, -1.f, -7.f,
           6.f, -1.f, 5.f};
    ASSERT_EQ(minor(m,0,0), -12);
    ASSERT_EQ(cofactor(m,0,0), -12);
    ASSERT_EQ(minor(m,1,0), 25);
    ASSERT_EQ(cofactor(m,1,0), -25);

    Mat3 m2{1.f, 2.f, 6.f,
            -5.f, 8.f, -4.f,
            2.f, 6.f, 4.f};
    ASSERT_EQ(cofactor(m2,0,0), 56);
    ASSERT_EQ(cofactor(m2,0,1), 12);
    ASSERT_EQ(cofactor(m2,0,2), -46);
    ASSERT_EQ(determinant(std::move(m2)), -196);

    Mat4 m3{-2.f, -8.f, 3.f, 5.f,
            -3.f, 1.f, 7.f, 3.f,
            1.f, 2.f, -9.f, 6.f,
            -6.f, 7.f, 7.f, -9.f};
    ASSERT_EQ(cofactor(m3,0,0), 690);
    ASSERT_EQ(cofactor(m3,0,1), 447);
    ASSERT_EQ(cofactor(m3,0,2), 210);
    ASSERT_EQ(cofactor(m3,0,3), 51);
    ASSERT_EQ(determinant(std::move(m3)), -4071);
}

TEST(matrix, should_support_invertibility_testing)
{
    Mat4 m1{6.f, 4.f, 4.f, 4.f,
            5.f, 5.f, 7.f, 6.f,
            4.f, -9.f, 3.f, -7.f,
            9.f, 1.f, 7.f, -6.f};
    ASSERT_TRUE(isInvertible(m1));
    Mat4 m2{-4.f, 2.f, -2.f, -3.f,
            9.f, 6.f, 2.f, 6.f,
            0.f, -5.f, 1.f, -5.f,
            0.f, 0.f, 0.f, 0.f};
    ASSERT_FALSE(isInvertible(m2));
}

TEST(matrix, should_support_inverse_operation)
{
    Mat4 m{-5.f, 2.f, 6.f, -8.f,
           1.f, -5.f, 1.f, 8.f,
           7.f, 7.f, -6.f, -7.f,
           1.f, -3.f, 7.f, 4.f};
    Mat4 expectedResult{ 0.21805f,  0.45113f,  0.24061f, -0.04511f,
                        -0.80827f, -1.45676f, -0.44360f,  0.52068f,
                        -0.07894f, -0.22368f, -0.05263f,  0.19737f,
                        -0.52255f, -0.81390f, -0.30075f,  0.30640f};
    m = inverse(std::move(m));
    for (std::size_t x{0}; x < 4; ++x) {
       for (std::size_t y{0}; y < 4; ++y) {
           m.at(x, y) = std::ceil(m.at(x,y)*100000.f)/100000.f;
       }
    }
    ASSERT_EQ(m, expectedResult);

//    Mat4 m1{3.f, -9.f, 7.f, 3.f,
//            3.f, -8.f, 2.f, -9.f,
//            -4.f, 4.f, 4.f, 1.f,
//            -6.f, 5.f, -1.f, 1.f};
//    Mat4 m2{8.f, 2.f, 2.f, 2.f,
//            3.f, -1.f, 7.f, 0.f,
//            7.f, 0.f, 5.f, 4.f,
//            6.f, -2.f, 0.f, 5.f};
//    auto multi = m1*m2;
//    m2.inverse();
//    ASSERT_EQ(multi*m2, m1);
}
