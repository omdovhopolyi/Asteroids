#include "GameOverWindow.h"
#include "MessengerEvents/Common.h"
#include <UI/UIWindow.h>
#include <UI/Components/UIButtonComponent.h>
#include <Messenger/Events/Common.h>

namespace asteroids
{
    void GameOverWindow::RegisterReferences()
    {
        RegisterReference("retryButton", &_retryButton);
        RegisterReference("quitButton", &_quitButton);
    }

    void GameOverWindow::Init()
    {
        InitButtonsSubscriptions();
    }

    void GameOverWindow::InitButtonsSubscriptions()
    {
        if (auto button = std::dynamic_pointer_cast<shen::UIButtonComponent>(_retryButton.lock()))
        {
            button->GetSignal().Subscribe(shen::ButtonSignalType::Up, [this]()
            {
                shen::Messenger::Instance().Broadcast<GameOverRetry>();
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