#pragma once

#include "Actions/ActionBase.h"

namespace asteroids
{
    class ShowHUDAction
        : public shen::ActionBase
    {
    public:
        void Execute(const shen::ContextBase&) const override;
    };
}
