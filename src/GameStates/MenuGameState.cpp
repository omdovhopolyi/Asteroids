#include "MenuGameState.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/UI/WindowsManager.h"
#include "MessengerEvents/Common.h"

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

    void MenuGameState::Update()
    {

    }

    void MenuGameState::OnExit(const std::string&)
    {
        auto systems = GetSystemsManager();
        if (auto windowsManager = systems->GetSystem<shen::WindowsManager>())
        {
            windowsManager->CloseTopWindow();
        }
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
