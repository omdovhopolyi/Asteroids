#pragma once

#include <UI/Components/Loaders/WindowComponentBaseLoader.h>
#include "UI/Windows/GameOverWindow.h"

namespace asteroids
{
    class GameOverWindowLoader
        : public shen::WindowComponentBaseLoader<GameOverWindow>
    {
        CLASS_LOADER(shen::UIWindowLoader, GameOverWindow)
    };
}
