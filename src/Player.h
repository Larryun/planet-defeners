#ifndef PLAYER_H
#define PLAYER_H
#include <set>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "PowerUp.h"


class Player : public GameObject
{

    float hp;
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
            5.0f		// Initial speed
        ), hp(PlanetDefenders::PLAYER_INITIAL_HEALTH)
    { }
    ~Player();

    float getHp() { return hp; }

    void heal(float amt) { hp = fmin(fmax(hp + amt, 0), 100); }
    void takeDamage(float amt) { hp = fmin(fmax(hp - amt, 0), 100); }
    bool isDead() { return hp <= 0; }
    bool isAlive() { return hp > 0; }

    // check if PowerUp p is in activePowerUp
    bool hasPowerUp(PowerUp* p);
    bool hasPowerUp(PowerUpEnum type);


    // check all powerup 
    // remove from activePowerUp set 
    // if it passes the duration
    void removeAllEndedPowerUp();

    // add PowerUp to activePowerUp set
    // and call applyPowerUp
    void addPowerUp(PowerUp* p);

};


#endif

