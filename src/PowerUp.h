#ifndef POWERUP_H
#define POWERUP_H
#include "GameObject.hpp"
#include "PlanetDefenders.h"
//using namespace PlanetDefenders; // for PowerUpEnum

namespace PlanetDefenders
{
    class PowerUp : public GameObject
    {
        // in seconds
        float powerUpDuration;
        PowerUpType powerUpType;
        sf::Clock* powerUpClock;

    public:
        PowerUp(const sf::Texture& texture, const sf::IntRect& rect,
            const sf::Vector2f& pos, float duration, PowerUpType type) :
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
            std::cout << "PowerUp Removed" << std::endl;
            delete powerUpClock;
        }

        void setDuration(float t) { powerUpDuration = t; }
        void setType(const PowerUpType& s) { powerUpType = s; }
        void startClock() { powerUpClock = new sf::Clock(); }

        const sf::Clock& getClock() { return *powerUpClock; }
        const PowerUpType& getType() const { return powerUpType; }
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
}

#endif

