#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"
#include <ECS/Entity.h>

namespace asteroids
{
    class PlayerAsteroidCollisionSystem
        : public shen::UpdateSystem
    {
        SYSTEMS_FACTORY(PlayerAsteroidCollisionSystem)

    public:
        void Update() override;

    private:
        void CreateAsteroidExplosion(shen::Entity entity);
        void CreatePlayerExplosion(shen::Entity entity);
        void CreateExplosion(shen::Entity entity, const std::string& assetId, const std::string& soundId);
    };
}
