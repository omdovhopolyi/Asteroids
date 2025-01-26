#include "EndLevelDelaySystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/TimeSystem.h"
#include "Components/Common.h"
#include "MessengerEvents/Common.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(EndLevelDelaySystem)

    void EndLevelDelaySystem::Start()
    {
        _subscriptions.Subscribe<AsteroidDestroyed>([this](const auto& event)
        {
            OnObjectDestroyed();
        });

        _subscriptions.Subscribe<PlayerDestroyed>([this](const auto& event)
        {
            OnObjectDestroyed();
        });
    }

    void EndLevelDelaySystem::Update()
    {
        auto& world = _systems->GetWorld();
        auto& time = _systems->GetTime();

        world.Each<EndLevelDelay>([&](auto entity, EndLevelDelay& endLevelDelay)
        {
            if (endLevelDelay.time > 0.f)
            {
                endLevelDelay.time -= time.Dt();
            }
        });
    }

    void EndLevelDelaySystem::OnObjectDestroyed()
    {
        auto& world = _systems->GetWorld();
        auto& time = _systems->GetTime();

        world.Each<EndLevelDelay>([&](auto entity, EndLevelDelay& endLevelDelay)
        {
            endLevelDelay.time = endLevelDelay.delay;
        });
    }
}
