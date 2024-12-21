#include "PlayingGameState.h"
#include <ECS/Systems/MapLoaderSystem.h>
#include <ECS/SystemsManager.h>
#include "Systems/GameLogic/PlayerInfoSystem.h"

// TODO refactor after new assets loading implementation
#include "GameConditions/WinLevelCondition.h"
#include "GameConditions/LoseLevelCondition.h"
#include "GameActions/ScheduleGameStateAction.h"

namespace asteroids
{
    std::string PlayingGameState::StateId = "GameState";

    PlayingGameState::PlayingGameState(const std::string& id)
        : shen::State(id)
    {}

    void PlayingGameState::Init(shen::StateMachineSystem* stateMachineSystem)
    {
        shen::State::Init(stateMachineSystem);

        _context = std::make_shared<shen::ContextBase>();
        _context->systems = GetSystemsManager();
    }

    void PlayingGameState::OnEnter(const std::string&)
    {
        StartLevel(1);
    }

    void PlayingGameState::Update()
    {
        if (_winCondition)
        {
            const bool levelWon = _winCondition->Check(*_context);
            if (levelWon)
            {
                if (_winAction)
                {
                    _winAction->Execute(*_context);
                }
            }
        }
        else if (_loseCondition)
        {
            const bool levelLose = _loseCondition->Check(*_context);
            if (levelLose)
            {
                if (_loseAction)
                {
                    _loseAction->Execute(*_context);
                }
            }
        }
    }

    void PlayingGameState::StartLevel(int index)
    {
        if (auto systems = GetSystemsManager())
        {
            auto playerInfo = systems->GetSystem<PlayerInfoSystem>();
            auto mapLoader = systems->GetSystem<shen::MapLoaderSystem>();
            auto levelsConfigs = systems->GetSystem<LevelsConfig>();

            if (playerInfo && mapLoader && levelsConfigs)
            {
                _currentConfig = levelsConfigs->GetConfig(index);

                if (auto config = _currentConfig.lock())
                {
                    mapLoader->LoadMap(config->mapId);

                    // TODO refactor after new assets loading implementation
                    _winCondition = std::make_shared<WinLevelCondition>();
                    _loseCondition = std::make_shared<LoseLevelCondition>();
                    _winAction = std::make_shared<ScheduleGameStateAction>("WinLevelState");
                    _loseAction = std::make_shared<ScheduleGameStateAction>("GameOverState");
                }
            }
        }
    }
}
