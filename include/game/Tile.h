#pragma once
#include <cstdint>
#include <SFML/System/Vector2.hpp>
#include <map>
#include <string>

struct Tile
{
	int32_t textureIndex;
	sf::Vector2u pos;
	std::map<std::string, std::string> properties;
};
