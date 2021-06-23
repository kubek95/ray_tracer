#pragma once
#include "Matrix.hpp"

auto translation(float x, float y, float z) -> Mat4;
auto scaling(float x, float y, float z) -> Mat4;
auto rotation_x(float rad) -> Mat4;
auto rotation_y(float rad) -> Mat4;
auto rotation_z(float rad) -> Mat4;
auto shearing(float x_y,float x_z,float y_x,float y_z,float z_x,float z_y) -> Mat4;
