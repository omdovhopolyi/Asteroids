#pragma once

#include "ECS/Components/TagComponent.h"

namespace shen
{
    class Serialization;
}

namespace asteroids
{
    struct Player
    {
        int lives = 3;

        static void Load(Player& component, const shen::Serialization& serialization);
        static void Save(Player& component, shen::Serialization& serialization);
    };

    struct Bullet
    {
        int damage = 1;

        static void Load(Bullet& component, const shen::Serialization& serialization);
        static void Save(Bullet& component, shen::Serialization& serialization);
    };

    struct Asteroid : shen::TagBaseComponent
    {
        int damage = 1;

        static void Load(Asteroid& component, const shen::Serialization& serialization);
        static void Save(Asteroid& component, shen::Serialization& serialization);
    };
}
