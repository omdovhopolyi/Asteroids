#include "Common.h"
#include "Serialization/Serialization.h"

namespace asteroids
{
    void Player::Load(Player& component, const shen::Serialization& serialization)
    {
        component.lives = serialization.GetInt("lives", component.lives);
    }

    void Player::Save(Player& component, shen::Serialization& serialization)
    {
        serialization.SetInt("lives", component.lives);
    }

    void Bullet::Load(Bullet& component, const shen::Serialization& serialization)
    {
        component.damage = serialization.GetInt("damage", component.damage);
        component.speed = serialization.GetFloat("speed", component.speed);
    }

    void Bullet::Save(Bullet& component, shen::Serialization& serialization)
    {
        serialization.SetInt("damage", component.damage);
        serialization.SetFloat("speed", component.speed);
    }

    void Asteroid::Load(Asteroid& component, const shen::Serialization& serialization)
    {
        component.damage = serialization.GetInt("damage", component.damage);
        component.lives = serialization.GetInt("lives", component.lives);
        component.speed = serialization.GetFloat("speed", component.speed);
    }

    void Asteroid::Save(Asteroid& component, shen::Serialization& serialization)
    {
        serialization.SetInt("damage", component.damage);
        serialization.SetInt("lives", component.lives);
        serialization.SetFloat("speed", component.speed);
    }

    void AsteroidSpawner::Load(AsteroidSpawner& component, const shen::Serialization& serialization)
    {
        component.config = serialization.GetStr("config");
    }

    void AsteroidSpawner::Save(AsteroidSpawner& component, shen::Serialization& serialization)
    {
        serialization.SetStr("config", component.config);
    }

    void Lifetime::Load(Lifetime& component, const shen::Serialization& serialization)
    {
        component.time = serialization.GetFloat("time", component.time);
    }

    void Lifetime::Save(Lifetime& component, shen::Serialization& serialization)
    {
        serialization.SetFloat("time", component.time);
    }
}
