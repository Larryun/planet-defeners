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
#include "GameText.hpp"
#include "GameObject.hpp"

class ToolBar : public GameObject{
    const unsigned int BAR_WIDTH = 300;
    const unsigned int BAR_HEIGHT = 720;
    const std::string TEXTURE_BASE_PATH = "resourses/texture/";

    GameObject *scoreSp;
    GameObject *timeSp;
    GameObject *timeHundred;
    GameObject *timeDecade;
    GameObject *timeUnit;
    GameObject *cureSp;
    GameObject *protectSp;
    GameObject *shipSp;
    GameObject *addProtect;
    GameObject *deleteProtect;

    GameObject *scoreHundred;
    GameObject *scoreDecade;
    GameObject *scoreUnit;

    std::vector<GameObject*> shipNum;
    std::vector<GameObject*> thingNum;

    sf::Texture texture;
    sf::RectangleShape hpBar;
    sf::Clock clock;
    sf::Time elapsed;
    sf::Font font;

    std::string countdownString;
    std::ostringstream convert1;
    GameText *hpText; //= new GameText(sf::Vector2f(1050.f, 50.f), "HP", sf::Color::Red, 17);
    GameText *dronText; //= new GameText(sf::Vector2f(1050.f, 70.f), "Drones", sf::Color::Red, 17);
    GameText *hpCountText;
    //GameText *timeText;
    int shipCount = 3;
    int protectTime;
    int time;
    bool isProtect = false;

public:
    ToolBar(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& pos) :
        GameObject(
            texture,
            rect,
            pos,
            sf::Vector2f(0, 0),
            0
        )
    { time = static_cast<double>(elapsed.asSeconds()); }
    ToolBar(sf::Vector2f pos); //const sf::Texture& texture,
    void setTextObject();
    void setSprites();
    void updateTime();
    void updateScore(int score);
    void updateShip();
    void addThings(int num);
    void addProtection(int num1);
    void setHpBar(int hp, sf::Color color, sf::Vector2f size, sf::Vector2f pos);
    //void addHp() { hp += 3;}
    void updateHpBarSize(int hp) {
        hpBar.setSize(sf::Vector2f(30.f, hp * 2.0f));
    }
    void drawTo(sf::RenderWindow &window);
    int getShipCount() { return shipCount; }
};
#endif /* ToolBar_hpp */
