#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"

namespace asteroids
{
    class OffscreenMoverSystem
        : public shen::UpdateSystem
    {
        SYSTEMS_FACTORY(OffscreenMoverSystem)

    public:
        void Update() override;
    };
}
