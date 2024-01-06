#pragma once
#include <map>
#include <functional>
#include <memory>
#include <string>

//Generic asset cache
template <typename T>
class AssetCache
{
private:
	std::function<std::shared_ptr<T>(std::string)> loadFunc;

public:
	AssetCache(const std::function<std::shared_ptr<T>(std::string)>& loadFunc)
		: loadFunc(loadFunc), cache() { }

	std::map<std::string, std::weak_ptr<T>> cache;
	std::shared_ptr<T> Load(std::string assetPath);
};

template <typename T>
inline std::shared_ptr<T> AssetCache<T>::Load(std::string assetPath) {
	//TODO: Check if the path is valid

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
