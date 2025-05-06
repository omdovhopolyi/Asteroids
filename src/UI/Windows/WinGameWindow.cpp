#include "WinGameWindow.h"
#include "MessengerEvents/Common.h"
#include <UI/UIWindow.h>
#include <UI/Components/UIButtonComponent.h>
#include <Messenger/Events/Common.h>
#include "ECS/SystemsManager.h"
#include "Systems/GameLogic/PlayerInfoSystem.h"
#include <Serialization/Types/SerializableFieldRef.h>

namespace asteroids
{
    REGISTER_LOADER(WinGameWindow);

    void WinGameWindow::Init()
    {
        InitButtonsSubscriptions();
    }

    void WinGameWindow::RegisterProperties()
    {
        shen::UIWindowComponent::RegisterProperties();

        RegisterVar<shen::SerializableFieldRef<shen::UIComponentWrapper<shen::UIButtonComponent>>>(_retryButton, "retryButton", weak_from_this());
        RegisterVar<shen::SerializableFieldRef<shen::UIComponentWrapper<shen::UIButtonComponent>>>(_quitButton, "quitButton", weak_from_this());
        RegisterVar<shen::SerializableFieldRef<shen::UIComponentWrapper<shen::UITextComponent>>>(_score, "score", weak_from_this());
    }

    void WinGameWindow::OnWindowOpen()
    {
        SetupScore();
    }

    void WinGameWindow::InitButtonsSubscriptions()
    {
        if (auto button = _retryButton.Get())
        {
            button->GetSignal().Subscribe(shen::ButtonSignalType::Up, [this]()
            {
                shen::Messenger::Instance().Broadcast<GameOverRetry>();
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

    void WinGameWindow::SetupScore()
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
