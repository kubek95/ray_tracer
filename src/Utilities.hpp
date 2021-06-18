#pragma once

#include <limits>

auto relativelyEqual(float a,
                     float b,
                     float maxRelativeDiff =
                        std::numeric_limits<float>::epsilon()) -> bool;
