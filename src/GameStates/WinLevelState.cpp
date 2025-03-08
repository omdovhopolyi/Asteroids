#include "WinLevelState.h"
#include "MessengerEvents/Common.h"
#include "Messenger/Events/Common.h"
#include "Messenger/Events/Sounds.h"
#include "Messenger/Events/UIEvents.h"
#include <ECS/SystemsManager.h>
#include "Systems/GameLogic/PlayerInfoSystem.h"
#include "Systems/Configs/LevelsConfig.h"

namespace asteroids
{
    std::string WinLevelState::StateId = "WinLevelState";

    WinLevelState::WinLevelState(const std::string& id)
        : shen::State(id)
    {}

    void WinLevelState::Init(shen::StateMachineSystem* stateMachineSystem)
    {
        InitSubscriptions();
    }

    void WinLevelState::OnEnter(const std::string&)
    {
        OpenWindow();
        shen::Messenger::Instance().Broadcast<shen::PlayMusicEvent>("track_win");
    }

    void WinLevelState::OnExit(const std::string&)
    {
        shen::Messenger::Instance().Broadcast<shen::CloseTopWindowEvent>();
        shen::Messenger::Instance().Broadcast<shen::StopMusicEvent>("track_win");
    }

    void WinLevelState::OpenWindow()
    {
        bool isGameWin = false;

        if (auto systems = GetSystemsManager())
        {
            const auto levelsConfig = systems->GetSystem<LevelsConfig>();
            const auto playerInfo = systems->GetSystem<PlayerInfoSystem>();

            if (levelsConfig && playerInfo)
            {
                isGameWin = !levelsConfig->HasLevel(playerInfo->GetLevel());
            }
        }
        
        shen::Messenger::Instance().Broadcast<shen::OpenWindowEvent>(isGameWin ? "win_game_window" : "win_level_window");
    }

    void WinLevelState::InitSubscriptions()
    {
        _subscriptions.Subscribe<WinLevelNextLevel>([this](const auto& event)
        {
            ScheduleState("GameState");
        });

        _subscriptions.Subscribe<AfterLevelExit>([this](const auto& event)
        {
            shen::Messenger::Instance().Broadcast<shen::Quit>();
        });

        _subscriptions.Subscribe<GameOverRetry>([this](const auto& event)
        {
            ResetLevel();
            ScheduleState("GameState");
        });
    }

    void WinLevelState::ResetLevel()
    {
        if (auto systems = GetSystemsManager())
        {
            if (auto playerInfo = systems->GetSystem<PlayerInfoSystem>())
            {
                playerInfo->ResetLevel();
            }
        }
    }
}
