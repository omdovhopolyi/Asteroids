#include "CheatDestroyAllAsteroidsCommandLoader.h"
#include "GameCommands/CheatDestroyAllAsteroidsCommand.h"

namespace asteroids
{
    REGISTER_CLASS_LOADER(CheatDestroyAllAsteroidsCommandLoader)

        std::unique_ptr<shen::Command> CheatDestroyAllAsteroidsCommandLoader::LoadCommand(const shen::Serialization& serialization)
    {
        auto command = std::make_unique<CheatDestroyAllAsteroidsCommand>();
        LoadTypeAndId(serialization, command.get());
        return command;
    }
}
