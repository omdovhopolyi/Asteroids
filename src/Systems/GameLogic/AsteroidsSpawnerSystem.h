#pragma once

#include "ECS/Systems/BaseSystems/UpdateSystem.h"
#include "Utils/TimedFunction.h"
#include "GameEnums/AsteroidTypeEnum.h"
#include "Messenger/SubscriptionsContainer.h"
#include <SFML/System/Vector2.hpp>

namespace asteroids
{
    enum class ScreenSide
    {
        Top,
        Right,
        Bottom,
        Left,
        Count
    };

    struct AsteroidSpawnData
    {
        AsteroidType type = AsteroidType::Default;
        sf::Vector2f position;
        sf::Vector2f direction;
    };

    class AsteroidsSpawnerSystem
        : public shen::UpdateSystem
    {
        SYSTEMS_FACTORY(AsteroidsSpawnerSystem)

    public:
        void Init(shen::SystemsManager* systems) override;
        void Start() override;
        void Update() override;

    private:
        void InitSubscriptions();
        void Spawn(const AsteroidSpawnData& spawnData);

        void OnMapLoaded();

        sf::Vector2f CalculateSpawnPosition() const;
        sf::Vector2f CalculateDirection() const;

    private:
        shen::SubcriptionsContainer _subscriptions;
        //std::map<ScreenSide, StarupPosition> _spawnPositions;
    };
}
