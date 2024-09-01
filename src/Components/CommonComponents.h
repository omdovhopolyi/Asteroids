#pragma once

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
}
