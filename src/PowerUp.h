#ifndef POWERUP_H
#define POWERUP_H
#include "GameObject.h"
#include "PlanetDefenders.cpp"
using namespace PlanetDefenders; // for PowerUpEnum

class PowerUp : public GameObject
{
    // in seconds
    float powerUpDuration;
    PowerUpEnum powerUpType;
    sf::Clock* powerUpClock;

public:
    PowerUp(const sf::Texture& texture, const sf::IntRect& rect, 
        const sf::Vector2f& pos, float duration, PowerUpEnum type) :
        GameObject(
            texture,
            rect,
            pos,
            sf::Vector2f(0, 0),
            0
        ), powerUpDuration(duration)
    {
        // dont initialize clock here
        // initialize clock when addPowerUp to player
        //powerUpClock = new sf::Clock();
        powerUpClock = nullptr;
        powerUpType = type;
    }

    ~PowerUp() {
        delete powerUpClock;
    }

    void setDuration(float t) { powerUpDuration = t; }
    void setType(const PowerUpEnum& s) { powerUpType = s; }
    void setClock(sf::Clock* c) { powerUpClock = c; }

    const sf::Clock& getClock() { return *powerUpClock; }
    const PowerUpEnum& getType() const { return powerUpType; }
    const float& getDuration() { return powerUpDuration; }

    void restartClock();
    bool isPowerUpEnded();


    // this is needed for find and erase operation for STL set
    bool operator<(const PowerUp& other) const
    {
        return this->getType() < other.getType();
    }
    bool operator>(const PowerUp& other) const
    {
        return this->getType() > other.getType();
    }
};
#endif

