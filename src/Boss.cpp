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


std::vector<Projectile*> Boss::shoot(int num) //, GameObject player)
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
                float randomPos = rand() % 100 - 50;
                shootArr.push_back(new Projectile(
                    *objSprite->getTexture(),
                    PROJECTILE_RECT,
                    sf::Vector2f(
                        getSprite().getPosition().x + getSprite().getGlobalBounds().width / 2 + i * randomPos, getSprite().getGlobalBounds().height),
                    sf::Vector2f(0, 1.0f),
                    5
                ));
            }
    }
    return shootArr;
}

void Boss::setBossHpBar(int hp, sf::Color color, sf::Vector2f size, sf::Vector2f pos) {
    bossHpBar.setFillColor(color);
    bossHpBar.setSize(size);
    bossHpBar.setPosition(pos);
}

void Boss::drawTo(sf::RenderWindow& window) {

    window.draw(bossHpBar);

}
