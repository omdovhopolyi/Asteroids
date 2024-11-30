#include "LifetimeSystem.h"
#include "ECS/Systems/TimeSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "Components/Common.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(LifetimeSystem)

    void LifetimeSystem::Update()
    {
        auto& time = _systems->GetTime();
        auto& world = _systems->GetWorld();

        world.Each<Lifetime>([&](auto entity, Lifetime& lifetime)
        {
            lifetime.time -= time.Dt();
            if (lifetime.time <= 0.f)
            {
                world.AddComponent<shen::Destroy>(entity);
            }
        });
    }
}
