#include "CollisionHandlerSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(CollisionHandlerSystem)

    void CollisionHandlerSystem::Update()
    {
        auto& world = _systems->GetWorld();
        world.Each<shen::Collision>([&](auto entity, shen::Collision& collision)
        {
            world.AddComponent<shen::Destroy>(entity);
        });
    }
}
