#include "GameObject.h"


void GameObject::move()
{
	// Call Parent move() method
	sf::Shape::move(this->getVelocity());
	update();
}
//
void GameObject::move(const sf::Vector2f& dir)
{
	this->setVelocity(dir);
	this->move();
}

bool GameObject::checkBoundry() const 
{
	return getPosition().y > -100;
}


