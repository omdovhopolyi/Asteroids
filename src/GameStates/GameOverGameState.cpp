#include "GameOverGameState.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/UI/WindowsManager.h"
#include "MessengerEvents/Common.h"
#include "Messenger/Events/Common.h"
#include "Messenger/Events/Sounds.h"
#include "Messenger/Events/UIEvents.h"
#include "Systems/GameLogic/PlayerInfoSystem.h"

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
        shen::Messenger::Instance().Broadcast<shen::CloseTopWindowEvent>();
        shen::Messenger::Instance().Broadcast<shen::StopMusicEvent>("track_lose");
    }

    void GameOverGameState::OpenWindow()
    {
        shen::Messenger::Instance().Broadcast<shen::OpenWindowEvent>({ "game_over_window" });
    }

    void GameOverGameState::InitSubscriptions()
    {
        _subscriptions.Subscribe<GameOverRetry>([this](const auto& event)
        {
            ScheduleState("GameState");
            ResetScore();
        });

        _subscriptions.Subscribe<AfterLevelExit>([this](const auto& event)
        {
            shen::Messenger::Instance().Broadcast<shen::Quit>();
        });
    }

    void GameOverGameState::ResetScore()
    {
        if (auto systems = GetSystemsManager())
        {
            if (auto playerInfo = systems->GetSystem<PlayerInfoSystem>())
            {
                playerInfo->SetResource(ResourceType::Score, 0);
            }
        }
    }
}
