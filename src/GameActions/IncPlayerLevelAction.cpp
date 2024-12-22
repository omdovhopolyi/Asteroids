#include "IncPlayerLevelAction.h"
#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "Systems/GameLogic/PlayerInfoSystem.h"

namespace asteroids
{
    void IncPlayerLevelAction::Execute(const shen::ContextBase& context) const
    {
        if (context.systems)
        {
            if (auto playerInfo = context.systems->GetSystem<PlayerInfoSystem>())
            {
                playerInfo->IncLevel();
            }
        }
    }
}
