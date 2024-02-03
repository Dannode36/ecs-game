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

public:
	AssetManager() = default;

	template<typename T> 
	inline std::shared_ptr<T> Load(std::string assetPath) {
		if (caches.find(typeid(T).name()) == caches.end()) {
			throw std::exception(fmt::format("FATAL: No cache for type {} exists\n", typeid(T).name()).c_str());
		}

		//This is so fucking stupid
		return std::any_cast<AssetCache<T>>(caches[typeid(T).name()]).Load(assetPath);
	}

	template<typename T> 
	inline std::future<std::shared_ptr<T>> LoadAsync(std::string assetPath) {
		if (caches.find(typeid(T).name()) == caches.end()) {
			throw std::exception(fmt::format("FATAL: No cache for type {} exists\n", typeid(T).name()).c_str());
		}

		//This is also so fucking stupid
		return std::any_cast<AssetCache<T>>(caches[typeid(T).name()]).LoadAsync(assetPath);
	}

	void RenderDebugMetricsUI(bool* open);

	template<typename T>
	inline void RegisterAssetType() {
		caches.emplace(std::make_pair(typeid(T).name(), AssetCache())
	}

private:
	std::map<std::string, std::any> caches;
};
