#pragma once

#include <cstdint>
#include <vector>

class Ray;

class Sphere
{
    public:
        auto intersect(const Ray& ray) const -> std::vector<float>;
        auto id() const -> std::size_t;

    private:
        static std::size_t counter;
        const std::size_t _id{counter++};
};
