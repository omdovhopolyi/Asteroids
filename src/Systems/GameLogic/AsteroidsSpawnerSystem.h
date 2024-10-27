#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"

namespace asteroids
{
    class AsteroidsSpawnerSystem
        : public shen::UpdateSystem
    {
        SYSTEMS_FACTORY(AsteroidsSpawnerSystem)

    public:
        void Start() override;
        void Update() override;
    };
}
