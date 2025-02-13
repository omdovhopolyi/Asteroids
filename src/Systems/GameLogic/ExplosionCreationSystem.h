#pragma once

#include "ECS/Systems/BaseSystems/System.h"
#include "Messenger/SubscriptionsContainer.h"

namespace asteroids
{
    class ExplosionCreationSystem
        : public shen::System
    {
        SYSTEMS_FACTORY(ExplosionCreationSystem)

    public:
        void Start() override;
        //void Update() override;

    private:
        shen::SubcriptionsContainer _subscriptions;
    };
}
