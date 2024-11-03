#include "PlayerInfoSystem.h"

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
        // TODO implement
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
            it->second--;
        }
    }

    void PlayerInfoSystem::AddResource(ResourceType type, int amount)
    {
        if (auto it = _resources.find(type); it != _resources.end())
        {
            it->second += amount;
        }
    }

    void PlayerInfoSystem::SetResource(ResourceType type, int amount)
    {
        if (auto it = _resources.find(type); it != _resources.end())
        {
            it->second = amount;
        }
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
}
