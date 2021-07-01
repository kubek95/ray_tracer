#pragma once

#include "Matrix.hpp"

auto translation(float x, float y, float z) -> Mat4;
auto scaling(float x, float y, float z) -> Mat4;
auto rotation_x(float rad) -> Mat4;
auto rotation_y(float rad) -> Mat4;
auto rotation_z(float rad) -> Mat4;
auto shearing(float x_y,float x_z,float y_x,float y_z,float z_x,float z_y) -> Mat4;

class TransformationStacker
{
    public:
        auto translate(float x, float y, float z) -> TransformationStacker&;
        auto scale(float x, float y, float z) -> TransformationStacker&;
        auto rotate_x(float rad) -> TransformationStacker&;
        auto rotate_y(float rad) -> TransformationStacker&;
        auto rotate_z(float rad) -> TransformationStacker&;
        auto shear(float x_y,float x_z,float y_x,float y_z,float z_x,float z_y) -> TransformationStacker&;
        auto getMatrix() -> Mat4;

    private:
        Mat4 _matrix{matrix::identity4};
};
