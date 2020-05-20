#include "Player.h"
#include <iostream>




Player::~Player()
{
	std::cout << "Player removed" << std::endl;
	delete objSprite;
}


