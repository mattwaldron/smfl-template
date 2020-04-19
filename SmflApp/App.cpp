#include<thread>
#include<chrono>
#include "App.h"

App::App() : _window(sf::VideoMode(800, 600), "SFML APP")
{
	_window.setVerticalSyncEnabled(true);	// Guidance is to not use this with setFramerateLimit, but
											// not sure how to get expected framerate otherwise
}

void App::run() 
{
	sf::Clock clock;
	while (_window.isOpen()) {
		auto delta = clock.restart();
		update(delta);
		render();
		processEvents(); // do this last, since we might close the window
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
		else {
			handleEvent(e);
		}
	}
}

void App::render()
{
	// clear and display are universal, so draw is overriden
	_window.clear(); // this is pretty universal
	draw(_window);
	_window.display();	// this is also universal
}

void App::handleEvent(const sf::Event &ev) {

}

void App::update(const sf::Time &delta) {

}

void App::draw(sf::RenderTarget &wnd) {

}


