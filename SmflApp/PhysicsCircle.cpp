#include "PhysicsCircle.h"
#include "SfColor.h"

constexpr auto RADIUS = 25;

PhysicsCircle::PhysicsCircle(float x, float y, int hue) : shape(RADIUS), velocity(0, 0), mass(1)
{
    shape.setFillColor(SfColor::fromHSV(hue, 1, 1));
    shape.setPosition(x, y);
}

void PhysicsCircle::applyMotion(sf::Time delta)
{
    applyMotion(delta, sf::Vector2f(0, 0));
}

void PhysicsCircle::applyMotion(sf::Time delta, sf::Vector2f force)
{
    auto a = force / mass;
    velocity += delta.asSeconds() * a;
    auto p = shape.getPosition();
    p += delta.asSeconds() * velocity;
    shape.setPosition(p);
}



