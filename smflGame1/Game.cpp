#include<thread>
#include<chrono>
#include "Game.h"

static int nextHue = 0;

using namespace std::chrono_literals;

Game::Game() : _window(sf::VideoMode(800, 600), "SFML APP"), _circles()
{
}

void Game::run() 
{
	while (_window.isOpen()) {
		processEvents();
		update();
		render();
		std::this_thread::sleep_for(10ms);
	}
}

void Game::processEvents()
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

void Game::update()
{
	if (_circles.size() <= 1) {
		return;
	}
	sf::Vector2f center(0, 0);
	for (auto& c : _circles) {
		center += c.getPosition();
	}
	center = center / (float)_circles.size();

	for (auto& c : _circles) {
		auto d = (c.getPosition() - center);
		auto d_squared = 200.f;
		c.velocity -= (d / d_squared);
		c.setPosition(c.getPosition() + (c.velocity));
	}
}

void Game::render()
{
	_window.clear();
    for(auto & c : _circles) {
        _window.draw(c.graphic);
    }
	_window.display();
}


