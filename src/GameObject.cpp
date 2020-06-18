#include "GameObject.hpp"
#include "PlanetDefenders.h"
#include <cmath>

using namespace PlanetDefenders;
using namespace PlanetDefenders::utils;

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

bool PlanetDefenders::GameObject::moveTo(const sf::Vector2f& destination)
{
    if (getPosition() != destination)
    {
        static sf::Vector2f dir = normalize(destination - getPosition());
        setDirection(dir);
        move();
        return false;
    }
    return true;
}

// Getters

const sf::Vector2f GameObject::getVelocity() const { return speed * direction; }

/*
    set the direction of the GameObject to another GameObject
    lower the SteeringCoefficient to make it steer harder
*/
void GameObject::moveToward(GameObject& obj)
{
    const static float SteeringCoefficient = 40.0f;
    const static sf::Vector2f offset = sf::Vector2f(obj.getBound().width / 2, obj.getBound().height / 2);
    setDirection(
        normalize(getDirection() + ((normalize(obj.getPosition() + offset - getPosition()) - getDirection()) / SteeringCoefficient))
    );
    roateToDirection();
}

bool GameObject::collide(GameObject& obj)
{
    return Collision::PixelPerfectTest(this->getSprite(), obj.getSprite());
}

bool GameObject::collide(sf::Sprite& spr)
{
    return Collision::PixelPerfectTest(this->getSprite(), spr);
}


void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*objSprite, states);
}

bool GameObject::_isOutOfBound(int margin)
{
    return (getSprite().getPosition().y < -margin ||
            getSprite().getPosition().x < -margin ||
            getSprite().getPosition().y > WindowHeight + margin ||
            getSprite().getPosition().x > WindowWidth + margin);
}

bool GameObject::isOutOfBound()
{
    return _isOutOfBound(BaseDestroyBoundMargin);
}
