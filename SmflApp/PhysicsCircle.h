#pragma once
#include <SFML/Graphics.hpp>

class PhysicsCircle {
public:
	PhysicsCircle(float x, float y, int hue);
	
	void applyMotion(sf::Time delta);
	void applyMotion(sf::Time delta, sf::Vector2f force);

	sf::Vector2f getPosition() { return shape.getPosition(); }
	
	sf::CircleShape shape;

private:
	
	sf::Vector2f velocity;
	float mass;
};