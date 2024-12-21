#include "ScheduleGameStateAction.h"
#include "ECS/SystemsManager.h"
#include "Systems/GameStatesSystem.h"

namespace asteroids
{
    ScheduleGameStateAction::ScheduleGameStateAction() = default;

    ScheduleGameStateAction::ScheduleGameStateAction(const std::string& stateId)
        : _stateId(stateId)
    {}

    void ScheduleGameStateAction::Execute(const shen::ContextBase& context) const
    {
        if (context.systems)
        {
            if (auto statesSystem = context.systems->GetSystem<GameStatesSystem>())
            {
                statesSystem->ScheduleState(_stateId);
            }
        }
    }

    void ScheduleGameStateAction::SetStateId(const std::string& stateId)
    {
        _stateId = stateId;
    }
}
