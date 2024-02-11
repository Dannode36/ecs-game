#pragma once
#include <map>
#include <string>
#include <memory>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include "AssetManager.h"

#define AUDIO_PATH std::string("assets/")

class MusicManager
{
	std::vector<std::shared_ptr<sf::Music>> music_cache;

	AssetManager* m_assetMgr;

	inline bool RegisterAssetManager(AssetManager* assetmanager) {
		m_assetMgr = assetmanager;
	}

	inline bool PlaySound(
		std::string soundId,
		float volume = 100.f,
		float pitch = 1.f,
		bool loop = false,
		bool relative = false,
		sf::Vector3f pos = sf::Vector3f()) 
	{
		//std::async(std::launch::async, 
		//	[=]() {
		//		auto future = m_assetMgr->LoadAsync<sf::SoundBuffer>(AUDIO_PATH + soundId);
		//		auto soundBuf = future.get();
		//		auto sound = std::make_shared<sf::Sound>(soundBuf);
		//		//Make a copy or somthing here
		//		sound_cache.push_back(sound);

		//		sound->setVolume(volume);
		//		sound->setPitch(volume);
		//		sound->setLoop(loop);
		//		sound->setRelativeToListener(relative);
		//		if (!relative) {
		//			sound->setPosition(pos);
		//		}

		//		sound->play();
		//	});
	}
};
