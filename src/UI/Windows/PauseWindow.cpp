#include "PauseWindow.h"
#include "MessengerEvents/Common.h"
#include <UI/UIWindow.h>
#include <UI/Components/UIButtonComponent.h>
#include <Messenger/Events/Common.h>
#include <Serialization/Types/SerializableFieldRef.h>

namespace asteroids
{
    REGISTER_LOADER(PauseWindow);

    void PauseWindow::RegisterProperties()
    {
        shen::UIWindowComponent::RegisterProperties();

        RegisterVar<shen::SerializableFieldRef<shen::UIComponentWrapper<shen::UIButtonComponent>>>(_resumeButton, "resumeButton", weak_from_this());
        RegisterVar<shen::SerializableFieldRef<shen::UIComponentWrapper<shen::UIButtonComponent>>>(_quitButton, "quitButton", weak_from_this());
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