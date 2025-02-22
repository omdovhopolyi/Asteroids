#include "PauseGameState.h"
#include <Messenger/Events/Common.h>
#include <ECS/SystemsManager.h>
#include <ECS/Systems/TimeSystem.h>

namespace asteroids
{
    std::string PauseGameState::StateId = "PauseState";

    PauseGameState::PauseGameState(const std::string& id)
        : shen::State(id)
    {}

    void PauseGameState::OnEnter(const std::string& fromState)
    {
        if (auto systems = GetSystemsManager())
        {
            auto& time = systems->GetTime();
            time.PauseGame(true);
        }

        InitSubscriptions();
    }

    void PauseGameState::OnExit(const std::string& toState)
    {
        ResetSubscriptions();

        if (auto systems = GetSystemsManager())
        {
            auto& time = systems->GetTime();
            time.PauseGame(false);
        }
    }

    void PauseGameState::InitSubscriptions()
    {
        _subscriptions.Subscribe<shen::PauseGameEvent>([this](const auto&)
        {
            ScheduleState("GameState");
        });
    }

    void PauseGameState::ResetSubscriptions()
    {
        _subscriptions.Reset();
    }
}
