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
        sf::Font font;
        sf::Text hpText;
        float eachInterval;
        const sf::Vector2f HpBarPos = sf::Vector2f(0, 0);
        const sf::Vector2f HpBarSize = sf::Vector2f(PlayerMovingBound.x, PlayerMovingBound.y);
        float difficulty = 1.0f;
        float MaxHp = 100;

    public:
        Boss(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& pos) :
            Enemy(
                texture,
                rect,
                pos,
                1, 100
            )
        {
            if (!font.loadFromFile("Samson_Bold_Oblique.ttf"));
            bossHpBar.setPosition(HpBarPos);
            bossHpBar.setFillColor(sf::Color::Red);
            bossHpBar.setSize(HpBarSize);
            eachInterval = HpBarSize.x / MaxHp;
            setHpText(getHp());
        }
        ~Boss();
        //boss hp bar
        void increaseDifficulty(float d)
        {
            difficulty += d;
            MaxHp += 35 * difficulty;
            eachInterval = HpBarSize.x / (float)MaxHp;
        }
        void setDifficulty(float d)
        {
            difficulty = d;
            MaxHp = 100 * difficulty;
            eachInterval = HpBarSize.x / (float)MaxHp;
        }
        float getDifficulty() { return difficulty; }
        void resetHp() { setHp(MaxHp); }
        void updateBossHpBarSize(int hp);
        void updateBossHpBarSize();
        void setHpText(int hp);
        void drawTo(sf::RenderWindow& window);
        std::vector<Projectile*>* shoot(int i);
    };
}
#endif /* Boss_hpp */
