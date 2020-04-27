#include "GameObject.h"


GameObject::GameObject(const sf::Vector2f& pos) : 
	velocity(sf::Vector2f(MOVABLE_X_VELOCITY, MOVABLE_Y_VELOCITY))
{
	dummyShape = new sf::RectangleShape(sf::Vector2f(MOVABLE_WIDTH, MOVABLE_HEIGHT));
	dummyShape->setPosition(pos);
}

GameObject::GameObject(const sf::Vector2f& pos, const sf::Vector2f& shapeSize, const sf::Vector2f& dir, float spd)
{
	setDirection(dir);
	setSpeed(spd);
	dummyShape = new sf::RectangleShape(shapeSize);
	dummyShape->setPosition(pos);
}

void GameObject::move()
{
	dummyShape->move(this->getVelocity());
}

// Move the shape with a given direction
void GameObject::move(const sf::Vector2f& dir)
{
	this->setDirection(dir);
	this->move();
}

bool GameObject::checkBound() const 
{
	return dummyShape->getPosition().y > -100;
}


void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*dummyShape, states);
}
