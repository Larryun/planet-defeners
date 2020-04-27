#include "Player.h"
#include <iostream>


const float Player::PLAYER_WIDTH = 30.0f;
const float Player::PLAYER_HEIGHT = 30.0f;
const float Player::PLAYER_X_VELOCITY = 0;
const float Player::PLAYER_Y_VELOCITY = 0;


Player::~Player()
{
	std::cout << "Player removed" << std::endl;
	delete dummyShape;
}


