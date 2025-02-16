#include "Systems/GameLogic/AsteroidBulletCollisionSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "ECS/Systems/MapLoaderSystem.h"
#include "Components/Common.h"
#include "MessengerEvents/Common.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Sounds.h"
#include "Systems/GameLogic/PlayerInfoSystem.h"
#include "Systems/Configs/ExplosionsListConfig.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(AsteroidBulletCollisionSystem)

    void AsteroidBulletCollisionSystem::Update()
    {
        auto playerInfo = _systems->GetSystem<PlayerInfoSystem>();

        auto& world = _systems->GetWorld();
        world.Each<Asteroid, shen::Collision>([&](auto asteroidEntity, Asteroid& asteroid, shen::Collision& collision)
        {
            auto bulletEntity = collision.other;

            if (auto bullet = world.GetComponent<Bullet>(bulletEntity))
            {
                CreateHit(bulletEntity);

                asteroid.lives -= bullet->damage;

                const bool needDestroy = (asteroid.lives <= 0);
                if (needDestroy)
                {
                    CreatedExplosion(asteroidEntity);

                    world.AddComponent<shen::Destroy>(asteroidEntity);
                    shen::Messenger::Instance().Broadcast<AsteroidDestroyed>();

                    if (playerInfo)
                    {
                        playerInfo->AddResource(ResourceType::Score, asteroid.points);
                        shen::Messenger::Instance().Broadcast<UpdateHud>();
                    }
                }

                world.AddComponent<shen::Destroy>(bulletEntity);
            }
        });
    }

    void AsteroidBulletCollisionSystem::CreateHit(shen::Entity bulletEntity)
    {
        auto& world = _systems->GetWorld();
        auto bulletTransform = world.GetComponent<shen::Transform>(bulletEntity);
        if (auto loader = _systems->GetSystem<shen::MapLoaderSystem>())
        {
            ExplosionEvent event;
            event.assetId = "hit_1";
            event.position = bulletTransform->position;
            event.soundId = "sound_hit";

            shen::Messenger::Instance().Broadcast<ExplosionEvent>(event);
        }
    }

    void AsteroidBulletCollisionSystem::CreatedExplosion(shen::Entity asteroidEntity)
    {
        auto& world = _systems->GetWorld();
        if (auto asteroidTransform = world.GetComponent<shen::Transform>(asteroidEntity))
        {
            if (auto explosions = _systems->GetSystem<ExplosionsListConfig>())
            {
                const auto explosionAssetId = explosions->GetRandomExplosion();

                ExplosionEvent event;
                event.assetId = explosionAssetId;
                event.position = asteroidTransform->position;
                event.soundId = "sound_explosion";

                shen::Messenger::Instance().Broadcast<ExplosionEvent>(event);
            }
        }
    }
}
