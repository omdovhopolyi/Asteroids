#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"

namespace asteroids
{
    class AsteroidBulletCollisionSystem
        : public shen::UpdateSystem
    {
        SYSTEMS_FACTORY(AsteroidBulletCollisionSystem)

    public:
        void Update() override;
    };
}
