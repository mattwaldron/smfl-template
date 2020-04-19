#pragma once

#include "App.h"
#include "SfGeometry.h"

class BezierDraw : public App {
public:
    BezierDraw() : _points(), _bezierTrace() {}


    virtual void handleEvent(const sf::Event& ev) {
        if (ev.type == sf::Event::MouseButtonPressed) {
			if (ev.mouseButton.button == sf::Mouse::Button::Right) {
				_points.clear();
			}
			else {
				_points.push_back(sf::Vector2f(ev.mouseButton.x,  ev.mouseButton.y));
				_tracePercent = 0;
				_bezierTrace.clear();
			}
		}
    }

	virtual void update(const sf::Time& delta) {
		_tracePercent += delta.asMilliseconds() / _traceDuration_ms;
		_tracePercent = std::min(_tracePercent, 1.0f);
		_bezierTrace.push_back(SfGeometry::bezier(_points, _tracePercent));
	}

	virtual void draw(sf::RenderTarget& wnd) {
		for(auto & p : _points) {
			const float radius = 5;
			auto c = sf::CircleShape(radius);
			c.setPosition(p.x - radius, p.y - radius);
			c.setFillColor(sf::Color::Cyan);
			wnd.draw(c);
		}
		if (_points.size() <= 1) {
			return;
		}
		std::vector<sf::Vertex> vertices(_bezierTrace.size());
		for (size_t i = 0; i < vertices.size(); ++i) {
			vertices[i] = sf::Vertex(_bezierTrace[i]);
		}
		wnd.draw(vertices.data(), vertices.size(), sf::PrimitiveType::LineStrip);
	}

private:
    std::vector<sf::Vector2f> _points;
	std::vector<sf::Vector2f> _bezierTrace;
	float _tracePercent = 0;
	const float _traceDuration_ms = 2000;
};