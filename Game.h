#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
	const unsigned int WINDOW_WIDTH = 512;
	const unsigned int WINDOW_HEIGHT = 512;
	const std::string GAME_TITLE = "Space Invaders?";
	const unsigned int FRAME_RATE_LIMIT = 65;

	const int MAX_PROJECTILE_NUM = 500;
	const int PROJECTILE_TIME_INTERVAL = 200;
	const sf::Time PROJECTILE_TIME_DELTA = sf::milliseconds(PROJECTILE_TIME_INTERVAL);

	sf::Clock* clock;
	sf::RenderWindow* window;
	std::vector<Projectile*> projectileArray;
	Player* player = new Player(sf::Vector2f(100,100));
	std::vector<Enemy*> enemiesArr;

public:
	Game();
	void init();
	void gameLoop();
	void handleKeyInput();
	void shoot();
	void drawProjectileArray(std::vector<Projectile*>&);


};
#endif

