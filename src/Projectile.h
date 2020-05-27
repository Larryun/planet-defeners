#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"


class Projectile : public GameObject
{

public:
    static int PROJECTILE_COUNTER;

    Projectile(const sf::Texture& texture, const sf::IntRect& rect, 
        const sf::Vector2f& pos, sf::Vector2f dir = sf::Vector2f(0, -1.0f), float spd = 10) :
        GameObject(
            texture,
            rect,
            pos,
            dir,
            spd
        )
    {}

    ~Projectile();

};
#endif

