#include <iostream>
#include "Boss.hpp"
#include "Projectile.h"
#include "PlanetDefenders.h"
using namespace PlanetDefenders;

Boss::~Boss()
{
    std::cout << "Boss removed" << std::endl;
    delete objSprite;
}

std::vector<Projectile*>* Boss::shoot(int num)
{
    // for demonstration
    double shootProbability = 0.8;
    double betweenZeroAndOne = ((double)rand() / RAND_MAX);
    sf::Time elapse_time = shootClock.getElapsedTime();
    std::vector<Projectile*>* shootArr = new std::vector<Projectile*>();
    sf::IntRect spriteRect;
    float spd = 0, damage;
    if (elapse_time >= BossShootTimeDelta + sf::milliseconds((betweenZeroAndOne) * 50))
    {
        shootClock.restart();
        if (betweenZeroAndOne < shootProbability)        // shoot
        {
            ProjectileType randType = static_cast<ProjectileType>(rand() % NumberOfProjectileType);
            switch (randType)
            {
            case RedCircle:
                spriteRect = ProjectileRedCircle;
                spd = ProjectileRedCircleSpd;
                damage = ProjectileRedCircleDamage;
                break;
            case RedSharp:
                spriteRect = ProjectileRedSharp;
                spd = ProjectileRedSharpSpd;
                damage = ProjectileRedSharpDamage;
                break;
            }
            for (int i = 0; i < num; i++) {
                float randomPos = rand() % 100 - 50;
                shootArr->push_back(new Projectile(
                    *objSprite->getTexture(),
                    spriteRect,
                    sf::Vector2f(
                        getSprite().getPosition().x + getSprite().getGlobalBounds().width / 2 + i * randomPos, getSprite().getGlobalBounds().height),
                    sf::Vector2f(0, 1.0f),
                    spd,
                    BossProjectileDamage,
                    randType
                ));

            }
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
    window.draw(getSprite());
}
