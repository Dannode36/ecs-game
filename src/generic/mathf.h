#pragma once
#include "../ECS/Components.h"

template <typename T>
inline T clip(const T& n, const T& lower, const T& upper) {
	return std::max(lower, std::min(n, upper));
}

inline bool CircleCircleOverlap(Transform& c1, Transform& c2) {
	return pow((c2.pos.x - c1.pos.x), 2) + pow((c2.pos.y - c1.pos.y), 2) <= pow((c1.radius + c2.radius), 2);
}

inline bool CirclePointOverlap(Transform& circle, Vector2& point) {
	return pow((point.x - circle.pos.x), 2) + pow((point.y - circle.pos.y), 2) <= circle.radius * circle.radius;
}