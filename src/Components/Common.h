#pragma once

#include "ECS/Components/TagComponent.h"
#include "GameEnums/AsteroidTypeEnum.h"

namespace shen
{
    class DataElementWrapper;
}

namespace asteroids
{
    struct Player : shen::TagBaseComponent
    {
        static void Load(Player& component, const shen::DataElementWrapper& elementWrapper);
        static void Save(Player& component, shen::DataElementWrapper& elementWrapper);
    };

    struct Bullet
    {
        int damage = 1;
        float speed = 10;

        static void Load(Bullet& component, const shen::DataElementWrapper& elementWrapper);
        static void Save(Bullet& component, shen::DataElementWrapper& elementWrapper);
    };

    struct Asteroid
    {
        int damage = 1;
        int lives = 3;
        float speed = 1.f;
        int points = 1;

        static void Load(Asteroid& component, const shen::DataElementWrapper& elementWrapper);
        static void Save(Asteroid& component, shen::DataElementWrapper& elementWrapper);
    };

    struct AsteroidSpawner
    {
        std::string config;

        float minDelay = 1.f;
        float maxDelay = 2.f;
        float currentDelay = 1.f;
        std::map<AsteroidType, int> asteroidsToLunch;

        static void Load(AsteroidSpawner& component, const shen::DataElementWrapper& elementWrapper);
        static void Save(AsteroidSpawner& component, shen::DataElementWrapper& elementWrapper);
    };

    struct Lifetime
    {
        float time = 0.f;

        static void Load(Lifetime& component, const shen::DataElementWrapper& elementWrapper);
        static void Save(Lifetime& component, shen::DataElementWrapper& elementWrapper);
    };

    struct OffscreenMove : shen::TagBaseComponent
    {
        static void Load(OffscreenMove& component, const shen::DataElementWrapper& elementWrapper) {};
        static void Save(OffscreenMove& component, shen::DataElementWrapper& elementWrapper) {};
    };

    struct EndLevelDelay
    {
        float delay = 3.f;
        float time = 0.f;

        static void Load(EndLevelDelay& component, const shen::DataElementWrapper& elementWrapper);
        static void Save(EndLevelDelay& component, shen::DataElementWrapper& elementWrapper);
    };

    struct Explosion
    {
        std::string assetId;
        sf::Vector2f position;
        sf::Vector2f scale;
        std::string soundId;
    };
}
