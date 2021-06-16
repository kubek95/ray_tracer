#include "Point.hpp"
#include "Vector.hpp"
#include "gtest/gtest.h"

TEST(vector, should_be_the_same_as_its_copy)
{
    Vec3 v1{1.f, 2.f, 3.f};
    Vec3 v2(v1);
    Vec3 v3 = v2;
    ASSERT_EQ(v1.x(), v2.x());
    ASSERT_EQ(v1.y(), v2.y());
    ASSERT_EQ(v1.z(), v2.z());
    ASSERT_EQ(v2.x(), v3.x());
    ASSERT_EQ(v2.y(), v3.y());
    ASSERT_EQ(v2.z(), v3.z());
}

TEST(vector, should_be_the_same_after_moving)
{
    float x{1.f};
    float y{2.f};
    float z{3.f};
    Vec3 v1{x, y, z};
    Vec3 v2 = std::move(v1);
    ASSERT_EQ(v1.x(), x);
    ASSERT_EQ(v1.y(), y);
    ASSERT_EQ(v1.z(), z);
    Vec3 v3{std::move(v2)};
    ASSERT_EQ(v3.x(), x);
    ASSERT_EQ(v3.y(), y);
    ASSERT_EQ(v3.z(), z);
}

TEST(vector, should_correctly_check_equality)
{
    Vec3 v1{3.f, 2.f, 3.f};
    constexpr float goodEnoughPrec{10e-5f};
    Vec3 v2{3.f+goodEnoughPrec, 2.f, 3.f};
    ASSERT_FALSE(v1 == v2);
}

TEST(vector, should_produce_vector_after_addition_with_point)
{
    Vec3 v1{3.f, -2.f, 5.f};
    Point p1{-2.f, 3.f, 1.f};
    v1 = v1+p1;
    ASSERT_EQ(v1.x(), 1.f);
    ASSERT_EQ(v1.y(), 1.f);
    ASSERT_EQ(v1.z(), 6.f);
}
