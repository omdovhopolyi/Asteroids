#pragma once

#include <UI/Components/UIWindowComponent.h>
#include <UI/Components/UIButtonComponent.h>

namespace asteroids
{
    class PauseWindow
        : public shen::UIWindowComponent
    {
        SERIALIZABLE(PauseWindow)

    public:
        void Init() override;
        void RegisterProperties() override;

    private:
        void InitButtonsSubscriptions();

    private:
        shen::UIComponentWrapper<shen::UIButtonComponent> _resumeButton;
        shen::UIComponentWrapper<shen::UIButtonComponent> _quitButton;
    };
}
