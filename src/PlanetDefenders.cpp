#include <vector>
#include <iostream>

#include "Collision.h"
#include "GameObject.hpp"
#include "PlanetDefenders.h"


// check if obj is out of a certain bound
// can be used to check if obj should be deleted
bool PlanetDefenders::isOutOfBound(PlanetDefenders::GameObject* obj1)
{
    return
        (obj1->getSprite().getPosition().y < -100 ||
            obj1->getSprite().getPosition().x < -100 ||
            obj1->getSprite().getPosition().y > WindowHeight + 10 ||
            obj1->getSprite().getPosition().x > WindowWidth + 100);
}

// calculate the unit vector
sf::Vector2f PlanetDefenders::normalize(const sf::Vector2f& v)
{
    float length = sqrt((v.x * v.x) + (v.y * v.y));
    if (length != 0)
        return sf::Vector2f(v.x / length, v.y / length);
    else
        return v;
}

// limit a vector
sf::Vector2f PlanetDefenders::truncate(const sf::Vector2f& v, const float MAXIMUM)
{
    return sf::Vector2f(std::min(v.x, MAXIMUM), std::min(v.y, MAXIMUM));
}


void PlanetDefenders::setSpriteOriginCenter(sf::Sprite& spr)
{ 
    spr.setOrigin(spr.getGlobalBounds().width / 2.0f, spr.getGlobalBounds().height / 2.0f);
}


void PlanetDefenders::drawOutline(sf::Sprite& spr, sf::RenderWindow& window)
{
    sf::RectangleShape rect = sf::RectangleShape(
        sf::Vector2f(spr.getGlobalBounds().width, spr.getGlobalBounds().height)
    );
    rect.setPosition(spr.getPosition() - spr.getOrigin());
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(3);
    window.draw(rect);
}
