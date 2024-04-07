#pragma once
#include "SFML/Graphics/Texture.hpp"

//Images are stacked vertically as Tiled id's are wound vertically
void condenseTextures(const std::vector<std::string>& texturePaths, sf::Texture& dest) {
	unsigned int maxSize = sf::Texture::getMaximumSize();
	
	//Load all textures into memory
	std::vector<sf::Image> images(texturePaths.size());
	unsigned int totalLength = 0;

	for (auto& path : texturePaths)
	{
		sf::Image& image = images.emplace_back();
		if (image.loadFromFile(path)) {
			totalLength += image.getSize().x;

			if (totalLength > maxSize) {
				images.pop_back();
				break; //Max atlas size reached. No more images can be added
			}
		}
	}
}
