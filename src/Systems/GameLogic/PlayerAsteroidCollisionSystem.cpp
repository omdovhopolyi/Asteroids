#include "Systems/GameLogic/PlayerAsteroidCollisionSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "Components/Common.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(PlayerAsteroidCollisionSystem)

    void PlayerAsteroidCollisionSystem::Update()
    {
        auto& world = _systems->GetWorld();
        world.Each<Player, shen::Collision>([&](auto playerEntity, Player& player, shen::Collision& collision)
        {
            auto asteroidEntity = collision.other;

            if (auto asteroid = world.GetComponent<Asteroid>(asteroidEntity))
            {
                player.lives -= asteroid->damage;

                const bool needDestroy = (player.lives <= 0);
                if (needDestroy)
                {
                    world.AddComponent<shen::Destroy>(playerEntity);

                    if (auto rigidBody = world.GetComponent<shen::RigidBody>(playerEntity))
                    {

                    }
                }

                world.AddComponent<shen::Destroy>(asteroidEntity);
            }
        });
    }
}
