#include "WinLevelAction.h"
#include "ECS/SystemsManager.h"
#include "Systems/GameStatesSystem.h"

namespace asteroids
{
    WinLevelAction::WinLevelAction() = default;

    WinLevelAction::WinLevelAction(const std::string& stateId)
        : _stateId(stateId)
    {}

    void WinLevelAction::Execute(const shen::ContextBase& context) const
    {
        if (context.systems)
        {
            if (auto statesSystem = context.systems->GetSystem<GameStatesSystem>())
            {
                statesSystem->ScheduleState(_stateId);
            }
        }
    }

    void WinLevelAction::SetStateId(const std::string& stateId)
    {
        _stateId = stateId;
    }
}
