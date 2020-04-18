#include<thread>
#include<chrono>
#include "App.h"
#include "SfGeometry.h"

#include <algorithm>
#include <functional>

static int nextHue = 0;
using namespace std::chrono_literals;

App::App() : _window(sf::VideoMode(800, 600), "SFML APP"), _circles()
{
	_window.setVerticalSyncEnabled(true);	// Guidance is to not use this with setFramerateLimit, but
											// not sure how to get expected framerate otherwise
}

void App::run() 
{
	sf::Clock clock;
	while (_window.isOpen()) {
		auto delta = clock.restart();
		processEvents();
		update(delta);
		render();
	}
}

// Use processEvents to gather user input and modify the objects within App
void App::processEvents()
{
	sf::Event e;
	while (_window.pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			_window.close();
		}
		else if (e.type == sf::Event::MouseButtonPressed) {
			if (e.mouseButton.button == sf::Mouse::Button::Right) {
				_circles.clear();
			}
			else {
				PhysicsCircle c(e.mouseButton.x, e.mouseButton.y, nextHue);
				_circles.push_back(c);
				nextHue += 50;
			}
		}
	}
}

// Update should modify the objects within App according to the time elapsed since
// the last render (e.g.: physics, changes derived from new user input).
void App::update(sf::Time delta)
{
	const float attraction_constant = 5.0f;
	if (_circles.size() <= 1) {
		return;
	}

	std::vector<sf::Vector2f> points;
	points.resize(_circles.size());
	std::transform(_circles.begin(), _circles.end(), points.begin(), std::mem_fn(&PhysicsCircle::getPosition));

	auto center = SfGeometry::centerOfMass(points);

	for (auto& c : _circles)
	{
		c.applyMotion(delta, attraction_constant * (_circles.size()-1) * (center - c.getPosition()));
	}
}

// Render should call draw for the objects in scene.
void App::render()
{
	_window.clear(); // this is pretty universal

    for(auto & c : _circles) {
        _window.draw(c.shape);
    }

	_window.display();	// this is also universal
}


