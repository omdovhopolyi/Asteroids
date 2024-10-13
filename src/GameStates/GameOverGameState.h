#pragma once

#include "ECS/Systems/GameStates/State.h"

namespace asteroids
{
    class GameOverGameState
        : public shen::State
    {
    public:
        static std::string StateId;

        GameOverGameState(const std::string& id);

        void Update() override;

    private:
    };
}
