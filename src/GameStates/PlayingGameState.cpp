#include "PlayingGameState.h"
#include <ECS/Systems/MapLoaderSystem.h>
#include <ECS/Systems/PhysicsBox2DSystem.h>
#include <ECS/SystemsManager.h>
#include <ECS/Systems/UI/WindowsManager.h>
#include "Systems/GameLogic/PlayerInfoSystem.h"

// TODO refactor after new assets loading implementation
#include "Conditions/AndCondition.h"
#include "GameConditions/EndLevelDelayFinishedCondition.h"
#include "GameConditions/WinLevelCondition.h"
#include "GameConditions/LoseLevelCondition.h"
#include "GameActions/ScheduleGameStateAction.h"
#include "GameActions/IncPlayerLevelAction.h"
#include "GameActions/ClearMapAction.h"
#include "GameActions/ResetPlayerLevelAction.h"
#include "GameActions/ShowHUDAction.h"
#include "Actions/PausePhysicsAction.h"
#include "Actions/ResetPhysicsAccumulatedTimeAction.h"

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
        if (auto systems = GetSystemsManager())
        {
            if (auto playerInfo = systems->GetSystem<PlayerInfoSystem>())
            {
                StartLevel(playerInfo->GetLevel());
            }
        }

        ExecuteStartActions();
    }

    void PlayingGameState::Update()
    {
        // TODO incapsulate in some kind of transition class

        if (_winCondition)
        {
            const bool levelWon = _winCondition->Check(*_context);
            if (levelWon)
            {
                ExecuteWinAction();
            }
        }

        if (_loseCondition)
        {
            const bool levelLose = _loseCondition->Check(*_context);
            if (levelLose)
            {
                ExecuteLoseAction();
            }
        }
    }

    void PlayingGameState::StartLevel(int index)
    {
        if (auto systems = GetSystemsManager())
        {
            auto mapLoader = systems->GetSystem<shen::MapLoaderSystem>();
            auto levelsConfigs = systems->GetSystem<LevelsConfig>();

            if (mapLoader && levelsConfigs)
            {
                _currentConfig = levelsConfigs->GetConfig(index);

                if (auto config = _currentConfig.lock())
                {
                    mapLoader->LoadMap(config->mapId);

                    _winCondition = nullptr;
                    _loseCondition = nullptr;
                    _startActions.clear();
                    _winActions.clear();
                    _loseActions.clear();

                    // TODO refactor after new assets loading implementation
                    auto winCondition = std::make_shared<shen::AndCondition>();
                    winCondition->AddCondition(std::make_shared<WinLevelCondition>());
                    winCondition->AddCondition(std::make_shared<EndLevelDelayFinishedCondition>());
                    _winCondition = winCondition;

                    // TODO refactor after new assets loading implementation
                    auto loseCondition = std::make_shared<shen::AndCondition>();
                    loseCondition->AddCondition(std::make_shared<LoseLevelCondition>());
                    loseCondition->AddCondition(std::make_shared<EndLevelDelayFinishedCondition>());
                    _loseCondition = loseCondition;

                    // TODO refactor after new assets loading implementation
                    _startActions.push_back(std::make_shared<ShowHUDAction>());
                    _startActions.push_back(std::make_shared<shen::PausePhisicsAction>(false));

                    // TODO refactor after new assets loading implementation
                    _winActions.push_back(std::make_shared<ClearMapAction>());
                    _winActions.push_back(std::make_shared<ScheduleGameStateAction>("WinLevelState"));
                    _winActions.push_back(std::make_shared<IncPlayerLevelAction>());
                    _winActions.push_back(std::make_shared<shen::PausePhisicsAction>(true));
                    _loseActions.push_back(std::make_shared<ClearMapAction>());
                    _loseActions.push_back(std::make_shared<ScheduleGameStateAction>("GameOverState"));
                    _loseActions.push_back(std::make_shared<ResetPlayerLevelAction>());
                    _loseActions.push_back(std::make_shared<shen::PausePhisicsAction>(true));
                }
            }
        }
    }

    void PlayingGameState::ExecuteStartActions()
    {
        ExecuteActions(_startActions);
    }

    void PlayingGameState::ExecuteWinAction()
    {
        ExecuteActions(_winActions);
    }

    void PlayingGameState::ExecuteLoseAction()
    {
        ExecuteActions(_loseActions);
    }

    void PlayingGameState::ExecuteActions(const std::vector<std::shared_ptr<shen::ActionBase>>& actions)
    {
        for (const auto& action : actions)
        {
            action->Execute(*_context);
        }
    }
}
