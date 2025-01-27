#pragma once

#include "ECS/Systems/BaseSystems/System.h"
#include <vector>
#include <memory>

namespace asteroids
{
    class ExplosionsListConfig
        : public shen::System
    {
        SYSTEMS_FACTORY(ExplosionsListConfig)

    public:
        using Ptr = std::shared_ptr<ExplosionsListConfig>;
        using WeakPtr = std::weak_ptr<ExplosionsListConfig>;

        void Load() override;

        std::string GetRandomExplosion() const;

    private:
        std::vector<std::string> _explosionAssetsIds;
    };
}
