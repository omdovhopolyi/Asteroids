#pragma once

#include "Actions/ActionBase.h"

namespace asteroids
{
    class IncPlayerLevelAction
        : public shen::ActionBase
    {
    public:
        void Execute(const shen::ContextBase& context) const override;
    };
}
