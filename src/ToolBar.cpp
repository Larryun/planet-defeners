//
//  ToolBar.cpp
//  First_SFML
//
//  Created by rich_chan on 5/20/20.
//  Copyright © 2020 rich_chan. All rights reserved.
//
//  Modified by Larry on 5/30/20

#include "ToolBar.hpp"
#include "PlanetDefenders.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace PlanetDefenders;


void ToolBar::initializeHpBar(int hp)
{
    hpBar.setFillColor(HpBarColor);
    hpBar.setSize(sf::Vector2f(30.f, (float)hp * 20.f));
    hpBar.setPosition(sf::Vector2f(1142.f, 161.f));
}

void ToolBar::updateHpBarSize(float hpPercent) {
    hpBar.setSize(sf::Vector2f(30.f, 260 * hpPercent));
    hpBar.setOrigin(0, hpBar.getSize().y - 250);
}


/*
    set the activated PowerUp in the toolbar
*/
void ToolBar::setPowerUp(PowerUpType type, unsigned int duration)
{
    if (type != HEAL)
    {
        powerUpDuration = duration;
        drawPowerUp = true;
        powerUpClock = new sf::Clock();         // "restart" the clock, don't forgot delete the clock when stop
    }
    switch (type)
    {
    case SHIELD:
        activatedPowerUpSp.setTextureRect(ToolBarShieldPowerUp);
        break;
    //case HEAL:
    //    activatedPowerUpSp.setTextureRect(ToolBarHealPowerUp);
    //    powerUpDuration = 1;                       // show it for 1 sec
    //    break;
    // add more case here if you have more PowerUps
    }
}


void ToolBar::generateDigitRects()
{
    for (int i = 1; i < 10; i++)
    {
        digitRects[i] = sf::IntRect(208, 24 + (i) * 24, 20, 22);
    }
    digitRects[0] = sf::IntRect(208, 264, 20, 22);
}

void ToolBar::initializeSprites() {
    initializeHpBar(0);
    // TODO use Game variable texture

    hpBorderSp = sf::Sprite(ToolBarTexture, PlanetDefenders::HpBorderRect);
    hpBorderSp.setPosition(sf::Vector2f(1136, 138));

    scoreSp = sf::Sprite(ToolBarTexture, PlanetDefenders::ScoreRect);
    scoreSp.setPosition(sf::Vector2f(1104, 24));

    timeSp = sf::Sprite(ToolBarTexture, PlanetDefenders::TimeRect);
    timeSp.setPosition(sf::Vector2f(1104, 72));

    activatedPowerUpSp = sf::Sprite(ToolBarTexture);
    activatedPowerUpSp.setPosition(sf::Vector2f(1212, 379));

    activatedPowerUpContainerSp = sf::Sprite(ToolBarTexture, TheThingThatLooksLikeaTV);
    activatedPowerUpContainerSp.setPosition(sf::Vector2f(1200, 364));

    generateDigitRects();

    // initialize score Sprites without IntRect first,
    // call lsetTextureRect() later to update the texture
    for (int i = 0; i < 8; i++)
    {
        scoreSprites[i] = sf::Sprite(ToolBarTexture);
        scoreSprites[i].setPosition(sf::Vector2f(1116 + i * 20, 48));
    }

    // initialize time Sprites without IntRect first,
    // call lsetTextureRect() later to update the texture
    for (int i = 0; i < 8; i++)
    {
        timeSprites[i] = sf::Sprite(ToolBarTexture);
        timeSprites[i].setPosition(sf::Vector2f(1116 + i * 20, 96));
    }
}

void ToolBar::addProtection(int num1) {
    if (isProtect) {
        if ((num1 - 30) % 10 == 0) {
            isProtect = false;
        }
    }
}

/*********/
void ToolBar::updateShip() {
    shipCount--;
    deleteObjectFromVector(shipNum, shipCount);
}

/*
    it will update the activatedPowerUpEnded variable to true if the it's ended
    if activatedPowerEnded == true, it won't be drawn in the drawTo function
*/
void ToolBar::updateActivatedPowerUp()
{
    // powerUpClock is uninitalized
    if (powerUpClock == nullptr)
        drawPowerUp = false;
    else
        drawPowerUp = powerUpClock->getElapsedTime().asSeconds() < powerUpDuration;
}


void ToolBar::updateScore() {
    std::stringstream ss;
        ss << std::setw(8) << std::setfill('0') << scoreCounter;
    // format the string to fill with zeros e.g. "009", "024"
    std::string scoreString = ss.str();
    for (int i = 0; i < 8; i++)
    {
        scoreSprites[i].setTextureRect(digitRects[scoreString[i] - '0']);
    }
}

void ToolBar::updateTime() {
    int time = static_cast<unsigned int>(timeClock.getElapsedTime().asSeconds());
    std::stringstream ss;
    // format the string to fill with zeros e.g. "009", "024"
    ss << std::setw(8) << std::setfill('0') << time;
    //std::cout << ss.str() << std::endl;
    std::string timeString = ss.str();
    for (int i = 0; i < 8; i++)
    {
        timeSprites[i].setTextureRect(digitRects[timeString[i] - '0']);
    }
}

/*
    Put all update functions in here
*/
void ToolBar::update()
{
    updateScore();
    updateTime();
    updateActivatedPowerUp();
}

/*
    Put all draw functions in here
*/
void ToolBar::drawTo(sf::RenderWindow& window) {
    for (int i = 0; i < 8; i++)
    {
        window.draw(scoreSprites[i]);
    }

    for (int i = 0; i < 8; i++)
    {
        window.draw(timeSprites[i]);
    }

    window.draw(scoreSp);
    window.draw(timeSp);
    window.draw(hpBorderSp);
    window.draw(hpBar);
    if (drawPowerUp)
        window.draw(activatedPowerUpSp);
    window.draw(activatedPowerUpContainerSp);
}
