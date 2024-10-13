#pragma once

#include "ECS/Systems/GameStates/State.h"

namespace asteroids
{
    class MenuGameState
        : public shen::State
    {
    public:
        static std::string StateId;

        MenuGameState(const std::string& id);

        void Init(shen::StateMachineSystem* stateMachineSystem) override;
        void Update() override;

    private:
    };
}
