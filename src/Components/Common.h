#pragma once

#include "ECS/Components/TagComponent.h"

namespace shen
{
    class Serialization;
}

namespace asteroids
{
    struct Bullet
    {
        int damage = 1;

        static void Load(Bullet& component, const shen::Serialization& serialization);
        static void Save(Bullet& component, shen::Serialization& serialization);
    };

    struct Asteroid : shen::TagBaseComponent
    {
        static void Load(Asteroid& component, const shen::Serialization& serialization);
        static void Save(Asteroid& component, shen::Serialization& serialization);
    };
}
