//
//  GameWindow.cpp
//  SFML_Temp
//
//  Created by rich_chan on 5/26/20.
//  Copyright © 2020 rich_chan. All rights reserved.
//
#include "GameWindow.hpp"
#include <iostream>

void GameWindow::setSprite(){
    if(!texture.loadFromFile(TEXTURE_BASE_PATH + "spaceBackground.png"))
        std::cout << "cannot laod .pngx" << std::endl;
    background = new GameObject(texture, sf::IntRect(0, 0, 1076, 720), sf::Vector2f(0.f, 0.f), sf::Vector2f(0, 0), 0);
}

void GameWindow::drawTo(sf::RenderWindow &window){
    window.draw(background->getSprite());
}
