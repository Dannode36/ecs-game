#pragma once
#include <cstdint>
#include <SFML/System/Vector2.hpp>
#include <map>
#include <string>
#include "Animation.h"
#include "PropertyCollection.h"
#include "TileMap.h"
#include "vendor/tileson.hpp"

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
	//inline Tile(uint32_t id, tson::Tileset* tileset, tson::Map* map);
	inline Tile(tson::Tile tsonTile);

	//[[nodiscard]] inline const std::vector<Frame> &getAnimation() const;
	[[nodiscard]] inline Animation& getAnimation();
	[[nodiscard]] inline PropertyCollection& getProperties();
	[[nodiscard]] inline const std::vector<int>& getTerrain() const;

	template <typename T>
	inline T get(const std::string& name);
	inline Property* getProp(const std::string& name);

	//v1.2.0-stuff
	inline void setProperties(const PropertyCollection& properties);

	//[[nodiscard]] inline Tileset* getTileset() const;
	[[nodiscard]] inline TileMap* getMap() const;

	inline const sf::Vector2f getPosition(const std::tuple<int, int>& tileDataPos);
	inline const sf::Vector2i getPositionInTileUnits(const std::tuple<int, int>& tileDataPos);
	[[nodiscard]] inline const sf::Vector2i getTileSize() const;                       /*! Declared in tileson_forward.hpp */

	[[nodiscard]] inline FlipFlags getFlipFlags() const;
	inline bool hasFlipFlags(FlipFlags flags);
	[[nodiscard]] inline uint32_t getGid() const;
private:
	Animation m_animation{};
	uint32_t m_textureIndex;
	sf::Vector2u pos;
	PropertyCollection  m_properties;
	std::vector<int> m_terrain;
	std::string m_type;

	uint32_t m_gid{};
	//Tileset* m_tileset;                          
	TileMap* m_map;                              
	FlipFlags m_flipFlags = FlipFlags::None;
};

Tile::Tile(tson::Tile tsonTile) {
	m_textureIndex = tsonTile.getId();
	m_gid = tsonTile.getGid();
	//m_tileset = tileset;
	m_map = map;
	manageFlipFlagsByIdThenRemoveFlags(m_gid);
	performDataCalculations();
}

/*!
 * Used in cases where you have a FLIP FLAGGED tile
 * @param id
 */
Tile::Tile(uint32_t id, Map* map) : m_id{ id }, m_gid{ id }
{
	m_map = map;
	manageFlipFlagsByIdThenRemoveFlags(m_gid);
}

/*!
 * For flip flagged tiles, tilesets must be resolved later.
 * @param tileset
 */
void Tile::addTilesetAndPerformCalculations(Tileset* tileset)
{
	m_tileset = tileset;
	performDataCalculations();
}

/*!
 * 'id': Local ID of the tile
 * @return
 */
uint32_t Tile::getId() const
{
	return m_id;
}

/*!
 * 'image': Image representing this tile (optional)
 * @return
 */

const fs::path& Tile::getImage() const { return m_image; }

/*!
 * x = 'imagewidth' and y = 'imageheight': in pixels
 * @return
 */
const Vector2i& Tile::getImageSize() const
{
	return m_imageSize;
}

/*!
 * 'type': The type of the tile (optional)
 * This was renamed to 'class' in Tiled v1.9
 * @return
 */
const std::string& Tile::getType() const
{
	return m_type;
}

/*!
  * 'class': String assigned to class field in editor (optional)
 * This was renamed from 'type' to 'class' in Tiled v1.9
 * @return
 */
const std::string& Tile::getClassType() const
{
	return m_type;
}

/*!
 * 'animation': Array of Frames
 * @return
 */
TileAnimation& Tile::getAnimation()
{
	return m_animation;
}

/*!
 * 'objectgroup': Layer with type objectgroup (optional)
 * @return
 */
Layer& Tile::getObjectgroup()
{
	return m_objectgroup;
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
 * 'terrain': Index of terrain for each corner of tile
 * @return
 */
const std::vector<int>& Tile::getTerrain() const
{
	return m_terrain;
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
 * Used for getting the Tileset who is the parent of this Tile.
 * @return a pointer to the Tileset where this tile is contained.
 */
Tileset* Tile::getTileset() const
{
	return m_tileset;
}

/*!
 * Used for getting the TileMap who is the parent of this Tile.
 * @return a pointer to the TileMap where this tile is contained.
 */
Map* Tile::getMap() const
{
	return m_map;
}

/*!
 * Get the information needed to draw the Tile based on its current tileset
 * @return a Rect containing the information needed to draw the tile.
 */
const Rect& Tile::getDrawingRect() const
{
	return m_drawingRect;
}

/*!
 * Helper function.
 *
 * Get the position of the tile in tile units.
 * The size of each unit is determined by the tile size property of the map.
 * Example: If the tile size is 16x16 in the map, a tile unit of [2, 4] would be [32, 64] in pixels.
 * If you want the position in pixels: use getPosition() instead.
 *
 * @return Position of tile in tile units.
 */
const Vector2i Tile::getPositionInTileUnits(const std::tuple<int, int>& tileDataPos)
{
	return { std::get<0>(tileDataPos), std::get<1>(tileDataPos) };
}

void Tile::manageFlipFlagsByIdThenRemoveFlags(uint32_t& id)
{
	if (id & FLIPPED_HORIZONTALLY_FLAG) m_flipFlags |= TileFlipFlags::Horizontally;
	if (id & FLIPPED_VERTICALLY_FLAG) m_flipFlags |= TileFlipFlags::Vertically;
	if (id & FLIPPED_DIAGONALLY_FLAG) m_flipFlags |= TileFlipFlags::Diagonally;

	id &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
}

TileFlipFlags Tile::getFlipFlags() const
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
bool Tile::hasFlipFlags(TileFlipFlags flags)
{
	return ((m_flipFlags & flags) == flags) ? true : false;
}

uint32_t Tile::getGid() const
{
	return m_gid;
}

void Tile::setProperties(const PropertyCollection& properties)
{
	m_properties = properties;
}

/*!
 * Tiled 1.9: Contains the newly added sub-rectangle variables: 'x', 'y', 'width' and 'height'
 * @return A Rect with the 'x', 'y', 'width' and 'height' values
 */
const Rect& Tile::getSubRectangle() const
{
	return m_subRect;
}