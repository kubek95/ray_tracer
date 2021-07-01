#include "Sphere.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Ray.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>

TEST(sphere, get_id)
{
    auto s1 = Sphere();
    auto s2 = Sphere();
    auto s3 = Sphere();

    ASSERT_EQ(s1.id(), 0);
    ASSERT_EQ(s2.id(), 1);
    ASSERT_EQ(s3.id(), 2);
}

TEST(sphere, intersect_with_ray_at_two_points)
{
    const auto ray = Ray{Point4{0.f, 0.f, -5.f, 1.f}, Vec4{0.f, 0.f, 1.f, 0.f}};
    const auto sphere = Sphere();
    ASSERT_THAT(sphere.intersect(ray), ::testing::ElementsAre(4.f, 6.f));
}

TEST(sphere, intersect_with_ray_at_one_point)
{
    const auto ray = Ray{Point4{0.f, 1.f, -5.f, 1.f}, Vec4{0.f, 0.f, 1.f, 0.f}};
    const auto sphere = Sphere();
    ASSERT_THAT(sphere.intersect(ray), ::testing::ElementsAre(5.f, 5.f));
}

TEST(sphere, does_not_intersect_with_ray)
{
    const auto ray = Ray{Point4{0.f, 2.f, -5.f, 1.f}, Vec4{0.f, 0.f, 1.f, 0.f}};
    const auto sphere = Sphere();
    ASSERT_TRUE(sphere.intersect(ray).empty()); 
}

TEST(sphere, intersects_at_two_points_when_ray_source_is_inside_sphere)
{
    const auto ray = Ray{Point4{0.f, 0.f, 0.f, 1.f}, Vec4{0.f, 0.f, 1.f, 0.f}};
    const auto sphere = Sphere();
    ASSERT_THAT(sphere.intersect(ray), ::testing::ElementsAre(-1.f, 1.f));
}

TEST(sphere, intersects_at_two_points_when_sphere_is_behind_ray_origin)
{
    const auto ray = Ray{Point4{0.f, 0.f, 5.f, 1.f}, Vec4{0.f, 0.f, 1.f, 0.f}};
    const auto sphere = Sphere();
    ASSERT_THAT(sphere.intersect(ray), ::testing::ElementsAre(-6.f, -4.f));
}
