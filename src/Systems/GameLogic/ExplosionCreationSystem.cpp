#include "ExplosionCreationSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Systems/MapLoaderSystem.h"
#include "Components/Common.h"
#include "Messenger/Messenger.h"
#include "Messenger/Events/Sounds.h"
#include "MessengerEvents/Common.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(ExplosionCreationSystem)

    void ExplosionCreationSystem::Start()
    {
        _subscriptions.Subscribe<ExplosionEvent>([this](const auto& event)
        {
            auto& world = _systems->GetWorld();
            if (auto loader = _systems->GetSystem<shen::MapLoaderSystem>())
            {
                if (auto explosionEntity = loader->InstantiateAsset(event.assetId); world.IsValid(explosionEntity))
                {
                    if (auto transform = world.GetOrCreateComponent<shen::Transform>(explosionEntity))
                    {
                        transform->position = event.position;
                    }
                }

                shen::Messenger::Instance().Broadcast<shen::PlaySoundEvent>(event.soundId);
            }
        });
    }
}
