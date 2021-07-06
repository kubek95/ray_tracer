#include "Transformations.hpp"
#include "Point.hpp"
#include "MathConsts.hpp"

#include "gtest/gtest.h"
#include <cmath>

template<std::size_t size>
auto roundPoint(Point<size>& mat) -> Point<size>&
{
    for(std::size_t column{0}; column < size; ++column) {
        mat.at(column) = std::floor(mat.at(column)*10e5f)/10e5f;
    }
    return mat;
}

TEST(transformations, create_correct_translation_matrix)
{
    auto transform = translation(5.f, -3.f, 2.f);
    auto p = Point4{-3.f, 4.f, 5.f, 1.f};
    auto translationResult = Point4{2.f, 1.f, 7.f, 1.f};
    ASSERT_EQ(transform*p, translationResult);
}

TEST(transformations, inverse_of_translation_matrix_should_move_point_in_reverse)
{
    auto transform = translation(5.f, -3.f, 2.f);
    auto p = Point4{-3.f, 4.f, 5.f, 1.f};
    auto translationResult = Point4{-8.f, 7.f, 3.f, 1.f};
    ASSERT_EQ(inverse(transform)*p, translationResult);
}

TEST(transformations, translation_should_not_change_vector)
{
    auto transform = translation(5.f, -3.f, 2.f);
    auto vec = Vec4{-3.f, 4.f, 5.f, 0.f};
    ASSERT_EQ(transform*vec, vec);
}

TEST(transformations, scaling)
{
    auto transform = scaling(2.f, 3.f, 4.f);
    auto p = Point4{-4.f, 6.f, 8.f, 1.f};
    auto scalingResult = Point4{-8.f, 18.f, 32.f, 1.f};
    ASSERT_EQ(transform*p, scalingResult);

    auto v = Vec4{-4.f, 6.f, 8.f, 0.f};
    auto scalingvResult = Vec4{-8.f, 18.f, 32.f, 0.f};
    ASSERT_EQ(transform*v, scalingvResult);

    auto scalingByInversetResult = Vec4{-2.f, 2.f, 2.f, 0.f};
    ASSERT_EQ(inverse(transform)*v, scalingByInversetResult);
}

TEST(transformations, reflection)
{
    auto transform = scaling(-1.f, 1.f, 1.f);
    auto p = Point4{2.f, 3.f, 4.f, 1.f};
    auto expectedResult = Point4{-2.f, 3.f, 4.f, 1.f};
    ASSERT_EQ(transform*p, expectedResult);
}

TEST(transformations, rotations)
{
    auto p = Point4{0.f, 1.f, 0.f, 1.f};
    auto p_y = Point4{0.f, 0.f, 1.f, 1.f};
    auto half_quarter_x = rotation_x(mathConst::pi/4.f);
    auto half_quarter_y = rotation_y(mathConst::pi/4.f);
    auto half_quarter_z = rotation_z(mathConst::pi/4.f);
    auto resX = Point4{0.f, std::sqrt(2.f)/2, std::sqrt(2.f)/2, 1.f};
    auto resY = Point4{std::sqrt(2.f)/2, 0.f, std::sqrt(2.f)/2, 1.f};
    auto resZ = Point4{-std::sqrt(2.f)/2, std::sqrt(2.f)/2, 0.f, 1.f};

    EXPECT_EQ(half_quarter_x*p, resX);
    EXPECT_EQ(half_quarter_y*p_y, resY);
    EXPECT_EQ(half_quarter_z*p, resZ);
}

TEST(transformations, shearing)
{
    auto transform = shearing(1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
    auto p = Point4{2.f, 3.f, 4.f, 1.f};
    auto expectedResult = Point4{5.f, 3.f, 4.f, 1.f};
    ASSERT_EQ(transform*p, expectedResult);

    transform = shearing(0.f, 1.f, 0.f, 0.f, 0.f, 0.f);
    expectedResult = Point4{6.f, 3.f, 4.f, 1.f};
    ASSERT_EQ(transform*p, expectedResult);

    transform = shearing(0.f, 0.f, 1.f, 0.f, 0.f, 0.f);
    expectedResult = Point4{2.f, 5.f, 4.f, 1.f};
    ASSERT_EQ(transform*p, expectedResult);

    transform = shearing(0.f, 0.f, 0.f, 1.f, 0.f, 0.f);
    expectedResult = Point4{2.f, 7.f, 4.f, 1.f};
    ASSERT_EQ(transform*p, expectedResult);

    transform = shearing(0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
    expectedResult = Point4{2.f, 3.f, 6.f, 1.f};
    ASSERT_EQ(transform*p, expectedResult);

    transform = shearing(0.f, 0.f, 0.f, 0.f, 0.f, 1.f);
    expectedResult = Point4{2.f, 3.f, 7.f, 1.f};
    ASSERT_EQ(transform*p, expectedResult);
}

TEST(transformations, transformations_stacking)
{
    auto p = Point4{1.f, 0.f, 1.f, 1.f};
    auto rot_mat = rotation_x(mathConst::pi/2.f);
    auto scal_mat = scaling(5.f, 5.f, 5.f);
    auto transl_mat = translation(10.f, 5.f, 7.f);

    auto exp_result = rot_mat*p;
    exp_result = scal_mat*exp_result;
    exp_result = transl_mat*exp_result;

    auto result = TransformationStacker().rotate_x(mathConst::pi/2.f)
                                         .scale(5.f, 5.f, 5.f)
                                         .translate(10.f, 5.f, 7.f)
                                         .getMatrix();
    ASSERT_EQ(result*p, exp_result);
}
