#pragma once

#include "Conditions/Loaders/ConditionsLoader.h"

namespace asteroids
{
    class WinLevelCondition;

    class WinLevelConditionLoader
        : public shen::ConditionLoader
    {
        CLASS_LOADER(shen::ConditionLoadersCollection, WinLevelCondition)

    public:
        std::unique_ptr<shen::ConditionBase> LoadCondition(const shen::Serialization& serialization) override;
    };
}
