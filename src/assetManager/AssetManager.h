#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "AssetCache.h"

class AssetManager
{
public:
	AssetCache<sf::SoundBuffer> soundCache{ 
		[](std::string assetPath) -> std::shared_ptr<sf::SoundBuffer> {
			auto buffer = std::make_shared<sf::SoundBuffer>();
			buffer->loadFromFile(assetPath);
			return buffer;
		} 
	};

	AssetCache<sf::Texture> textureCache{ 
		[](std::string assetPath) -> std::shared_ptr<sf::Texture> {
			auto buffer = std::make_shared<sf::Texture>();
			buffer->loadFromFile(assetPath);
			return buffer;
		}
	};

	AssetManager() = default;

	void RenderDebugMetricsUI(bool* open);
};

