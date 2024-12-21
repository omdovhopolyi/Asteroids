#pragma once

#include <UI/Components/UIWindowComponent.h>

namespace asteroids
{
    class GameOverWindow
        : public shen::UIWindowComponent
    {
    public:
        void Init() override;
        void RegisterReferences() override;

    private:
        void InitButtonsSubscriptions();

    private:
        std::weak_ptr<UIComponent> _retryButton;
        std::weak_ptr<UIComponent> _quitButton;
    };
}
