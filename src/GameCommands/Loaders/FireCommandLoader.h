#pragma once

#include "Commands/Loaders/InputCommandLoader.h"

namespace asteroids
{
    class FireCommand;

    class FireCommandLoader
        : public shen::InputCommandLoader
    {
        CLASS_LOADER(shen::InputCommandsLoadersCollection, FireCommand)

    public:
        std::unique_ptr<shen::Command> LoadCommand(const shen::Serialization& serialization) override;
    };
}
