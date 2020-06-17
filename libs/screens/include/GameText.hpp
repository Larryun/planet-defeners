//
//  GameText.hpp
//  First_SFML
//
//  Created by rich_chan on 5/17/20.
//  Copyright © 2020 rich_chan. All rights reserved.
//

#ifndef GameText_hpp
#define GameText_hpp
#include <SFML/Graphics.hpp>
#include <cstring>
#include <sstream>
#include <stdio.h>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class GameText {
private:
    sf::Text textbox;

    std::ostringstream text;
    //    int limit;
    //    bool isSelect = false;
    //    bool hasLimit = false;
    //    void inputLogic(int charType);
    //    void deleteLastChar();
        //sf::Vector2f _direction;
        //std::string _textString;
        //sf::Color _color;

public:
    GameText() {}
    //GameText(int size, sf::Color color, bool sel);
    void setFont(sf::Font& font) { textbox.setFont(font); }
    void setPosition(sf::Vector2f pos) { textbox.setPosition(pos); }
    std::string getText() { return text.str(); }
    void drawTo(sf::RenderWindow& window) { window.draw(textbox); }
    void setString(std::string t) { textbox.setString(t); }
    GameText(const sf::Vector2f position, std::string textString, sf::Color color, int size, sf::Font& font);

    //    
    //    void setLimit(bool toF) { hasLimit = toF;}
    //    void setLimit(bool toF, int lim) { hasLimit = toF; limit = lim;}
    //    void setSelected(bool sel);
    //    void typedOn(sf::Event input);
        //    void draw(sf::RenderWindow& target) const;
    //    //sf::Vector2f getSize(){ return text->getSize(); }
    //
    //    //std::string getString() { return text->getString(); }
    //    void setString(std::string text) { _textString = text; }
    //    void setColor(sf::Color color) { _color = color; }
    //    void setSize(int size) { _size = size; }
    //    void setDirection(const sf::Vector2f& dir) { _direction = dir; }
};
#endif /* GameText_hpp */
