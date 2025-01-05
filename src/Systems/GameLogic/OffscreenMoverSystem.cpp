#include "Systems/GameLogic/OffscreenMoverSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include "ECS/Systems/PhysicsBox2DSystem.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Render.h"
#include "ECS/Components/Physics.h"
#include "Components/Common.h"
#include <box2d/box2d.h>

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(OffscreenMoverSystem)

    void OffscreenMoverSystem::Update()
    {
        auto& world = _systems->GetWorld();

        if (auto renderTextures = _systems->GetSystem<shen::SfmlRenderTargetsSystem>())
        {
            const auto viewBounds = renderTextures->GetTargetWorldRect(shen::SfmlRenderTargetsSystem::WorldTargetId);

            world.Each<OffscreenMove, shen::Transform>([&](const auto entity, const OffscreenMove&, shen::Transform& transform)
            {
                sf::Vector2f position;

                auto rigidBody = world.GetComponent<shen::RigidBody>(entity);
                if (rigidBody)
                {
                    auto box2dPos = rigidBody->body->GetPosition();
                    position = shen::PhysicsBox2DSystem::Box2dPosToWorld(box2dPos);
                }
                else
                {
                    position = transform.position;
                }

                const bool needMove = !viewBounds.contains(position);
                if (needMove)
                {
                    if (position.x > viewBounds.width)
                    {
                        position.x = 0.f;
                    }
                    if (position.x < 0.f)
                    {
                        position.x = viewBounds.width;
                    }
                    if (position.y > viewBounds.height)
                    {
                        position.y = 0.f;
                    }
                    if (position.y < 0.f)
                    {
                        position.y = viewBounds.height;
                    }

                    if (rigidBody)
                    {
                        auto box2dPos = shen::PhysicsBox2DSystem::WorldToBox2dPos(position);
                        rigidBody->body->SetTransform(box2dPos, rigidBody->body->GetAngle());
                    }
                    else
                    {
                        transform.position = position;
                    }
                }
            });
        }
    };
}
