//
//  GameText.cpp
//  First_SFML
//
//  Created by rich_chan on 5/17/20.
//  Copyright © 2020 rich_chan. All rights reserved.
//

#include "GameText.hpp"
#include <string>

GameText::GameText(const sf::Vector2f position, std::string textString, sf::Color color, int size, sf::Font& font) {
    textbox.setCharacterSize(size);
    textbox.setFillColor(color);
    textbox.setPosition(position);
    textbox.setString(textString);
    textbox.setFont(font);
}
//GameText::GameText(int size, sf::Color color, bool sel){
//    textbox.setCharacterSize(size);
//    textbox.setFillColor(color);
//    isSelect = sel;
//    if(sel){
//        textbox.setString("_");
//    }else{
//        textbox.setString("");
//    }
//}

//
//void GameText::setSelected(bool sel){
//    isSelect = sel;
//    if(!sel){
//        std::string t = text.str();
//        std::string newT = "";
//        for(int i = 0; i < t.length(); i++){
//            newT += t[i];
//        }
//        textbox.setString(text.str());
//    }
//}
//
//void GameText::typedOn(sf::Event input){
//    if(isSelect){
//        int charType = input.text.unicode;
//        if(charType < 128){
//            if(hasLimit){
//                if(text.str().length() <= limit){
//                    inputLogic(charType);
//                }else if(text.str().length() > limit && charType == DELETE_KEY){
//                    deleteLastChar();
//                }
//            }else{
//                inputLogic(charType);
//            }
//        }
//    }
//}
//
//void GameText::inputLogic(int charType){
//    if(charType != DELETE_KEY && charType != ENTER_KEY && charType != ESCAPE_KEY) {
//        text << static_cast<char>(charType);
//    }else if(charType == DELETE_KEY){
//        if(text.str().length() > 0){
//            deleteLastChar();
//        }
//    }
//    textbox.setString(text.str() + "_");
//}
//
//void GameText::deleteLastChar(){
//    std::string t = text.str();
//    std::string newT = "";
//    for(int i = 0; i < t.length()-1; i++){
//        newT += t[i];
//    }
//    text.str("");
//    text << newT;
//    textbox.setString(text.str());
//
//}

//
//void GameText::draw(sf::RenderWindow& target) const
//{
//    target.draw(text);
//}
