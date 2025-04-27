#include "WinLevelWindow.h"
#include "MessengerEvents/Common.h"
#include <ECS/SystemsManager.h>
#include <Systems/GameLogic/PlayerInfoSystem.h>
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
        RegisterVar<shen::SerializableFieldRef<shen::UIComponentWrapper<shen::UITextComponent>>>(_score, "score", weak_from_this());
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

    void WinLevelWindow::OnWindowOpen()
    {
        SetupScore();
    }

    void WinLevelWindow::SetupScore()
    {
        auto window = GetWindow();
        auto systems = window->GetSystemsManager();
        if (auto playerInfo = systems->GetSystem<PlayerInfoSystem>())
        {
            if (auto score = _score.Get())
            {
                const int scoreValue = playerInfo->GetResource(ResourceType::Score);
                score->SetText(std::to_string(scoreValue));
            }
        }
    }
}