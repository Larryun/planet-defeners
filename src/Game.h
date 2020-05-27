#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"
#include "ToolBar.hpp"

class Game
{
    bool GAME_PAUSED = 0;

    // frequency of how often can a player shoot

    sf::Sprite background;
    //background music
    sf::SoundBuffer backgroundBuffer;
    sf::Sound backgroundMusic;
    sf::SoundBuffer laserSoundBuffer;
    sf::Sound laserSound;
    sf::SoundBuffer powerupSoundBuffer;
    sf::Sound powerupSound;
    sf::SoundBuffer enemyHurtSoundBuffer;
    sf::Sound enemyHurtSound;
    sf::Texture SPACE_TEXTURE;


    // Put these into namespace ??

    //background texture
    sf::Texture BACKGROUND_TEXTURE;
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

    // PowerUp
    // health restore
    sf::IntRect HEALTH_RESTORE_RECT = sf::IntRect(100, 48, 20, 20);
    // shield powerup
    sf::IntRect SHIELD_POWERUP_RECT = sf::IntRect(122, 48, 20, 20);

    // shield
    sf::IntRect SHIELD_RECT = sf::IntRect(132, 0, 47, 46);

    sf::Clock* clock;
    sf::RenderWindow* window;
    std::vector<GameObject*> projectileArray;
    std::vector<GameObject*> enemyArr;
    std::vector<GameObject*> powerUpArr;

    Player* player;
    ToolBar* tool;

    int count = 0;
    // move that to player member later
    int hp = 10;

    // for test
    PowerUp* healPower;
    PowerUp* shield;
    sf::Sprite shieldSprite;


public:
    Game();
    ~Game();
    void init() = delete;
    void gameLoop();
    void updateGame();
    void handleKeyInput();
    void shoot();
    void updateGameObjectArray(std::vector<GameObject*>&);
    void drawGameObjectArray(std::vector<GameObject*>&);
    void initEnemy(const sf::Vector2u, unsigned int, unsigned int);
    void loadAllMusic();
    void pauseGame();

};
#endif

