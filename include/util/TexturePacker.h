#include <SFML/Graphics.hpp>

#ifndef SPDLOG_FMT_EXTERNAL
	#define SPDLOG_FMT_EXTERNAL
#endif
#include "vendor/spdlog/spdlog.h"

struct TileSet {
	std::string texturePath;
	unsigned int firstId;
	unsigned int tileCount;
};

#pragma warning( push )
#pragma warning( disable : 4244)
inline std::shared_ptr<sf::Texture> packTilesets(const std::vector<TileSet>& tilesets, unsigned int tileSize) {
	unsigned int maxTextureSize = sf::Texture::getMaximumSize();
	unsigned int maxNumTiles = (maxTextureSize / (float)tileSize) * (maxTextureSize / (float)tileSize);
	unsigned int tileCount = 0;
	
	for (auto& tileset : tilesets) {
		tileCount += tileset.tileCount;

		if (tileCount > maxNumTiles) {
			throw std::exception("Can't fit textures into one atlas. Max number of tiles: " + maxNumTiles);
		}
	}

	sf::RenderTexture outputTex;
	unsigned int outTexSize = static_cast<unsigned int>(ceil(sqrt(tileCount))) * tileSize;

	if (ceil(sqrt(tileCount)) - (tileCount / ceil(sqrt(tileCount))) >= 1) {
		outputTex.create(outTexSize, outTexSize - tileSize);
	}
	else {
		outputTex.create(outTexSize, outTexSize);
	}

	sf::VertexArray vertices(sf::Triangles);

	for (auto& tileset : tilesets) {
		sf::Texture tilesetTex;
		tilesetTex.loadFromFile(tileset.texturePath);

		unsigned int tilesetWidth = (tilesetTex.getSize().x / tileSize);
		unsigned int tilesetHeight = (tilesetTex.getSize().y / tileSize);

		//Manipulate vertex array
		vertices.resize(static_cast<size_t>(tileset.tileCount) * 6);
		for (unsigned int i = 0; i < tilesetWidth; ++i) {
			for (unsigned int j = 0; j < tilesetHeight; ++j) {
				// get the current tile number
				int tileNumber = i + j * tilesetWidth;

				// find its position in the tileset texture
				int tu = tileNumber % (tilesetTex.getSize().x / tileSize);
				int tv = tileNumber / (tilesetTex.getSize().x / tileSize);

				// get a pointer to the triangles' vertices of the current tile
				sf::Vertex* triangles = &vertices[(i + static_cast<size_t>(j) * tilesetWidth) * 6];

				unsigned int x = (tileNumber + tileset.firstId) % (outTexSize / tileSize);
				unsigned int y = (tileNumber + tileset.firstId) / (outTexSize / tileSize);

				// define the 6 corners of the two triangles
				triangles[0].position = sf::Vector2f(x * tileSize, y * tileSize);
				triangles[1].position = sf::Vector2f((x + 1) * tileSize, y * tileSize);
				triangles[2].position = sf::Vector2f(x * tileSize, (y + 1) * tileSize);
				triangles[3].position = sf::Vector2f(x * tileSize, (y + 1) * tileSize);
				triangles[4].position = sf::Vector2f((x + 1) * tileSize, y * tileSize);
				triangles[5].position = sf::Vector2f((x + 1) * tileSize, (y + 1) * tileSize);

				// define the 6 matching texture coordinates
				triangles[0].texCoords = sf::Vector2f(tu * tileSize, tv * tileSize);
				triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize, tv * tileSize);
				triangles[2].texCoords = sf::Vector2f(tu * tileSize, (tv + 1) * tileSize);
				triangles[3].texCoords = sf::Vector2f(tu * tileSize, (tv + 1) * tileSize);
				triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize, tv * tileSize);
				triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize, (tv + 1) * tileSize);
			}
		}

		outputTex.draw(vertices, &tilesetTex);
	}
	outputTex.display();

	spdlog::info(
		"TexturePacker Completed!\n    Number of textures: {}\n    Output dimensions: {}x{}\n    Empty tiles: {}",
		tilesets.size(),
		outputTex.getSize().x,
		outputTex.getSize().y,
		(outputTex.getSize().x * outputTex.getSize().y / (float)(tileSize * tileSize)) - tileCount);

	return std::make_shared<sf::Texture>(outputTex.getTexture());
}
#pragma warning( pop ) 
