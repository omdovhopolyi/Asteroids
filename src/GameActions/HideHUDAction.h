#pragma once

#include "Actions/ActionBase.h"

namespace asteroids
{
    class HideHUDAction
        : public shen::ActionBase
    {
    public:
        void Execute(const shen::ContextBase&) const override;
    };
}
