#include "CheatDestroyAllAsteroidsCommand.h"
#include <ECS/SystemsManager.h>
#include <ECS/World.h>
#include <ECS/Components/Common.h>
#include "Components/Common.h"
#include "MessengerEvents/Common.h"

namespace asteroids
{
    REGISTER_CLASS_LOADER(CheatDestroyAllAsteroidsCommand);

    void CheatDestroyAllAsteroidsCommand::Execute(const shen::CommandContext& context) const
    {
#ifdef _DEBUG
        auto& world = context.systems->GetWorld();
        world.Each<Asteroid>([&](auto entity, const Asteroid&)
        {
            world.AddOrReplaceComponent<shen::Destroy>(entity);
        });

        world.Each<AsteroidSpawner>([&](auto entity, AsteroidSpawner& spawner)
        {
            spawner.asteroidsToLunch.clear();
        });

        shen::Messenger::Instance().Broadcast<AsteroidDestroyed>();
#endif
    }
}
