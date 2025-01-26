#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"
#include "Messenger/SubscriptionsContainer.h"

namespace asteroids
{
    class EndLevelDelaySystem
        : public shen::UpdateSystem
    {
        SYSTEMS_FACTORY(EndLevelDelaySystem)

    public:
        void Start() override;
        void Update() override;

    private:
        void OnObjectDestroyed();

    private:
        shen::SubcriptionsContainer _subscriptions;
    };
}
