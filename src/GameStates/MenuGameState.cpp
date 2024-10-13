#include "MenuGameState.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/UI/WindowsManager.h"

namespace asteroids
{
    std::string MenuGameState::StateId = "MenuState";

    MenuGameState::MenuGameState(const std::string& id)
        : shen::State(id)
    {}

    void MenuGameState::Init(shen::StateMachineSystem* stateMachineSystem)
    {
        auto systems = GetSystemsManager();
        auto windowsManager = systems->GetSystem<shen::WindowsManager>();

        auto windowContext = shen::UIWindowContext{};
        windowContext.windowId = "menu_window";
        windowContext.systems = systems;

        windowsManager->OpenWindow(windowContext);
    }

    void MenuGameState::Update()
    {

    }
}
