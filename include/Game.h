#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"
#include "ToolBar.hpp"
#include "ShipSelection.hpp"
#include "Boss.hpp"
#include "Projectile.h"
#include <Menu.h>
#include <Options.h>
#include <Endscreen.h>
#include <InputHighscore.h>
class Game
{
    bool GAME_PAUSED = 0;

    // frequency of how often can a player shoot

    // Sprites
    sf::Sprite shieldSprite;
    sf::Sprite bossSignSprite;
    sf::Sprite GameBackground;
    sf::Sprite ToolBarBackground;

    //background music
    sf::SoundBuffer backgroundBuffer;
    sf::SoundBuffer titleThemeBuffer;
    sf::Sound backgroundMusic;
    sf::SoundBuffer laserSoundBuffer;
    sf::Sound laserSound;
    sf::SoundBuffer powerupSoundBuffer;
    sf::Sound powerupSound;
    sf::SoundBuffer enemyHurtSoundBuffer;
    sf::Sound enemyHurtSound;
    sf::Texture SpaceTexture;


    // background texture
    sf::Texture BackgroundTexture;
    sf::Texture ToolBarBackgroundTexture;

    // shield
    sf::IntRect SHIELD_RECT = sf::IntRect(132, 0, 47, 46);

    sf::RenderWindow* window;
    std::vector<Projectile*> playerProjectileArray;
    std::vector<Projectile*> enemyProjectileArray;
    std::vector<Projectile*> bossProjectileArray;
    std::vector<Enemy*> enemyArr;
    std::vector<PowerUp*> powerUpArr;
    std::vector<sf::IntRect> enemyRectArr;
    
    // Objects
    Player* player;
    Boss* boss;
    ToolBar* tool;
    Menu* menu;
    Options* options;
    Endscreen* endscreen;
    InputHighscore* inputHighscore;
    
    ShipSelection* shipSelect;

    // Clocks
    sf::Clock genPowerUpClock;
    sf::Clock genEnemyClock;
    sf::Clock genBossClock;
    sf::Clock bossMoveClock;
    sf::Clock gameClock;
    
    // States
    enum ShipType shipType;
    bool ShowBoss = false;
    bool BackdoorTriggered = false;
    bool InfinityHpTriggered = false;
    bool BiggerProjTriggered = false;

    BossStates bossMoveDir = BossStates::MoveRight;
    
public:
    Game();
    ~Game();
    // restart all clock
    void restartClocks();
    void resetBoss();
    void resetGame();
    void gameLoop();
    void handleKeyInput();
    void handleBackdoorKeyInput(sf::Keyboard::Key code);
    void generatePowerUp();
    //void initEnemy(const sf::Vector2u, unsigned int, unsigned int);
    void loadAllMusic();
    void updateBoss(BossStates state, sf::Vector2f destination);
    void updateGame();
    void drawGame();
    void pauseGame();

    // Menu stuff
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
    
    // collision detections
    void collisionPlayerProjAndBoss();
    void collisionBossProjAndPlayer();
    void collisionPlayerProjAndEnemy();
    void collisionEnemyProjAndShield();
    void collisionBossProjAndShield();
    void collisionPlayerAndBoss();
    // Collision between enemyProjectile and player
    void collisionEnemyProjAndPlayer();
    // Check colliision between enemy and player
    void collisionEnemyAndPlayer();
    // Check colliision between powerup and player
    void collisionPowerUpAndPlayer();

    // Enemy Generations
    void generateEnemy();
    int generateDiagonalEnemy(int n, sf::Vector2f initialPos, sf::Vector2f direction, float attribute);
    int generateSquqreEnemy( int row, int col, sf::Vector2f initialPos, sf::Vector2f direction, float attribute);
        
    // for demonstration
    // enemy shoot
    void enemyRandomShoot();
    void bossRandomShoot();
};
#endif

