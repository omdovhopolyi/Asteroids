#pragma once

#include "Commands/Loaders/InputCommandLoader.h"

namespace shen
{
    class FireCommand;

    class FireCommandLoader
        : public shen::InputCommandLoader
    {
        CLASS_LOADER(shen::InputCommandsLoadersCollection, FireCommand)

    public:
        std::unique_ptr<Command> LoadCommand(const shen::Serialization& serialization) override;
    };
}
