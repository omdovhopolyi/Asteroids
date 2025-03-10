#pragma once

#include "ECS/Components/TagComponent.h"
#include "GameEnums/AsteroidTypeEnum.h"

namespace shen
{
    class Serialization;
}

namespace asteroids
{
    struct Player : shen::TagBaseComponent
    {
        static void Load(Player& component, const shen::Serialization& serialization);
        static void Save(Player& component, shen::Serialization& serialization);
    };

    struct Bullet
    {
        int damage = 1;
        float speed = 10;

        static void Load(Bullet& component, const shen::Serialization& serialization);
        static void Save(Bullet& component, shen::Serialization& serialization);
    };

    struct Asteroid
    {
        int damage = 1;
        int lives = 3;
        float speed = 1.f;
        int points = 1;

        static void Load(Asteroid& component, const shen::Serialization& serialization);
        static void Save(Asteroid& component, shen::Serialization& serialization);
    };

    struct AsteroidSpawner
    {
        std::string config;

        float minDelay = 1.f;
        float maxDelay = 2.f;
        float currentDelay = 1.f;
        std::map<AsteroidType, int> asteroidsToLunch;

        static void Load(AsteroidSpawner& component, const shen::Serialization& serialization);
        static void Save(AsteroidSpawner& component, shen::Serialization& serialization);
    };

    struct Lifetime
    {
        float time = 0.f;

        static void Load(Lifetime& component, const shen::Serialization& serialization);
        static void Save(Lifetime& component, shen::Serialization& serialization);
    };

    struct OffscreenMove : shen::TagBaseComponent
    {
        static void Load(OffscreenMove& component, const shen::Serialization& serialization) {};
        static void Save(OffscreenMove& component, shen::Serialization& serialization) {};
    };

    struct EndLevelDelay
    {
        float delay = 3.f;
        float time = 0.f;

        static void Load(EndLevelDelay& component, const shen::Serialization& serialization);
        static void Save(EndLevelDelay& component, shen::Serialization& serialization);
    };

    struct Explosion
    {
        std::string assetId;
        sf::Vector2f position;
        sf::Vector2f scale;
        std::string soundId;
    };
}
