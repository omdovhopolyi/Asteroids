#pragma once

#include "Actions/ActionBase.h"

namespace asteroids
{
    class ClearMapAction
        : public shen::ActionBase
    {
    public:
        void Execute(const shen::ContextBase& context) const override;
    };
}
