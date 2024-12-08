#pragma once

#include "GameEnums/AsteroidTypeEnum.h"
#include "ECS/Systems/BaseSystems/System.h"
#include <map>
#include <memory>

namespace asteroids
{
    class AsteroidConfig
    {
    public:
        using Ptr = std::shared_ptr<AsteroidConfig>;
        using WeakPtr = std::weak_ptr<AsteroidConfig>;

        void SetSpeed(float speed);
        float GetSpeed() const;

        void SetLives(int lives);
        int GetLives() const;

        void SetAsstetId(const std::string& assetId);
        const std::string& GetAssetId() const;

    private:
        float _speed = 1.f;
        int _lives = 1;
        std::string _assetId;
    };

    class AsteroidsConfig
        : public shen::System
    {
        SYSTEMS_FACTORY(AsteroidsConfig)

    public:
        using Ptr = std::shared_ptr<AsteroidsConfig>;
        using WeakPtr = std::weak_ptr<AsteroidsConfig>;

        void Load() override;

        std::shared_ptr<AsteroidConfig> GetConfig(AsteroidType type) const;

    private:
        std::map<AsteroidType, std::shared_ptr<AsteroidConfig>> _asteroids;
    };
}
