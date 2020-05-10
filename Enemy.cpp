#include <iostream>
#include "Enemy.h"



Enemy::~Enemy()
{
	std::cout << "Enemy removed" << std::endl;
	delete objSprite;
}
