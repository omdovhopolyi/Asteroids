#include "ManualWindow.h"
#include "MessengerEvents/Common.h"
#include <UI/UIWindow.h>
#include <UI/Components/UIButtonComponent.h>
#include <Messenger/Events/Common.h>
#include <Serialization/Types/SerializationFieldRef.h>

namespace asteroids
{
    REGISTER_CLASS_LOADER_TEST(ManualWindow);

    void ManualWindow::Init()
    {
        InitButtonsSubscriptions();
    }

    void ManualWindow::RegisterProperties()
    {
        shen::UIWindowComponent::RegisterProperties();

        RegisterVar<shen::SerializableFieldRef<shen::UIComponentWrapper<shen::UIButtonComponent>>>(_backButton, "backButton", weak_from_this());
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
