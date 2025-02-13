#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"
#include "ECS/Entity.h"

namespace asteroids
{
    class AsteroidBulletCollisionSystem
        : public shen::UpdateSystem
    {
        SYSTEMS_FACTORY(AsteroidBulletCollisionSystem)

    public:
        void Update() override;

    private:
        void CreateHit(shen::Entity bulletEntity);
        void CreatedExplosion(shen::Entity asteroidEntity);
    };
}
