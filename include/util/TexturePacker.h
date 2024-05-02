#include <SFML/Graphics.hpp>
struct TileSet {
	std::string texturePath;
	unsigned int firstId;
	unsigned int tileCount;
};

std::shared_ptr<sf::Texture> packTexture(std::vector<TileSet> tilesets, unsigned int tileSize) {
	unsigned int maxTileCount = (sf::Texture::getMaximumSize() / tileSize) * (sf::Texture::getMaximumSize() / tileSize);
	unsigned int tileCount = 0;
	
	for (auto& tileset : tilesets) {
		tileCount += tileCount;

		if (tileCount > maxTileCount) {
			throw std::exception("Can't fit textures into one atlas. Max tile count: " + maxTileCount);
		}
	}

	unsigned int outputTexSize = static_cast<unsigned int>(ceil(sqrt(maxTileCount)));
	sf::RenderTexture outputTex;
	outputTex.create(outputTexSize, outputTexSize);


	for (auto& tileset : tilesets) {
		sf::VertexArray vertices(sf::Triangles, maxTileCount * 4);
		sf::Texture tsTexture;
		tsTexture.loadFromFile(tileset.texturePath);

		//Manipulate vertex array

		sf::RenderStates states = sf::RenderStates::Default;
		states.texture = &tsTexture;
		outputTex.draw(vertices, states);
	}
	outputTex.display();
	return std::make_shared<sf::Texture>(outputTex.getTexture());
}
