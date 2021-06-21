#include "Vector.hpp"
#include "Point.hpp"
#include "Canvas.hpp"
#include "Color.hpp"

#include <iostream>

struct Projectile
{
    Point3 position;
    Vec3 velocity;
};

struct Environment
{
    Vec3 gravity;
    Vec3 wind;
};

auto tick(const Environment& env, Projectile& p) -> void
{
    auto newPosition{p.velocity + p.position};
    auto newVelocity{p.velocity + env.gravity + env.wind};
    p.position = newPosition;
    p.velocity = newVelocity;
}

auto printProjectilePosition(const Projectile& p) -> void
{
    std::cout << p.position << '\n';
}

#ifdef UNIT_TEST
int uut_main()
#else
int main()
#endif
{
    Environment env{Vec3{0.f, -3.f, 0}, Vec3{-0.1f, 0.f, 0.5f}};
    Projectile proj{Point3{0.f, 0.f, 0.f}, Vec3{7.f, 43.f, 0.f}};
    Canvas canvas{300, 300, Color{0.1f, 0.1f, 0.1f}};
    Color projColor{1.f, 0.f, 0.f};
    do {
        printProjectilePosition(proj);
        try {
        canvas.setPixel(static_cast<std::size_t>(proj.position.at(0)),
                        canvas.height()-static_cast<std::size_t>(proj.position.at(1)),
                        projColor);
        } catch (std::runtime_error& e) {
        }
        tick(env, proj);
    } while(proj.position.at(1) >= 0.f);
    canvas.saveToFile("./shot.ppm");
    return 0;
}
