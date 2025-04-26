#pragma once

#include "Commands/Command.h"

namespace asteroids
{
    class CheatDestroyAllAsteroidsCommand
        : public shen::Command
    {
        SERIALIZABLE(CheatDestroyAllAsteroidsCommand);

    public:
        void Execute(const shen::CommandContext& context) const override;
    };
}
