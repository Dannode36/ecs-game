#pragma once
#include <cstdint>
#include <SFML/System/Vector2.hpp>
#include <map>
#include <string>
#include "Animation.h"
#include "PropertyCollection.h"
#include "vendor/tileson.hpp"
#include "TileMap.h"

enum FlipFlags : char {
	None		 =	0,
	Diagonally   =	1 << 0,
	Vertically   =	1 << 1,
	Horizontally =	1 << 2
};

class Tile
{
public:
	inline Tile() = default;
	inline Tile(tson::Tile tsonTile, TileMap* map);

	[[nodiscard]] inline uint32_t getTextureIndex() const;
	[[nodiscard]] inline void setTextureIndex(uint32_t i);
	[[nodiscard]] inline Animation& getAnimation();
	[[nodiscard]] inline PropertyCollection& getProperties();
	inline void setProperties(const PropertyCollection& properties);

	template <typename T>
	inline T get(const std::string& name);
	inline Property* getProp(const std::string& name);

	[[nodiscard]] inline TileMap* getMap() const;
	[[nodiscard]] inline FlipFlags getFlipFlags() const;
	inline bool hasFlipFlags(FlipFlags flags) const;
private:
	uint32_t m_textureIndex;
	Animation m_animation{};
	PropertyCollection  m_properties;

	TileMap* m_map;                              
	FlipFlags m_flipFlags = FlipFlags::None;
};

Tile::Tile(tson::Tile tsonTile, TileMap* map) {
	m_textureIndex = tsonTile.getGid();
	m_map = map;

	//Flip flag shenanigans
	uint32_t shiftedFlipFlags = (uint32_t)tsonTile.getFlipFlags() >> 29; //Shift tson flags down to the first 3 bits
	m_flipFlags = (FlipFlags)shiftedFlipFlags; //cast back to a char type (I hope this works)

	for (auto& prop : tsonTile.getProperties().getProperties())
	{
		m_properties.add(prop.second);
	}
}

/*!
 * 'id': Local ID of the tile
 * @return
 */
uint32_t Tile::getTextureIndex() const
{
	return m_textureIndex;
}

void Tile::setTextureIndex(uint32_t i)
{
	m_textureIndex = i;
}

/*!
 * 'animation': Array of Frames
 * @return
 */
Animation& Tile::getAnimation()
{
	return m_animation;
}

/*!
 * 'properties': A list of properties (name, value, type).
 * @return
 */
PropertyCollection& Tile::getProperties()
{
	return m_properties;
}

/*!
 * Shortcut for getting a property object. Alternative to getProperties().getProperty("<name>");
 * @param name Name of the property
 * @return
 */
Property* Tile::getProp(const std::string& name)
{
	if (m_properties.hasProperty(name))
		return m_properties.getProperty(name);

	return nullptr;
}

/*!
 * Used for getting the TileMap who is the parent of this Tile.
 * @return a pointer to the TileMap where this tile is contained.
 */
TileMap* Tile::getMap() const
{
	return m_map;
}

FlipFlags Tile::getFlipFlags() const
{
	return m_flipFlags;
}

/*!
 *
 * @param flags Which flags to check for. Several flags can be checked at once using the bitwise or operator.
 * Example:
 * hasFlipFlags(TileFlipFlags::Vertically | TileFlipFlags::Horizontally)
 *
 * @return true if the flag(s) specified are set
 */
bool Tile::hasFlipFlags(FlipFlags flags) const
{
	return ((m_flipFlags & flags) == flags) ? true : false;
}

void Tile::setProperties(const PropertyCollection& properties)
{
	m_properties = properties;
}
