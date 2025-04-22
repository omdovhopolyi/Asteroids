#pragma once

#include <UI/Components/UIWindowComponent.h>
#include <UI/Components/UIButtonComponent.h>

namespace asteroids
{
    class ManualWindow
        : public shen::UIWindowComponent
    {
        SERIALIZABLE(ManualWindow)

    public:
        void Init() override;
        void RegisterProperties() override;

    private:
        void InitButtonsSubscriptions();

    private:
        shen::UIComponentWrapper<shen::UIButtonComponent> _backButton;
    };
}
