#include "MenuGameState.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/UI/WindowsManager.h"
#include "Systems/GameLogic/PlayerInfoSystem.h"
#include "MessengerEvents/Common.h"
#include "Messenger/Events/Sounds.h"
#include "Messenger/Events/UIEvents.h"

namespace asteroids
{
    std::string MenuGameState::StateId = "MenuState";

    MenuGameState::MenuGameState(const std::string& id)
        : shen::State(id)
    {}

    void MenuGameState::Init(shen::StateMachineSystem* stateMachineSystem)
    {
        InitSubscriptions();
        OpenMenuWindow();
    }

    void MenuGameState::OnEnter(const std::string&)
    {
        shen::Messenger::Instance().Broadcast<shen::PlayMusicEvent>("track_main");

        if (auto systems = GetSystemsManager())
        {
            if (auto playerInfo = systems->GetSystem<PlayerInfoSystem>())
            {
                playerInfo->SetResource(ResourceType::Score, 0);
            }
        }
    }

    void MenuGameState::OnExit(const std::string&)
    {
        shen::Messenger::Instance().Broadcast<shen::CloseTopWindowEvent>();
        shen::Messenger::Instance().Broadcast<shen::StopMusicEvent>("track_main");
    }

    void MenuGameState::OpenMenuWindow()
    {
        shen::Messenger::Instance().Broadcast<shen::OpenWindowEvent>({ "menu_window" });
    }

    void MenuGameState::InitSubscriptions()
    {
        _subscriptions.Subscribe<MenuStatePlayButtonPressedEvent>([this](const auto& event)
        {
            ScheduleState("GameState");
        });

        _subscriptions.Subscribe<ManualWindowBackButtonPressedEvent>([this](const auto& event)
        {
            shen::Messenger::Instance().Broadcast<shen::CloseTopWindowEvent>();
            shen::Messenger::Instance().Broadcast<shen::OpenWindowEvent>({ "menu_window" });
        });

        _subscriptions.Subscribe<MenuStateManualButtonPressedEvent>([this](const auto& event)
        {
            shen::Messenger::Instance().Broadcast<shen::CloseTopWindowEvent>();
            shen::Messenger::Instance().Broadcast<shen::OpenWindowEvent>({ "manual_window" });
        });
    }
}
