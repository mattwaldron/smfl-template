#include<thread>
#include<chrono>
#include "App.h"

static int nextHue = 0;

using namespace std::chrono_literals;

App::App() : _window(sf::VideoMode(800, 600), "SFML APP"), _circles()
{
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

void App::update(sf::Time delta)
{
	const float attraction_constant = 10.0f;
	if (_circles.size() <= 1) {
		return;
	}
	sf::Vector2f center(0, 0);
	for (auto& c : _circles) {
		center += c.getPosition();
	}
	center = center / (float)_circles.size();

	for (auto& c : _circles)
	{
		c.applyMotion(delta, attraction_constant * (center - c.getPosition()));
	}
}

void App::render()
{
	_window.clear();
    for(auto & c : _circles) {
        _window.draw(c.shape);
    }
	_window.display();
}


