#pragma once
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "PropertyCollection.h"
#include <vendor/tileson.hpp>
#include <util/Logging.h>
//#include "TileMap.h"
class TileMap;

class TileLayer : public sf::Drawable, public sf::Transformable
{
public:
	inline TileLayer() = default;
	bool load(tson::Layer* tsonTileLayer, TileMap* caller)
	{
		if (tsonTileLayer == nullptr || tsonTileLayer->getType() != tson::LayerType::TileLayer) {
			return false;
		}

		//Load name first so texture can be checked
		m_name = tsonTileLayer->getName();

		//Try loading textures first for a possible early return
		std::filesystem::path texturePath = tsonTileLayer->getMap()->getTileset(m_name)->getImagePath();

		if (!m_texture.loadFromFile(texturePath.string())) {
			LOG_ERROR("Texture at \"" + texturePath.string() + "\" is not valid");

			return false; //No vaild texture found 
		}

		//Copy tile data
		m_data = tsonTileLayer->getData();
		m_id = tsonTileLayer->getId();
		m_opacity = tsonTileLayer->getOpacity();

		/*	Gets a little bit iffy...
			Must rebuild entire collection as tson::Property and Property
			are different but luckily its easy to cast between them	*/
		for (auto& prop : tsonTileLayer->getProperties().getProperties())
		{
			m_properties.add(prop.second);
		}

		m_size.x = tsonTileLayer->getSize().x;
		m_size.y = tsonTileLayer->getSize().y;

		m_visible = tsonTileLayer->isVisible();

		m_parallax.x = tsonTileLayer->getParallax().x;
		m_parallax.y = tsonTileLayer->getParallax().y;

		//m_tileData = tsonTileLayer->gett

		m_map = caller;
		//This is where stuff gets weird
		
		
		//// load the tileset texture
		//if (!m_tileset.loadFromFile(tsonTileLayer->getMap()->getTileset()))
		//    return false;

		//// resize the vertex array to fit the level size
		//m_vertices.setPrimitiveType(sf::Quads);
		//m_vertices.resize(width * height * 4);

		// populate the vertex array, with one quad per tile
		//for (unsigned int i = 0; i < m_size.x; ++i) {
		//	for (unsigned int j = 0; j < m_size.y; ++j)
		//	{
		//		// get the current tile number
		//		int tileNumber = m_data[i + j * m_size.x];

		//		// find its position in the tileset texture
		//		int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
		//		int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

		//		// get a pointer to the current tile's quad
		//		sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

		//		// define its 4 corners
		//		quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
		//		quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
		//		quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
		//		quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

		//		// define its 4 texture coordinates
		//		quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
		//		quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
		//		quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		//	}
		//}

		return true;
	}

	[[nodiscard]] inline const std::vector<uint32_t>& getData() const;
	[[nodiscard]] inline int getId() const;
	[[nodiscard]] inline const std::string& getName() const;
	[[nodiscard]] inline float getOpacity() const;
	[[nodiscard]] inline const sf::Vector2i& getSize() const;
	[[nodiscard]] inline const sf::Vector2f& getParallax() const;

	[[nodiscard]] inline bool isVisible() const;

	[[nodiscard]] inline PropertyCollection& getProperties();
	inline Property* getProp(const std::string& name);
	template <typename T> inline T get(const std::string& name);

	inline void assignTileMap(std::map<uint32_t, Tile*>* tileMap);
	inline void createTileData(const sf::Vector2i& mapSize);

	[[nodiscard]] inline const std::map<std::tuple<int, int>, Tile*>& getTileData() const;
	inline Tile* getTileData(int x, int y);
	inline Tile* getTileData(const sf::Vector2i& pos);

	[[nodiscard]] inline const sf::Color& getTintColor() const;
	inline TileMap* getMap() const;

private:
	int m_id{};											/* 'id': Incremental id - unique across all TileLayers */
	std::string m_name;									/* 'name': Name assigned to this TileLayer */
	sf::Vector2i m_size;								/* x = width, y = height */
	std::vector<uint32_t> m_data;						/* 'data': Array of unsigned int (GIDs) */
	std::map<sf::Vector2i, Tile*> m_tileData;			/* Key: sf::Vector2i in tile units. */
	PropertyCollection m_properties; 					/* 'properties': A list of properties (name, value, type). */

	bool m_visible{};									/* 'visible': Whether TileLayer is shown or hidden in editor */
	float m_opacity{};									/* 'opacity': Value between 0 and 1 */
	sf::Vector2f m_parallax{ 1.f, 1.f };				/* Tiled v1.5: parallax factor for this TileLayer. Defaults to 1. */

	sf::Color m_tintColor;								/* 'tintcolor': Hex-formatted color (#RRGGBB or #AARRGGBB) that is multiplied with
															any graphics drawn by this TileLayer or any child TileLayers (optional). */
	TileMap* m_map;										/* The map who owns this TileLayer */

	//MAY SUPPORT IN FUTURE VERSIONS
	//std::set<uint32_t>                           m_uniqueFlaggedTiles;
	//std::vector<FlaggedTile>                     m_flaggedTiles;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &m_texture;

		// draw the vertex array
		target.draw(m_verticies, states);
	}

	//sf::VertexArray m_verticies;
	std::vector<sf::RectangleShape> tiles;
	sf::Texture m_texture;
};
#pragma warning(default : 4244)

/*!
 * @return Array of unsigned int (GIDs)
 */
const std::vector<uint32_t>& TileLayer::getData() const {
	return m_data;
}

/*!
 * @return Incremental id - unique across all TileLayers
 */
int TileLayer::getId() const {
	return m_id;
}

/*!
 * @return Name assigned to this TileLayer
 */
const std::string& TileLayer::getName() const {
	return m_name;
}

/*!
 * @return Value between 0 and 1
 */
float TileLayer::getOpacity() const {
	return m_opacity;
}

/*
 * @return width and height as a single size
 */
const sf::Vector2i& TileLayer::getSize() const {
	return m_size;
}

/*!
 * @return Whether TileLayer is shown or hidden in editor
 */
bool TileLayer::isVisible() const {
	return m_visible;
}

/*!
 * @return A list of properties (name, value, type).
 */
PropertyCollection& TileLayer::getProperties() {
	return m_properties;
}
template <typename T> 
T get(const std::string& name) {
	return m_properties.getValue<T>(name);
}

/*!
 * Shortcut for getting a property object. Alternative to getProperties().getProperty("<name>");
 * @param name Name of the property
 * @return Property or nullptr if doesn't exist
 */
Property* TileLayer::getProp(const std::string& name) {
	if (m_properties.hasProperty(name))
		return m_properties.getProperty(name);
	return nullptr;
}

/*!
 * Assigns a tilemap of pointers to existing tiles.
 * @param tileMap The tilemap. key: tile id, value: pointer to Tile.
 */
void TileLayer::assignTileMap(std::map<uint32_t, Tile*>* tileMap) {
	m_tileMap = tileMap;
}

/*!
 * Get tile data as some kind of map with x and y position with pointers to existing tiles.
 * TileMap only contains tiles that are not empty. x and y position is in tile units.
 *
 * Example of getting tile from the returned map:
 *
 * Tile *tile = tileData[{0, 4}];
 *
 * @return A map that represents the data returned from getData() in a 2D map with Tile pointers.
 */
const std::map<std::tuple<int, int>, Tile*>& TileLayer::getTileData() const {
	return m_tileData;
}

/*!
 * A safe way to get tile data
 * Get tile data as some kind of map with x and y position with pointers to existing tiles.
 * TileMap only contains tiles that are not empty. x and y position is in tile units.
 *
 * Example of getting tile:
 * Tile *tile = TileLayer->getTileData(0, 4)
 *
 * @param x X position in tile units
 * @param y Y position in tile units
 * @return pointer to tile, if it exists. nullptr otherwise.
 */
Tile* TileLayer::getTileData(int x, int y) {
	return (m_tileData.count({ x, y }) > 0) ? m_tileData[{x, y}] : nullptr;
}

/*!
 * A safe way to get tile data
 * Get tile data as some kind of map with x and y position with pointers to existing tiles.
 * TileMap only contains tiles that are not empty. x and y position is in tile units.
 *
 * Example of getting tile:
 * Tile *tile = TileLayer->getTileData(0, 4)
 *
 * @param x X position in tile units
 * @param y Y position in tile units
 * @return pointer to tile, if it exists. nullptr otherwise.
 */
Tile* TileLayer::getTileData(const sf::Vector2i& pos) {
	return (m_tileData.count({ pos.x, pos.y }) > 0) ? m_tileData[{pos.x, pos.y}] : nullptr;
}

/*!
 * Used for getting the TileMap who is the parent of this TileLayer.
 * @return a pointer to the TileMap where this TileLayer is contained.
 */
TileMap* TileLayer::getMap() const {
	return m_map;
}

/*!
 * @param mapSize The size of the map
 */
void TileLayer::createTileData(const sf::Vector2i& mapSize) {
	size_t x = 0;
	size_t y = 0;
	std::for_each(m_data.begin(), m_data.end(), [&](uint32_t tileId) {
		if (static_cast<int>(x) == mapSize.x)
		{
			++y;
			x = 0;
		}

		if (tileId > 0 && m_tileMap->count(tileId) > 0)
		{
			m_tileData[{static_cast<int>(x), static_cast<int>(y)}] = m_tileMap->at(tileId);
			//m_tileObjects[{static_cast<int>(x), static_cast<int>(y)}] = { {static_cast<int>(x), static_cast<int>(y)}, m_tileData[{static_cast<int>(x), static_cast<int>(y)}] };
		}
		x++;
	});
}

/*!
 * 'tintcolor': Hex-formatted color (#RRGGBB or #AARRGGBB) that is multiplied with any graphics drawn by this TileLayer or any child TileLayers (optional).
 *
 * @return tintcolor
 */
const sf::Color& TileLayer::getTintColor() const {
	return m_tintColor;
}

/*!
 * Gets the parallax factor for current TileLayer. Defaults to 1.
 * @return A vector with the x and y values of the parallax factor.
 */
const sf::Vector2f& TileLayer::getParallax() const {
	return m_parallax;
}
