#pragma once

#include "App.h"
#include "SfGeometry.h"
#include "SfColor.h"

#include <algorithm>
#include <functional>

static int nextHue = 0;

class GravitySim : public App {
public:
	GravitySim() : _circles() {}

    virtual void handleEvent(const sf::Event &ev) {
		if (ev.type == sf::Event::MouseButtonPressed) {
			if (ev.mouseButton.button == sf::Mouse::Button::Right) {
				_circles.clear();
			}
			else {
				PhysicsCircle c(ev.mouseButton.x, ev.mouseButton.y, SfColor::fromHSV(nextHue, 1, 1));
				_circles.push_back(c);
				nextHue += 50;
			}
		}
    }

	virtual void update(const sf::Time &delta) {
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
			c.applyMotion(delta, attraction_constant * (_circles.size() - 1) * (center - c.getPosition()));
		}
	}

	virtual void draw(sf::RenderTarget&wnd) {
		for (auto& c : _circles) {
			wnd.draw(c.shape);
		}
	}

private:
	std::vector<PhysicsCircle> _circles;
};