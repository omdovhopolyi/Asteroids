#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"
#include "Utils/TimedFunction.h"
#include "GameEnums/AsteroidTypeEnum.h"

namespace asteroids
{
    class AsteroidsSpawnerSystem
        : public shen::UpdateSystem
    {
        SYSTEMS_FACTORY(AsteroidsSpawnerSystem)

    public:
        void Start() override;
        void Update() override;

    private:
        void Spawn(AsteroidType type);

    private:
        shen::TimedFunction _updateFunc;
        float _spawnDelay = 1.f;

    };
}
