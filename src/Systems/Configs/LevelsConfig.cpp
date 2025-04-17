#include "LevelsConfig.h"
#include "Utils/FilePath.h"
#include "Utils/Assert.h"
#include "Serialization/WrapperTypes/XmlDataElementWrapper.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(LevelsConfig)

    void LevelsConfig::Load()
    {
        auto elementWrapper = shen::XmlDataElementWrapper{ _systems };
        elementWrapper.LoadFile(shen::FilePath::Path("assets/configs/levels.xml"));
        if (elementWrapper.IsValid())
        {
            elementWrapper.ForAllChildren("level", [&](const shen::DataElementWrapper& element)
            {
                auto levelConfig = std::make_shared<LevelConfig>();

                const int index = element.GetInt("index");
                levelConfig->index = index;
                levelConfig->mapId = element.GetStr("mapId");

                auto [it, isInserted] = _levels.insert({ index, std::move(levelConfig) });
                Assert(isInserted, "[LevelsConfig::Load] Possible duplicated config");
            });
        }
    }

    std::shared_ptr<LevelConfig> LevelsConfig::GetConfig(int index) const
    {
        if (auto it = _levels.find(index); it != _levels.end())
        {
            return it->second;
        }

        return nullptr;
    }

    bool LevelsConfig::HasLevel(int index) const
    {
        return GetConfig(index) != nullptr;
    }
}
