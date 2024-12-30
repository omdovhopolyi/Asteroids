#pragma once
#include "ResetPlayerLevelAction.h"
#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "Systems/GameLogic/PlayerInfoSystem.h"

namespace asteroids
{
    void ResetPlayerLevelAction::Execute(const shen::ContextBase& context) const
    {
        if (context.systems)
        {
            if (auto playerInfo = context.systems->GetSystem<PlayerInfoSystem>())
            {
                playerInfo->ResetLevel();
                playerInfo->Load();
            }
        }
    }
}
