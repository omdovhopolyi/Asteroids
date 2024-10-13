#pragma once

#include <UI/Components/UIWindowComponent.h>

namespace asteroids
{
    class MenuWindow
        : public shen::UIWindowComponent
    {
    public:
        void Init() override;
        void RegisterReferences() override;

    private:
        void InitButtonsSubscriptions();

    private:
        std::weak_ptr<UIComponent> _playButton;
        std::weak_ptr<UIComponent> _settingsButton;
        std::weak_ptr<UIComponent> _quitButton;
    };
}

