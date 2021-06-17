#include "Vector.hpp"
#include "Point.hpp"

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

auto tick(const Environment& env, const Projectile& p) -> Projectile
{
    auto newPosition{p.velocity + p.position};
    auto newVelocity{p.velocity + env.gravity + env.wind};
    return Projectile{newPosition, newVelocity};
}

#ifdef UNIT_TEST
int uut_main()
#else
int main()
#endif
{
    return 0;
}
