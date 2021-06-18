#include "Vector.hpp"
#include "Point.hpp"

#include <iostream>

struct Projectile
{
    Point position;
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
    Environment env{Vec3{0.f, -3.f, 0}, Vec3{1.f, 0.f, 0.5f}};
    Projectile proj{Point{0.f, 10.f, 0.f}, Vec3{7.f, 33.f, 0.f}};
    do {
        printProjectilePosition(proj);
        tick(env, proj);
    } while(proj.position.y() >= 0.f);
    return 0;
}
