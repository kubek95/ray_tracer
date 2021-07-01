#include "Ray.hpp"
#include "Point.hpp"
#include "Vector.hpp"

#include "gtest/gtest.h"

TEST(ray, query_about_origin_and_direction)
{
    const Point4 origin{1.f, 2.f, 3.f, 1.f};
    const Vec4 direction{4.f, 5.f, 6.f, 0.f};
    const Ray ray{origin, direction};
    ASSERT_EQ(ray.origin(), origin);
    ASSERT_EQ(ray.direction(), direction);
}

TEST(ray, calculate_position)
{
    const Ray r{Point4{2.f, 3.f, 4.f, 1.f}, Vec4{1.f, 0.f, 0.f, 0.f}};
    auto expectedResult{Point4{2.f, 3.f, 4.f, 1.f}};
    ASSERT_EQ(r.position(0.f), expectedResult);
    expectedResult.at(0) = 3.f;
    ASSERT_EQ(r.position(1.f), expectedResult);
    expectedResult.at(0) = 1.f;
    ASSERT_EQ(r.position(-1.f), expectedResult);
    expectedResult.at(0) = 4.5f;
    ASSERT_EQ(r.position(2.5f), expectedResult);
}
