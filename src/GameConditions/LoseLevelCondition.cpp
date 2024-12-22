#include "LoseLevelCondition.h"
#include "ECS/SystemsManager.h"
#include "Systems/GameLogic/PlayerInfoSystem.h"

namespace asteroids
{
    bool LoseLevelCondition::Check(const shen::ContextBase& context) const
    {
        bool result = true;

        if (context.systems)
        {
            if (auto playerInfo = context.systems->GetSystem<PlayerInfoSystem>())
            {
                const int lives = playerInfo->GetResource(ResourceType::Lives);
                result = lives <= 0;
            }
        }

        return result;
    }
}
