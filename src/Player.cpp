#include <iostream>
#include "Player.h"
#include "HealthRestore.h"

Player::~Player()
{
    std::cout << "Player removed" << std::endl;
    delete objSprite;
}


void Player::applyPowerUp(PowerUp& powerUp)
{
    switch (powerUp.getType())
    {
    case (PlanetDefenders::HEAL):
        heal(static_cast<HealthRestore*>(&powerUp)->getHealAmount());
        std::cout << "HEAL POWERUPPP" << std::endl;
        if (activePowerUp.erase(&powerUp) >= 1)
            std::cout << "HEAL POWERUPPP ERASED" << std::endl;
    case (PlanetDefenders::SHIELD):
        std::cout << "SHIELD POWERUPPP" << std::endl;
    }
}

void Player::addPowerUp(PowerUp* p) {
    std::cout << "ADD POWER UP" << std::endl;
    if (!hasPowerUp(p))
    {
        activePowerUp.insert(p);
        p->startClock();
        applyPowerUp(*p);
    }
    else
    {
        std::cout << "ALEADY EXISTS" << std::endl;
    }
}


/*
    return a Projectile object if it is ready to shoot
    else return a nullptr
*/
Projectile* Player::shoot()
{
    sf::Time elapse_time = shootClock.getElapsedTime();
    Projectile* newProjectile = nullptr;
    if (elapse_time >= PlayerShootTimeDelta)
    {
        shootClock.restart();
        return new Projectile(
            *objSprite->getTexture(),
            PROJECTILE_RECT,
            // x-axis offset by: 2.0f
            getSprite().getPosition() + sf::Vector2f((getBound().width / 2.0f) - 2.0f, 0.0f)
        );
    }
    return nullptr;
}

void Player::removeAllEndedPowerUp() {
    std::set<PowerUp*>::iterator it = activePowerUp.begin();
    while (it != activePowerUp.end())
    {
        if ((*it)->isPowerUpEnded())
        {
            std::cout << (*it)->getClock().getElapsedTime().asSeconds() << std::endl;
            it = activePowerUp.erase(it);
        }
        else
        {
            it++;
        }
    }
}


bool Player::hasPowerUp(PowerUpEnum type) {
    std::set<PowerUp*>::iterator it = activePowerUp.begin();
    while (it != activePowerUp.end())
    {
        if ((*it)->getType() == type)
            return true;
        it++;
    }

    return false;
}

bool Player::hasPowerUp(PowerUp* p)
{
    return activePowerUp.find(p) != activePowerUp.end();
}
