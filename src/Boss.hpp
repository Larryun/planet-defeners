#ifndef Boss_hpp
#define Boss_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Projectile.h"

class Boss : public GameObject {
    sf::Clock shootClock;
    sf::RectangleShape bossHpBar;



public:
    Boss(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& pos) :
        GameObject(
            texture,
            rect,
            pos,
            sf::Vector2f(0, 0.0f),
            0
        )
    {}
    ~Boss();
    //sf::Vector2f getPosition
    bool isOutOfBound() { return false; }

        void setBossHpBar(int hp, sf::Color color, sf::Vector2f size, sf::Vector2f pos);
        void updateBossHpBarSize(int hp) { bossHpBar.setSize(sf::Vector2f(33.f, (float)hp * 7.2f)); }
        void drawTo(sf::RenderWindow &window);
        std::vector<Projectile*>* shoot(int i);
};
#endif /* Boss_hpp */
