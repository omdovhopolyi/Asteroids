#include "LoseLevelConditionLoader.h"
#include "GameConditions/LoseLevelCondition.h"

namespace asteroids
{
    REGISTER_CLASS_LOADER(LoseLevelConditionLoader);

    std::unique_ptr<shen::ConditionBase> LoseLevelConditionLoader::LoadCondition(const shen::Serialization&)
    {
        return std::make_unique<LoseLevelCondition>();
    }
}
