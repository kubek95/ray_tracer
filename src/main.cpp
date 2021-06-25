#include "Vector.hpp"
#include "Point.hpp"
#include "Canvas.hpp"
#include "Color.hpp"
#include "Transformations.hpp"
#include "MathConsts.hpp"

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

auto throwStone(Canvas& canvas) -> void
{
    Environment env{Vec3{0.f, -3.f, 0}, Vec3{-0.1f, 0.f, 0.5f}};
    Projectile proj{Point3{0.f, 0.f, 0.f}, Vec3{7.f, 43.f, 0.f}};
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

}

auto drawClock(Canvas& canvas) -> void
{
    const float halfOfCanvHeight = static_cast<float>(canvas.height()/2);
    const float halfOfCanvWidth = static_cast<float>(canvas.width()/2);
    auto startPoint = Point4{0.f, halfOfCanvHeight - 30.f, 0.f, 1.f};
    auto degreeBetweenHours = mathConst::pi/6.f;
    Color color{1.f, 0.f, 0.f};

    for (float hour{0.f}; hour < 12.f; ++hour) {
        auto rotateOneHour = TransformationStacker().rotate_z(hour*degreeBetweenHours)
                                                    .translate(halfOfCanvWidth, halfOfCanvHeight, 0.f)
                                                    .getMatrix();
        auto hourPos = rotateOneHour*startPoint;
        try{
            canvas.setPixel(static_cast<std::size_t>(hourPos.at(0)),
                            canvas.height()-static_cast<std::size_t>(hourPos.at(1)),
                            color);
        } catch (const std::runtime_error& r) {
            std::cout << "Point outside of canvas";
        }
    }
}

#ifdef UNIT_TEST
int uut_main()
#else
int main()
#endif
{
    Canvas canvas{300, 300, Color{0.1f, 0.1f, 0.1f}};
    drawClock(canvas);
    canvas.saveToFile("./shot.ppm");
    return 0;
}
