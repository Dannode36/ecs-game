#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "AssetCache.h"

class AssetManager
{
private:
	//Represents audio that is loaded once from the source
	AssetCache<sf::SoundBuffer> soundCache{ 
		[](std::string assetPath) -> std::shared_ptr<sf::SoundBuffer> {
			auto buffer = std::make_shared<sf::SoundBuffer>();
			buffer->loadFromFile(assetPath);
			return buffer;
		} 
	};

	//Represents single instanced audio that is streamed continuously from the source
	AssetCache<sf::Music> musicCache {
		[](std::string assetPath) -> std::shared_ptr<sf::Music> {
			auto buffer = std::make_shared<sf::Music>();
			buffer->openFromFile(assetPath);
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

public:
	AssetManager() = default;

	template<typename T> inline std::shared_ptr<T> Load(std::string assetPath) { throw; } //Generic. Throws exception
	template<> inline std::shared_ptr<sf::SoundBuffer> Load<sf::SoundBuffer>(std::string assetPath) {
		return soundCache.Load(assetPath);
	}
	template<> inline std::shared_ptr<sf::Music> Load<sf::Music>(std::string assetPath) {
		return musicCache.Load(assetPath);
	}
	template<> inline std::shared_ptr<sf::Texture> Load<sf::Texture>(std::string assetPath) {
		return textureCache.Load(assetPath);
	}

	void RenderDebugMetricsUI(bool* open);
};
