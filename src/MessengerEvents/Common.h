#pragma once

#include <Messenger/Events/Event.h>

namespace asteroids
{
    struct MenuStatePlayButtonPressedEvent : shen::Event {};

    struct MenuStateSettingsButtonPressedEvent : shen::Event {};
}
