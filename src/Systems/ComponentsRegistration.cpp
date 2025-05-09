#include "ComponentsRegistration.h"
#include "ECS/Systems/MapLoaderSystem.h"
#include "ECS/SystemsManager.h"
#include "Components/Common.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(ComponentsRegistration)

    void ComponentsRegistration::Load()
    {
        if (auto mapLoader = _systems->GetSystem<shen::MapLoaderSystem>())
        {
            /*mapLoader->RegisterLoader<Bullet>("bullet");
            mapLoader->RegisterLoader<Asteroid>("asteroid");
            mapLoader->RegisterLoader<Player>("player");
            mapLoader->RegisterLoader<Lifetime>("lifetime");
            mapLoader->RegisterLoader<AsteroidSpawner>("asteroidSpawner");
            mapLoader->RegisterLoader<OffscreenMove>("offscreenMove");
            mapLoader->RegisterLoader<EndLevelDelay>("endleveldelay");*/
        }
    }
}
