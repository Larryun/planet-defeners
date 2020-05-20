#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
    const std::string TEXTURE_BASE_PATH = "resourses/texture/";
    const unsigned int WINDOW_WIDTH = 1280;
    const unsigned int WINDOW_HEIGHT = 720;
    const std::string GAME_TITLE = "Space Invaders?";
    const unsigned int FRAME_RATE_LIMIT = 65;

    const int MAX_PROJECTILE_NUM = 500;
    // frequency of how often can a player shoot
    const int PROJECTILE_TIME_INTERVAL = 100;
    const sf::Time PROJECTILE_TIME_DELTA = sf::milliseconds(PROJECTILE_TIME_INTERVAL);

    // the base texture
    sf::Texture SPACE_TEXTURE;
    // then crop the texture according to the IntRect given
    //sf::IntRect SHIP_1_TEXTURE_RECT = sf::IntRect(6, 2, 31, 30);
    sf::IntRect PROJECTILE_RECT = sf::IntRect(0, 32, 5, 11);
    sf::IntRect ENEMY_RECT = sf::IntRect(33, 0, 27, 21);
    // ship1 
    sf::IntRect SHIP_1_TEXTURE_RECT = sf::IntRect(0, 0, 31, 30);
    sf::IntRect SHIP_1_LASER_RECT = sf::IntRect(0, 33, 5, 11);
    // ship2 
    sf::IntRect SHIP_2_TEXTURE_RECT = sf::IntRect(33, 0, 27, 21);
    sf::IntRect SHIP_2_LASER_RECT = sf::IntRect(33, 33, 7, 14);
    // ship3 
    sf::IntRect SHIP_3_TEXTURE_RECT = sf::IntRect(62, 0, 39, 25);
    sf::IntRect SHIP_3_LASER_RECT = sf::IntRect(62, 33, 11, 11);
    // ship4 
    sf::IntRect SHIP_4_TEXTURE_RECT = sf::IntRect(103, 0, 29, 30);
    sf::IntRect SHIP_4_LASER_RECT = sf::IntRect(103, 33, 3, 12);

    sf::Clock* clock;
    sf::RenderWindow* window;
    std::vector<GameObject*> projectileArray;
    std::vector<GameObject*> enemyArr;
    Player* player;

public:
    Game();
    ~Game();
    void init();
    void gameLoop();
    void handleKeyInput();
    void shoot();
    void drawGameObjectArray(std::vector<GameObject*>&);
    void initEnemy(const sf::Vector2u, unsigned int, unsigned int);
    bool isOutOfBound(GameObject*);

};
#endif

