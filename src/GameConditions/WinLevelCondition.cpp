#include "WinLevelCondition.h"
#include "Components/Common.h"
#include "ECS/SystemsManager.h"

namespace asteroids
{
    bool WinLevelCondition::Check(const shen::ContextBase& context) const
    {
        bool result = true;

        if (context.systems)
        {
            auto& world = context.systems->GetWorld();

            bool hasScheduledAsteroids = false;
            const auto hasAliveAsteroids = world.Size<Asteroid>() > 0;

            world.Each<AsteroidSpawner>([&](auto entity, const AsteroidSpawner& asteroidsSpawner)
            {
                int left = 0;
                for (const auto& [type, amount] : asteroidsSpawner.asteroidsToLunch)
                {
                    left += amount;
                }

                hasScheduledAsteroids |= left > 0;
            });

            result = (!hasAliveAsteroids && !hasScheduledAsteroids);
        }

        return result;
    }
}
