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
            Spawn(AsteroidType::Common);

        }, _spawnDelay, shen::TimedFunctionType::Update);
    }

    void AsteroidsSpawnerSystem::Update()
    {
        const auto time = GetSystem<shen::TimeSystem>();
        _updateFunc.Update(time->Dt());
    }

    void AsteroidsSpawnerSystem::Spawn(AsteroidType type)
    {
        // TODO

        auto& world = _systems->GetWorld();
        
        auto entity = world.CreateEntity();
        world.AddComponent<Asteroid>(entity);
        auto transform = world.AddComponent<shen::Transform>(entity);
        transform->position.y = 310.f;
        auto rigidBody = world.AddComponent<shen::RigidBody>(entity);
        rigidBody->sensor = true;

        if (auto spriteCollection = GetSystem<shen::SfmlSpritesCollection>())
        {
            auto spriteData = spriteCollection->GetSpriteData("asteroid");
            auto spriteComponent = world.AddComponent<shen::Sprite>(entity);
            spriteComponent->sprite = spriteData.sprite;
            spriteComponent->textureId = spriteData.textureId;
        }
        
        if (auto physicsSystem = GetSystem<shen::PhysicsBox2DSystem>())
        {
            physicsSystem->SetupRigidBody(entity);
            physicsSystem->ApplyLinearImpulseToCenter(entity, { 1.f, 0.f });
        }
    }
}
