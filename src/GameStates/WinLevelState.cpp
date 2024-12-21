#include "WinLevelState.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/UI/WindowsManager.h"
#include "MessengerEvents/Common.h"
#include "Messenger/Events/Common.h"

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
    }

    void WinLevelState::Update()
    {

    }

    void WinLevelState::OnExit(const std::string&)
    {
        auto systems = GetSystemsManager();
        if (auto windowsManager = systems->GetSystem<shen::WindowsManager>())
        {
            windowsManager->CloseTopWindow();
        }
    }

    void WinLevelState::OpenWindow()
    {
        auto systems = GetSystemsManager();
        if (auto windowsManager = systems->GetSystem<shen::WindowsManager>())
        {
            auto windowContext = shen::UIWindowContext{};
            windowContext.windowId = "win_level_window";
            windowContext.systems = systems;

            windowsManager->OpenWindow(windowContext);
        }
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
    }
}
