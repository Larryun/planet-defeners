//
//  GameWindow.hpp
//  SFML_Temp
//
//  Created by rich_chan on 5/26/20.
//  Copyright © 2020 rich_chan. All rights reserved.
//

#ifndef GameWindow_hpp
#define GameWindow_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Powerup.hpp"
#include "GameObject.hpp"

class GameWindow : public GameObject{
    const std::string TEXTURE_BASE_PATH = "resourses/texture/";
    const unsigned int GAME_HEIGHT = 720;
    const unsigned int GAME_WIDTH = 1076;
    
    
    GameObject *background;
    sf::Texture texture;
public:
    ~GameWindow();
    GameWindow(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& pos) :
        GameObject(
            texture,
            rect,
            pos,
            sf::Vector2f(0, 0),
            0.0f        // Initial speed
        )
    { }
    void setSprite();

    void drawTo(sf::RenderWindow &window);
};
#endif /* GameWindow_hpp */
