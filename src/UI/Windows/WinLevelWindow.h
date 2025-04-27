#pragma once

#include <UI/Components/UIWindowComponent.h>
#include <UI/Components/UIButtonComponent.h>
#include <UI/Components/UITextComponent.h>

namespace asteroids
{
    class WinLevelWindow
        : public shen::UIWindowComponent
    {
        SERIALIZABLE(WinLevelWindow)

    public:
        void Init() override;
        void RegisterProperties() override;
        void OnWindowOpen() override;

    private:
        void InitButtonsSubscriptions();
        void SetupScore();

    private:
        shen::UIComponentWrapper<shen::UIButtonComponent> _nextButton;
        shen::UIComponentWrapper<shen::UIButtonComponent> _quitButton;
        shen::UIComponentWrapper<shen::UITextComponent> _score;
    };
}
