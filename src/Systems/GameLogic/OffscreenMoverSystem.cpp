#include "Systems/GameLogic/OffscreenMoverSystem.h"
#include "ECS/SystemsManager.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include "ECS/Systems/PhysicsBox2DSystem.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Render.h"
#include "ECS/Components/Physics.h"
#include <box2d/box2d.h>

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(OffscreenMoverSystem)

    void OffscreenMoverSystem::Update()
    {
        auto& world = _systems->GetWorld();

        // TODO standalone function for getting world screen rect

        if (auto renderTextures = _systems->GetSystem<shen::SfmlRenderTargetsSystem>())
        {
            if (auto target = renderTextures->GetRenderTexture(shen::SfmlRenderTargetsSystem::WorldTargetId))
            {
                const auto& view = target->getView();
                const auto center = view.getCenter();
                const auto size = view.getSize();
                sf::FloatRect viewBounds;
                viewBounds.width = size.x;
                viewBounds.height = size.y;
                viewBounds.left = center.x - size.x / 2.f;
                viewBounds.top = center.y - size.y / 2.f;

                world.Each<shen::RigidBody, shen::Transform>([&](const auto entity, shen::RigidBody& rigidBody, shen::Transform& transform)
                {
                    auto box2dPos = rigidBody.body->GetPosition();
                    auto position = shen::PhysicsBox2DSystem::Box2dPosToWorld(box2dPos);

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

                        box2dPos = shen::PhysicsBox2DSystem::WorldToBox2dPos(position);

                        rigidBody.body->SetTransform(box2dPos, rigidBody.body->GetAngle());
                    }
                });
            }
        }
    };
}
