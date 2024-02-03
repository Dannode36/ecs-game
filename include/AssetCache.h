#pragma once
#include <map>
#include <functional>
#include <memory>
#include <string>
#include <mutex>
#include <future>
#include <iterator>

template<typename T>
struct AssetPtrDeleter {
	std::map<std::string, std::weak_ptr<T>>& cache;
	std::map<std::string, std::weak_ptr<T>>::iterator it;

	void operator()() {
		cache.erase(it);
	}
};

//Generic asset cache
template<typename T>
class AssetCache
{
public:
	//Custom copy and ctor copy functions for std::any ;3

	inline AssetCache(const AssetCache& ac) : mutex() {
		loadFromDisk = ac.loadFromDisk;
		cache = ac.cache;
	}
	inline AssetCache operator=(const AssetCache& ac) {
		loadFromDisk = ac.loadFromDisk;
		cache = ac.cache;
	}

	AssetCache(const std::function<std::shared_ptr<T>(std::string)>& loadFunc)
		: loadFromDisk(loadFunc), mutex(), cache() { }

	std::shared_ptr<T> Load(std::string assetPath) {
		std::lock_guard<std::mutex> lock_guard(*mutex);
		//TODO: Check if the path is valid
		//If asset exists in cache and the ptr is valid return it, otherwise load it
		if (cache.find(assetPath) != cache.end() && !cache[assetPath].expired()) {
			std::shared_ptr<T> asset(cache[assetPath]);
			return asset;
		}
		else {
			std::shared_ptr<T> asset(loadFromDisk(assetPath));
			cache[assetPath] = asset;
			return asset;
		}
	}
	std::future<std::shared_ptr<T>> LoadAsync(std::string assetPath) {
		while(!mutex->try_lock()) { /*Wait for mutex to unlock*/ }

		return std::async([&]() -> std::shared_ptr<T> {
			if (cache.find(assetPath) != cache.end() && !cache[assetPath].expired()) {
				std::shared_ptr<T> asset(cache[assetPath]);

				mutex->unlock();
				return asset;
			}
			else {
				std::shared_ptr<T> asset = loadFromDisk(assetPath);
				cache[assetPath] = asset;

				mutex->unlock();
				return asset;
			}
		});
	}
	
	//maybe (called from custom deleter somehow
	/*bool RemoveAsset(std::map<std::string, std::weak_ptr<T>>::iterator it) {
		if (it->second.expired()) {
			cache.erase(it);
		}
	}*/

	size_t validAssetCount() {
		size_t i = 0;
		for (auto& asset : cache) {
			if (!asset.second.expired()) {
				i++;
			}
		}
		return i;
	}
private:
	inline std::shared_ptr<T> internal_Load(std::string assetPath) {
		//TODO: Check if the path is valid
		//If asset exists in cache and the ptr is valid return it, otherwise load it
		if (cache.find(assetPath) != cache.end() && !cache[assetPath].expired()) {
			std::shared_ptr<T> asset(cache[assetPath]);
			return asset;
		}
		else {
			std::shared_ptr<T> asset = loadFromDisk(assetPath);
			cache[assetPath] = asset;
			return asset;
		}
	}

	std::function<std::shared_ptr<T>(std::string)> loadFromDisk; //Function used to load new assets
	std::map<std::string, std::weak_ptr<T>> cache;
	std::unique_ptr<std::mutex> mutex;
};
