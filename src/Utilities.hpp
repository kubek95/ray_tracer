#pragma once

#include <cmath>
#include <cstdint>
#include <limits>

auto relativelyEqual(float a,
                     float b,
                     float maxRelativeDiff =
                        std::numeric_limits<float>::epsilon()) -> bool;
auto roundUp(float number) -> float;

