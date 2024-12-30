#pragma once

#include "Actions/ActionBase.h"

namespace asteroids
{
    class ResetPlayerLevelAction
        : public shen::ActionBase
    {
    public:
        void Execute(const shen::ContextBase& context) const override;
    };
}
