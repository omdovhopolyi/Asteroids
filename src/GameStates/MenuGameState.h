#pragma once

#include "ECS/Systems/GameStates/State.h"

namespace asteroids
{
    class MenuGameState
        : public shen::State
    {
    public:
        static std::string StateId;

        void Update() override;

    private:
    };
}
