#pragma once

#include "GameEnums/AsteroidTypeEnum.h"
#include "ECS/Systems/BaseSystems/System.h"
#include <map>
#include <memory>

namespace asteroids
{
    class SpawnerLevelConfig
    {
    public:
        using Ptr = std::shared_ptr<SpawnerLevelConfig>;
        using WeakPtr = std::weak_ptr<SpawnerLevelConfig>;

        void SetAmount(AsteroidType type, int amount);
        int GetAmount(AsteroidType type) const;

        void SetMinDelay(float delay);
        float GetMinDelay() const;

        void SetMaxDelay(float delay);
        float GetMaxDelay() const;

    private:
        std::map<AsteroidType, int> _asteroidsPerLevel;
        float _minDelay = 1.f;
        float _maxDelay = 5.f;
    };

    class SpawnerConfig
        : public shen::System
    {
        SYSTEMS_FACTORY(SpawnerConfig)

    public:
        using Ptr = std::shared_ptr<SpawnerConfig>;
        using WeakPtr = std::weak_ptr<SpawnerConfig>;

        const SpawnerLevelConfig::WeakPtr GetLevelConfig(int level) const;

        void Load() override;

    private:
        std::map<int, std::shared_ptr<SpawnerLevelConfig>> _levels;
    };
}
