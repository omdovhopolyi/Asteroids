#include "PlayingGameState.h"
#include <ECS/Systems/MapLoaderSystem.h>
#include <ECS/SystemsManager.h>
#include "Systems/GameLogic/PlayerInfoSystem.h"
#include <ECS/Systems/UI/WindowsManager.h>

// TODO refactor after new assets loading implementation
#include "GameConditions/WinLevelCondition.h"
#include "GameConditions/LoseLevelCondition.h"
#include "GameActions/ScheduleGameStateAction.h"
#include "GameActions/IncPlayerLevelAction.h"
#include "GameActions/ClearMapAction.h"
#include "GameActions/ResetPlayerLevelAction.h"

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

        ShowHud();
    }

    void PlayingGameState::Update()
    {
        // TODO incapsulate in some kind of transition class

        if (_winCondition)
        {
            const bool levelWon = _winCondition->Check(*_context);
            if (levelWon)
            {
                for (const auto& action : _winActions)
                {
                    action->Execute(*_context);
                }
            }
        }

        if (_loseCondition)
        {
            const bool levelLose = _loseCondition->Check(*_context);
            if (levelLose)
            {
                for (const auto& action : _loseActions)
                {
                    action->Execute(*_context);
                }
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
                    _winActions.clear();
                    _loseActions.clear();

                    // TODO refactor after new assets loading implementation
                    _winCondition = std::make_shared<WinLevelCondition>();
                    _loseCondition = std::make_shared<LoseLevelCondition>();


                    _winActions.push_back(std::make_shared<ClearMapAction>());
                    _winActions.push_back(std::make_shared<ScheduleGameStateAction>("WinLevelState"));
                    _winActions.push_back(std::make_shared<IncPlayerLevelAction>());
                    _loseActions.push_back(std::make_shared<ClearMapAction>());
                    _loseActions.push_back(std::make_shared<ScheduleGameStateAction>("GameOverState"));
                    _loseActions.push_back(std::make_shared<ResetPlayerLevelAction>());
                }
            }
        }
    }

    void PlayingGameState::ShowHud()
    {
        auto systems = GetSystemsManager();
        if (auto windowsManager = systems->GetSystem<shen::WindowsManager>())
        {
            auto windowContext = shen::UIWindowContext{};
            windowContext.windowId = "hud_window";
            windowContext.systems = systems;

            windowsManager->OpenWindow(windowContext);
        }
    }
}
