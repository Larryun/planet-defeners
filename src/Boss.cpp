#include "Boss.hpp"
#include "Projectile.h"
#include "PlanetDefenders.h"
#include <iostream>
using namespace PlanetDefenders;



Boss::~Boss()
{
    std::cout << "Boss removed" << std::endl;
    delete objSprite;
}


std::vector<Projectile*> Boss::shoot(int num)
{
    // for demonstration
    double shootProbability = 0.2;
    double betweenZeroAndOne = ((double)rand() / RAND_MAX);
    sf::Time elapse_time = shootClock.getElapsedTime();
    if (elapse_time >= BossShootTimeDelta + sf::milliseconds((betweenZeroAndOne) * 50))
    {
        shootClock.restart();
        if (betweenZeroAndOne < shootProbability)        // shoot
            //std::cout << elapse_time.asSeconds() << std::endl;
            for (int i = 0; i < num; i++) {
                shootArr.push_back(new Projectile(
                    *objSprite->getTexture(),
                    PROJECTILE_RECT,
                    getSprite().getPosition() + sf::Vector2f(i * 10.f, getSprite().getGlobalBounds().height),
                    sf::Vector2f(0, 1.0f),
                    5
                ));
            }
    }
    return shootArr;
}
