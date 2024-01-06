#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "AssetCache.h"
#include "types.h"

class AssetManager
{
private:
	//Represents audio that is loaded once from the source
	AssetCache<sf::SoundBuffer> soundCache{ 
		[](std::string assetPath) -> SoundBufferPtr {
			auto buffer = std::make_shared<sf::SoundBuffer>();
			buffer->loadFromFile(assetPath);
			return buffer;
		} 
	};

	//Represents single instanced audio that is streamed continuously from the source
	AssetCache<sf::Music> musicCache {
		[](std::string assetPath) -> MusicPtr {
			auto buffer = std::make_shared<sf::Music>();
			buffer->openFromFile(assetPath);
			return buffer;
		}
	};

	AssetCache<sf::Texture> textureCache{ 
		[](std::string assetPath) -> TexturePtr {
			auto buffer = std::make_shared<sf::Texture>();
			buffer->loadFromFile(assetPath);
			return buffer;
		}
	};

public:
	AssetManager() = default;

	template<typename T> inline std::shared_ptr<T> Load(std::string assetPath) { throw std::exception("Not Implemented"); } //Generic. Throws exception
	template<> inline SoundBufferPtr Load<sf::SoundBuffer>(std::string assetPath) {
		return soundCache.Load(assetPath);
	}
	template<> inline MusicPtr Load<sf::Music>(std::string assetPath) {
		return musicCache.Load(assetPath);
	}
	template<> inline TexturePtr Load<sf::Texture>(std::string assetPath) {
		return textureCache.Load(assetPath);
	}

	void RenderDebugMetricsUI(bool* open);
};
