#include "PauseGameState.h"
#include "MessengerEvents/Common.h"
#include <Messenger/Events/Common.h>
#include <ECS/SystemsManager.h>
#include <ECS/Systems/TimeSystem.h>
#include "ECS/Systems/UI/WindowsManager.h"

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
        auto systems = GetSystemsManager();
        if (auto windowsManager = systems->GetSystem<shen::WindowsManager>())
        {
            auto windowContext = shen::UIWindowContext{};
            windowContext.windowId = "pause_window";
            windowContext.systems = systems;

            windowsManager->OpenWindow(windowContext);
        }
    }

    void PauseGameState::CloseWindow()
    {
        auto systems = GetSystemsManager();
        if (auto windowsManager = systems->GetSystem<shen::WindowsManager>())
        {
            windowsManager->CloseTopWindow();
        }
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
