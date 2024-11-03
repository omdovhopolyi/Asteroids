#include "PlayingGameState.h"
#include <ECS/Systems/MapLoaderSystem.h>
#include <ECS/SystemsManager.h>

namespace asteroids
{
    std::string PlayingGameState::StateId = "GameState";

    PlayingGameState::PlayingGameState(const std::string& id)
        : shen::State(id)
    {}

    void PlayingGameState::OnEnter(const std::string&)
    {
        auto systems = GetSystemsManager();
        if (auto mapLoader = systems->GetSystem<shen::MapLoaderSystem>())
        {
            mapLoader->LoadMap("level_1");
        }
    }

    void PlayingGameState::Update()
    {

    }
}
