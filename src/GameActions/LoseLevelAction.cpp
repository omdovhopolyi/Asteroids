#include "LoseLevelAction.h"
#include "ECS/SystemsManager.h"
#include "Systems/GameStatesSystem.h"

namespace asteroids
{
    LoseLevelAction::LoseLevelAction() = default;

    LoseLevelAction::LoseLevelAction(const std::string& stateId)
        : _stateId(stateId)
    {}

    void LoseLevelAction::Execute(const shen::ContextBase& context) const
    {
        if (context.systems)
        {
            if (auto statesSystem = context.systems->GetSystem<GameStatesSystem>())
            {
                statesSystem->ScheduleState(_stateId);
            }
        }
    }

    void LoseLevelAction::SetStateId(const std::string& stateId)
    {
        _stateId = stateId;
    }
}
