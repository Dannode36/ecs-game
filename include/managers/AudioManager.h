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
    //std::vector<std::future<std::shared_ptr<sf::Music>>> music_cache;
    std::map<std::string, std::shared_ptr<sf::Sound>> sound_cache; //Sound UUID -> Sound
    std::map<int, std::future<void>> sound_futures;

    AssetManager* m_assetMgr;
    int sound_counter = 0;

    inline bool RegisterAssetManager(AssetManager* assetmanager) {
        m_assetMgr = assetmanager;
    }

    inline void PlaySound(
        std::string soundId,
        float volume = 100.f,
        float pitch = 1.f,
        bool loop = false,
        bool relative = false,
        sf::Vector3f pos = sf::Vector3f()) 
    {
        int sound_id_num = ++sound_counter;

        sound_futures[sound_id_num] = std::async(std::launch::async,
            [=]() {
                auto soundBuf = m_assetMgr->LoadAsync<sf::SoundBuffer>(AUDIO_PATH + soundId).get();
                auto sound = std::make_shared<sf::Sound>(*soundBuf);
                //Make a copy or somthing here

                sound->setVolume(volume);
                sound->setPitch(volume);
                sound->setLoop(loop);
                sound->setRelativeToListener(relative);
                if (!relative) {
                    sound->setPosition(pos);
                }

                sound->play();

                while (sound->getStatus() == sf::SoundSource::Status::Playing) {
                    __noop; // wait for sound to stop playing before deconstructing it
                }

                sound_futures.erase(sound_id_num);
            });
    }
};
