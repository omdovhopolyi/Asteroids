#pragma once

#include "ECS/Systems/GameStates/State.h"

namespace asteroids
{
    class GameOverGameState
        : public shen::State
    {
    public:
        static std::string StateId;

        void Update() override;

    private:
    };
}
