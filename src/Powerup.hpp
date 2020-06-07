#ifndef POWERUP_H
#define POWERUP_H
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include <iostream>

class Powerup : public GameObject
{
    int powerupType;
public:

    Powerup(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& pos, int i) :
        GameObject(
            texture,
            rect,
            pos,
            sf::Vector2f(0, 0),
            0.f        // Initial speed
        )
    { powerupType = i;}
    void setPowerup(int p) {powerupType = p;}
    int getPowerup() { return powerupType; }
    ~Powerup();

};
#endif

