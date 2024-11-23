#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"

namespace asteroids
{
    class PlayerAsteroidCollisionSystem
        : public shen::UpdateSystem
    {
        SYSTEMS_FACTORY(PlayerAsteroidCollisionSystem)

    public:
        void Update() override;
    };
}
