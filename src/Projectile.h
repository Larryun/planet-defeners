#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"


class Projectile : public GameObject
{

    float damage;

public:
    static int PROJECTILE_COUNTER;

    Projectile(const sf::Texture& texture, const sf::IntRect& rect, 
        const sf::Vector2f& pos, sf::Vector2f dir = sf::Vector2f(0, -1.0f), float spd = 10, float damage=1.0f) :
        GameObject(
            texture,
            rect,
            pos,
            dir,
            spd
        ), damage(damage)
    {}

    void setDamage(float d) { damage = d; }
    float getDamage() { return damage; }
    ~Projectile();

};
#endif

