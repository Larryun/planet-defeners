#pragma once
#include "GameObject.hpp"
#include "Projectile.h"

class Enemy : public GameObject
{
    sf::Clock shootClock;
    float hp;

    float attribute;
    float projectileScale;
    float projectileDamage;
    float projectileSpeed;

public:
    Enemy(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& pos,
        float attribute = 1, float hp = 5) :
        GameObject(
            texture,
            rect,
            pos,
            sf::Vector2f(0, 0.0f),
            0
        ), hp(hp), projectileScale(1), projectileDamage(1), projectileSpeed(5), attribute(attribute)
    {
        getSprite().scale(attribute, attribute);
        // larger the randAttribute, slower it moves
        setSpeed(4 / attribute);
        setProjectileDamage(attribute * 1);
        setProjectileSpeed(8 / attribute);
        setProjectileScale(attribute * 1.1);
        hp = 5 * attribute;
    }
    ~Enemy();
    //sf::Vector2f getPosition
    bool isOutOfBound() { return false; }
    bool isDead() { return hp <= 0; }
    bool isAlive() { return hp > 0; }

    void takeDamage(float x) { hp -= x; }

    float getHp() { return hp; }
    void setHp(float x) { hp = x; }

    void setProjectileScale(float s) { projectileScale = s; }
    void setProjectileDamage(float s) { projectileDamage = s; }
    void setProjectileSpeed(float s) { projectileSpeed = s; }

    Projectile* shoot();

};

