#ifndef Boss_hpp
#define Boss_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Projectile.h"
#include "Enemy.h"

namespace PlanetDefenders
{
    class Boss : public Enemy {
        sf::Clock shootClock;
        sf::RectangleShape bossHpBar;

    public:
        Boss(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& pos) :
            Enemy(
                texture,
                rect,
                pos,
                1, 100
            ) 
        {
            setBossHpBar(getHp(), sf::Color::Red, sf::Vector2f(33.f, (float)getHp() * 7.2f), sf::Vector2f(0, 720.f));
        }
        ~Boss();
        //sf::Vector2f getPosition
        void setBossHpBar(int hp, sf::Color color, sf::Vector2f size, sf::Vector2f pos);
        void updateBossHpBarSize(int hp) { bossHpBar.setSize(sf::Vector2f(33.f, (float)hp * 7.2f)); }
        void drawTo(sf::RenderWindow& window);
        std::vector<Projectile*>* shoot(int i);
    };
}
#endif /* Boss_hpp */
