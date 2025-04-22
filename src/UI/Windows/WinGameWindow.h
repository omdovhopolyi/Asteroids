#pragma once

#include <UI/Components/UIWindowComponent.h>
#include <UI/Components/UIButtonComponent.h>
#include <UI/Components/UITextComponent.h>

namespace asteroids
{
    class WinGameWindow
        : public shen::UIWindowComponent
    {
        SERIALIZABLE(WinGameWindow)

    public:
        void Init() override;
        void RegisterProperties() override;

    private:
        void InitButtonsSubscriptions();
        void SetupScore();
        void OnWindowOpen();

    private:
        shen::UIComponentWrapper<shen::UIButtonComponent> _retryButton;
        shen::UIComponentWrapper<shen::UIButtonComponent> _quitButton;
        shen::UIComponentWrapper<shen::UITextComponent> _score;
    };
}
