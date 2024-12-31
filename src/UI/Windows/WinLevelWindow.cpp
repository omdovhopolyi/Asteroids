#include "WinLevelWindow.h"
#include "MessengerEvents/Common.h"
#include <UI/UIWindow.h>
#include <UI/Components/UIButtonComponent.h>
#include <Messenger/Events/Common.h>

namespace asteroids
{
    void WinLevelWindow::RegisterReferences()
    {
        RegisterReference("nextButton", _nextButton);
        RegisterReference("quitButton", _quitButton);
    }

    void WinLevelWindow::Init()
    {
        InitButtonsSubscriptions();
    }

    void WinLevelWindow::InitButtonsSubscriptions()
    {
        if (auto button = _nextButton.Get())
        {
            button->GetSignal().Subscribe(shen::ButtonSignalType::Up, [this]()
            {
                shen::Messenger::Instance().Broadcast<MenuStatePlayButtonPressedEvent>();
            });
        }

        if (auto button = _quitButton.Get())
        {
            button->GetSignal().Subscribe(shen::ButtonSignalType::Up, [this]()
            {
                shen::Messenger::Instance().Broadcast<shen::Quit>();
            });
        }
    }
}