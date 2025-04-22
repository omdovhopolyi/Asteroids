#pragma once

#include <UI/Components/UIWindowComponent.h>
#include <UI/Components/UIButtonComponent.h>
#include <UI/Components/UITextComponent.h>

namespace asteroids
{
    class GameOverWindow
        : public shen::UIWindowComponent
    {
        SERIALIZABLE(GameOverWindow)

    public:
        void Init() override;
        void OnWindowOpen() override;
        void RegisterProperties() override;

    private:
        void InitButtonsSubscriptions();
        void SetupScore();

    private:
        shen::UIComponentWrapper<shen::UIButtonComponent> _retryButton;
        shen::UIComponentWrapper<shen::UIButtonComponent> _quitButton;
        shen::UIComponentWrapper<shen::UITextComponent> _score;
    };
}
