#include "ShowHUDAction.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/UI/WindowsManager.h"
#include "UI/UIWindowContext.h"

namespace asteroids
{
    void ShowHUDAction::Execute(const shen::ContextBase& context) const
    {
        if (auto windowsManager = context.systems->GetSystem<shen::WindowsManager>())
        {
            auto windowContext = shen::UIWindowContext{};
            windowContext.windowId = "hud_window";
            windowContext.systems = context.systems;

            windowsManager->OpenWindow(windowContext);
        }
    }
}
