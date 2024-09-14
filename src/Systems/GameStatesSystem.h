#pragma once

#include "ECS/Systems/GameStates/StateMachineSystem.h"

namespace asteroids
{
    class GameStatesSystem
        : public shen::StateMachineSystem
    {
        SYSTEMS_FACTORY(GameStatesSystem)

    public:
        void Start() override;

    private:
        void RegisterStates();
    };
}
