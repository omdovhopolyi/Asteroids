#include "LoseLevelCondition.h"
#include "ECS/SystemsManager.h"
#include "Components/Common.h"

namespace asteroids
{
    bool LoseLevelCondition::Check(const shen::ContextBase& context) const
    {
        bool result = true;

        if (context.systems)
        {
            auto& world = context.systems->GetWorld();
            world.Each<Player>([&](auto entity, const Player& player)
            {
                result = player.lives <= 0;
            });
        }

        return result;
    }
}
