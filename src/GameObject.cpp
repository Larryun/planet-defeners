#include "GameObject.hpp"
#include <cmath>

GameObject::GameObject(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& pos, const sf::Vector2f& dir, float spd)
{
    setDirection(dir);
    setSpeed(spd);
    objSprite = new sf::Sprite(texture);
    objSprite->setTextureRect(rect);
    objSprite->setPosition(pos);
}

void GameObject::move()
{
    //printf("%f %f --\n", dummyShape->getPosition().x, dummyShape->getPosition().y);
    objSprite->move(this->getVelocity());

    // if movingBound == (0, 0) that means no movingBound
    if (movingBound != sf::Vector2u(0, 0)) {
        // bound limit
        objSprite->setPosition(sf::Vector2f(fmin(fmax(0, objSprite->getPosition().x), movingBound.x - getBound().width),
            fmin(fmax(0, objSprite->getPosition().y), movingBound.y - getBound().height)));
    }
}

// Move the shape with a given direction
void GameObject::move(const sf::Vector2f& dir)
{
    this->setDirection(dir);
    this->move();
}


void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*objSprite, states);
}

