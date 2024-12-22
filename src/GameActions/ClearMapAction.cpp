#include "ClearMapAction.h"
#include "ECS/SystemsManager.h"
#include "ECS/World.h"

namespace asteroids
{
    void ClearMapAction::Execute(const shen::ContextBase& context) const
    {
        if (context.systems)
        {
            auto& world = context.systems->GetWorld();
            world.Clear();
        }
    }
}
