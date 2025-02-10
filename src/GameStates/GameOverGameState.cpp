#include "GameOverGameState.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/UI/WindowsManager.h"
#include "MessengerEvents/Common.h"
#include "Messenger/Events/Common.h"
#include "Messenger/Events/Sounds.h"

namespace asteroids
{
    std::string GameOverGameState::StateId = "GameOverState";

    GameOverGameState::GameOverGameState(const std::string& id)
        : shen::State(id)
    {}

    void GameOverGameState::Init(shen::StateMachineSystem* stateMachineSystem)
    {
        InitSubscriptions();
    }

    void GameOverGameState::OnEnter(const std::string&)
    {
        OpenWindow();
        shen::Messenger::Instance().Broadcast<shen::PlayMusicEvent>("track_lose");
    }

    void GameOverGameState::OnExit(const std::string&)
    {
        auto systems = GetSystemsManager();
        if (auto windowsManager = systems->GetSystem<shen::WindowsManager>())
        {
            windowsManager->CloseTopWindow();
        }

        shen::Messenger::Instance().Broadcast<shen::StopMusicEvent>("track_lose");
    }

    void GameOverGameState::OpenWindow()
    {
        auto systems = GetSystemsManager();
        if (auto windowsManager = systems->GetSystem<shen::WindowsManager>())
        {
            auto windowContext = shen::UIWindowContext{};
            windowContext.windowId = "game_over_window";
            windowContext.systems = systems;

            windowsManager->OpenWindow(windowContext);
        }
    }

    void GameOverGameState::InitSubscriptions()
    {
        _subscriptions.Subscribe<GameOverRetry>([this](const auto& event)
        {
            ScheduleState("GameState");
        });

        _subscriptions.Subscribe<AfterLevelExit>([this](const auto& event)
        {
            shen::Messenger::Instance().Broadcast<shen::Quit>();
        });
    }
}
