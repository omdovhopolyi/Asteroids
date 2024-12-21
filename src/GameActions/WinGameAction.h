#pragma once

#include "Actions/ActionBase.h"

namespace asteroids
{
    class WinGameAction
        : public shen::ActionBase
    {
    public:
        WinGameAction();
        WinGameAction(const std::string& stateId);

        void Execute(const shen::ContextBase& context) const override;

        void SetStateId(const std::string& stateId);

    private:
        std::string _stateId;
    };
}
