#include "CheatLoseLevelCommand.h"
#include <ECS/SystemsManager.h>
#include <ECS/World.h>
#include <ECS/Components/Common.h>
#include "Systems/GameLogic/PlayerInfoSystem.h"
#include "Components/Common.h"
#include "MessengerEvents/Common.h"

namespace asteroids
{
    void CheatLoseLevelCommand::Execute(const shen::CommandContext& context) const
    {
#ifdef _DEBUG
        if (auto playerInfo = context.systems->GetSystem<PlayerInfoSystem>())
        {
            playerInfo->SetResource(ResourceType::Lives, 0);
        }

        shen::Messenger::Instance().Broadcast<PlayerDestroyed>();
#endif
    }
}
