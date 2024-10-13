#include "LoadingGameState.h"

namespace asteroids
{
    std::string LoadingGameState::StateId = "LoadingState";

    LoadingGameState::LoadingGameState(const std::string& id)
        : shen::State(id)
    {}

    void LoadingGameState::Update()
    {

    }
}
