#include "MenuWindow.h"
#include "MessengerEvents/Common.h"
#include <UI/UIWindow.h>
#include <UI/Components/UIButtonComponent.h>
#include <Messenger/Events/Common.h>

namespace asteroids
{
    void MenuWindow::RegisterReferences()
    {
        RegisterReference("playButton", _playButton);
        RegisterReference("manualButton", _manualButton);
        RegisterReference("quitButton", _quitButton);
    }

    void MenuWindow::Init()
    {
        InitButtonsSubscriptions();
    }

    void MenuWindow::InitButtonsSubscriptions()
    {
        if (auto button = _playButton.Get())
        {
            button->GetSignal().Subscribe(shen::ButtonSignalType::Up, [this]()
            {
                shen::Messenger::Instance().Broadcast<MenuStatePlayButtonPressedEvent>();
            });
        }

        if (auto button = _manualButton.Get())
        {
            button->GetSignal().Subscribe(shen::ButtonSignalType::Up, [this]()
            {
                shen::Messenger::Instance().Broadcast<MenuStateManualButtonPressedEvent>();
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