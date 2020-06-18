#include <iostream>
#include <cassert>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ResourceNotLoaded.h>
#include <Menu.h>
#include <Options.h>
#include <Endscreen.h>
#include <InputHighscore.h>
#include "Collision.h"
#include "Game.h"
#include "Player.h"
#include "Projectile.h"
#include "ToolBar.hpp"
#include "HealthRestore.h"
#include "Shield.h"

using namespace PlanetDefenders;
using namespace PlanetDefenders::utils;

void Game::loadAllMusic()
{
    // add exception handling here
    if (!titleThemeBuffer.loadFromFile(AudioBasePath + "titleTheme.ogg"))
        throw MusicNotLoaded("titleTheme.ogg");
    else
        backgroundMusic.setBuffer(titleThemeBuffer);
    if (!backgroundBuffer.loadFromFile(AudioBasePath + "game_music.ogg"))
        throw MusicNotLoaded("game_music.ogg");
    if (!laserSoundBuffer.loadFromFile(AudioBasePath + "laser.ogg"))
        throw MusicNotLoaded("laser.ogg");
    else {
        laserSound.setBuffer(laserSoundBuffer);
        laserSound.setVolume(120);
    }
    if (!powerupSoundBuffer.loadFromFile(AudioBasePath + "enemy_hurt.ogg"))
        throw MusicNotLoaded("enemy_hurt.ogg");
    else
        enemyHurtSound.setBuffer(powerupSoundBuffer);
    if (!enemyHurtSoundBuffer.loadFromFile(AudioBasePath + "powerup.ogg"))
        throw MusicNotLoaded("powerup.ogg");
    else {
        powerupSound.setBuffer(enemyHurtSoundBuffer);
        powerupSound.setVolume(40);
    }
}

template<class T>
void Game::updateGameObjectArray(std::vector<T*>& arr)
{
    for (auto& v : arr)
        v->move();
}

template<class T>
void Game::drawGameObjectArray(std::vector<T*>& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i]->isOutOfBound() == false)
            window->draw(arr[i]->getSprite());
        else
            deleteObjectFromVector(arr, i);
    }
}

void Game::pauseGame()
{
    if (GAME_PAUSED) backgroundMusic.pause();
    else backgroundMusic.play();
}

bool Game::menuHandleKeyboard(sf::Event& event)
{
    //using left and right keys to switch between the options
    switch (event.key.code) {
    case sf::Keyboard::Left:
        menu->MoveLeft();
        break;
    case sf::Keyboard::Right:
        menu->MoveRight();
        break;
    case sf::Keyboard::Return:
        switch (menu->getPressedItem()) {
        case 0:
            std::cout << "Play button has been pressed" << std::endl;
            return true;
            break;
        case 1:
            std::cout << "Options button has been pressed" << std::endl;
            // to options view
            options->work(*window, event, *options, GameBackground, backgroundMusic);
            break;
        case 2:
            std::cout << "Exit button has been pressed" << std::endl;
            window->close();
            return true;
            break;
        }
    }
    return false;
}

bool Game::menuHandleMouseClicked(sf::Event& event)
{
    if (menu->inY(event, *window)) {
        if (menu->inXPlay(event, *window)) {
            std::cout << "PLAY" << std::endl;
            return true;
        }
        else if (menu->inXOptions(event, *window)) {
            std::cout << "Options" << std::endl;
            // to options view
            options->work(*window, event, *options, GameBackground, backgroundMusic);
        }
        else if (menu->inXExit(event, *window)) {
            std::cout << "Exit" << std::endl;
            window->close();
            return true;
        }
    }
    return false;
}

bool Game::menuHandleMouseMove(sf::Event& event)
{
    if (menu->inYHover(event, *window)) {
        if (menu->inXPlayHover(event, *window)) {
            menu->clickMenu();
        }
        else if (menu->inXOptionsHover(event, *window)) {
            menu->clickOptions();
        }
        else if (menu->inXExitHover(event, *window)) {
            menu->clickExit();
        }
    }
    return false;
}


/*
    return true to leave the menu and go back to main game loop
    return false keep showing menu
*/
bool Game::displayMenu()
{
    sf::Event event;
    while (window->pollEvent(event)) {
        switch (event.type) {
        case sf::Event::KeyReleased:
            if (menuHandleKeyboard(event))
                return true;
            //Clicking on a button
        case sf::Event::MouseButtonReleased:
            if (menuHandleMouseClicked(event))
                return true;
            //Changing colors when hovering over the buttons
        case sf::Event::MouseMoved:
            menuHandleMouseMove(event);
            break;
        case sf::Event::Closed:
            window->close();
            return true;
            break;
        }
    }
    window->draw(GameBackground);
    menu->draw(*window);
    return false;
}

void Game::collisionPlayerProjAndBoss()
{
    // Collision between playerProjectile and enemy
    for (int i = 0; i < playerProjectileArray.size(); i++)
    {
        if (playerProjectileArray[i]->collide(*dynamic_cast<GameObject*>(boss)))
        {
            enemyHurtSound.play();
            tool->addScore(1);
            boss->takeDamage(playerProjectileArray[i]->getDamage());
            //std::cout << "PROJECTILE COLIDED BOSS" << std::endl;
            deleteObjectFromVector(playerProjectileArray, i);
            break;
        }
    }
}

void Game::collisionBossProjAndPlayer()
{
    for (int i = 0; i < bossProjectileArray.size(); i++)
    {
        //if (checkCollision(bossProjectileArray[i], player))
        if (bossProjectileArray[i]->collide(*dynamic_cast<GameObject*>(player)))
        {
            player->takeDamage(bossProjectileArray[i]->getDamage());

            //std::cout << "BOSS PROJECTILE COLIDED PLAYER" << std::endl;
            deleteObjectFromVector(bossProjectileArray, i);
            break;
        }
    }
}

void Game::collisionPlayerProjAndEnemy()
{
    // Collision between playerProjectile and enemy
    for (int i = 0; i < playerProjectileArray.size(); i++)
    {
        for (int j = 0; j < enemyArr.size(); j++)
        {
            if (playerProjectileArray[i]->collide(*dynamic_cast<GameObject*>(enemyArr[j])))
            {
                enemyHurtSound.play();
                enemyArr[j]->takeDamage(playerProjectileArray[i]->getDamage());
                if (enemyArr[j]->isDead())
                {
                    tool->addScore(roundf(pow(enemyArr[j]->getAttribute(), 3) * RegularEnemyScore));
                    deleteObjectFromVector(enemyArr, j);
                }
                deleteObjectFromVector(playerProjectileArray, i);
                //std::cout << "PROJECTILE COLIDED ENEMY" << std::endl;
                break;
            }
        }
    }
}

void Game::collisionEnemyProjAndShield()
{
    // Collision between enemyProjectile player shield
    for (int i = 0; i < enemyProjectileArray.size(); i++)
    {
        if (enemyProjectileArray[i]->collide(shieldSprite))
        {
            deleteObjectFromVector(enemyProjectileArray, i);
            break;
        }
    }
}

void Game::collisionBossProjAndShield()
{
    for (int i = 0; i < bossProjectileArray.size(); i++)
    {
        if (bossProjectileArray[i]->collide(shieldSprite))
        {
            deleteObjectFromVector(bossProjectileArray, i);
            break;
        }
    }
}

void Game::collisionPlayerAndBoss()
{
    if (player->collide(*dynamic_cast<GameObject*>(boss)))
        player->takeDamage(0.5);
}

void Game::collisionEnemyProjAndPlayer()
{
    for (int i = 0; i < enemyProjectileArray.size(); i++)
    {
        if (player->collide(*dynamic_cast<GameObject*>(enemyProjectileArray[i])))
        {
            player->takeDamage(enemyProjectileArray[i]->getDamage());
            deleteObjectFromVector(enemyProjectileArray, i);
            break;
        }
    }

}

void Game::collisionEnemyAndPlayer()
{
    for (int i = 0; i < enemyArr.size(); i++)
    {
        if (player->collide(*dynamic_cast<GameObject*>(enemyArr[i])))
        {
            //std::cout << "PLAYER COLIDED ENEMY" << std::endl;
            player->takeDamage(0.5);
            break;
        }
    }
}

void Game::collisionPowerUpAndPlayer()
{
    for (int i = 0; i < powerUpArr.size(); i++)
    {
        if (player->collide(*dynamic_cast<GameObject*>(powerUpArr[i])))
        {
            //std::cout << "PLAYER COLIDED POWERUP" << std::endl;
            // do not delete powerUp in GameLoop
            player->addPowerUp(dynamic_cast<PowerUp*>(powerUpArr[i]));
            tool->setPowerUp(
                dynamic_cast<PowerUp*>(powerUpArr[i])->getType(),
                dynamic_cast<PowerUp*>(powerUpArr[i])->getDuration()
            );
            std::swap(powerUpArr[i], powerUpArr.back());
            powerUpArr.pop_back();
            powerupSound.play();
            break;
        }
    }
}

void Game::enemyRandomShoot()
{
    for (int i = 0; i < enemyArr.size(); i++)
    {
        Projectile* newProjectile = dynamic_cast<Enemy*>(enemyArr[i])->shoot();
        if (newProjectile)
        {
            //std::cout << *newProjectile << std::endl;
            newProjectile->roateToDirection();
            enemyProjectileArray.push_back(newProjectile);
        }
    }
}
void Game::bossRandomShoot()
{
    int randShoot = rand() % 4;
    std::vector<Projectile*> newProjectile;
    // v1 = boss position + boss bottom middle posision
    const sf::Vector2f v1 =
        sf::Vector2f(boss->getBound().width / 2.0f, boss->getBound().height) +
        boss->getPosition();
    const static sf::Vector2f offset =
        sf::Vector2f(player->getBound().width / 2.0f, player->getBound().height / 2.0f);

    newProjectile = *boss->shoot(randShoot);
    for (auto& proj : newProjectile)
    {
        // vector with the direction to the player = player position - v1
        proj->setDirection(normalize(player->getPosition() - v1 + offset));
        proj->roateToDirection();
    }
    bossProjectileArray.insert(
        bossProjectileArray.end(),
        newProjectile.begin(),
        newProjectile.end()
    );
}

// return the first index of the newly added enemy in enemyArr
int Game::generateDiagonalEnemy(int n, sf::Vector2f initialPos, sf::Vector2f direction, float attribute)
{
    int startIndex = enemyArr.size();
    Enemy* newEnemy;
    for (int i = 0; i < n; i++) {
        enemyArr.push_back(new Enemy(
            SpaceTexture,
            enemyRectArr[rand() % 2],
            sf::Vector2f(
                initialPos.x + i * 20.f,
                initialPos.y + i * 26.f),
            attribute
        ));
    }
    return startIndex;
}

// return the first index of the newly added enemy in enemyArr
int Game::generateSquqreEnemy(int row, int col, sf::Vector2f initialPos, sf::Vector2f direction, float attribute)
{
    int startIndex = enemyArr.size();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            enemyArr.push_back(new Enemy(
                SpaceTexture,
                enemyRectArr[rand() % 2],
                sf::Vector2f(
                    initialPos.x + i * 40.f,
                    initialPos.y + j * 30.f),
                attribute
            ));
        }
    }
    return startIndex;
}

// given a side s, set initialPos and direction to corresponding value
void decideSide(Side s, sf::Vector2f& initialPos, sf::Vector2f& direction)
{
    int offset = 0;
    switch (s)
    {
    case Side::Top:
        offset = rand() % (PlayerMovingBound.x - 100);
        initialPos = sf::Vector2f(offset, -400);
        direction = sf::Vector2f(0, 1);
        break;
    case Side::Bottom:
        offset = rand() % (PlayerMovingBound.x - 100);
        initialPos = sf::Vector2f(offset, WindowHeight);
        direction = sf::Vector2f(0, -1);
        break;
    case Side::Left:
        offset = rand() % (PlayerMovingBound.y - 100);
        initialPos = sf::Vector2f(-400, offset);
        direction = sf::Vector2f(1, 0);
        break;
    case Side::Right:
        offset = rand() % (PlayerMovingBound.y - 100);
        initialPos = sf::Vector2f(WindowWidth, offset);
        direction = sf::Vector2f(-1, 0);
        break;
    }
}

/*
    Generate enemy in different layout
    each wave of enemy has a random attribute which determine their
    size, speed, damage, projectile size
*/
void Game::generateEnemy() {
    if (genEnemyClock.getElapsedTime().asMilliseconds() > 3000 - boss->getDifficulty() * 100)           // every 2 - difficulty * 0.015 seconds
    {
        sf::Vector2f initialPos; //where should the layout start
        sf::Vector2f direction; //they all move in the same direction
        int startIndex = 0;
        int layoutType = rand() % 3;
        Side s = static_cast<Side>(rand() % 4);
        decideSide(s, initialPos, direction);
        // 0.8 < x < 2.6
        float randAttribute = (rand() % 16) / 10.0f + 0.8f;
        int enemyNum, rows, cols;
        switch(layoutType)
        {
        case 0:
            enemyNum = 3 + rand() % 5;
            startIndex = generateDiagonalEnemy(enemyNum, initialPos, direction, randAttribute);
            break;
        case 1:
            rows = 1 + rand() % 4;
            cols = 1 + rand() % 4;
            startIndex = generateSquqreEnemy(abs(rows), abs(cols), initialPos, direction, randAttribute);
            break;
        case 2: // horizontal line of enemy
            enemyNum = 3 + rand() % 5;
            startIndex = generateSquqreEnemy(enemyNum, 1, initialPos, direction, randAttribute);
            break;
        }
        // set the enemy from first index to the last element
        for (int i = startIndex; i < enemyArr.size(); i++) {
            enemyArr[i]->setDirection(direction);
            std::cout << *enemyArr[i] << std::endl;
        }
        genEnemyClock.restart();
    }
}

Game::Game()
{
    srand(static_cast<unsigned int>(time(0)));
    // screens setup
    menu = new Menu(WindowWidth, WindowHeight);
    options = new Options(WindowWidth, WindowHeight);
    endscreen = new Endscreen(WindowWidth, WindowHeight);
    inputHighscore = new InputHighscore(WindowWidth, WindowHeight);

    // window setup
    window = new sf::RenderWindow(sf::VideoMode(WindowWidth, WindowHeight), GameTitle, sf::Style::Close | sf::Style::Resize);
    window->setFramerateLimit(FrameRateLimit);

    // sounds setup
    try { loadAllMusic(); }
    catch (const MusicNotLoaded & exception) { exit(-1); }

    backgroundMusic.play();
    backgroundMusic.setLoop(true);

    // base texture setup
    if (!SpaceTexture.loadFromFile(TextureBasePath + "spaceSprites.png"))
        throw TextureNotLoaded("spaceSprites.png");
    if (!BackgroundTexture.loadFromFile(TextureBasePath + "spaceBackground.png"))
        throw TextureNotLoaded("spaceBackground.png");
    if (!ToolBarBackgroundTexture.loadFromFile(TextureBasePath + "toolbar.png"))
        throw TextureNotLoaded("toolbar.png");

    GameBackground = sf::Sprite(BackgroundTexture);
    sf::Vector2u TextureSize = BackgroundTexture.getSize();
    sf::Vector2u WindowSize = window->getSize();
    float ScaleX = (float)WindowSize.x / TextureSize.x;
    float ScaleY = (float)WindowSize.y / TextureSize.y;
    GameBackground.setScale(ScaleX, ScaleY);

    // Player
    shipType = static_cast<ShipType>(rand() % 4);
    player = new Player(SpaceTexture, ShipTextureRect[(int)shipType], PlayerInitialPos, shipType);
    player->setMovingBoundary(PlayerMovingBound);
    player->getSprite().scale(sf::Vector2f(1, 1) * 1.5f);

    // ToolBar
    ToolBarBackground = sf::Sprite(ToolBarBackgroundTexture, sf::IntRect(0, 0, 204, 720));
    ToolBarBackground.setPosition(sf::Vector2f(1076, 0));
    tool = new ToolBar(sf::Vector2f(980, 0), ToolBarBackgroundTexture);
    tool->updateHpBarSize(player->getHp() / ShipMaxHp[(int)shipType]); //send percentage of health
    assert(tool);           // Make sure tool is not null


    enemyRectArr.push_back(EnemyRectEye);
    enemyRectArr.push_back(EnemyRectBlue);

    boss = new Boss(SpaceTexture, EnemyRectBoss, BossInitialPos);
    boss->setSpeed(1);
    // "disable" boss
    boss->getSprite().setColor(sf::Color::Color(125, 125, 125, 125));
    
    // Shield
    shieldSprite = sf::Sprite(SpaceTexture);
    shieldSprite.setTextureRect(ShieldRect);
    setSpriteOriginCenter(shieldSprite);
    shieldSprite.setScale(1.4f, 1.4f);

    bossSignSprite = sf::Sprite(ToolBarBackgroundTexture, sf::IntRect(0, 720, 204, 64));
    bossSignSprite.setPosition(sf::Vector2f(1076.f, 581.0f));
    restartClocks();
}


void Game::handleKeyInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player->move(sf::Vector2f(-ShipSpeed[(int)shipType], 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player->move(sf::Vector2f(ShipSpeed[(int)shipType], 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        player->move(sf::Vector2f(0.0f, -ShipSpeed[(int)shipType]));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        player->move(sf::Vector2f(0.0f, ShipSpeed[(int)shipType]));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Projectile* newProjectile = player->shoot();
        if (newProjectile) {
            playerProjectileArray.push_back(newProjectile);
            laserSound.play();
        }
    }
}

void Game::handleBackdoorKeyInput(sf::Keyboard::Key code)
{
    switch (code)
    {
    case InfinityHpKey:
        InfinityHpTriggered = !InfinityHpTriggered;
        break;
    case AccelerateKey:
        player->accelerate(5);
        break;
    case DeaccelerateKey:
        player->deaccelerate(5);
        break;
    case BiggerProjectile:
        BiggerProjTriggered = !BiggerProjTriggered;
        if (BiggerProjTriggered)
        {
            player->setBackdoorProjScale(5.0f);
            player->setProjDamage(15.0f);
        }
        else
        {
            player->setBackdoorProjScale(1.0f);
            player->setProjDamage(PlayerProjectileDamage);
        }
        break;
    case ChangeShipTypeBlue:
        player->changeType(ShipType::BlueShip);
        shipType = ShipType::BlueShip;
        break;
    case ChangeShipTypeRed:
        player->changeType(ShipType::RedShip);
        shipType = ShipType::RedShip;
        break;
    case ChangeShipTypeGreen:
        player->changeType(ShipType::GreenShip);
        shipType = ShipType::GreenShip;
        break;
    case ChangeShipTypeBee:
        player->changeType(ShipType::BeeShip);
        shipType = ShipType::BeeShip;
        break;
    }
}

void Game::generatePowerUp()
{
    int numberOfPowerUpTypes = 2;
    if (genPowerUpClock.getElapsedTime().asSeconds() > 8)
    {
        PowerUpType randomPowerUpType = static_cast<PowerUpType>(rand() % numberOfPowerUpTypes);
        float randX = rand() % (1076 - 30);
        float randY = -50;
        genPowerUpClock.restart();
        switch (randomPowerUpType)
        {
        case PowerUpType::HEAL:
            powerUpArr.push_back(new HealthRestore(SpaceTexture, sf::Vector2f(randX, randY)));
            break;
        case PowerUpType::SHIELD:
            powerUpArr.push_back(new Shield(SpaceTexture, sf::Vector2f(randX, randY)));
            break;
        default:
            break;
        }
        // set the direction and speed of the newly added powerup
        powerUpArr.back()->setDirection(sf::Vector2f(0, 1));
        powerUpArr.back()->setSpeed(3);
    }
}


void Game::updateBoss(BossStates state = BossStates::Stay, sf::Vector2f destination = sf::Vector2f(0, 0))
{
    if (boss->isDead())
    {
        tool->addScore(BossScore * boss->getDifficulty());
        boss->getSprite().setColor(sf::Color::Color(125, 125, 125, 125));
        boss->increaseDifficulty(0.2);
        ShowBoss = false;
        genBossClock.restart();
    }
    else
    {
        bossRandomShoot();
        collisionPlayerProjAndBoss();
    }
    switch (state)
    {
    case BossStates::MoveLeft:
        boss->setDirection(DirectionMap.at(Direction::LeftDirection));
        boss->move();
        break;
    case BossStates::MoveRight:
        boss->setDirection(DirectionMap.at(Direction::RightDirection));
        boss->move();
        break;
    case BossStates::MoveDown:
        boss->setDirection(DirectionMap.at(Direction::DownDirection));
        boss->move();
        break;
    case BossStates::MoveUp:
        boss->setDirection(DirectionMap.at(Direction::UpDirection));
        boss->move();
        break;
    case BossStates::MoveTo:        // does not work
        boss->moveTo(destination);
        break;
    case BossStates::Stay:
        boss->setDirection(sf::Vector2f(0, 0));
        break;
    }

}

void Game::updateGame()
{
    collisionPlayerProjAndEnemy();
    if (player->hasPowerUp(PowerUpType::SHIELD))
    {
        collisionEnemyProjAndShield();
        collisionBossProjAndShield();
    }
    else
    {
        collisionEnemyProjAndPlayer();
        collisionEnemyAndPlayer();
        if (ShowBoss)
            collisionPlayerAndBoss();
    }
    collisionPowerUpAndPlayer();
    updateGameObjectArray(enemyProjectileArray);
    updateGameObjectArray(playerProjectileArray);
    updateGameObjectArray(enemyArr);
    updateGameObjectArray(powerUpArr);
    generateEnemy();
    generatePowerUp();
    // check all powerup 
    // remove from activePowerUp set 
    // if it passes the duration
    enemyRandomShoot();

    if (!ShowBoss && static_cast<int>(genBossClock.getElapsedTime().asSeconds() + 1) % BossReviveInterval == 0)
        resetBoss();
    if (ShowBoss)
    {
        // change direction when hit 200 or 800
        if (boss->getPosition().x <= 200 || boss->getPosition().x >= 800)
        {
            if (bossMoveDir == BossStates::MoveRight)
                bossMoveDir = BossStates::MoveLeft;
            else if (bossMoveDir == BossStates::MoveLeft)
                bossMoveDir = BossStates::MoveRight;
        }
        updateBoss(bossMoveDir);
    }
    collisionBossProjAndPlayer();

    // only RedSharp will follow the player
    for (auto& proj : bossProjectileArray)
        if (proj->getType() == ProjectileType::RedSharp) proj->moveToward(*player);
    updateGameObjectArray(bossProjectileArray);

    if (InfinityHpTriggered)
        player->setHp(PlanetDefenders::ShipMaxHp[(int)shipType]);
    player->removeAllEndedPowerUp();

    tool->update();
    tool->updateHpBarSize(player->getHp() / ShipMaxHp[(int)shipType]);
    boss->updateBossHpBarSize();
}

void Game::drawGame() {
    window->draw(GameBackground);
    window->draw(player->getSprite());
    drawGameObjectArray(enemyProjectileArray);
    drawGameObjectArray(playerProjectileArray);
    drawGameObjectArray(enemyArr);
    drawGameObjectArray(powerUpArr);
    drawGameObjectArray(bossProjectileArray);
    if (player->hasPowerUp(PowerUpType::SHIELD))
    {
        shieldSprite.setPosition(
            player->getPosition() +
            sf::Vector2f(player->getBound().width / 2, player->getBound().height / 2)
        );
        window->draw(shieldSprite);
    }
    window->draw(ToolBarBackground);
    tool->drawTo(*window);
    if (ShowBoss)
        window->draw(bossSignSprite);
    boss->drawTo(*window);
    window->display();
}

Game::~Game() {
    delete window;
    delete player;
    delete tool;
    delete boss;
    delete options;
    delete endscreen;
    delete inputHighscore;
    playerProjectileArray.clear();
    enemyProjectileArray.clear();
    enemyArr.clear();
    playerProjectileArray.clear();
    powerUpArr.clear();
    bossProjectileArray.clear();
}

void Game::restartClocks()
{
    genPowerUpClock.restart();
    genEnemyClock.restart();
    genBossClock.restart();
    bossMoveClock.restart();
    gameClock.restart();
}

void Game::resetBoss()
{
    ShowBoss = true;
    boss->getSprite().setColor(sf::Color::White);
    boss->resetHp();
}

void Game::resetGame()
{
    backgroundMusic.stop();
    backgroundMusic.play();
    enemyProjectileArray.clear();
    enemyArr.clear();
    powerUpArr.clear();
    bossProjectileArray.clear();
    playerProjectileArray.clear();

    tool->minusScore(tool->getScore());
    tool->restartClock();
    restartClocks();
    
    shipType = static_cast<ShipType>(rand() % 4);
    player->changeType(shipType);
    player->getSprite().setPosition(PlayerInitialPos);
    boss->setDifficulty(1);
    boss->resetHp();
    boss->getSprite().setColor(sf::Color::Color(125, 125, 125, 125));
    boss->getSprite().setPosition(BossInitialPos);
    ShowBoss = false;
    BackdoorTriggered = false;
}

void Game::gameLoop() {
    srand(static_cast<unsigned>(time(0)));
    sf::Event e;
    backgroundMusic.setBuffer(titleThemeBuffer);
    backgroundMusic.setVolume(69);
    backgroundMusic.play();
    // display menu
    while (!displayMenu()) { sf::sleep(sf::milliseconds(10)); }
    resetGame();
    backgroundMusic.setBuffer(backgroundBuffer);
    backgroundMusic.play();
    // main game loop
    while (window->isOpen())
    {
        while (window->pollEvent(e))
        {
            switch (e.type)
            {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyReleased:
                if (e.key.code == sf::Keyboard::Key::Escape)
                {
                    GAME_PAUSED ^= 1;
                    pauseGame();
                }
                if (e.key.code == BackdoorTriggerKey)
                {
                    BackdoorTriggered = !BackdoorTriggered;
                    if (!BackdoorTriggered)
                    {
                        InfinityHpTriggered = false;
                        BiggerProjTriggered = false;
                        player->setBackdoorProjScale(1.0f);
                        player->setProjDamage(PlayerProjectileDamage);
                        player->setSpeed(PlayerInitialSpeed);
                        std::cout << "BACKDOOR OFF" << std::endl;
                    }
                    else
                    {
                        std::cout << "BACKDOOR ON" << std::endl;
                    }
                }
                if (BackdoorTriggered)
                    handleBackdoorKeyInput(e.key.code);
                break;
            }
        }
        if (!GAME_PAUSED)
        {
            window->clear();
            handleKeyInput();
            updateGame();
            drawGame();
        }
        else
        {
            // prevent drawing TOO MUCH CPU power while pause
            sf::sleep(sf::milliseconds(10));
        }
        // show high score if checkScore is true
        if (player->isDead())
        {
            do {
                if (CheckScore::checkScore(tool->getScore()) == true)
                    inputHighscore->work(*window, *inputHighscore, GameBackground, backgroundMusic, tool->getScore());
            } while (!endscreen->work(*window, *endscreen, GameBackground, backgroundMusic));
            // leave the game
            if (window->isOpen() == false) break;
            backgroundMusic.setBuffer(titleThemeBuffer);
            backgroundMusic.play();
            // draw menu again
            while (!displayMenu()) { sf::sleep(sf::milliseconds(5)); }
            // reset everything in the game
            resetGame();
            backgroundMusic.setBuffer(backgroundBuffer);
            backgroundMusic.play();
        }
    }
}
