#include "GameOverGameState.h"

namespace asteroids
{
    std::string GameOverGameState::StateId = "GameOverState";

    GameOverGameState::GameOverGameState(const std::string& id)
        : shen::State(id)
    {}

    void GameOverGameState::Update()
    {

    }
}
