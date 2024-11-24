#include "AsteroidsSpawnerSystem.h"
#include "ECS/Systems/MapLoaderSystem.h"
#include "ECS/Systems/TimeSystem.h"
#include "ECS/Systems/PhysicsBox2DSystem.h"
#include "ECS/Systems/Sfml/SfmlSpritesCollection.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "ECS/Components/Render.h"
#include "Components/Common.h"
#include "Serialization/Serialization.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(AsteroidsSpawnerSystem);

    void AsteroidsSpawnerSystem::Start()
    {
        _updateFunc.SetFunc([&]()
        {
            Spawn(AsteroidType::Default);

        }, _spawnDelay, shen::TimedFunctionType::Update);
    }

    void AsteroidsSpawnerSystem::Update()
    {
        const auto time = GetSystem<shen::TimeSystem>();
        _updateFunc.Update(time->Dt());
    }

    void AsteroidsSpawnerSystem::Spawn(AsteroidType type)
    {
        // TODO randomize spawn point and direction

        if (auto loader = GetSystem<shen::MapLoaderSystem>())
        {
            auto& world = _systems->GetWorld();

            if (auto entity = loader->InstantiateAsset("asteroid_default"); world.IsValid(entity))
            {
                auto transform = world.GetComponent<shen::Transform>(entity);
                auto asteroid = world.GetComponent<Asteroid>(entity);

                const bool hasComponents = (asteroid && transform);
                if (hasComponents)
                {
                    if (auto physicsSystem = GetSystem<shen::PhysicsBox2DSystem>())
                    {
                        transform->position.y = 300.f;

                        auto velocity = sf::Vector2f{ 1.f, 0.f };
                        velocity *= asteroid->speed;

                        physicsSystem->SetupRigidBody(entity);
                        physicsSystem->SetLinearVelocity(entity, velocity);
                    }
                }
            }
        }
    }
}
