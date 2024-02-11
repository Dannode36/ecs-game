#pragma once
#include <map>
#include <functional>
#include <memory>
#include <string>
#include <mutex>
#include <future>
#include <iterator>

enum CacheType {
	Weak,
	Persist
};

//Generic asset cache
template<typename T>
class AssetCache
{
public:
	AssetCache(const std::function<std::shared_ptr<T>(std::string)>& loadFunc)
		: loadFromDisk(loadFunc), mutex(), cache() { }

	std::shared_ptr<T> Load(std::string assetPath, CacheType cacheType = Weak) {
		std::lock_guard<std::mutex> lock_guard(mutex);
		//TODO: Check if the path is valid
		//If asset exists in cache and the ptr is valid return it, otherwise load it
		if (cache.find(assetPath) != cache.end() && !cache[assetPath].expired()) {
			return std::shared_ptr<T>(cache[assetPath]);
		}
		else {
			std::shared_ptr<T> asset(loadFromDisk(assetPath));
			cache[assetPath] = asset;
			/*if (cacheType == Persist) {
				persistence_cache.push_back(asset);
			}*/
			return asset;
		}
	}
	std::future<std::shared_ptr<T>> LoadAsync(std::string assetPath) {
		return std::async([=]() -> std::shared_ptr<T> {
			while (!mutex.try_lock()) { /*Wait for mutex to unlock*/ }

			if (cache.find(assetPath) != cache.end() && !cache[assetPath].expired()) {
				std::shared_ptr<T> asset(cache[assetPath]);

				mutex.unlock();
				return asset;
			}
			else {
				std::shared_ptr<T> asset = loadFromDisk(assetPath);
				cache[assetPath] = asset;
				/*if (cacheType == Persist) {
					persistence_cache.push_back(asset);
				}*/

				mutex.unlock();
				return std::shared_ptr<T>(asset);
			}
		});
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
private:
	std::function<std::shared_ptr<T>(std::string)> loadFromDisk; //Function used to load new assets
	std::map<std::string, std::weak_ptr<T>> cache;
	std::vector<std::shared_ptr<T>> persistence_cache;
	std::mutex mutex;
};
