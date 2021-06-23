#include "Transformations.hpp"
#include <cmath>

auto translation(float x, float y, float z) -> Mat4
{
    auto temp = matrix::identity4;
    temp.at(0,3) = x;
    temp.at(1,3) = y;
    temp.at(2,3) = z;
    return temp;
}

auto scaling(float x, float y, float z) -> Mat4
{
    auto temp = matrix::identity4;
    temp.at(0,0) = x;
    temp.at(1,1) = y;
    temp.at(2,2) = z;
    return temp;
}

auto rotation_x(float rad) -> Mat4
{
    auto temp = matrix::identity4;
    temp.at(1,1) = std::cos(rad);
    temp.at(1,2) = -std::sin(rad);
    temp.at(2,1) = std::sin(rad);
    temp.at(2,2) = std::cos(rad);
    return temp;
}

auto rotation_y(float rad) -> Mat4
{
    auto temp = matrix::identity4;
    temp.at(0,0) = std::cos(rad);
    temp.at(0,2) = std::sin(rad);
    temp.at(2,0) = -std::sin(rad);
    temp.at(2,2) = std::cos(rad);
    return temp;
}

auto rotation_z(float rad) -> Mat4
{
    auto temp = matrix::identity4;
    temp.at(0,0) = std::cos(rad);
    temp.at(0,1) = -std::sin(rad);
    temp.at(1,0) = std::sin(rad);
    temp.at(1,1) = std::cos(rad);
    return temp;
}

auto shearing(float x_y,float x_z,float y_x,float y_z,float z_x,float z_y) -> Mat4
{
    auto temp = matrix::identity4;
    temp.at(0,1) = x_y;
    temp.at(0,2) = x_z;
    temp.at(1,0) = y_x;
    temp.at(1,2) = y_z;
    temp.at(2,0) = z_x;
    temp.at(2,1) = z_y;
    return temp;
}
