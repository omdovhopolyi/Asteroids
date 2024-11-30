#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"

namespace asteroids
{
    class LifetimeSystem
        : public shen::UpdateSystem
    {
        SYSTEMS_FACTORY(LifetimeSystem)

    public:
        void Update() override;
    };
}
