//
//  ToolBar.hpp
//  First_SFML
//
//  Created by rich_chan on 5/20/20.
//  Copyright © 2020 rich_chan. All rights reserved.
//

#ifndef ToolBar_hpp
#define ToolBar_hpp
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <set>
#include "GameObject.hpp"
#include "PlanetDefenders.h"
#include "PowerUp.h"

using namespace PlanetDefenders;

namespace PlanetDefenders
{
    class ToolBar
    {
        const unsigned int BAR_WIDTH = 300;
        const unsigned int BAR_HEIGHT = 720;

        sf::IntRect digitRects[10];
        sf::Sprite scoreSprites[8];
        sf::Sprite timeSprites[8];

        sf::Sprite hpBorderSp;
        sf::Sprite scoreSp;
        sf::Sprite timeSp;
        sf::Sprite activatedPowerUpContainerSp;
        sf::Sprite activatedPowerUpSp;
        PowerUp* activatedPowerUp;

        // Unused
        sf::Sprite cureSp;
        sf::Sprite protectSp;
        sf::Sprite shipSp;
        sf::Sprite addProtect;
        sf::Sprite deleteProtect;


        sf::Texture ToolBarTexture;
        sf::RectangleShape hpBar;
        sf::Clock timeClock;
        sf::Clock* powerUpClock;
        unsigned int powerUpDuration;

        int protectTime;
        bool isProtect = false;
        unsigned int scoreCounter = 0;
        bool drawPowerUp = false;

        void generateDigitRects();
        void initializeHpBar(int hp);
        void updateScore();
        void updateTime();
        void updateActivatedPowerUp();
        void initializeSprites();

    public:
        ToolBar(const sf::Vector2f& pos, sf::Texture& toolbarTexture) : ToolBarTexture(toolbarTexture)
        {
            initializeSprites();
        }
        ~ToolBar() 
        { 
            delete powerUpClock;
            delete activatedPowerUp;
        }


        void restartClock() { timeClock.restart(); }

        const sf::Clock getTime() { return timeClock; }
        const sf::Vector2f getSize() { return sf::Vector2f(BAR_WIDTH, BAR_HEIGHT); }
        const unsigned int getScore() { return scoreCounter; }

        void addProtection(int num1);
        void addScore(unsigned int x) { scoreCounter += x; }
        void minusScore(int x) { scoreCounter -= x; }
        void updateHpBarSize(float hp);
        void setPowerUp(PowerUpType type, unsigned int duration);
        void update();
        void drawTo(sf::RenderWindow& window);
    };

}
#endif /* ToolBar_hpp */
