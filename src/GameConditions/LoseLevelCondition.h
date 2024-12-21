#pragma once

#include "Conditions/ConditionBase.h"

namespace asteroids
{
    class LoseLevelCondition
        : public shen::ConditionBase
    {
    public:
        bool Check(const shen::ContextBase& context) const override;
    };
}
