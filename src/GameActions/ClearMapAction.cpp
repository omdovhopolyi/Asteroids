#include "ClearMapAction.h"
#include "ECS/SystemsManager.h"
#include "ECS/World.h"
#include "ECS/Components/Common.h"

namespace asteroids
{
    void ClearMapAction::Execute(const shen::ContextBase& context) const
    {
        if (context.systems)
        {
            auto& world = context.systems->GetWorld();
            world.ForAllEntities([&](auto entity)
            {
                world.AddOrReplaceComponent<shen::Destroy>(entity);
            });
        }
    }
}
