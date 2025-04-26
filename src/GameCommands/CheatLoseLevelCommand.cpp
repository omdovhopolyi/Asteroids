#include "CheatLoseLevelCommand.h"
#include <ECS/SystemsManager.h>
#include <ECS/World.h>
#include <ECS/Components/Common.h>
#include "Systems/GameLogic/PlayerInfoSystem.h"
#include "Components/Common.h"
#include "MessengerEvents/Common.h"

namespace asteroids
{
    REGISTER_CLASS_LOADER_TEST(CheatLoseLevelCommand);

    void CheatLoseLevelCommand::Execute(const shen::CommandContext& context) const
    {
#ifdef _DEBUG
        if (auto playerInfo = context.systems->GetSystem<PlayerInfoSystem>())
        {
            playerInfo->SetResource(ResourceType::Lives, 0);
        }

        if (context.systems)
        {
            auto& world = context.systems->GetWorld();
            world.Each<Player>([&](auto entity, const Player&)
            {
                world.AddOrReplaceComponent<shen::Destroy>(entity);
            });
        }

        shen::Messenger::Instance().Broadcast<PlayerDestroyed>();
#endif
    }
}
