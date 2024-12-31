#pragma once

#include <Messenger/Events/Event.h>

namespace asteroids
{
    struct MenuStatePlayButtonPressedEvent : shen::Event {};
    struct MenuStateSettingsButtonPressedEvent : shen::Event {};
    struct WinLevelNextLevel : shen::Event {};
    struct AfterLevelExit : shen::Event {};
    struct GameOverRetry : shen::Event {};
    struct UpdateHud : shen::Event {};
}
