#include "FireCommandLoader.h"
#include "GameCommands/FireCommand.h"

namespace shen
{
    REGISTER_CLASS_LOADER(FireCommandLoader)

    std::unique_ptr<Command> FireCommandLoader::LoadCommand(const shen::Serialization& serialization)
    {
        auto command = std::make_unique<FireCommand>();
        LoadTypeAndId(serialization, command.get());
        return command;
    }
}
