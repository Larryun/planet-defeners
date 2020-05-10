#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
	const std::string TEXTURE_BASE_PATH = "resourses/texture/";
	const unsigned int WINDOW_WIDTH = 512;
	const unsigned int WINDOW_HEIGHT = 512;
	const std::string GAME_TITLE = "Space Invaders?";
	const unsigned int FRAME_RATE_LIMIT = 65;

	const int MAX_PROJECTILE_NUM = 500;
	const int PROJECTILE_TIME_INTERVAL = 200;
	const sf::Time PROJECTILE_TIME_DELTA = sf::milliseconds(PROJECTILE_TIME_INTERVAL);
	// For different type of ship textures
	sf::Texture SPACE_TEXTURE;
	sf::IntRect SHIP_1_TEXTURE_RECT = sf::IntRect(18, 6, 93, 90);
	sf::IntRect PROJECTILE_RECT = sf::IntRect(30, 105, 15, 33);
	sf::IntRect ENEMY_RECT = sf::IntRect(51, 114, 12, 12);



	sf::Clock* clock;
	sf::RenderWindow* window;
	std::vector<Projectile*> projectileArray;
	std::vector<Enemy*> enemiesArr;
	Player* player;

public:
	Game();
	void init();
	void gameLoop();
	void handleKeyInput();
	void shoot();
	template <class T>
	void drawGameObjectArray(std::vector<T*>&);


};
#endif

