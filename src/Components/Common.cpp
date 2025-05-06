#include "Common.h"
#include "Serialization/DataElementWrapper.h"
#include "Serialization/Types/SerializableFieldInt.h"
#include "Serialization/Types/SerializableFieldFloat.h"
#include "Serialization/Types/SerializableFieldString.h"

namespace asteroids
{
    REGISTER_LOADER(Player)

    REGISTER_LOADER(Bullet)

    void Bullet::RegisterProperties()
    {
        RegisterVar<shen::SerializableFieldInt>(damage, "damage");
        RegisterVar<shen::SerializableFieldFloat>(speed, "speed");
    }

    REGISTER_LOADER(Asteroid)

    void Asteroid::RegisterProperties()
    {
        RegisterVar<shen::SerializableFieldInt>(damage, "damage");
        RegisterVar<shen::SerializableFieldInt>(lives, "lives");
        RegisterVar<shen::SerializableFieldFloat>(speed, "speed");
    }

    REGISTER_LOADER(AsteroidSpawner)

    void AsteroidSpawner::RegisterProperties()
    {
        RegisterVar<shen::SerializableFieldString>(config, "config");
    }

    REGISTER_LOADER(Lifetime)

    void Lifetime::RegisterProperties()
    {
        RegisterVar<shen::SerializableFieldFloat>(time, "time");
    }

    REGISTER_LOADER(OffscreenMove)

    REGISTER_LOADER(EndLevelDelay)

    void EndLevelDelay::RegisterProperties()
    {
        RegisterVar<shen::SerializableFieldFloat>(delay, "delay");
    }
}
