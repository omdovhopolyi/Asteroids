#include "WinLevelConditionLoader.h"
#include "GameConditions/WinLevelCondition.h"

namespace asteroids
{
    REGISTER_CLASS_LOADER(WinLevelConditionLoader)

    std::unique_ptr<shen::ConditionBase> WinLevelConditionLoader::LoadCondition(const shen::Serialization& serialization)
    {
        return std::make_unique<WinLevelCondition>();
    }
}
