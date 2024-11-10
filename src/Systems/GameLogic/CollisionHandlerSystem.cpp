#include "CollisionHandlerSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "Components/Common.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(CollisionHandlerSystem)

    void CollisionHandlerSystem::Update()
    {
        auto& world = _systems->GetWorld();
        world.Each<shen::Collision, Asteroid>([&](auto entity, shen::Collision& collision, Asteroid& asteroid)
        {
            if (auto playerComp = world.GetComponent<Player>(collision.other))
            {
                playerComp->lives -= asteroid.damage;
                const bool needDestroy = (playerComp->lives <= 0);

                if (needDestroy)
                {
                    world.AddComponent<shen::Destroy>(collision.other);
                }

                world.AddComponent<shen::Destroy>(entity);
            }
        });
    }
}
