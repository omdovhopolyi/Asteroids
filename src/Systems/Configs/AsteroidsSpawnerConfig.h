#pragma once

#include "GameEnums/AsteroidTypeEnum.h"
#include "ECS/Systems/BaseSystems/System.h"
#include <map>
#include <memory>

namespace asteroids
{
    struct AsteroidTypeData
    {
        int amount = 0;
        std::string assetId;
    };

    class SpawnerLevelConfig
    {
    public:
        using Ptr = std::shared_ptr<SpawnerLevelConfig>;
        using WeakPtr = std::weak_ptr<SpawnerLevelConfig>;

        void SetAmount(AsteroidType type, const AsteroidTypeData& data);
        int GetAmount(AsteroidType type) const;

        const std::string& GetAssetId(AsteroidType type) const;

        void SetMinDelay(float delay);
        float GetMinDelay() const;

        void SetMaxDelay(float delay);
        float GetMaxDelay() const;

        const std::map<AsteroidType, AsteroidTypeData>& GetAsteroids() const;

    private:
        std::map<AsteroidType, AsteroidTypeData> _asteroidsPerLevel;
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

        const SpawnerLevelConfig::Ptr GetConfig(const std::string& id) const;

        void Load() override;

    private:
        std::map<std::string, std::shared_ptr<SpawnerLevelConfig>> _levels;
    };
}
