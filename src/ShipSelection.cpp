//
//  ShipSelection.cpp
//  SFML_Temp
//
//  Created by rich_chan on 6/5/20.
//  Copyright © 2020 rich_chan. All rights reserved.
//

#include "ShipSelection.hpp"
#include "Player.h"
ShipSelection::ShipSelection(const sf::Texture& texture, const sf::Vector2f& pos)
{
    shipTexture = texture;
    position = pos;
    shipSize = sf::Vector2f(100.f, 100.f);
}

void ShipSelection::setRectVector(sf::Color color, sf::Vector2f pos) {
    for (auto i = 0U; i < MAX_NUMBER_OF_ITEMS; i++) {
        selectShap[i].setSize(sf::Vector2f(80.f, 80.f));
        selectShap[i].setFillColor(color);
        selectShap[i].setPosition(pos.x + 150.f * i, pos.y);
    }
}

void ShipSelection::setShipVector() {
    shipRect.push_back(SHIP_1_TEXTURE_RECT);
    shipRect.push_back(SHIP_2_TEXTURE_RECT);
    shipRect.push_back(SHIP_3_TEXTURE_RECT);
    shipRect.push_back(SHIP_4_TEXTURE_RECT);
}

void ShipSelection::setPlayerVector(sf::Vector2f shipsize) {
    for (auto i = 0U; i < MAX_NUMBER_OF_ITEMS; i++) {
        //playerArray.push_back(new PlanetDefenders::Player(shipTexture, shipRect[i], shipSize));
        playerArray[i]->setScale(sf::Vector2f(2.0f, 2.0f));
        playerArray[i]->setPosition(sf::Vector2f(200.f + 150.f * i, 300.f));

    }
}

void ShipSelection::drawTo(sf::RenderWindow& window) {
    window.clear();
    for (auto i = 0U; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(playerArray[i]->getSprite());
        window.draw(selectShap[i]);
    }
    window.display();
}
