#include "GameStatesSystem.h"
#include "GameStates/LoadingGameState.h"
#include "GameStates/MenuGameState.h"
#include "GameStates/PlayingGameState.h"
#include "GameStates/PauseGameState.h"
#include "GameStates/GameOverGameState.h"

namespace asteroids
{
    REGISTER_SYSTEMS_FACTORY(GameStatesSystem)

    void GameStatesSystem::Start()
    {
        RegisterStates();
        shen::StateMachineSystem::Start();
    }

    void GameStatesSystem::RegisterStates()
    {
        RegisterState<LoadingGameState>(LoadingGameState::StateId);
        RegisterState<MenuGameState>(MenuGameState::StateId);
        RegisterState<PlayingGameState>(PlayingGameState::StateId);
        RegisterState<PauseGameState>(PauseGameState::StateId);
        RegisterState<GameOverGameState>(GameOverGameState::StateId);

        ScheduleState(LoadingGameState::StateId);
    }
}
