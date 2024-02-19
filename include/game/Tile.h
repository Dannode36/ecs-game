#pragma once
#include <cstdint>
#include <SFML/System/Vector2.hpp>

struct Tile
{
	int32_t index;
	std::map<std::string, std::string> properties;
};
