#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicsCircle.h"

class App
{
public:
    App();
    void run();

private:
    void processEvents();
    void update(sf::Time delta);
    void render();

    sf::RenderWindow _window;
    std::vector<PhysicsCircle> _circles;
};