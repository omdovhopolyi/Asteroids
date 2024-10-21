#include "PlayerInfo.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(PlayerInfo)

    void PlayerInfo::Start()
    {

    }

    void PlayerInfo::Save()
    {
        // TODO implement
    }

    void PlayerInfo::Load()
    {
        // TODO implement
    }

    void PlayerInfo::SetFlag(const std::string& flag)
    {
        _flags.insert(flag);
    }

    void PlayerInfo::ResetFlag(const std::string& flag)
    {
        _flags.erase(flag);
    }

    bool PlayerInfo::IsFlagSet(const std::string& flag)
    {
        return _flags.contains(flag);
    }

    void PlayerInfo::ResetAllFlags()
    {
        _flags.clear();
    }

    int PlayerInfo::GetResource(ResourceType type) const
    {
        if (const auto it = _resources.find(type); it != _resources.cend())
        {
            return it->second;
        }

        return 0;
    }

    void PlayerInfo::IncResource(ResourceType type)
    {
        if (auto it = _resources.find(type); it != _resources.end())
        {
            it->second++;
        }
    }

    void PlayerInfo::DecResource(ResourceType type)
    {
        if (auto it = _resources.find(type); it != _resources.end())
        {
            it->second--;
        }
    }

    void PlayerInfo::AddResource(ResourceType type, int amount)
    {
        if (auto it = _resources.find(type); it != _resources.end())
        {
            it->second += amount;
        }
    }

    void PlayerInfo::SetResource(ResourceType type, int amount)
    {
        if (auto it = _resources.find(type); it != _resources.end())
        {
            it->second = amount;
        }
    }

    void PlayerInfo::ResetResource(ResourceType type)
    {
        _resources.erase(type);
    }

    void PlayerInfo::ResetAllResources()
    {
        _resources.clear();
    }

    void PlayerInfo::SetLevel(int level)
    {
        _level = level;
    }

    int PlayerInfo::GetLevel() const
    {
        return _level;
    }

    void PlayerInfo::IncLevel()
    {
        _level++;
    }

    void PlayerInfo::ResetLevel()
    {
        _level = 1;
    }
}
