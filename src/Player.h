#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Projectile.h"
#include "PowerUp.h"


class Player : public GameObject
{

    float hp;
    float backdoorProjScale = 1.0f;
    float projDamage = PlanetDefenders::PlayerProjectileDamage;
    sf::Clock shootClock;

    std::set<PowerUp*> activePowerUp;
    // apply power up effect to player
    void applyPowerUp(PowerUp& powerUp);

public:
    Player(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& pos) :
        GameObject(
            texture,
            rect,
            pos,
            sf::Vector2f(0, 0),
            7.0f		// Initial speed
        ), hp(PlanetDefenders::PlayerInitialHealth)
    {
        hp = 100;
    }
    ~Player();

    float getHp() { return hp; }
    void setHp(float _hp) { hp = _hp; }

    void heal(float amt) { hp = std::min(std::max(static_cast<int>(hp + amt), 0), 100); }
    void takeDamage(float amt) { hp = std::min(std::max(static_cast<int>(hp - amt), 0), 100); }
    bool isDead() { return hp <= 0; }
    bool isAlive() { return hp > 0; }

    // check if PowerUp p is in activePowerUp
    bool hasPowerUp(PowerUp* p);
    bool hasPowerUp(PowerUpType type);

    // check all powerup 
    // remove from activePowerUp set 
    // if it passes the duration
    void removeAllEndedPowerUp();

    // add PowerUp to activePowerUp set
    // and call applyPowerUp
    void addPowerUp(PowerUp* p);

    void setBackdoorProjScale(float scale) { backdoorProjScale = scale; }
    void setProjDamage(float dmg) { projDamage = dmg; }

    std::set<PowerUp*>& getPowerUpSet() { return activePowerUp;  }

    Projectile* shoot();
};


#endif

