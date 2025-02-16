#include "MenuGameState.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/UI/WindowsManager.h"
#include "Systems/GameLogic/PlayerInfoSystem.h"
#include "MessengerEvents/Common.h"
#include "Messenger/Events/Sounds.h"

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
        auto systems = GetSystemsManager();
        if (auto windowsManager = systems->GetSystem<shen::WindowsManager>())
        {
            windowsManager->CloseTopWindow();
        }

        shen::Messenger::Instance().Broadcast<shen::StopMusicEvent>("track_main");
    }

    void MenuGameState::OpenMenuWindow()
    {
        auto systems = GetSystemsManager();
        if (auto windowsManager = systems->GetSystem<shen::WindowsManager>())
        {
            auto windowContext = shen::UIWindowContext{};
            windowContext.windowId = "menu_window";
            windowContext.systems = systems;

            windowsManager->OpenWindow(windowContext);
        }
    }

    void MenuGameState::InitSubscriptions()
    {
        _subscriptions.Subscribe<MenuStatePlayButtonPressedEvent>([this](const auto& event)
        {
            ScheduleState("GameState");
        });
    }
}
