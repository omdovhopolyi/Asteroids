#pragma once

#include <UI/Components/Loaders/WindowComponentBaseLoader.h>
#include "UI/Windows/ManualWindow.h"

namespace asteroids
{
    class ManualWindowLoader
        : public shen::WindowComponentBaseLoader<ManualWindow>
    {
        CLASS_LOADER(shen::UIWindowLoader, ManualWindow)
    };
}
