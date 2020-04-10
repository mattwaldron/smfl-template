#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicsCircle.h"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow _window;
    std::vector<PhysicsCircle> _circles;
};