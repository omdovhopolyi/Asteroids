#include "Systems/GameLogic/AsteroidBulletCollisionSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "Components/Common.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(AsteroidBulletCollisionSystem)

    void AsteroidBulletCollisionSystem::Update()
    {
        auto& world = _systems->GetWorld();
        world.Each<Asteroid, shen::Collision>([&](auto asteroidEntity, Asteroid& asteroid, shen::Collision& collision)
        {
            auto bulletEntity = collision.other;

            if (auto bullet = world.GetComponent<Bullet>(bulletEntity))
            {
                asteroid.lives -= bullet->damage;

                const bool needDestroy = (asteroid.lives <= 0);
                if (needDestroy)
                {
                    world.AddComponent<shen::Destroy>(asteroidEntity);
                }

                world.AddComponent<shen::Destroy>(bulletEntity);
            }
        });
    }
}
