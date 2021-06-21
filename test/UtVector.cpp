#include "Point.hpp"
#include "Vector.hpp"
#include "gtest/gtest.h"

#include <cmath>

TEST(vector, should_correctly_check_equality)
{
    Vec3 v1{3.f, 2.f, 3.f};
    constexpr float goodEnoughPrec{10e-5f};
    Vec3 v2{3.f+goodEnoughPrec, 2.f, 3.f};
    ASSERT_FALSE(v1 == v2);
}

TEST(vector, should_produce_point_after_addition_with_point)
{
    Vec3 v1{3.f, -2.f, 5.f};
    Point3 p1{-2.f, 3.f, 1.f};
    Point3 expected_result{1.f, 1.f, 6.f};
    ASSERT_EQ(v1+p1, expected_result);
}

TEST(vector, subtraction_of_two_vectors_produce_vector)
{
    Vec3 v1{3.f, 2.f, 1.f};
    Vec3 v2{5.f, 6.f, 7.f};
    Vec3 expected_result{-2.f, -4.f, -6.f};
    ASSERT_EQ(v1-v2, expected_result);
}

TEST(vector, should_support_negation)
{
    Vec3 v1{-3.f, 5.f, 2.f};
    Vec3 expected_result{3.f, -5.f, -2.f};
    ASSERT_EQ(-v1, expected_result);
}

TEST(vector, should_support_multiplication_by_scalar)
{
    Vec3 v1{1.f, -2.f, 3.f};
    float scalar{3.5f};
    Vec3 expected_result{3.5f, -7.f, 10.5f};
    ASSERT_EQ(v1*scalar, expected_result);
}

TEST(vector, should_support_division_by_scalar)
{
    Vec3 v1{1.f, -2.f, 3.f};
    float scalar{2};
    Vec3 expected_result{0.5f, -1.f, 1.5f};
    ASSERT_EQ(v1/scalar, expected_result);
}

TEST(vector, should_support_magnitude_quantification)
{
    float expected_magnitude{1.f};
    Vec3 v1{1.f,0.f,0.f};
    Vec3 v2{0.f,1.f,0.f};
    Vec3 v3{0.f,0.f,1.f};
    ASSERT_EQ(v1.magnitude(), expected_magnitude);
    ASSERT_EQ(v2.magnitude(), expected_magnitude);
    ASSERT_EQ(v3.magnitude(), expected_magnitude);
    expected_magnitude = std::sqrt(14.f);
    Vec3 v4{1.f,2.f,3.f};
    Vec3 v5{-1.f,-2.f,-3.f};
    ASSERT_EQ(v4.magnitude(), expected_magnitude);
    ASSERT_EQ(v5.magnitude(), expected_magnitude);
}

TEST(vector, should_support_normalization)
{
    Vec3 v1{4.f, 0.f, 0.f};
    Vec3 expected_result{1.f, 0.f, 0.f};
    ASSERT_EQ(v1.normalize(), expected_result);

    Vec3 v2{1.f, 2.f, 3.f};
    expected_result = Vec3{1/std::sqrt(14.f), 2/std::sqrt(14.f), 3/std::sqrt(14.f)};
    ASSERT_EQ(v2.normalize(), expected_result);

    ASSERT_EQ(v1.normalize().magnitude(), 1);
    ASSERT_EQ(v2.normalize().magnitude(), 1);
}

TEST(vector, should_support_dot_product)
{
    Vec3 v1{1.f, 2.f, 3.f};
    Vec3 v2{2.f, 3.f, 4.f};
    const auto expected_result{20.f};
    ASSERT_EQ(v1.dot(v2), expected_result);
}

TEST(vector, should_support_cross_product)
{
    Vec3 v1{1.f, 2.f, 3.f};
    Vec3 v2{2.f, 3.f, 4.f};
    Vec3 v1Crossv2{-1.f, 2.f, -1.f};
    Vec3 v2Crossv1{1.f, -2.f, 1.f};
    ASSERT_EQ(v1.cross(v2), v1Crossv2);
    v1 = Vec3{1.f, 2.f, 3.f};
    ASSERT_EQ(v2.cross(v1), v2Crossv1);
}

TEST(vector, addition_of_two_vectors_should_produce_a_vector)
{
    Vec3 v1{3.f, 2.f, 1.f};
    Vec3 v2{5.f, 6.f, 7.f};
    Vec3 expected_result{8.f, 8.f, 8.f};
    ASSERT_EQ(v1+v2, expected_result);
    ASSERT_EQ(v2+v1, expected_result);
}
