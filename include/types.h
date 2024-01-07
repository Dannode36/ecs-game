#pragma once
#include <memory>
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Audio/Music.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

enum StatusType
{
    // Values from -99 to 99 are common Error and Good status responses
    StatusAppMissingAsset = -4,  ///< Application failed due to missing asset file
    StatusAppStackEmpty = -3,  ///< Application States stack is empty
    StatusAppInitFailed = -2,  ///< Application initialization failed
    StatusError = -1,  ///< General error status response
    StatusAppOK = 0,  ///< Application quit without error
    StatusNoError = 0,  ///< General no error status response
    StatusFalse = 0,  ///< False status response
    StatusTrue = 1,  ///< True status response
    StatusOK = 1   ///< OK status response

    // Values from +-100 to +-199 are reserved for File status responses
};

class IApplication;
class AssetManager;
class StateManager;

typedef std::shared_ptr<sf::SoundBuffer> SoundBufferPtr;
typedef std::shared_ptr<sf::Music> MusicPtr;
typedef std::shared_ptr<sf::Texture> TexturePtr;