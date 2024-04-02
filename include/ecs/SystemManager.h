#pragma once
#include <memory>
#include "Types.h"
#include <unordered_map>
#include "Systems/System.h"

class SystemManager
{
public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        const char* typeName = typeid(T).name();

        assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

        // Create a pointer to the system and return it so it can be used externally
        auto system = std::make_shared<T>();
        mSystems.insert({ typeName, system });
        return system;
    }

    template<typename T>
    void SetSignature(Signature signature)
    {
        const char* typeName = typeid(T).name();

        assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

        // Set the signature for this system
        mSignatures.insert({ typeName, signature });
    }

    void EntityDestroyed(Entity entity)
    {
        // Erase a destroyed entity from all system lists
        // mEntities is a set so no check needed
        for (auto const& pair : mSystems)
        {
            auto const& system = pair.second;

            system->mEntities.erase(entity);
        }
    }

    void EntitySignatureChanged(Entity entity, Signature entitySignature)
    {
        // Notify each system that an entity's signature changed
        for (auto const& pair : mSystems)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = mSignatures[type];

            // Entity signature contains same bits as system signature - add to set
            if ((entitySignature & systemSignature) == systemSignature)
            {
                system->mEntities.insert(entity);
            }
            // Entity signature does not match system signature - erase from set
            else
            {
                system->mEntities.erase(entity);
            }
        }
    }

    void RemoveFromEntities(std::vector<Entity> &v, Entity K) {
        auto it = find(v.begin(), v.end(), K);

        // If element was found
        if (it != v.end())
        {
            v.erase(it);
        }
    }

private:
    // TileMap from system type string pointer to a signature
    std::unordered_map<const char*, Signature> mSignatures{};

    // TileMap from system type string pointer to a system pointer
    std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
};
