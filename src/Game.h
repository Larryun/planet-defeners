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
	// frequency of how often can a player shoot
	const int PROJECTILE_TIME_INTERVAL = 200;
	const sf::Time PROJECTILE_TIME_DELTA = sf::milliseconds(PROJECTILE_TIME_INTERVAL);

	// the base texture
	sf::Texture SPACE_TEXTURE;
	// then crop the texture according to the IntRect given
	sf::IntRect SHIP_1_TEXTURE_RECT = sf::IntRect(6, 2, 31, 30);
	sf::IntRect PROJECTILE_RECT = sf::IntRect(10, 35, 5, 11);
	sf::IntRect ENEMY_RECT = sf::IntRect(11, 52, 10, 10);

	sf::Clock* clock;
	sf::RenderWindow* window;
	std::vector<Projectile*> projectileArray;
	std::vector<Enemy*> enemyArr;
	Player* player;

public:
	Game();
	~Game();
	void init();
	void gameLoop();
	void handleKeyInput();
	void shoot();
	template <class T>
	void drawGameObjectArray(std::vector<T*>&);


};
#endif

