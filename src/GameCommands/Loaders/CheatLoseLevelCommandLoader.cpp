#include "CheatLoseLevelCommandLoader.h"
#include "GameCommands/CheatLoseLevelCommand.h"

namespace asteroids
{
    REGISTER_CLASS_LOADER(CheatLoseLevelCommandLoader)

    std::unique_ptr<shen::Command> CheatLoseLevelCommandLoader::LoadCommand(const shen::Serialization& serialization)
    {
        auto command = std::make_unique<CheatLoseLevelCommand>();
        LoadTypeAndId(serialization, command.get());
        return command;
    }
}
