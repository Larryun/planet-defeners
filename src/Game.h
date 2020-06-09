#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"
#include "ToolBar.hpp"
#include "Menu.h"
#include "Options.h"
#include "ShipSelection.hpp"
#include "Boss.hpp"
#include "Projectile.h"
#include "Endscreen.h"
#include "InputHighscore.h"
class Game
{
    bool GAME_PAUSED = 0;

    // frequency of how often can a player shoot

    sf::Sprite GameBackground;
    sf::Sprite ToolBarBackground;
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


    // background texture
    sf::Texture BackgroundTexture;
    sf::Texture ToolBarBackgroundTexture;
    //for ships
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


    // shield
    sf::IntRect SHIELD_RECT = sf::IntRect(132, 0, 47, 46);

    sf::RenderWindow* window;
    std::vector<GameObject*> playerProjectileArray;
    std::vector<GameObject*> enemyProjectileArray;
    //std::vector<Projectile*> bossProjectileArray;
    std::vector<Projectile*> bossProjectileArray;
    std::vector<GameObject*> enemyArr;
    std::vector<GameObject*> powerUpArr;
    std::vector<sf::IntRect> enemyRectArr;
    
    Player* player;
    Boss* boss;
    ToolBar* tool;
    Menu* menu;
    Options* options;
    Endscreen* endscreen;
    InputHighscore* inputHighscore;
    
    ShipSelection* shipSelect;
    sf::Sprite shieldSprite;
    sf::Sprite bossSprite;
  
    sf::Clock genPowerUpClock;
    sf::Clock genEnemyClock;
    
    int numEnemy;
    int randomEnemy;
    int bossHp;
    sf::Vector2f initialPos; //where should the layout start
    sf::Vector2f direction; //they all move in the same direction
    
public:
    Game();
    ~Game();
    void resetGame();
    void gameLoop();
    void handleKeyInput();
    void generatePowerUp();
    //void initEnemy(const sf::Vector2u, unsigned int, unsigned int);
    void loadAllMusic();
    void updateGame();
    void drawGame();
    void pauseGame();

    bool menuHandleKeyboard(sf::Event& event);
    bool menuHandleMouseClicked(sf::Event& event);
    bool menuHandleMouseMove(sf::Event& event);
    bool displayMenu();

    //void loadEnemyRectArray();
    template<class T>
    void updateGameObjectArray(std::vector<T*>& arr);
    template<class T>
    void drawGameObjectArray(std::vector<T*>& arr);
//    void updateProjectile(std::vector<Projectile*>&);
    
    // collision detection
    void collisionPlayerProjAndBoss();
    void collisionBossProjAndPlayer();
    void collisionPlayerProjAndEnemy();
    void collisionEnemyProjAndShield();
    void collisionBossProjAndShield();
    // Collision between enemyProjectile and player
    void collisionEnemyProjAndPlayer();
    // Check colliision between enemy and player
    void collisionEnemyAndPlayer();
    // Check colliision between powerup and player
    void collisionPowerUpAndPlayer();

    void generateEnemy();
    int generateDiagonalEnemy(int n, sf::Vector2f initialPos, sf::Vector2f direction);
    int generateSquqreEnemy( int row, int col, sf::Vector2f initialPos, sf::Vector2f direction);
        
    // for demonstration
    // enemy shoot
    void enemyRandomShoot();
    void bossRandomShoot();
};
#endif

