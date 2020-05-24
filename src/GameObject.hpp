/*
    GameObject class definition that handle collision detection(TODO) and other logic
*/
#ifndef MOVABLE_H
#define MOVABLE_H
#include <SFML/Graphics.hpp>

class GameObject
{
    // Default values
    sf::Vector2f velocity;

protected:

    sf::Sprite* objSprite;
    sf::Vector2f direction;
    sf::Vector2f pos;
    sf::Vector2u movingBound;
    float speed;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    GameObject(const sf::Vector2f&) = delete;
    GameObject(const sf::Vector2f&, const sf::Vector2f&, float) = delete;

    // initialize a GameObject with
    // Texutre of thet sprite
    // IntRect for the position and dimemsion in the texture
    // Vector2f for initial posistion
    // Vector2f for initial dir (may remove that)
    // float for the speed
    GameObject(const sf::Texture&, const sf::IntRect&, const sf::Vector2f&, const sf::Vector2f&, float);

    void move();
    void move(const sf::Vector2f&);

    // Getters
    const sf::Vector2f getVelocity() const { return speed * direction;  }
    sf::Sprite& getSprite() { return *objSprite; }
    // Get size of sprite
    sf::FloatRect getBound() { return objSprite->getGlobalBounds(); }
    float getSpeed() { return speed; }

    // Setters
    void setSpeed(float const& spd) { speed = spd; }
    void setDirection(const sf::Vector2f& dir) { direction = dir; }
    void setPosition(const sf::Vector2f& p) { objSprite->setPosition(p); }
    void setScale(const sf::Vector2f& scale) { objSprite->setScale(scale); }
    void setMovingBoundary(const sf::Vector2u& bound_) { movingBound = bound_; }
    void setSpriteTexture(sf::Texture& texture) { getSprite().setTexture(texture); }
    void accelerate(float a) { setSpeed(getSpeed() + a); }
    
    //void drawTo(sf::RenderWindow &window){ window.draw(*objSprite); }

};

#endif