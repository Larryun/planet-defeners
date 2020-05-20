#include "Projectile.h"
#include <iostream>

int Projectile::PROJECTILE_COUNTER = 0;


Projectile::~Projectile()
{
	PROJECTILE_COUNTER--;
	std::cout << "Projectile removed" << std::endl;
	delete objSprite;
}



