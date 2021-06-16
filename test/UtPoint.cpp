#include "Point.hpp"
#include "Vector.hpp"

#include "gtest/gtest.h"

TEST(Point, copy_should_be_the_same_as_original)
{
    Point p1{1.f, 2.f, 3.f};
    Point p2 = p1;
    Point p3{p2};
    ASSERT_EQ(p1.x(), p2.x());
    ASSERT_EQ(p1.y(), p2.y());
    ASSERT_EQ(p1.z(), p2.z());
    ASSERT_EQ(p2.x(), p3.x());
    ASSERT_EQ(p2.y(), p3.y());
    ASSERT_EQ(p2.z(), p3.z());
}

TEST(Point, subtraction_should_produce_vector)
{
    Point p1{3.f, 2.f, 1.f};
    Point p2{5.f, 6.f, 7.f};
    Vec3 expected_result{-2.f, -4.f, -6.f};
    const auto result = p1-p2;
    EXPECT_EQ(result, expected_result);
}

TEST(Point, comparison_should_work_with_given_precision)
{
    Point p1{1.f, 2.f, 3.f};
    constexpr float sufficientPrecision{10e-5f};
    Point p2{1.f, 2.f+sufficientPrecision, 3.f};
    ASSERT_FALSE(p1 == p2);
}
TEST(Point, subtraction_of_a_vector_from_a_point_should_produce_a_point)
{
    Point p1{3.f, 2.f, 1.f};
    Vec3 v1{5.f, 6.f, 7.f};
    Point expected_result{-2.f, -4.f, -6.f};
    const auto result = p1-v1;
    ASSERT_EQ(result, expected_result);
}
