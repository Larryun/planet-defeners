//
//  ShipSelection.hpp
//  SFML_Temp
//
//  Created by rich_chan on 6/5/20.
//  Copyright © 2020 rich_chan. All rights reserved.
//

#ifndef ShipSelection_hpp
#define ShipSelection_hpp

#include <stdio.h>
#include "Player.h"


class ShipSelection {
    
    int MAX_NUMBER_OF_ITEMS = 4;
    
    // ship1
    sf::IntRect SHIP_1_TEXTURE_RECT = sf::IntRect(0, 0, 31, 30);
    sf::IntRect SHIP_1_LASER_RECT = sf::IntRect(0, 33, 5, 11);
    // ship2
    sf::IntRect SHIP_2_TEXTURE_RECT = sf::IntRect(33, 0, 27, 21);
    sf::IntRect SHIP_2_LASER_RECT = sf::IntRect(33, 33, 7, 14);
    // ship3
    sf::IntRect SHIP_3_TEXTURE_RECT = sf::IntRect(62, 0, 39, 25);
    sf::IntRect SHIP_3_LASER_RECT = sf::IntRect(62, 33, 11, 11);
    // ship4
    sf::IntRect SHIP_4_TEXTURE_RECT = sf::IntRect(103, 0, 29, 30);
    sf::IntRect SHIP_4_LASER_RECT = sf::IntRect(103, 33, 3, 12);
    
    std::vector<sf::IntRect> shipRect;
    //std::vector<sf::RectangleShape> selectShap;
    sf::RectangleShape selectShap[4];
    std::vector<PlanetDefenders::Player*> playerArray;
    
    sf::Texture shipTexture;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;
    sf::Vector2f shipSize;
public:
    ShipSelection();
    ShipSelection(const sf::Texture&, const sf::Vector2f&);
    void setShipVector();
    void setRectVector(sf::Color color, sf::Vector2f pos);
    void setPlayerVector(sf::Vector2f shipsize);
    
    void drawTo(sf::RenderWindow& window);
//    void setPosition(const sf::Vector2f& p) { getSprite().setPosition(p); }
//    void setSpriteTexture(sf::Texture& texture) { getSprite().setTexture(texture); }
};
#endif /* ShipSelection_hpp */
