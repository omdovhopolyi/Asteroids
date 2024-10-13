#pragma once

#include "ECS/Systems/GameStates/State.h"

namespace asteroids
{
    class PlayingGameState
        : public shen::State
    {
    public:
        static std::string StateId;

        PlayingGameState(const std::string& id);

        void OnEnter(const std::string&) override;
        void Update() override;

    private:
    };
}

