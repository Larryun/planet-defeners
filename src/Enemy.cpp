#include <iostream>
#include <cstdlib>
#include "Enemy.h"
#include "Projectile.h"
#include "PlanetDefenders.h"
using namespace PlanetDefenders;



Enemy::~Enemy()
{
    //std::cout << "Enemy removed" << std::endl;
    delete objSprite;
}


Projectile* Enemy::shoot()
{
    Projectile* newProj;
    double shootProbability = 0.2;
    sf::Time elapse_time = shootClock.getElapsedTime();
    if (elapse_time >= shootInterval*5.0f)
    {
        shootClock.restart();
        newProj = new Projectile(
            *objSprite->getTexture(),
            ProjectileMiniCircle,
            // position the projictile to the center of the object
            getSprite().getPosition() + sf::Vector2f(getBound().width / 2.0f, getBound().height),
            sf::Vector2f(0, 1.0f),
            projectileSpeed,
            projectileDamage
        );
        newProj->getSprite().scale(projectileScale, projectileScale);
        newProj->roateToDirection();
        return newProj;
    }
    return nullptr;
}
