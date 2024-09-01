#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"

namespace asteroids
{
    class ComponentsRegistration
        : public shen::UpdateSystem
    {
        SYSTEMS_FACTORY(ComponentsRegistration)

    public:
        void Start() override;
    };
}
