#pragma once
#include <cmath>
#include "SFML/System/Vector2.hpp"

//General Math-----------------------------------------------------------------

template <typename T>
inline T clip(const T& n, const T& lower, const T& upper) {
	return std::max(lower, std::min(n, upper));
}

#pragma warning( push )
#pragma warning( disable : 4244 )
template <typename T>
inline T lerp(const T& a, const T& b, const float& t) {
	return a + (b - a) * t;
}
#pragma warning( pop )

//Vector Math------------------------------------------------------------------

inline sf::Vector2f normalize(sf::Vector2f vec) {
	float vu = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (vu != 0) {
		vec.x = vec.x / vu;
		vec.y = vec.y / vu;
	}
	return vec;
}

template <typename T>
static double distance(sf::Vector2<T> a, sf::Vector2<T> b) {
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

template <typename T>
static double angle(sf::Vector2<T> a, sf::Vector2<T> b) {
	return atan2(b.x - a.x, b.y - a.y) * (180 / Constants::PI);
}

//MISC-------------------------------------------------------------------------

inline bool circleCircleOverlap(sf::Vector2f p1, float r1, sf::Vector2f p2, float r2) {
	return pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2) <= pow((r1 + r2), 2);
}

inline bool circlePointOverlap(sf::Vector2f p, sf::Vector2f c, float r) {
	return pow((p.x - c.x), 2) + pow((p.y - c.y), 2) <= pow(r, 2);
}
