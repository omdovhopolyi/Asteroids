#pragma once

#include <UI/Components/UIWindowComponent.h>
#include <UI/Components/UIButtonComponent.h>

namespace asteroids
{
    class WinLevelWindow
        : public shen::UIWindowComponent
    {
    public:
        void Init() override;
        void RegisterReferences() override;

    private:
        void InitButtonsSubscriptions();

    private:
        shen::UIComponentWrapper<shen::UIButtonComponent> _nextButton;
        shen::UIComponentWrapper<shen::UIButtonComponent> _quitButton;
    };
}
