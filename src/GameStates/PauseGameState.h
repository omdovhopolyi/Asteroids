#pragma once

#include "ECS/Systems/GameStates/State.h"
#include <Messenger/SubscriptionsContainer.h>

namespace asteroids
{
    class PauseGameState
        : public shen::State
    {
    public:
        static std::string StateId;

        PauseGameState(const std::string& id);

        void OnEnter(const std::string& fromState) override;
        void OnExit(const std::string& toState) override;

    private:
        void InitSubscriptions();
        void ResetSubscriptions();
        void OpenWindow();
        void CloseWindow();
        void PauseGame();
        void UnpauseGame();

    private:
        shen::SubcriptionsContainer _subscriptions;
    };
}

