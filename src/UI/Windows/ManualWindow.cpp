#include "ManualWindow.h"
#include "MessengerEvents/Common.h"
#include <UI/UIWindow.h>
#include <UI/Components/UIButtonComponent.h>
#include <Messenger/Events/Common.h>

namespace asteroids
{
    void ManualWindow::Init()
    {
        InitButtonsSubscriptions();
    }

    void ManualWindow::RegisterReferences()
    {
        RegisterReference("backButton", _backButton);
    }

    void ManualWindow::InitButtonsSubscriptions()
    {
        if (auto button = _backButton.Get())
        {
            button->GetSignal().Subscribe(shen::ButtonSignalType::Up, [this]()
            {
                shen::Messenger::Instance().Broadcast<ManualWindowBackButtonPressedEvent>();
            });
        }
    }
}
