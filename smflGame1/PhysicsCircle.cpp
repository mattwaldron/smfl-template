#include "PhysicsCircle.h"

constexpr auto RADIUS = 25;

static sf::Color fromHSV(int hue, float sat, float val)
{
    hue %= 360;
    while (hue < 0) hue += 360;

    if (sat < 0.f) sat = 0.f;
    if (sat > 1.f) sat = 1.f;

    if (val < 0.f) val = 0.f;
    if (val > 1.f) val = 1.f;

    int h = hue / 60;
    float f = float(hue) / 60 - h;
    float p = val * (1.f - sat);
    float q = val * (1.f - sat * f);
    float t = val * (1.f - sat * (1 - f));

    switch (h)
    {
    default:
    case 0:
    case 6: return sf::Color(val * 255, t * 255, p * 255);
    case 1: return sf::Color(q * 255, val * 255, p * 255);
    case 2: return sf::Color(p * 255, val * 255, t * 255);
    case 3: return sf::Color(p * 255, q * 255, val * 255);
    case 4: return sf::Color(t * 255, p * 255, val * 255);
    case 5: return sf::Color(val * 255, p * 255, q * 255);
    }
}

PhysicsCircle::PhysicsCircle(float x, float y, int hue) : graphic(RADIUS), velocity(0, 0)
{
    graphic.setFillColor(fromHSV(hue, 1, 1));
    setPosition(x, y);
}

sf::Vector2f PhysicsCircle::getPosition()
{
    return _position;
}

void PhysicsCircle::setPosition(float x, float y)
{
    setPosition(sf::Vector2f(x, y));
}

void PhysicsCircle::setPosition(sf::Vector2f p) {
    _position = p;
    graphic.setPosition(p.x - RADIUS, p.y - RADIUS);
}

