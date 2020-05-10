#include "Projectile.h"
#include <iostream>

int Projectile::PROJECTILE_COUNTER = 0;
const float Projectile::PROJECTILE_WIDTH = 5.0f;
const float Projectile::PROJECTILE_HEIGHT = 10.0f;
const float Projectile::PROJECTILE_X_VELOCITY = 0.0f;
const float Projectile::PROJECTILE_Y_VELOCITY = -5.0f;


Projectile::~Projectile()
{
	PROJECTILE_COUNTER--;
	std::cout << "Projectile removed" << std::endl;
	delete objSprite;
}

bool Projectile::isOutOfBound() const
{
	return objSprite->getPosition().y < -100;
}


