#pragma once

#include "ECS/Systems/GameStates/State.h"

namespace asteroids
{
    class LoadingGameState
        : public shen::State
    {
    public:
        static std::string StateId;

        LoadingGameState(const std::string& id);

        void Update() override;

    private:
    };
}
