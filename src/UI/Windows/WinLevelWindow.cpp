#include "WinLevelWindow.h"
#include "MessengerEvents/Common.h"
#include <UI/UIWindow.h>
#include <UI/Components/UIButtonComponent.h>
#include <Messenger/Events/Common.h>

namespace asteroids
{
    void WinLevelWindow::RegisterReferences()
    {
        RegisterReference("nextButton", &_nextButton);
        RegisterReference("quitButton", &_quitButton);
    }

    void WinLevelWindow::Init()
    {
        InitButtonsSubscriptions();
    }

    void WinLevelWindow::InitButtonsSubscriptions()
    {
        if (auto button = std::dynamic_pointer_cast<shen::UIButtonComponent>(_nextButton.lock()))
        {
            button->GetSignal().Subscribe(shen::ButtonSignalType::Up, [this]()
            {
                shen::Messenger::Instance().Broadcast<MenuStatePlayButtonPressedEvent>();
            });
        }

        if (auto button = std::dynamic_pointer_cast<shen::UIButtonComponent>(_quitButton.lock()))
        {
            button->GetSignal().Subscribe(shen::ButtonSignalType::Up, [this]()
            {
                shen::Messenger::Instance().Broadcast<shen::Quit>();
            });
        }
    }
}