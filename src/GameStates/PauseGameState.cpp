#include "PauseGameState.h"

namespace asteroids
{
    std::string PauseGameState::StateId = "PauseState";

    PauseGameState::PauseGameState(const std::string& id)
        : shen::State(id)
    {}

    void PauseGameState::Update()
    {

    }
}
