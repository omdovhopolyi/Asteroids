#pragma once

#include "ECS/Systems/GameStates/State.h"
#include "Systems/Configs/LevelsConfig.h"

namespace asteroids
{
    class PlayingGameState
        : public shen::State
    {
    public:
        static std::string StateId;

        PlayingGameState(const std::string& id);

        void Init(shen::StateMachineSystem* stateMachineSystem) override;
        void OnEnter(const std::string&) override;
        void Update() override;

    private:
        void StartLevel(int index);
        void ShowHud();

    private:
        std::shared_ptr<shen::ContextBase> _context;
        std::weak_ptr<LevelConfig> _currentConfig;
        std::shared_ptr<shen::ConditionBase> _winCondition;
        std::shared_ptr<shen::ConditionBase> _loseCondition;
        std::shared_ptr<shen::ConditionBase> _winGameCondition;
        std::vector<std::shared_ptr<shen::ActionBase>> _winActions;
        std::vector<std::shared_ptr<shen::ActionBase>> _loseActions;
    };
}

