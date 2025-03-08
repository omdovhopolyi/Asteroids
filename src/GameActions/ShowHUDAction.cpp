#include "ShowHUDAction.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/UIEvents.h"

namespace asteroids
{
    void ShowHUDAction::Execute(const shen::ContextBase&) const
    {
        shen::Messenger::Instance().Broadcast<shen::OpenWindowEvent>("hud_window");
    }
}
