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

	static sf::Vector2f interpolate(sf::Vector2f start, sf::Vector2f end, float percent) {
		auto diff = (end - start) * percent;
		return start + diff;
	}

	static sf::Vector2f interpolate(std::vector<sf::Vector2f> points, float percent) {
		if (points.size() < 2) {
			return sf::Vector2f(NAN, NAN);
		}
		return (interpolate(points[0], points[1], percent));
	}

	static sf::Vector2f bezier(std::vector<sf::Vector2f> points, float percent) {
		if (points.size() < 2) {
			return sf::Vector2f(NAN, NAN);
		}
		if (points.size() == 2) {
			return interpolate(points, percent);
		}
		std::vector<sf::Vector2f> newControlPoints;
		for (auto i = 1; i < points.size(); i++) {
			newControlPoints.push_back(interpolate(points[i - 1], points[i], percent));
		}
		return bezier(newControlPoints, percent);
	}

	static std::vector<sf::Vector2f> traceBezier(std::vector<sf::Vector2f> controlPoints, float resolution) {
		std::vector<sf::Vector2f> tracePoints;
		for (auto p = 0.0f; p <= 1.0; p += resolution) {
			tracePoints.push_back(bezier(controlPoints, p));
		}
		return tracePoints;
	}
};