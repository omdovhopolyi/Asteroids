#include "Common.h"
#include "Serialization/DataElementWrapper.h"

namespace asteroids
{
    void Player::Load(Player& component, const shen::DataElementWrapper& elementWrapper)
    {
    }

    void Player::Save(Player& component, shen::DataElementWrapper& elementWrapper)
    {
    }

    void Bullet::Load(Bullet& component, const shen::DataElementWrapper& elementWrapper)
    {
        component.damage = elementWrapper.GetInt("damage", component.damage);
        component.speed = elementWrapper.GetFloat("speed", component.speed);
    }

    void Bullet::Save(Bullet& component, shen::DataElementWrapper& elementWrapper)
    {
        elementWrapper.SetInt("damage", component.damage);
        elementWrapper.SetFloat("speed", component.speed);
    }

    void Asteroid::Load(Asteroid& component, const shen::DataElementWrapper& elementWrapper)
    {
        component.damage = elementWrapper.GetInt("damage", component.damage);
        component.lives = elementWrapper.GetInt("lives", component.lives);
        component.speed = elementWrapper.GetFloat("speed", component.speed);
    }

    void Asteroid::Save(Asteroid& component, shen::DataElementWrapper& elementWrapper)
    {
        elementWrapper.SetInt("damage", component.damage);
        elementWrapper.SetInt("lives", component.lives);
        elementWrapper.SetFloat("speed", component.speed);
    }

    void AsteroidSpawner::Load(AsteroidSpawner& component, const shen::DataElementWrapper& elementWrapper)
    {
        component.config = elementWrapper.GetStr("config");
    }

    void AsteroidSpawner::Save(AsteroidSpawner& component, shen::DataElementWrapper& elementWrapper)
    {
        elementWrapper.SetStr("config", component.config);
    }

    void Lifetime::Load(Lifetime& component, const shen::DataElementWrapper& elementWrapper)
    {
        component.time = elementWrapper.GetFloat("time", component.time);
    }

    void Lifetime::Save(Lifetime& component, shen::DataElementWrapper& elementWrapper)
    {
        elementWrapper.SetFloat("time", component.time);
    }

    void EndLevelDelay::Load(EndLevelDelay& component, const shen::DataElementWrapper& elementWrapper)
    {
        component.delay = elementWrapper.GetFloat("delay", 3.f);
    }

    void EndLevelDelay::Save(EndLevelDelay& component, shen::DataElementWrapper& elementWrapper)
    {
        elementWrapper.SetFloat("delay", component.delay);
    }
}
