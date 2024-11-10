#include "ComponentsRegistration.h"
#include "ECS/Systems/MapLoaderSystem.h"
#include "ECS/SystemsManager.h"
#include "Components/Common.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(ComponentsRegistration)

    void ComponentsRegistration::Start()
    {
        if (auto mapLoader = _systems->GetSystem<shen::MapLoaderSystem>())
        {
            mapLoader->RegisterLoader<Bullet>("bullet");
            mapLoader->RegisterLoader<Asteroid>("asteroid");
            mapLoader->RegisterLoader<Player>("player");
        }
    }
}
