#pragma once

#include "ECS/Systems/BaseSystems/System.h"
#include "GameEnums/ResourcesEnum.h"
#include <map>
#include <set>

namespace asteroids
{
    class PlayerInfo
        : public shen::System
    {
        SYSTEMS_FACTORY(PlayerInfo)

    public:
        void Start() override;

        void Save() override;
        void Load() override;

        void SetFlag(const std::string& flag);
        void ResetFlag(const std::string& flag);
        bool IsFlagSet(const std::string& flag);
        void ResetAllFlags();

        int GetResource(ResourceType type) const;
        void IncResource(ResourceType type);
        void DecResource(ResourceType type);
        void AddResource(ResourceType type, int amount);
        void SetResource(ResourceType type, int amount);
        void ResetResource(ResourceType type);
        void ResetAllResources();

        void SetLevel(int level);
        int GetLevel() const;
        void IncLevel();
        void ResetLevel();

    private:
        int _level = 1;
        std::map<ResourceType, int> _resources;
        std::set<std::string> _flags;
    };
}
