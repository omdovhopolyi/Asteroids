#pragma once

#include "ECS/Systems/GameStates/State.h"
#include "Systems/Configs/LevelsConfig.h"
#include "Conditions/ConditionBase.h"
#include <Messenger/SubscriptionsContainer.h>

namespace asteroids
{
    class PlayingGameState
        : public shen::State
    {
    public:
        static std::string StateId;

        PlayingGameState(const std::string& id);

        void Init(shen::StateMachineSystem* stateMachineSystem) override;
        void OnEnter(const std::string& fromState) override;
        void Update() override;
        void OnExit(const std::string&) override;

        void AppActivated() override;
        void AppDeactivated() override;

    private:
        void InitSubscriptions();
        void ResetSubscriptions();
        void StartLevel(int index);

        void ExecuteStartActions();
        void ExecuteWinAction();
        void ExecuteLoseAction();

        void ExecuteActions(const std::vector<std::shared_ptr<shen::ActionBase>>& actions);

    private:
        std::shared_ptr<shen::ContextBase> _context;
        std::weak_ptr<LevelConfig> _currentConfig;
        std::shared_ptr<shen::ConditionBase> _winCondition;
        std::shared_ptr<shen::ConditionBase> _loseCondition;
        std::shared_ptr<shen::ConditionBase> _winGameCondition;
        std::vector<std::shared_ptr<shen::ActionBase>> _startActions;
        std::vector<std::shared_ptr<shen::ActionBase>> _winActions;
        std::vector<std::shared_ptr<shen::ActionBase>> _loseActions;

        shen::SubcriptionsContainer _subscriptions;
    };
}

