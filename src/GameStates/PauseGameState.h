#pragma once

#include "ECS/Systems/GameStates/State.h"

namespace asteroids
{
    class PauseGameState
        : public shen::State
    {
    public:
        static std::string StateId;

        void Update() override;

    private:
    };
}

