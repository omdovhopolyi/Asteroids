#pragma once

#include "ECS/Systems/GameStates/State.h"
#include <Messenger/SubscriptionsContainer.h>

namespace asteroids
{
    class GameOverGameState
        : public shen::State
    {
    public:
        static std::string StateId;

        GameOverGameState(const std::string& id);

        void Init(shen::StateMachineSystem* stateMachineSystem) override;
        void OnEnter(const std::string&) override;
        void OnExit(const std::string&) override;

    private:
        void OpenWindow();
        void InitSubscriptions();
        void ResetScore();

    private:
        shen::SubcriptionsContainer _subscriptions;
    };
}
