#pragma once
#include <map>
#include <functional>
#include <memory>
#include <string>
#include <mutex>

//Generic asset cache
template <typename T>
class AssetCache
{
private:
	std::function<std::shared_ptr<T>(std::string)> loadFunc;
	std::mutex m_mutex;

public:
	std::map<std::string, std::weak_ptr<T>> cache;

public:
	AssetCache(const std::function<std::shared_ptr<T>(std::string)>& loadFunc)
		: loadFunc(loadFunc), m_mutex(), cache() { }

	std::shared_ptr<T> Load(std::string assetPath) {
		std::lock_guard<std::mutex> lock_guard(m_mutex);
		//TODO: Check if the path is valid
		//If asset exists in cache and the ptr is valid return it, otherwise load it
		if (cache.find(assetPath) != cache.end() && !cache[assetPath].expired()) {
			std::shared_ptr<T> asset(cache[assetPath]);
			return asset;
		}
		else {
			std::shared_ptr<T> asset = loadFunc(assetPath);
			cache[assetPath] = asset;
			return asset;
		}
	}

	size_t validAssetCount() {
		size_t i = 0;
		for (auto& asset : cache) {
			if (!asset.second.expired()) {
				i++;
			}
		}
		return i;
	}
};
