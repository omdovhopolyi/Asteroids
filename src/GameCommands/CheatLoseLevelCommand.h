#pragma once

#include "Commands/Command.h"

namespace asteroids
{
    class CheatLoseLevelCommand
        : public shen::Command
    {
        SERIALIZABLE(CheatLoseLevelCommand);

    public:
        void Execute(const shen::CommandContext& context) const override;
    };
}
