#include "AsteroidsSpawnerConfig.h"
#include "Serialization/Serialization.h"
#include "GameEnums/AsteroidTypeEnum.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(SpawnerConfig);

    void SpawnerLevelConfig::SetAmount(AsteroidType type, int amount)
    {
        _asteroidsPerLevel[type] = amount;
    }

    int SpawnerLevelConfig::GetAmount(AsteroidType type) const
    {
        if (auto it = _asteroidsPerLevel.find(type); it != _asteroidsPerLevel.end())
        {
            return it->second;
        }

        return 0;
    }

    const SpawnerLevelConfig::WeakPtr SpawnerConfig::GetLevelConfig(int level) const
    {
        if (auto it = _levels.find(level); it != _levels.end())
        {
            return it->second;
        }

        return {};
    }

    void SpawnerConfig::Load()
    {
        const std::string fileName = "../assets/configs/asteroids_spawner.xml";
        auto serialization = shen::Serialization{ _systems, fileName };
        serialization.SetupElement("spawner");
        if (auto levelsElement = serialization.GetElement("levels"); levelsElement.IsValid())
        {
            levelsElement.ForAllChildElements("level", [&](const shen::Serialization& element)
            {
                const auto level = element.GetInt("index");
                auto [it, isInserted] = _levels.insert({ level, std::make_shared<SpawnerLevelConfig>() });

                if (isInserted)
                {
                    element.ForAllChildElements("item", [&, levelConfig = it->second](const shen::Serialization& item)
                    {
                        const auto type = AsteroidTypeEnum.FromString(item.GetStr("type"));
                        const auto amount = item.GetInt("amount");

                        levelConfig->SetAmount(type, amount);
                    });
                }
            });
        }
    }
}
