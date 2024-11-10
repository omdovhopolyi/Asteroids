#pragma once

#include "Commands/Command.h"
#include <SFML/System/Vector2.hpp>

namespace shen
{
    class FireCommand
        : public shen::Command
    {
    public:
        void Execute(const shen::CommandContext& context) const override;
    };
}
