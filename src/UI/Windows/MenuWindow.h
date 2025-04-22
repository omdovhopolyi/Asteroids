#pragma once

#include <UI/Components/UIWindowComponent.h>
#include <UI/Components/UIButtonComponent.h>

namespace asteroids
{
    class MenuWindow
        : public shen::UIWindowComponent
    {
        SERIALIZABLE(MenuWindow)

    public:
        void Init() override;
        void RegisterProperties() override;

    private:
        void InitButtonsSubscriptions();

    private:
        shen::UIComponentWrapper<shen::UIButtonComponent> _playButton;
        shen::UIComponentWrapper<shen::UIButtonComponent> _manualButton;
        shen::UIComponentWrapper<shen::UIButtonComponent> _quitButton;
    };
}

