#include "WinLevelWindow.h"
#include "MessengerEvents/Common.h"
#include <UI/UIWindow.h>
#include <UI/Components/UIButtonComponent.h>
#include <Messenger/Events/Common.h>
#include <Serialization/Types/SerializationFieldRef.h>

namespace asteroids
{
    REGISTER_CLASS_LOADER_TEST(WinLevelWindow);

    void WinLevelWindow::RegisterProperties()
    {
        shen::UIWindowComponent::RegisterProperties();

        RegisterVar<shen::SerializableFieldRef<shen::UIComponentWrapper<shen::UIButtonComponent>>>(_nextButton, "nextButton", weak_from_this());
        RegisterVar<shen::SerializableFieldRef<shen::UIComponentWrapper<shen::UIButtonComponent>>>(_quitButton, "quitButton", weak_from_this());
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