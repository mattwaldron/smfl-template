#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicsCircle.h"

class App
{
public:
    App();
    void run();

protected:
    // processEvents polls for each new event and calls handleEvent for each.  handleEvent should be
    // overriden for application-specific processing.
    virtual void handleEvent(const sf::Event &ev);

    // update should modify the objects within the scene according to the time elapsed since
    // the last render (e.g.: physics, changes derived from new user input, etc.).
    virtual void update(const sf::Time &delta);

    // draw is called by render between clearing the frame and displaying.  The derived class need
    // only to draw its components to the screen.
    virtual void draw(sf::RenderTarget&wnd);

private:
    sf::RenderWindow _window;
    void processEvents();
    void render();
};