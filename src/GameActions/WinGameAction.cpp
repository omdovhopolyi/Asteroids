#include "WinGameAction.h"
#include "ECS/SystemsManager.h"
#include "Systems/GameStatesSystem.h"

namespace asteroids
{
    WinGameAction::WinGameAction() = default;

    WinGameAction::WinGameAction(const std::string& stateId)
        : _stateId(stateId)
    {}

    void WinGameAction::Execute(const shen::ContextBase& context) const
    {
        if (context.systems)
        {
            if (auto statesSystem = context.systems->GetSystem<GameStatesSystem>())
            {
                statesSystem->ScheduleState(_stateId);
            }
        }
    }

    void WinGameAction::SetStateId(const std::string& stateId)
    {
        _stateId = stateId;
    }
}
