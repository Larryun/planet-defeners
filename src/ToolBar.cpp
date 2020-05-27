//
//  ToolBar.cpp
//  First_SFML
//
//  Created by rich_chan on 5/20/20.
//  Copyright © 2020 rich_chan. All rights reserved.
//

#include "ToolBar.hpp"
#include "GameText.hpp"
#include <iostream>


template <class T>
void deleteObjectFromVector(std::vector<T*>&, int);

template <class T>
void deleteObjectFromVector(std::vector<T*>& v, int i)
{
    std::swap(v[i], v.back());
    delete v.back();
    v.pop_back();
}

void ToolBar::setHpBar(int hp, sf::Color color, sf::Vector2f size, sf::Vector2f pos){
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setSize(sf::Vector2f(20.f, (float)hp * 20.f));
    hpBar.setPosition(1050.f, 250.f);
}

void ToolBar::setSprites(){
    if(!texture.loadFromFile(TEXTURE_BASE_PATH + "spaceSprites.png"))
        std::cout << "cannot laod .png" << std::endl;
    scoreSp = new GameObject(texture, sf::IntRect(0, 47, 100, 22), sf::Vector2f(990.f,30.0f), sf::Vector2f(0, 0), 0);
    scoreSp->setScale(sf::Vector2f(1.5f, 1.5f));
    timeSp = new GameObject(texture, sf::IntRect(0, 96, 80, 22), sf::Vector2f(1020.0f,100.0f), sf::Vector2f(0, 0), 0);
    timeSp->setScale(sf::Vector2f(1.5f, 1.5f));
    cureSp = new GameObject(texture, sf::IntRect(100, 47, 22, 20), sf::Vector2f(1.f,1.f), sf::Vector2f(0, 0), 0);
    cureSp->setScale(sf::Vector2f(1.5f, 1.5f));
    protectSp = new GameObject(texture, sf::IntRect(122, 47, 22, 20), sf::Vector2f(1.f,1.f), sf::Vector2f(0, 0), 0);
    protectSp->setScale(sf::Vector2f(1.5f, 1.5f));
    shipSp = new GameObject(texture, sf::IntRect(0, 0, 31, 30), sf::Vector2f(100.f,100.f), sf::Vector2f(0, 0), 0);
    shipSp->setScale(sf::Vector2f(1.5f, 1.5f));
    addProtect = new GameObject(texture, sf::IntRect(132, 0, 48, 48), sf::Vector2f(100.f,100.f), sf::Vector2f(0, 0), 0);
    addProtect->setScale(sf::Vector2f(1.5f, 1.5f));
    deleteProtect = new GameObject(texture, sf::IntRect(500, 0, 48, 48), sf::Vector2f(100.f,100.f), sf::Vector2f(0, 0), 0);
    deleteProtect->setScale(sf::Vector2f(1.5f, 1.5f));
    for(int i = 0; i < shipCount; i++){
        shipNum.push_back(new GameObject(texture, sf::IntRect(0, 0, 31, 30), sf::Vector2f(100.f ,100.f), sf::Vector2f(0, 0), 0));
        shipNum[i]->setScale(sf::Vector2f(1.5f, 1.5f));
    }

}

void ToolBar::addProtection(int num1){
    if(isProtect){
        if((num1 - 30) % 10 == 0){
            isProtect = false;
        }
    }
}

void ToolBar::updateShip(){
    shipCount--;
    deleteObjectFromVector(shipNum, shipCount);
}

void ToolBar::addThings(int num){
    if(num == 1){
        thingNum.push_back(cureSp);
    }else{
        isProtect = true;
        thingNum.push_back(protectSp);
    }
    //std::cout << "added!" << std::endl;
}

void ToolBar::updateScore(int score){
    int hundreds = 0, decade = 0, unit = 0;;
    unit = score % 10;
    decade = score / 10 % 10;
    if(unit == 0){
        unit = 10;
    }
    hundreds = score / 100 % 10;
    if(decade == 0){
        decade = 10;
    }
    if(score < 10){
        decade = 10;
        hundreds = 10;
    }
    if(score < 100){
        hundreds = 10;
    }
    scoreHundred = new GameObject(texture, sf::IntRect((hundreds-1) * 20, 72, 20, 22), sf::Vector2f(1160.0f, 30.0f), sf::Vector2f(0, 0), 0);
    scoreHundred->setScale(sf::Vector2f(1.5f, 1.5f));
    scoreDecade = new GameObject(texture, sf::IntRect((decade-1) * 20, 72, 20, 22), sf::Vector2f(1193.0f, 30.0f), sf::Vector2f(0, 0), 0);
    scoreDecade->setScale(sf::Vector2f(1.5f, 1.5f));
    scoreUnit = new GameObject(texture, sf::IntRect((unit-1) * 20, 72, 20, 22), sf::Vector2f(1231.0f, 30.0f), sf::Vector2f(0, 0), 0);
    scoreUnit->setScale(sf::Vector2f(1.5f, 1.5f));
}

void ToolBar::updateTime(){
    sf::Time elapsed = clock.getElapsedTime();
    time = static_cast<double>(elapsed.asSeconds());
    int hundreds = 0, decade = 0, unit = 0;;
    unit = time % 10;
    decade = time / 10 % 10;
    if(unit == 0){
        unit = 10;
    }
    hundreds = time / 100 % 10;
    if(decade == 0){
        decade = 10;
    }
    if(time < 10){
        decade = 10;
        hundreds = 10;
    }
    if(time < 100){
        hundreds = 10;
    }
    timeHundred = new GameObject(texture, sf::IntRect((hundreds-1) * 20, 72, 20, 22), sf::Vector2f(1160.0f,102.0f), sf::Vector2f(0, 0), 0);
    timeHundred->setScale(sf::Vector2f(1.5f, 1.5f));
    timeDecade = new GameObject(texture, sf::IntRect((decade-1) * 20, 72, 20, 22), sf::Vector2f(1193.0f,102.0f), sf::Vector2f(0, 0), 0);
    timeDecade->setScale(sf::Vector2f(1.5f, 1.5f));
    timeUnit = new GameObject(texture, sf::IntRect((unit-1) * 20, 72, 20, 22), sf::Vector2f(1231.0f,102.0f), sf::Vector2f(0, 0), 0);
    timeUnit->setScale(sf::Vector2f(1.5f, 1.5f));

}

void ToolBar::setTextObject(){
    if(!font.loadFromFile("/Users/rich_chan/Downloads/arial.ttf")){
        std::cout << "cannot laod .png" << std::endl;
    }
    hpText = new GameText(sf::Vector2f(1050.f, 210.f), "HP", sf::Color::Red, 24, font);
    dronText = new GameText(sf::Vector2f(1180.f, 210.f), "Things", sf::Color::Green, 24, font);
    hpCountText = new GameText(sf::Vector2f(975.f, 640.f), "ShipCount", sf::Color::Red, 24, font);
}

void ToolBar::drawTo(sf::RenderWindow &window){
    if(isProtect){
        window.draw(addProtect->getSprite());
    }else{
        window.draw(deleteProtect->getSprite());
    }
//    if(time - 5 != 0)
//        window.draw(addProtect->getSprite());
//    if(time - 5 == 0)
//        window.draw(deleteProtect->getSprite());

    hpText->drawTo(window);
    dronText->drawTo(window);
    hpCountText->drawTo(window);

    window.draw(scoreSp->getSprite());
    window.draw(timeSp->getSprite());
    //window.draw(cureSp->getSprite());
    //window.draw(protectSp->getSprite());

    for(int i = 0; i < shipNum.size(); i++){
        shipNum[i]->setPosition(sf::Vector2f(1100.f + 60.f * i, 630.f));
        window.draw(shipNum[i]->getSprite());
    }

    for(int i = 0; i < thingNum.size(); i++){
        //std::cout << "size: "<< thingNum.size() << std::endl;
        thingNum[i]->setPosition(sf::Vector2f(1200.f, 250.f + 40.f * i));
        window.draw(thingNum[i]->getSprite());
    }

    window.draw(timeUnit->getSprite());
    window.draw(timeDecade->getSprite());
    window.draw(timeHundred->getSprite());

    window.draw(scoreUnit->getSprite());
    window.draw(scoreDecade->getSprite());
    window.draw(scoreHundred->getSprite());

    window.draw(hpBar);
}
