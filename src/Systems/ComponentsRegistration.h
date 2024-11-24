#pragma once

#include "ECS/Systems/BaseSystems/System.h"

namespace asteroids
{
    class ComponentsRegistration
        : public shen::System
    {
        SYSTEMS_FACTORY(ComponentsRegistration)

    public:
        void Load() override;
    };
}
