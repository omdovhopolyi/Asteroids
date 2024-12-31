#pragma once

#include <UI/Components/UIWindowComponent.h>
#include <UI/Components/UITextComponent.h>
#include "Messenger/SubscriptionsContainer.h"

namespace asteroids
{
    class HudWindow
        : public shen::UIWindowComponent
    {
    public:
        void Init() override;
        void OnWindowOpen() override;
        void RegisterReferences() override;

    private:
        void InitSubscriptions();
        void UpdateValues();

    private:
        shen::UIComponentWrapper<shen::UITextComponent> _lives;
        shen::UIComponentWrapper<shen::UITextComponent> _score;

        shen::SubcriptionsContainer _subscriptions;
    };
}
