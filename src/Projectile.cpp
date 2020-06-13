#include <iostream>
#include "Projectile.h"

using namespace PlanetDefenders;

int Projectile::PROJECTILE_COUNTER = 0;

Projectile::~Projectile()
{
	PROJECTILE_COUNTER--;
	std::cout << "Projectile removed" << std::endl;
	delete objSprite;
}



