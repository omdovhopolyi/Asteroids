#include "MenuWindow.h"
#include <UI/UIWindow.h>
#include <UI/Components/UIButtonComponent.h>
#include <Messenger/Messenger.h>
#include <Messenger/Events/Common.h>

namespace asteroids
{
    void MenuWindow::RegisterReferences()
    {
        RegisterReference("playButton", &_playButton);
        RegisterReference("settingsButton", &_settingsButton);
        RegisterReference("quitButton", &_quitButton);
    }

    void MenuWindow::Init()
    {
        InitButtonsSubscriptions();
    }

    void MenuWindow::InitButtonsSubscriptions()
    {
        if (auto button = std::dynamic_pointer_cast<shen::UIButtonComponent>(_playButton.lock()))
        {
            button->GetSignal().Subscribe(shen::ButtonSignalType::Up, [this]()
            {
                bool check = true;
            });
        }

        if (auto button = std::dynamic_pointer_cast<shen::UIButtonComponent>(_settingsButton.lock()))
        {
            button->GetSignal().Subscribe(shen::ButtonSignalType::Up, [this]()
            {
                // TODO
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