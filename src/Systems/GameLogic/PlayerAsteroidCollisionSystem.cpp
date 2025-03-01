#include "Systems/GameLogic/PlayerAsteroidCollisionSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "ECS/Systems/MapLoaderSystem.h"
#include "Components/Common.h"
#include "Systems/GameLogic/PlayerInfoSystem.h"
#include "Systems/Configs/ExplosionsListConfig.h"
#include "Messenger/Messenger.h"
#include "MessengerEvents/Common.h"
#include "Messenger/Events/Sounds.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(PlayerAsteroidCollisionSystem)

    void PlayerAsteroidCollisionSystem::Update()
    {
        if (auto playerInfo = _systems->GetSystem<PlayerInfoSystem>())
        {
            auto& world = _systems->GetWorld();
            world.Each<Player, shen::Collision>([&](auto playerEntity, const Player&, shen::Collision& collision)
            {
                auto asteroidEntity = collision.other;

                if (auto asteroid = world.GetComponent<Asteroid>(asteroidEntity))
                {
                    CreateAsteroidExplosion(asteroidEntity);

                    playerInfo->DecResource(ResourceType::Lives);
                    const int currentLives = playerInfo->GetResource(ResourceType::Lives);

                    const bool needDestroy = (currentLives <= 0);
                    if (needDestroy)
                    {
                        CreatePlayerExplosion(playerEntity);

                        world.AddComponent<shen::Destroy>(shen::Entity(playerEntity));
                        shen::Messenger::Instance().Broadcast<PlayerDestroyed>();
                    }

                    world.AddComponent<shen::Destroy>(asteroidEntity);

                    shen::Messenger::Instance().Broadcast<UpdateHud>();
                }
            });
        }
    }

    void PlayerAsteroidCollisionSystem::CreateAsteroidExplosion(shen::Entity entity)
    {
        if (auto explosions = _systems->GetSystem<ExplosionsListConfig>())
        {
            const auto explosionAssetId = explosions->GetRandomExplosion();

            CreateExplosion(entity, explosionAssetId, "sound_explosion");
        }
    }

    void PlayerAsteroidCollisionSystem::CreatePlayerExplosion(shen::Entity entity)
    {
        CreateExplosion(entity, "big_explosion", "sound_big_explosion");
    }

    void PlayerAsteroidCollisionSystem::CreateExplosion(shen::Entity entity, const std::string& assetId, const std::string& soundId)
    {
        auto& world = _systems->GetWorld();
        if (auto transform = world.GetComponent<shen::Transform>(entity))
        {
            ExplosionEvent event;
            event.assetId = assetId;
            event.position = transform->position;
            event.soundId = soundId;

            shen::Messenger::Instance().Broadcast<ExplosionEvent>(event);
        }
    }
}
