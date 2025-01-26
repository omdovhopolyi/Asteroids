#pragma once

#include "Commands/Command.h"
#include <SFML/System/Vector2.hpp>

namespace asteroids
{
    class FireCommand
        : public shen::Command
    {
    public:
        void Execute(const shen::CommandContext& context) const override;

    private:
        std::string _bulletAssetId = "bullet";
        float _angleDeviation = 3.f;
    };
}
