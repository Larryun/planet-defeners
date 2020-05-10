#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Projectile.h"
#include "Player.h"
#include "Game.h"



int main()
{
	Game* spaceinvader = new Game();
	spaceinvader->gameLoop();
	return 0;
}
