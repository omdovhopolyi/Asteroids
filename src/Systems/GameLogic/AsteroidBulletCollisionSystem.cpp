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
                asteroid.lives -= bullet->damage;

                const bool needDestroy = (asteroid.lives <= 0);
                if (needDestroy)
                {
                    auto loader = _systems->GetSystem<shen::MapLoaderSystem>();
                    auto explosions = _systems->GetSystem<ExplosionsListConfig>();
                    if (loader && explosions)
                    {
                        const auto explosionAssetId = explosions->GetRandomExplosion();

                        if (auto explosionEntity = loader->InstantiateAsset(explosionAssetId); world.IsValid(explosionEntity))
                        {
                            auto explosionTransform = world.GetOrCreateComponent<shen::Transform>(explosionEntity);
                            auto asteroidTransform = world.GetComponent<shen::Transform>(asteroidEntity);

                            if (explosionTransform && asteroidTransform)
                            {
                                explosionTransform->position = asteroidTransform->position;
                            }
                        }

                        shen::Messenger::Instance().Broadcast<shen::PlaySoundEvent>("sound_exposion");
                    }

                    shen::Messenger::Instance().Broadcast<shen::PlaySoundEvent>("sound_hit");

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
}
