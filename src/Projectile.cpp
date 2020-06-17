#include <iostream>
#include "Projectile.h"

using namespace PlanetDefenders;

int Projectile::PROJECTILE_COUNTER = 0;

Projectile::~Projectile()
{
	PROJECTILE_COUNTER--;
	//std::cout << *this << " removed" << std::endl;
	delete objSprite;
}

bool PlanetDefenders::Projectile::isOutOfBound()
{
    return _isOutOfBound(ProjectileDestroyBoundMargin);
}



