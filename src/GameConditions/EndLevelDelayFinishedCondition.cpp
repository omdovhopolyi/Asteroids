#include "EndLevelDelayFinishedCondition.h"
#include "ECS/World.h"
#include "ECS/SystemsManager.h"
#include "Components/Common.h"

namespace asteroids
{
    bool EndLevelDelayFinishedCondition::Check(const shen::ContextBase& context) const
    {
        bool result = true;
        auto& world = context.systems->GetWorld();
        world.Each<EndLevelDelay>([&](auto entity, const EndLevelDelay& endLevelDelay)
        {
            result &= (endLevelDelay.time <= 0.f);
        });

        return result;
    }
}
