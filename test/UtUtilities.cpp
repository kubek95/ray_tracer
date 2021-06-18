#include "Utilities.hpp"
#include "gtest/gtest.h"

TEST(utils, should_correctly_check_equality)
{
    constexpr float f1{3.f};
    constexpr float goodEnoughPrec{10e-5f};
    ASSERT_FALSE(f1 == f1+goodEnoughPrec);
}
