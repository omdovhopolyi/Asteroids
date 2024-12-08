#include "AsteroidsConfig.h"
#include "Serialization/Serialization.h"
#include "Utils/FilePath.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(AsteroidsConfig);

    void AsteroidConfig::SetSpeed(float speed)
    {
        _speed = speed;
    }

    float AsteroidConfig::GetSpeed() const
    {
        return _speed;
    }

    void AsteroidConfig::SetLives(int lives)
    {
        _lives = lives;
    }

    int AsteroidConfig::GetLives() const
    {
        return _lives;
    }

    void AsteroidConfig::SetAsstetId(const std::string& assetId)
    {
        _assetId = assetId;
    }

    const std::string& AsteroidConfig::GetAssetId() const
    {
        return _assetId;
    }

    void AsteroidsConfig::Load()
    {
        const auto fileName = shen::FilePath::Path("assets/configs/asteroids.xml");
        auto serialization = shen::Serialization{ _systems, fileName };
        serialization.SetupElement("asteroids");

        if (serialization.IsValid())
        {
            serialization.ForAllChildElements("asteroid", [&](const shen::Serialization& element)
            {
                const auto asteroid = std::make_shared<AsteroidConfig>();

                const auto type = AsteroidTypeEnum.FromString(element.GetStr("type"));
                const float speed = element.GetFloat("speed", asteroid->GetSpeed());
                const int lives = element.GetInt("lives", asteroid->GetLives());
                const auto assetId = element.GetStr("assetId");

                asteroid->SetSpeed(speed);
                asteroid->SetLives(lives);
                asteroid->SetAsstetId(assetId);

                auto [it, isInserted] = _asteroids.insert({ type, asteroid });
                if (!isInserted)
                {
                    // TODO assert
                }
            });
        }
    }

    std::shared_ptr<AsteroidConfig> AsteroidsConfig::GetConfig(AsteroidType type) const
    {
        if (auto it = _asteroids.find(type); it != _asteroids.end())
        {
            return it->second;
        }

        return nullptr;
    }
}
