#pragma once

#include <UI/Components/Loaders/WindowComponentBaseLoader.h>
#include "UI/Windows/WinLevelWindow.h"

namespace asteroids
{
    class WinLevelWindowLoader
        : public shen::WindowComponentBaseLoader<WinLevelWindow>
    {
        CLASS_LOADER(shen::UIWindowLoader, WinLevelWindow)
    };
}
