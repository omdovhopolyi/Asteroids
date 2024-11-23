#include "FireCommand.h"
#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "ECS/Components/Render.h"
#include "ECS/Systems/Sfml/SfmlSpritesCollection.h"
#include "ECS/Systems/PhysicsBox2DSystem.h"
#include "Components/Common.h"

namespace asteroids
{
    void FireCommand::Execute(const shen::CommandContext& context) const
    {
        // TODO maybe implement some kind of asset instantiation

        auto& world = context.systems->GetWorld();

        if (auto ownerTransform = world.GetComponent<shen::Transform>(context.entity))
        {
            auto bulletEntity = world.CreateEntity();

            const bool isValid = world.IsValid(bulletEntity);
            if (isValid)
            {
                world.AddComponent<Bullet>(bulletEntity);

                auto velocity = sf::Vector2f{ 1.f, 0.f };

                if (auto transform = world.AddComponent<shen::Transform>(bulletEntity))
                {
                    transform->position = ownerTransform->position;

                    auto rotationTransform = sf::Transform::Identity;
                    rotationTransform.rotate(ownerTransform->rotation);

                    velocity = rotationTransform.transformPoint(velocity);                    
                }
                
                if (auto rigidBody = world.AddComponent<shen::RigidBody>(bulletEntity))
                {
                    rigidBody->sensor = true;
                    rigidBody->size = { 0.1f, 0.1f };
                }

                if (auto spriteCollection = context.systems->GetSystem<shen::SfmlSpritesCollection>())
                {
                    auto spriteData = spriteCollection->GetSpriteData("bullet");
                    auto spriteComponent = world.AddComponent<shen::Sprite>(bulletEntity);
                    spriteComponent->sprite = spriteData.sprite;
                    spriteComponent->textureId = spriteData.textureId;
                }

                if (auto physicsSystem = context.systems->GetSystem<shen::PhysicsBox2DSystem>())
                {
                    const auto speed = 2.f;
                    velocity *= speed;

                    physicsSystem->SetupRigidBody(bulletEntity);
                    physicsSystem->SetLinearVelocity(bulletEntity, velocity);
                }
            }
        }
    }
}
