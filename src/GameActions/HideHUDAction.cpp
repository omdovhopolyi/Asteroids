#include "HideHUDAction.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/UI/WindowsManager.h"

namespace asteroids
{
    void HideHUDAction::Execute(const shen::ContextBase& context) const
    {
        if (auto windowsManager = context.systems->GetSystem<shen::WindowsManager>())
        {
            windowsManager->CloseWindow("hud_window");
        }
    }
}
