#pragma once

#include <UI/Components/Loaders/WindowComponentBaseLoader.h>
#include "UI/Windows/PauseWindow.h"

namespace asteroids
{
    class PauseWindowLoader
        : public shen::WindowComponentBaseLoader<PauseWindow>
    {
        CLASS_LOADER(shen::UIWindowLoader, PauseWindow)
    };
}
