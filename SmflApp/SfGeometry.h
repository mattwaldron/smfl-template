#pragma once
#include <SFML/Graphics.hpp>

class SfGeometry {
public:
	static sf::Vector2f centerOfMass(std::vector<sf::Vector2f> points) {
		sf::Vector2f center(0, 0);
		for (auto& c : points) {
			center += c;
		}
		center = center / (float)points.size();
		return center;
	}
};