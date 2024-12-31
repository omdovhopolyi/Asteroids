#include "PlayerInfoSystem.h"
#include "Utils/Assert.h"
#include "Utils/FilePath.h"
#include "Serialization/Serialization.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(PlayerInfoSystem)

    void PlayerInfoSystem::Start()
    {

    }

    void PlayerInfoSystem::Save()
    {
        // TODO implement
    }

    void PlayerInfoSystem::Load()
    {
        LoadConfig();
    }

    void PlayerInfoSystem::SetFlag(const std::string& flag)
    {
        _flags.insert(flag);
    }

    void PlayerInfoSystem::ResetFlag(const std::string& flag)
    {
        _flags.erase(flag);
    }

    bool PlayerInfoSystem::IsFlagSet(const std::string& flag)
    {
        return _flags.contains(flag);
    }

    void PlayerInfoSystem::ResetAllFlags()
    {
        _flags.clear();
    }

    int PlayerInfoSystem::GetResource(ResourceType type) const
    {
        if (const auto it = _resources.find(type); it != _resources.cend())
        {
            return it->second;
        }

        return 0;
    }

    void PlayerInfoSystem::IncResource(ResourceType type)
    {
        if (auto it = _resources.find(type); it != _resources.end())
        {
            it->second++;
        }
    }

    void PlayerInfoSystem::DecResource(ResourceType type)
    {
        if (auto it = _resources.find(type); it != _resources.end())
        {
            Assert(it->second > 0, std::format("[PlayerInfoSystem::DecResource] Cannot decrease resource {}", ResourceTypeEnum.ToString(type)));
            it->second--;
        }
    }

    void PlayerInfoSystem::AddResource(ResourceType type, int amount)
    {
        _resources[type] += amount;
    }

    void PlayerInfoSystem::SetResource(ResourceType type, int amount)
    {
        _resources[type] = amount;
    }

    void PlayerInfoSystem::ResetResource(ResourceType type)
    {
        _resources.erase(type);
    }

    void PlayerInfoSystem::ResetAllResources()
    {
        _resources.clear();
    }

    void PlayerInfoSystem::SetLevel(int level)
    {
        _level = level;
    }

    int PlayerInfoSystem::GetLevel() const
    {
        return _level;
    }

    void PlayerInfoSystem::IncLevel()
    {
        _level++;
    }

    void PlayerInfoSystem::ResetLevel()
    {
        _level = 1;
    }

    void PlayerInfoSystem::LoadConfig()
    {
        const auto fileName = shen::FilePath::Path("assets/configs/player_info.xml");
        auto serialization = shen::Serialization{ _systems, fileName };
        if (serialization.IsValid())
        {
            auto resourcesElement = serialization.GetElement("resources");
            resourcesElement.ForAllChildElements("item", [this](const auto& itemElement)
            {
                const auto typeStr = itemElement.GetStr("type");
                const auto type = ResourceTypeEnum.FromString(typeStr);
                const auto amount = itemElement.GetInt("amount");

                _resources[type] = amount;
            });
            
            auto flagsElement = serialization.GetElement("flags");
            flagsElement.ForAllChildElements("flag", [this](const auto& flagElement)
            {
                _flags.insert(flagElement.GetStr("flag"));
            });
        }
    }
}
