#include "GameObject.h"
#include <cmath>


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
	//printf("%f %f --\n", dummyShape->getPosition().x, dummyShape->getPosition().y);
	dummyShape->move(this->getVelocity());

	if (bound != sf::Vector2u(0, 0)) {
		// bound limit
		dummyShape->setPosition(sf::Vector2f(fmin(fmax(0, dummyShape->getPosition().x), bound.x - dummyShape->getSize().x),
			fmin(fmax(0, dummyShape->getPosition().y), bound.y - dummyShape->getSize().y)));
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
	target.draw(*dummyShape, states);
}

