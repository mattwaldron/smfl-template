#pragma once
#include <SFML/Graphics.hpp>

class PhysicsCircle {
public:
	PhysicsCircle(float x, float y, int hue);
	
	sf::Vector2f getPosition();
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f p);
	
	sf::CircleShape graphic;

	sf::Vector2f velocity;

private:
	sf::Vector2f _position;

};