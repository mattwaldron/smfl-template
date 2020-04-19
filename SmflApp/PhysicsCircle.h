#pragma once
#include <SFML/Graphics.hpp>

constexpr auto RADIUS = 25;

class PhysicsCircle {
public:
	PhysicsCircle(float x, float y, sf::Color hue) : shape(RADIUS), velocity(0, 0), mass(1)
	{
		shape.setFillColor(hue);
		shape.setPosition(x, y);
	}
	
	void applyMotion(sf::Time delta){
		applyMotion(delta, sf::Vector2f(0, 0));
	}

	void applyMotion(sf::Time delta, sf::Vector2f force) {
		auto a = force / mass;
		velocity += delta.asSeconds() * a;
		auto p = shape.getPosition();
		p += delta.asSeconds() * velocity;
		shape.setPosition(p);
	}

	sf::Vector2f getPosition() { return shape.getPosition(); }
	
	sf::CircleShape shape;

private:
	sf::Vector2f velocity;
	float mass;
};