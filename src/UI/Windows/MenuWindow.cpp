#include "MenuWindow.h"
#include "MessengerEvents/Common.h"
#include <UI/UIWindow.h>
#include <UI/Components/UIButtonComponent.h>
#include <Messenger/Events/Common.h>
#include <Serialization/Types/SerializationFieldRef.h>

namespace asteroids
{
    REGISTER_CLASS_LOADER(MenuWindow);

    void MenuWindow::RegisterProperties()
    {
        shen::UIWindowComponent::RegisterProperties();

        RegisterVar<shen::SerializableFieldRef<shen::UIComponentWrapper<shen::UIButtonComponent>>>(_playButton, "playButton", weak_from_this());
        RegisterVar<shen::SerializableFieldRef<shen::UIComponentWrapper<shen::UIButtonComponent>>>(_manualButton, "manualButton", weak_from_this());
        RegisterVar<shen::SerializableFieldRef<shen::UIComponentWrapper<shen::UIButtonComponent>>>(_quitButton, "quitButton", weak_from_this());
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