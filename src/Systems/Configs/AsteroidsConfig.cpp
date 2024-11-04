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

                asteroid->SetSpeed(speed);
                asteroid->SetLives(lives);

                auto [it, isInserted] = _asteroids.insert({ type, asteroid });
            });
        }
    }
}
