#include "PauseWindow.h"
#include "MessengerEvents/Common.h"
#include <UI/UIWindow.h>
#include <UI/Components/UIButtonComponent.h>
#include <Messenger/Events/Common.h>

namespace asteroids
{
    void PauseWindow::RegisterReferences()
    {
        RegisterReference("resumeButton", _resumeButton);
        RegisterReference("quitButton", _quitButton);
    }

    void PauseWindow::Init()
    {
        InitButtonsSubscriptions();
    }

    void PauseWindow::InitButtonsSubscriptions()
    {
        if (auto button = _resumeButton.Get())
        {
            button->GetSignal().Subscribe(shen::ButtonSignalType::Up, [this]()
            {
                shen::Messenger::Instance().Broadcast<PauseStateResumeButtonPressedEvent>();
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