#include "Projectile.h"
#include <iostream>

int Projectile::PROJECTILE_COUNTER = 0;

Projectile::Projectile(sf::Vector2f pos)
{
	projectileShape = new sf::RectangleShape(sf::Vector2f(5.0f, 10.0f));
	projectileShape->setPosition(pos);
	PROJECTILE_COUNTER++;
	std::cout << "Projectile Created " << PROJECTILE_COUNTER << std::endl;
}

Projectile::~Projectile()
{
	PROJECTILE_COUNTER--;
	std::cout << "Projectile removed" << std::endl;
	delete projectileShape;
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*projectileShape, states);
}

void Projectile::update()
{
	projectileShape->move(velocity);
}

bool Projectile::checkBoundry()
{
	return projectileShape->getPosition().y > -100;
}

sf::Vector2f Projectile::getPosition()
{
	return projectileShape->getPosition();
}


