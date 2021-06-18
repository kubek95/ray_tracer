#include "Color.hpp"

#include "gtest/gtest.h"

TEST(color, test_color_getters)
{
    Color color{-0.5f, 0.4f, 1.7f};
    ASSERT_EQ(color.r(), -0.5f);
    ASSERT_EQ(color.g(), 0.4f);
    ASSERT_EQ(color.b(), 1.7f);
}

TEST(color, should_support_addition)
{
    Color c1{0.9f, 0.6f, 0.75f};
    Color c2{0.7f, 0.1f, 0.25f};
    Color expected_result{1.6f, 0.7f, 1.f};
    ASSERT_EQ(c1+c2, expected_result);
}

TEST(color, should_support_subtraction)
{
    Color c1{0.9f, 0.6f, 0.75f};
    Color c2{0.7f, 0.1f, 0.25f};
    Color expected_result{0.2f, 0.5f, 0.5f};
    ASSERT_EQ(c1-c2, expected_result);
}

TEST(color, should_support_multiplication_by_scalar)
{
    Color c1{0.2f, 0.3f, 0.4f};
    const float scalar{2.f};
    Color expected_result{0.4f, 0.6f, 0.8f};
    ASSERT_EQ(c1*scalar, expected_result);
}

TEST(color, should_support_multiplication_by_another_color)
{
    Color c1{1.f, 0.2f, 0.4f};
    Color c2{0.9f, 1.f, 0.1f};
    Color expected_result{0.9f, 0.2f, 0.04f};
    ASSERT_EQ(c1*c2, expected_result);
}
