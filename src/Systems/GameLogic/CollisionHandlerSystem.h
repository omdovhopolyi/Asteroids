#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"

namespace asteroids
{
    class CollisionHandlerSystem
        : public shen::UpdateSystem
    {
        SYSTEMS_FACTORY(CollisionHandlerSystem)

    public:
        void Update() override;
    };
}
