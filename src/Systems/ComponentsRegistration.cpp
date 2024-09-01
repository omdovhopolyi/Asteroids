#include "ComponentsRegistration.h"
#include "ECS/Systems/MapLoaderSystem.h"
#include "ECS/SystemsManager.h"
#include "Components/CommonComponents.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(ComponentsRegistration)

    void ComponentsRegistration::Start()
    {
        if (auto mapLoader = _systems->GetSystem<shen::MapLoaderSystem>())
        {
            mapLoader->RegisterLoader<Bullet>("bullet");
        }
    }
}
