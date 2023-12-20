#pragma once
#include "Types.h"
#include "Math.h"
#include <cstdint>
#include <vector>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

struct Renderer {
	sf::Color color{ 255,255,255 };
	bool active{ false };
};

struct Transform {
	Vector2 pos{ 0,0 };
	float rotation{ 0.0 };
	float radius{ 5.0 };
};

struct RigidBody
{
	double mass{ 1.0 };
	Vector2 velocity{ 0,0 };
	bool kinematic{ false };
	double drag{ 0.47 };

	//Atmosphere
	double atmosAlt{ 0.0 };
	double atmosDen{ 0.0 };
	//ref area = 2pir
};
