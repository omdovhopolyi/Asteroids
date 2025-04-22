#pragma once

#include <UI/Components/UIWindowComponent.h>
#include <UI/Components/UIButtonComponent.h>

namespace asteroids
{
    class WinLevelWindow
        : public shen::UIWindowComponent
    {
        SERIALIZABLE(WinLevelWindow)

    public:
        void Init() override;
        void RegisterProperties() override;

    private:
        void InitButtonsSubscriptions();

    private:
        shen::UIComponentWrapper<shen::UIButtonComponent> _nextButton;
        shen::UIComponentWrapper<shen::UIButtonComponent> _quitButton;
    };
}
