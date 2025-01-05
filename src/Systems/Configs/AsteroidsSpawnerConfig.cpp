#include "AsteroidsSpawnerConfig.h"
#include "Serialization/Serialization.h"
#include "GameEnums/AsteroidTypeEnum.h"
#include "Utils/FilePath.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(SpawnerConfig);

    void SpawnerLevelConfig::SetAmount(AsteroidType type, const AsteroidTypeData& data)
    {
        _asteroidsPerLevel[type] = data;
    }

    int SpawnerLevelConfig::GetAmount(AsteroidType type) const
    {
        if (auto it = _asteroidsPerLevel.find(type); it != _asteroidsPerLevel.end())
        {
            return it->second.amount;
        }

        return 0;
    }

    const std::string& SpawnerLevelConfig::GetAssetId(AsteroidType type) const
    {
        if (auto it = _asteroidsPerLevel.find(type); it != _asteroidsPerLevel.end())
        {
            return it->second.assetId;
        }

        static std::string empty;
        return empty;
    }

    void SpawnerLevelConfig::SetMinDelay(float delay)
    {
        _minDelay = delay;
    }

    float SpawnerLevelConfig::GetMinDelay() const
    {
        return _minDelay;
    }

    void SpawnerLevelConfig::SetMaxDelay(float delay)
    {
        _maxDelay = delay;
    }

    float SpawnerLevelConfig::GetMaxDelay() const
    {
        return _maxDelay;
    }

    const std::map<AsteroidType, AsteroidTypeData>& SpawnerLevelConfig::GetAsteroids() const
    {
        return _asteroidsPerLevel;
    }

    const SpawnerLevelConfig::Ptr SpawnerConfig::GetConfig(const std::string& id) const
    {
        if (auto it = _levels.find(id); it != _levels.end())
        {
            return it->second;
        }

        return {};
    }

    float SpawnerConfig::GetMinTorque() const
    {
        return _minTorque;
    }

    float SpawnerConfig::GetMaxTorque() const
    {
        return _maxTorque;
    }

    void SpawnerConfig::Load()
    {
        const auto fileName = shen::FilePath::Path("assets/configs/asteroids_spawner.xml");
        auto serialization = shen::Serialization{ _systems, fileName };
        serialization.SetupElement("assets");
        serialization.ForAllChildElements("asset", [&](const shen::Serialization& element)
        {
            const auto id = element.GetStr("id");
            auto [it, isInserted] = _levels.insert({ id, std::make_shared<SpawnerLevelConfig>() });

            if (isInserted)
            {
                element.ForAllChildElements("item", [&, levelConfig = it->second](const shen::Serialization& item)
                {
                    const auto type = AsteroidTypeEnum.FromString(item.GetStr("type"));
                    const auto amount = item.GetInt("amount");
                    const auto assetId = item.GetStr("assetId");

                    levelConfig->SetAmount(type, { amount, assetId });
                });

                const int minDelay = element.GetInt("minDelay", it->second->GetMinDelay());
                const int maxDelay = element.GetInt("maxDelay", it->second->GetMaxDelay());

                it->second->SetMinDelay(minDelay);
                it->second->SetMaxDelay(maxDelay);
            }
        });
    }
}
