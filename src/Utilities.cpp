#include "Utilities.hpp"

auto relativelyEqual(float a,
                     float b,
                     float maxRelativeDiff) -> bool
{
    const auto diff = std::abs(a - b);
    a = std::abs(a);
    b = std::abs(b);
    const auto scaledEps = maxRelativeDiff * std::max(a, b);
    return diff <= scaledEps;
}

auto roundUp(float number) -> float
{
    return std::ceil(number*10e5)/10e5;
}
