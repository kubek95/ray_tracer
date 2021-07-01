#include "Sphere.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

#include <algorithm>
#include <cmath>

std::size_t Sphere::counter{0};

auto Sphere::intersect(const Ray& ray) const -> std::vector<float>
{
    const auto sphereToRay{ray.origin() - Point4{0.f, 0.f, 0.f, 1.f}};
    const auto a{ray.direction().dot(ray.direction())};
    const auto b{ray.direction().dot(sphereToRay)*2.f};
    const auto c{sphereToRay.dot(sphereToRay)-1.f};
    const auto discriminant{std::pow(b,2.f)-4*a*c};
    if (discriminant < 0) {
        return {};
    }
    std::vector<float> tmp{(-b-std::sqrt(discriminant))/2.f*a,
                           (-b+std::sqrt(discriminant))/2.f*a};
    return tmp;
}

auto Sphere::id() const -> std::size_t
{
    return _id;
}
