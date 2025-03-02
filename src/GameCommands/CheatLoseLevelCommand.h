#pragma once

#include "Commands/Command.h"

namespace asteroids
{
    class CheatLoseLevelCommand
        : public shen::Command
    {
    public:
        void Execute(const shen::CommandContext& context) const override;
    };
}
