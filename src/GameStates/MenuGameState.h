#pragma once

#include "ECS/Systems/GameStates/State.h"
#include <Messenger/SubscriptionsContainer.h>

namespace asteroids
{
    class MenuGameState
        : public shen::State
    {
    public:
        static std::string StateId;

        MenuGameState(const std::string& id);

        void Init(shen::StateMachineSystem* stateMachineSystem) override;
        void OnEnter(const std::string&) override;
        void OnExit(const std::string&) override;

    private:
        void OpenMenuWindow();
        void InitSubscriptions();

    private:
        shen::SubcriptionsContainer _subscriptions;
    };
}
