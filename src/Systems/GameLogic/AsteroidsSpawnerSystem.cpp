#include "AsteroidsSpawnerSystem.h"
#include "ECS/Systems/MapLoaderSystem.h"
#include "ECS/Systems/TimeSystem.h"
#include "ECS/Systems/PhysicsBox2DSystem.h"
#include "ECS/Systems/Sfml/SfmlSpritesCollection.h"
#include "ECS/Systems/Sfml/SfmlRenderTargetsSystem.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "ECS/Components/Common.h"
#include "ECS/Components/Physics.h"
#include "ECS/Components/Render.h"
#include "Components/Common.h"
#include "Serialization/Serialization.h"
#include "Messenger/Events/Common.h"
#include "Systems/Configs/AsteroidsSpawnerConfig.h"
#include "Systems/Configs/AsteroidsConfig.h"
#include "Utils/Math.h"
#include "GameEnums/AsteroidTypeEnum.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(AsteroidsSpawnerSystem);

    void AsteroidsSpawnerSystem::Init(shen::SystemsManager* systems)
    {
        shen::UpdateSystem::Init(systems);
        InitSubscriptions();
    }

    void AsteroidsSpawnerSystem::Update()
    {
        auto& time = _systems->GetTime();
        auto& world = _systems->GetWorld();

        world.Each<AsteroidSpawner>([&](auto entity, AsteroidSpawner& spawner)
        {
            spawner.currentDelay -= time.GameDt();

            if (spawner.currentDelay <= 0.f)
            {
                spawner.currentDelay = shen::RandomFloat(spawner.minDelay, spawner.maxDelay);

                std::vector<AsteroidType> availableTypes;
                availableTypes.reserve(spawner.asteroidsToLunch.size());

                for (const auto& [type, amount] : spawner.asteroidsToLunch)
                {
                    if (amount > 0)
                    {
                        availableTypes.push_back(type);
                    }
                }

                if (!availableTypes.empty())
                {
                    const int typeIndex = shen::RandomInt(0, static_cast<int>(availableTypes.size() - 1));
                    const auto type = availableTypes[typeIndex];

                    spawner.asteroidsToLunch[type]--;

                    AsteroidSpawnData spawnData;
                    spawnData.type = type;
                    spawnData.position = CalculateSpawnPosition();
                    spawnData.direction = CalculateDirection();

                    Spawn(spawnData);
                }
            }
        });
    }

    void AsteroidsSpawnerSystem::InitSubscriptions()
    {
        _subscriptions.Subscribe<shen::MapLoadedEvent>([&](const shen::MapLoadedEvent&)
        {
            OnMapLoaded();
        });
    }

    void AsteroidsSpawnerSystem::InitSpawnerComponent()
    {
        if (auto collection = _systems->GetSystem<SpawnerConfig>())
        {
            auto& world = _systems->GetWorld();
            world.Each<AsteroidSpawner>([&](auto entity, AsteroidSpawner& spawner)
            {
                if (const auto& config = collection->GetConfig(spawner.config))
                {
                    spawner.minDelay = config->GetMinDelay();
                    spawner.maxDelay = config->GetMaxDelay();

                    spawner.asteroidsToLunch.clear();

                    for (const auto& [type, data] : config->GetAsteroids())
                    {
                        spawner.asteroidsToLunch.insert({ type, data.amount });
                    }
                }
            });
        }
    }

    void AsteroidsSpawnerSystem::Spawn(const AsteroidSpawnData& spawnData)
    {
        auto& world = _systems->GetWorld();
        auto assetsConfig = _systems->GetSystem<AsteroidsConfig>();
        auto loader = _systems->GetSystem<shen::MapLoaderSystem>();
        auto spawnerConfig = _systems->GetSystem<SpawnerConfig>();

        const float minTorque = spawnerConfig->GetMinTorque();
        const float maxTorque = spawnerConfig->GetMaxTorque();

        if (assetsConfig && loader && spawnerConfig)
        {
            if (const auto asteroidConfig = assetsConfig->GetConfig(spawnData.type))
            {
                const auto assetId = asteroidConfig->GetAssetId();

                if (auto entity = loader->InstantiateAsset(assetId); world.IsValid(entity))
                {
                    auto transform = world.GetComponent<shen::Transform>(entity);
                    auto asteroid = world.GetComponent<Asteroid>(entity);

                    const bool hasComponents = (asteroid && transform);
                    if (hasComponents)
                    {
                        if (auto physicsSystem = _systems->GetSystem<shen::PhysicsBox2DSystem>())
                        {
                            transform->position = spawnData.position;

                            auto velocity = spawnData.direction * asteroid->speed;

                            physicsSystem->SetupRigidBody(entity);
                            physicsSystem->SetLinearVelocity(entity, velocity);
                            physicsSystem->ApplyTorque(entity, shen::RandomFloat(minTorque, maxTorque));
                        }
                    }
                }
            }
        }
    }

    void AsteroidsSpawnerSystem::OnMapLoaded()
    {
        InitSpawnerComponent();
    }

    sf::Vector2f AsteroidsSpawnerSystem::CalculateSpawnPosition() const
    {
        sf::Vector2f position;

        if (auto renderTargets = _systems->GetSystem<shen::SfmlRenderTargetsSystem>())
        {
            const auto rect = renderTargets->GetTargetWorldRect(shen::SfmlRenderTargetsSystem::WorldTargetId);
            const auto side = static_cast<ScreenSide>(shen::RandomInt(0, static_cast<int>(ScreenSide::Count) - 1));
            const auto normalPointOnSide = shen::RandomFloat(0.f, 1.f);

            switch (side)
            {
            case ScreenSide::Top:
            {
                position.x = rect.width * normalPointOnSide;
                position.y = 0.f;
                break;
            }
            case ScreenSide::Right:
            {
                position.x = rect.width;
                position.y = rect.height * normalPointOnSide;
                break;
            }
            case ScreenSide::Bottom:
            {
                position.x = rect.width;
                position.y = rect.height * normalPointOnSide;
                break;
            }
            case ScreenSide::Left:
            {
                position.x = 0.f;
                position.y = rect.height * normalPointOnSide;
                break;
            }
            default:
            {
                // empty
            }
            }
        }

        return position;
    }

    sf::Vector2f AsteroidsSpawnerSystem::CalculateDirection() const
    {
        sf::Vector2f direction = { 1.f, 1.f };
        const float angle = shen::RandomFloat(0.f, 360.f);
        shen::RotateThis(direction, angle);
        return direction;
    }
}
