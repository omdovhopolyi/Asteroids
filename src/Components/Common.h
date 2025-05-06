#pragma once

#include "ECS/Components/TagComponent.h"
#include "GameEnums/AsteroidTypeEnum.h"
#include "Serialization/Serializable.h"

namespace shen
{
    class DataElementWrapper;
}

namespace asteroids
{
    struct Player
        : public shen::Serializable
    {
        SERIALIZABLE_COMP(Player)
    };

    struct Bullet
        : public shen::Serializable
    {
        SERIALIZABLE_COMP(Bullet)

        int damage = 1;
        float speed = 10;

        void RegisterProperties() override;
    };

    struct Asteroid
        : public shen::Serializable
    {
        SERIALIZABLE_COMP(Asteroid)

        int damage = 1;
        int lives = 3;
        float speed = 1.f;
        int points = 1;

        void RegisterProperties() override;
    };

    struct AsteroidSpawner
        : public shen::Serializable
    {
        SERIALIZABLE_COMP(AsteroidSpawner)

        std::string config;

        float minDelay = 1.f;
        float maxDelay = 2.f;
        float currentDelay = 1.f;
        std::map<AsteroidType, int> asteroidsToLunch;

        void RegisterProperties() override;
    };

    struct Lifetime
        : public shen::Serializable
    {
        SERIALIZABLE_COMP(Lifetime)

        float time = 0.f;

        void RegisterProperties() override;
    };

    struct OffscreenMove
        : public shen::Serializable
    {
        SERIALIZABLE_COMP(OffscreenMove)
    };

    struct EndLevelDelay
        : public shen::Serializable
    {
        SERIALIZABLE_COMP(EndLevelDelay)

        float delay = 3.f;
        float time = 0.f;

        void RegisterProperties() override;
    };

    struct Explosion
    {
        std::string assetId;
        sf::Vector2f position;
        sf::Vector2f scale;
        std::string soundId;
    };
}
