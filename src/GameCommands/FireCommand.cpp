#include "FireCommand.h"
#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "ECS/Components/Render.h"
#include "ECS/Systems/Sfml/SfmlSpritesCollection.h"
#include "ECS/Systems/PhysicsBox2DSystem.h"
#include "ECS/Systems/MapLoaderSystem.h"
#include "Components/Common.h"
#include "Utils/Math.h"
#include "Messenger/Events/Sounds.h"
#include "Messenger/Messenger.h"

namespace asteroids
{
    REGISTER_CLASS_LOADER(FireCommand);

    void FireCommand::Execute(const shen::CommandContext& context) const
    {
        if (auto loader = context.systems->GetSystem<shen::MapLoaderSystem>())
        {
            auto& world = context.systems->GetWorld();

            if (auto bulletEntity = loader->InstantiateAsset(_bulletAssetId); world.IsValid(bulletEntity))
            {
                shen::Messenger::Instance().Broadcast<shen::PlaySoundEvent>("sound_shot");

                auto playerTransform = world.GetComponent<shen::Transform>(context.entity);
                auto bulletTransform = world.GetComponent<shen::Transform>(bulletEntity);
                auto bullet = world.GetComponent<Bullet>(bulletEntity);

                const bool hasComponents = (bullet && playerTransform && bulletTransform);
                if (hasComponents)
                {
                    if (auto physicsSystem = context.systems->GetSystem<shen::PhysicsBox2DSystem>())
                    {
                        auto velocity = sf::Vector2f{ 1.f, 0.f };

                        auto rotationTransform = sf::Transform::Identity;
                        const auto angle = shen::RandomFloat(playerTransform->rotation - _angleDeviation, playerTransform->rotation + _angleDeviation);
                        rotationTransform.rotate(angle);
                        velocity = rotationTransform.transformPoint(velocity);

                        bulletTransform->position = playerTransform->position;
                        bulletTransform->rotation = angle;
                        
                        velocity *= bullet->speed;

                        physicsSystem->SetupRigidBody(bulletEntity);
                        physicsSystem->SetLinearVelocity(bulletEntity, velocity);
                    }
                }
            }
        }
    }
}
