#include "PauseGameState.h"
#include "MessengerEvents/Common.h"
#include <Messenger/Events/Common.h>
#include <Messenger/Events/UIEvents.h>
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
        PauseGame();
        OpenWindow();
        InitSubscriptions();
    }

    void PauseGameState::OnExit(const std::string& toState)
    {
        ResetSubscriptions();
        CloseWindow();
        UnpauseGame();
    }

    void PauseGameState::InitSubscriptions()
    {
        _subscriptions.Subscribe<shen::PauseGameEvent>([this](const auto&)
        {
            ScheduleState("GameState");
        });

        _subscriptions.Subscribe<PauseStateResumeButtonPressedEvent>([this](const auto& event)
        {
            ScheduleState("GameState");
        });
    }

    void PauseGameState::ResetSubscriptions()
    {
        _subscriptions.Reset();
    }

    void PauseGameState::OpenWindow()
    {
        shen::Messenger::Instance().Broadcast<shen::OpenWindowEvent>({ "pause_window" });
    }

    void PauseGameState::CloseWindow()
    {
        shen::Messenger::Instance().Broadcast<shen::CloseTopWindowEvent>();
    }

    void PauseGameState::PauseGame()
    {
        if (auto systems = GetSystemsManager())
        {
            auto& time = systems->GetTime();
            time.PauseGame(true);
        }
    }

    void PauseGameState::UnpauseGame()
    {
        if (auto systems = GetSystemsManager())
        {
            auto& time = systems->GetTime();
            time.PauseGame(false);
        }
    }
}
