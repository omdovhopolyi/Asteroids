#include "GameOverWindow.h"
#include "MessengerEvents/Common.h"
#include <UI/UIWindow.h>
#include <UI/Components/UIButtonComponent.h>
#include <Messenger/Events/Common.h>
#include "ECS/SystemsManager.h"
#include "Systems/GameLogic/PlayerInfoSystem.h"

namespace asteroids
{
    void GameOverWindow::RegisterReferences()
    {
        RegisterReference("retryButton", _retryButton);
        RegisterReference("quitButton", _quitButton);
        RegisterReference("score", _score);
    }

    void GameOverWindow::Init()
    {
        InitButtonsSubscriptions();
    }

    void GameOverWindow::OnWindowOpen()
    {
        SetupScore();
    }

    void GameOverWindow::InitButtonsSubscriptions()
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

    void GameOverWindow::SetupScore()
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