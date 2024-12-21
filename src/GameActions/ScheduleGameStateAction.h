#pragma once

#include "Actions/ActionBase.h"

namespace asteroids
{
    class ScheduleGameStateAction
        : public shen::ActionBase
    {
    public:
        ScheduleGameStateAction();
        ScheduleGameStateAction(const std::string& stateId);

        void Execute(const shen::ContextBase& context) const override;

        void SetStateId(const std::string& stateId);

    private:
        std::string _stateId;
    };
}
