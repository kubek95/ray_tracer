#include "Point.hpp"
#include "Vector.hpp"

#include "gtest/gtest.h"

TEST(Point, copy_should_be_the_same_as_original)
{
    Point3 p1{1.f, 2.f, 3.f};
    Point3 p2 = p1;
    Point3 p3{p2};
    ASSERT_EQ(p1.at(0), p2.at(0));
    ASSERT_EQ(p1.at(1), p2.at(1));
    ASSERT_EQ(p1.at(2), p2.at(2));
    ASSERT_EQ(p2.at(0), p3.at(0));
    ASSERT_EQ(p2.at(1), p3.at(1));
    ASSERT_EQ(p2.at(2), p3.at(2));
}

TEST(Point, should_produce_vector_after_addition_with_vector)
{
    Vec3 v1{3.f, -2.f, 5.f};
    Point3 p1{-2.f, 3.f, 1.f};
    v1 = p1+v1;
    ASSERT_EQ(v1.at(0), 1.f);
    ASSERT_EQ(v1.at(1), 1.f);
    ASSERT_EQ(v1.at(2), 6.f);
}

TEST(Point, subtraction_should_produce_vector)
{
    Point3 p1{3.f, 2.f, 1.f};
    Point3 p2{5.f, 6.f, 7.f};
    Vec3 expected_result{-2.f, -4.f, -6.f};
    const auto result = p1-p2;
    EXPECT_EQ(result, expected_result);
}

TEST(Point, comparison_should_work_with_given_precision)
{
    Point3 p1{1.f, 2.f, 3.f};
    constexpr float sufficientPrecision{10e-5f};
    Point3 p2{1.f, 2.f+sufficientPrecision, 3.f};
    ASSERT_FALSE(p1 == p2);
}

TEST(Point, subtraction_of_a_vector_from_a_point_should_produce_a_point)
{
    Point3 p1{3.f, 2.f, 1.f};
    Vec3 v1{5.f, 6.f, 7.f};
    Point3 expected_result{-2.f, -4.f, -6.f};
    const auto result = p1-v1;
    ASSERT_EQ(result, expected_result);
}
