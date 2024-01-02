#pragma once
#include <cmath>
#include "SFML/System/Vector2.hpp"

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

inline sf::Vector2f normalize(sf::Vector2f vec) {
	float vu = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (vu != 0) {
		vec.x = vec.x / vu;
		vec.y = vec.y / vu;
	}
	return vec;
}

inline bool CircleCircleOverlap(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r) {
	return pow((c2x - c1x), 2) + pow((c2y - c1y), 2) <= pow((c1r + c2r), 2);
}

inline bool CirclePointOverlap(float cx, float cy, float cr, float px, float py) {
	return pow((px - cx), 2) + pow((py - cy), 2) <= pow(cr, 2);
}
