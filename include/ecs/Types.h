#pragma once
#include <bitset>
#include <vector>
#include <functional>
#include <cmath>
#include <iostream>
#include "CONSTANTS.h"

#define COMPONENT struct

using Entity = uint16_t;
const Entity MAX_ENTITIES = 256;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 8;
using Signature = std::bitset<MAX_COMPONENTS>;

//struct Vector2
//{
//	float x;
//	float y;
//
//	Vector2 operator+=(Vector2 rhs)
//	{
//		x += rhs.x;
//		y += rhs.y;
//		return *this;
//	}
//
//	static double Dist(Vector2 a, Vector2 b) {
//		return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
//	}
//
//	static double Angle(Vector2 a, Vector2 b) {
//		return atan2(b.x - a.x, b.y - a.y) * (180/ Constants::PI);
//	}
//
//	static Vector2 Normalise(Vector2 vec) {
//		float vu = sqrt((vec.x * vec.x) + (vec.y * vec.y));
//		vec.x = vec.x / vu;
//		vec.y = vec.y / vu;
//		return vec;
//	}
//};
