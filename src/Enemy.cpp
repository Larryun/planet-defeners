#include <iostream>
#include <cstdlib>
#include "Enemy.h"
#include "Projectile.h"
#include "PlanetDefenders.h"
using namespace PlanetDefenders;



Enemy::~Enemy()
{
	std::cout << "Enemy removed" << std::endl;
	delete objSprite;
}


Projectile* Enemy::shoot()
{
    // for demonstration
    double shootProbability = 0.2;
    double betweenZeroAndOne = ((double)rand() / RAND_MAX) ;
    sf::Time elapse_time = shootClock.getElapsedTime();
    if (elapse_time >= EnemyShootTimeDelta + sf::milliseconds((betweenZeroAndOne)*50))
    {
        shootClock.restart();
        if(betweenZeroAndOne < shootProbability)        // shoot
            return new Projectile(
                *objSprite->getTexture(),
                ProjectileMiniCircle,
                // position the projictile to the center of the object
                getSprite().getPosition() + sf::Vector2f(getBound().width / 2.0f, getBound().height/2.0f),
                sf::Vector2f(0, 1.0f),
                5
            );
    }
    return nullptr;
}
