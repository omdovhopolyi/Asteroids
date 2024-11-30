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
        float speed = 10;

        static void Load(Bullet& component, const shen::Serialization& serialization);
        static void Save(Bullet& component, shen::Serialization& serialization);
    };

    struct Asteroid
    {
        int damage = 1;
        int lives = 3;
        float speed = 1.f;

        static void Load(Asteroid& component, const shen::Serialization& serialization);
        static void Save(Asteroid& component, shen::Serialization& serialization);
    };

    struct Lifetime
    {
        float time = 0.f;

        static void Load(Lifetime& component, const shen::Serialization& serialization);
        static void Save(Lifetime& component, shen::Serialization& serialization);
    };
}
