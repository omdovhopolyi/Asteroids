#pragma once

#include "ECS/Systems/BaseSystems/System.h"
#include "Utils/UsingPtrsMacro.h"
#include "Conditions/ConditionBase.h"
#include "Actions/ActionBase.h"
#include <map>

namespace asteroids
{
    class LevelConfig
    {
    public:
        int index = -1;
        std::string mapId;
        std::shared_ptr<shen::ConditionBase> winCondition;
        std::shared_ptr<shen::ConditionBase> loseCondition;
        std::shared_ptr<shen::ActionBase> winAction;
        std::shared_ptr<shen::ActionBase> loseActions;
    };

    class LevelsConfig
        : public shen::System
    {
        SYSTEMS_FACTORY(LevelsConfig)

    public:
        void Load() override;

        std::shared_ptr<LevelConfig> GetConfig(int index) const;

    private:
        std::map<int, std::shared_ptr<LevelConfig>> _levels;
    };
}
