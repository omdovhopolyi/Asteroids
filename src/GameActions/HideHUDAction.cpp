#include "HideHUDAction.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/UIEvents.h"
#include "UI/UIWindowContext.h"

namespace asteroids
{
    void HideHUDAction::Execute(const shen::ContextBase&) const
    {
        shen::Messenger::Instance().Broadcast<shen::CloseWindowEvent>("hud_window");
    }
}
