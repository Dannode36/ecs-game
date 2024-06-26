#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "AssetCache.h"
#include "types.h"
#include <any>
#include "fmt/format.h"

//TODO: find a better way to do this
class AssetManager
{
private:
	////Represents audio that is loaded once from the source
	//[](std::string assetPath) -> SoundBufferPtr {
	//	auto buffer = std::make_shared<sf::SoundBuffer>();
	//	buffer->loadFromFile(assetPath);
	//	return buffer;
	//}

	////Represents single instanced audio that is streamed continuously from the source
	//[](std::string assetPath) -> MusicPtr {
	//	auto buffer = std::make_shared<sf::Music>();
	//	buffer->openFromFile(assetPath);
	//	return buffer;
	//}

	//[](std::string assetPath) -> TexturePtr {
	//	auto buffer = std::make_shared<sf::Texture>();
	//	buffer->loadFromFile(assetPath);
	//	return buffer;
	//}

	//Represents audio that is loaded once from the source
	AssetCache<sf::SoundBuffer> soundCache{
		[](std::string assetPath) -> SoundBufferPtr {
			auto buffer = std::make_shared<sf::SoundBuffer>();
			buffer->loadFromFile(assetPath);
			return buffer;
		}
	};

	//Represents single instanced audio that is streamed continuously from the source
	AssetCache<sf::Music> musicCache{
		[](std::string assetPath) -> MusicPtr {
			//fmt::print("{}\n", assetPath);
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

	template<typename T> 
	inline std::shared_ptr<T> Load(std::string assetPath) {
		throw std::exception("fuck this"); //This is so fucking stupid
	}

	template<> 
	inline TexturePtr Load<sf::Texture>(std::string assetPath) {
		return textureCache.Load(assetPath);
	}

	template<>
	inline MusicPtr Load<sf::Music>(std::string assetPath) {
		return musicCache.Load(assetPath);
	}

	template<typename T> 
	inline std::future<std::shared_ptr<T>> LoadAsync(std::string assetPath) {
		throw std::exception("fuck this"); //This is so fucking stupid

		////This is also so fucking stupid
		//return std::any_cast<AssetCache<T>>(caches[typeid(T).name()]).LoadAsync(assetPath);
	}

	template<>
	inline std::future<MusicPtr> LoadAsync <sf::Music>(std::string assetPath) {
		return musicCache.LoadAsync(assetPath);
	}
	/// <summary>
	///	Loads an asset into cache for future use. Used when batch loading
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="assetPath"></param>
	/// <returns></returns>
	/*template<typename T>
	inline void Prepare(std::string assetPath) {
		std::any_cast<AssetCache<T>>(caches[typeid(T).name()]).Load(assetPath);
	}

	template<typename T>
	inline void PrepareAsync(std::string assetPath) {
		std::any_cast<AssetCache<T>>(caches[typeid(T).name()]).LoadAsync(assetPath);
	}*/

	void RenderDebugMetricsUI(bool* open = NULL);

	template<typename T>
	inline void RegisterAssetType() {
		//caches.emplace(std::make_pair(typeid(T).name(), AssetCache())
	}

private:
	std::map<std::string, std::any> caches;
};
