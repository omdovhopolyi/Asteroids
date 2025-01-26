#include "Systems/GameLogic/PlayerAsteroidCollisionSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "Components/Common.h"
#include "Systems/GameLogic/PlayerInfoSystem.h"
#include "Messenger/Messenger.h"
#include "MessengerEvents/Common.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(PlayerAsteroidCollisionSystem)

    void PlayerAsteroidCollisionSystem::Update()
    {
        if (auto playerInfo = GetSystem<PlayerInfoSystem>())
        {
            auto& world = _systems->GetWorld();
            world.Each<Player, shen::Collision>([&](auto playerEntity, const Player&, shen::Collision& collision)
            {
                auto asteroidEntity = collision.other;

                if (auto asteroid = world.GetComponent<Asteroid>(asteroidEntity))
                {
                    playerInfo->DecResource(ResourceType::Lives);
                    const int currentLives = playerInfo->GetResource(ResourceType::Lives);

                    const bool needDestroy = (currentLives <= 0);
                    if (needDestroy)
                    {
                        world.AddComponent<shen::Destroy>(shen::Entity(playerEntity));
                        shen::Messenger::Instance().Broadcast<PlayerDestroyed>();
                    }

                    world.AddComponent<shen::Destroy>(asteroidEntity);

                    shen::Messenger::Instance().Broadcast<UpdateHud>();
                }
            });
        }
    }
}
