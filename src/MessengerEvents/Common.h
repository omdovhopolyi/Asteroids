#pragma once

#include <Messenger/Events/Event.h>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace asteroids
{
    struct MenuStatePlayButtonPressedEvent : shen::Event {};
    struct MenuStateSettingsButtonPressedEvent : shen::Event {};
    struct PauseStateResumeButtonPressedEvent : shen::Event {};
    struct WinLevelNextLevel : shen::Event {};
    struct AfterLevelExit : shen::Event {};
    struct GameOverRetry : shen::Event {};
    struct UpdateHud : shen::Event {};
    struct AsteroidDestroyed : shen::Event {};
    struct PlayerDestroyed : shen::Event {};

    struct ExplosionEvent : shen::Event
    {
        std::string assetId;
        sf::Vector2f position;
        sf::Vector2f scale;
        std::string soundId;

        /*ExplosionEvent(const std::string& id, const sf::Vector2f& pos, const sf::Vector2f& sl, std::string& sound)
            : assetId(id)
            , position(pos)
            , scale(sl)
            , soundId(sound)
        {}*/
    };
}
