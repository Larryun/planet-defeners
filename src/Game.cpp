#include <iostream>
#include <cassert>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collision.h"
#include "Game.h"
#include "Player.h"
#include "Projectile.h"
#include "ToolBar.hpp"
#include "HealthRestore.h"
#include "Shield.h"
#include "Menu.h"
#include "Options.h"
#include "TextureNotLoaded.h"


using namespace PlanetDefenders;


void Game::loadAllMusic()
{
    // add exception handling here
    if (!backgroundBuffer.loadFromFile(AUDIO_BASE_PATH + "game_music.ogg"))
        std::cout << "Music not loaded" << std::endl;
    else
        backgroundMusic.setBuffer(backgroundBuffer);
    if (!laserSoundBuffer.loadFromFile(AUDIO_BASE_PATH + "laser.ogg"))
        std::cout << "LaserSound not loaded" << std::endl;
    else
        laserSound.setBuffer(laserSoundBuffer);

    if (!powerupSoundBuffer.loadFromFile(AUDIO_BASE_PATH + "enemy_hurt.ogg"))
        std::cout << "enemy_hurt not loaded" << std::endl;
    else
        enemyHurtSound.setBuffer(powerupSoundBuffer);

    if (!enemyHurtSoundBuffer.loadFromFile(AUDIO_BASE_PATH + "powerup.ogg"))
        std::cout << "powerup not loaded" << std::endl;
    else
        powerupSound.setBuffer(enemyHurtSoundBuffer);
}

void Game::pauseGame()
{
    if (GAME_PAUSED)
        backgroundMusic.pause();
    else
        backgroundMusic.play();
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
            std::cout << "PLAY";
            return true;
        }
        else if (menu->inXOptions(event, *window)) {
            std::cout << "Options";
            // to options view
            options->work(*window, event, *options, GameBackground, backgroundMusic);
        }
        else if (menu->inXExit(event, *window)) {
            std::cout << "Exit";
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
        window->draw(GameBackground);
        menu->draw(*window);
    }
    return false;
}


void Game::collisionPlayerProjAndEnemy()
{
    // Collision between playerProjectile and enemy
    for (int i = 0; i < playerProjectileArray.size(); i++)
    {
        for (int j = 0; j < enemyArr.size(); j++)
        {
            if (checkCollision(playerProjectileArray[i], enemyArr[j]))
            {
                tool->addScore(1);
                enemyHurtSound.play();
                deleteObjectFromVector(playerProjectileArray, i);
                deleteObjectFromVector(enemyArr, j);
                std::cout << "PROJECTILE COLIDED ENEMY" << std::endl;
                break;
            }
        }
    }
}

void Game::collisionPlayerAndShield()
{
    // Collision between enemyProjectile and player shield
    for (int i = 0; i < enemyProjectileArray.size(); i++)
    {
        if (checkCollision(&enemyProjectileArray[i]->getSprite(), &shieldSprite))
        {
            player->takeDamage(1);
            tool->updateHpBarSize(player->getHp());
            deleteObjectFromVector(enemyProjectileArray, i);
            break;
        }
    }
}

void Game::collisionEnemyProjAndPlayer()
{
    for (int i = 0; i < enemyProjectileArray.size(); i++)
    {
        if (checkCollision(enemyProjectileArray[i], player))
        {
            player->takeDamage(1);
            tool->updateHpBarSize(player->getHp());
            deleteObjectFromVector(enemyProjectileArray, i);
            break;
        }
    }

}


void Game::collisionEnemyAndPlayer()
{
    for (int i = 0; i < enemyArr.size(); i++)
    {
        if (checkCollision(player, enemyArr[i]))
        {
            std::cout << "PLAYER COLIDED ENEMY" << std::endl;
            player->takeDamage(1);
            tool->updateHpBarSize(player->getHp());
            break;
        }
    }

}

void Game::collisionPowerUpAndPlayer()
{
    for (int i = 0; i < powerUpArr.size(); i++)
    {
        if (checkCollision(player, powerUpArr[i]))
        {
            std::cout << "PLAYER COLIDED POWERUP" << std::endl;
            // do not delete powerUp in GameLoop
            player->addPowerUp(dynamic_cast<PowerUp*>(powerUpArr[i]));
            tool->setPowerUp(
                dynamic_cast<PowerUp*>(powerUpArr[i])->getType(),
                dynamic_cast<PowerUp*>(powerUpArr[i])->getDuration()
            );
            std::swap(powerUpArr[i], powerUpArr.back());
            powerUpArr.pop_back();
            tool->updateHpBarSize(player->getHp());
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
            newProjectile->roateToDirection();
            enemyProjectileArray.push_back(newProjectile);
        }
    }

}

void Game::bossRandomShoot()
{
    //int randShoot = random() % 4;
    int randShoot = 0;
    std::vector<Projectile*> newProjectile;
    const static sf::Vector2f offset = 
        sf::Vector2f(boss->getBound().width/2.0f - 10, boss->getBound().height - 10 ) + 
        boss->getPosition();
    switch (randShoot) {
    case 0:
        for (int i = 0; i < 4; i++) {
            newProjectile = *boss->shoot(i);
            for (auto it = newProjectile.begin(); it != newProjectile.end(); it++)
            {
                (*it)->setDirection(normalize(player->getPosition() - offset));
                (*it)->roateToDirection();
            }
            bossProjectileArray.insert(
                bossProjectileArray.end(),
                newProjectile.begin(),
                newProjectile.end()
            );
        }
        break;
    default:
        break;
    }
}

//void Game::generateDiagonalEnemy(int n, sf::Vector2f initialPos, sf::Vector2f direction) {
int Game::generateDiagonalEnemy(int n, sf::Vector2f initialPos, sf::Vector2f direction) {
    int startIndex = enemyArr.size();
    for (int i = 0; i < n; i++) {
        enemyArr.push_back(new Enemy(
            SPACE_TEXTURE,
            enemyRectArr[rand() % 2],
            sf::Vector2f(
                initialPos.x + i * direction.x * 20.f,
                initialPos.y + i * direction.y * 26.f)
        ));
    }
    return startIndex;
}

int Game::generateSquqreEnemy(int row, int col, sf::Vector2f initialPos, sf::Vector2f direction) {
    int startIndex = enemyArr.size();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            enemyArr.push_back(new Enemy(
                SPACE_TEXTURE,
                enemyRectArr[rand() % 2],
                sf::Vector2f(
                    initialPos.x + i * 40.f,
                    initialPos.y + j * 30.f)
            ));
        }
    }
    return startIndex;
}

void Game::generateEnemy() {
    int time = genEnemyClock.getElapsedTime().asSeconds();
    randomEnemy = 1 + rand() % 5;
    //initialPos = sf::Vector2f(rand() % 900, -100);
    initialPos = sf::Vector2f(-100, 200);
    float randX = rand() % 8 - 4;
    float randY = rand() % 8 - 4;
    direction = sf::Vector2f(randX, randY);
    int randNum = 1 + rand() % 4;
    int startIndex = 0;
    if (time > 2)           // every 2 seconds
    {
        if (tool->getTime().getElapsedTime().asSeconds() < 30)
            startIndex = generateDiagonalEnemy(randomEnemy, initialPos, direction);
        else {
            if (randNum % 2 == 0)
                startIndex = generateDiagonalEnemy(randomEnemy, initialPos, direction);
            else
                startIndex = generateSquqreEnemy(abs(randX), abs(randY), initialPos, direction);
        }
        genEnemyClock.restart();
        for (int i = startIndex; i < enemyArr.size(); i++) {
            enemyArr[i]->setDirection(sf::Vector2f(1, 0));
            enemyArr[i]->setSpeed(randNum);
            //std::cout << speed << std::endl;
            //if(enemyArr[i]->getPosition().x > window->Window::getSize().x - tool->getSize().x || enemyArr[i]->getPosition().y > window->Window::getSize().y)
            //    enemyArr.erase(enemyArr.begin() + i);
        }
    }
}

Game::Game()
{
    menu = new Menu(WINDOW_WIDTH, WINDOW_HEIGHT);
    options = new Options(WINDOW_WIDTH, WINDOW_HEIGHT);

    // window setup
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE, sf::Style::Close | sf::Style::Resize);
    //std::cout << window->getSize().x << " " << window->getSize().y << std::endl;
    window->setFramerateLimit(FRAME_RATE_LIMIT);

    // sounds setup
    loadAllMusic();
    backgroundMusic.play();
    backgroundMusic.setVolume(20.0f);

    // base texture setup
    if (!SPACE_TEXTURE.loadFromFile(TEXTURE_BASE_PATH + "spaceSprites.png"))
        throw TextureNotLoaded("spaceSprites.png");
    if (!BackgroundTexture.loadFromFile(TEXTURE_BASE_PATH + "spaceBackground.png"))
        throw TextureNotLoaded("spaceBackground.png");

    GameBackground = sf::Sprite(BackgroundTexture);
    GameBackground.setScale(1.3, 1.3);

    // ToolBar
    if (!ToolBarBackgroundTexture.loadFromFile(TEXTURE_BASE_PATH + "toolbar.png"))
        throw TextureNotLoaded("toolbar.png");
    ToolBarBackground = sf::Sprite(ToolBarBackgroundTexture, sf::IntRect(0, 0, 204, 720));
    ToolBarBackground.setPosition(sf::Vector2f(1076, 0));
    tool = new ToolBar(sf::Vector2f(980, 0));
    assert(tool);           // Make sure tool is not null

    player = new Player(SPACE_TEXTURE, SHIP_1_TEXTURE_RECT, sf::Vector2f(100, 100));
    player->setMovingBoundary(sf::Vector2u(1076, 720));      // set moving bound so that it wont go over to ToolBar
    player->getSprite().scale(sf::Vector2f(1, 1) * 1.5f);

    // demo
    // build enemies array
    //initEnemy(window->getSize());

    enemyRectArr.push_back(ENEMY_RECTEYE);
    enemyRectArr.push_back(ENEMY_RECTBLUE);

    boss = new Boss(SPACE_TEXTURE, ENEMY_RECTBOSS, sf::Vector2f((window->getSize().x - tool->getSize().x) / 2, 0));

    shieldSprite = sf::Sprite(SPACE_TEXTURE);
    shieldSprite.setTextureRect(sf::IntRect(134, 0, 45, 45));
    shieldSprite.setScale(1.4, 1.4);

    bossSprite = sf::Sprite(ToolBarBackgroundTexture, sf::IntRect(0, 720, 204, 64));
    bossSprite.setPosition(sf::Vector2f(1076.f, 581.0f));


}


void Game::handleKeyInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player->move(sf::Vector2f(-0.5f, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player->move(sf::Vector2f(0.5f, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        player->move(sf::Vector2f(0.0f, -0.5f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        player->move(sf::Vector2f(0.0f, 0.5f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        // demo
        // press R the accerlerate
        player->accelerate(1.1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Projectile* newProjectile = player->shoot();
        if (newProjectile)
            playerProjectileArray.push_back(newProjectile);
        laserSound.play();
    }
}

void Game::generatePowerUp()
{
    int numberOfPowerUpTypes = 2;
    if (genPowerUpClock.getElapsedTime().asSeconds() > 2)
    {
        PowerUpEnum randomPowerUpType = static_cast<PowerUpEnum>(rand() % numberOfPowerUpTypes);
        float randX = rand() % (1076 - 30);
        float randY = -50;
        genPowerUpClock.restart();
        switch (randomPowerUpType)
        {
        case HEAL:
            powerUpArr.push_back(new HealthRestore(SPACE_TEXTURE, sf::Vector2f(randX, randY)));
            break;
        case SHIELD:
            powerUpArr.push_back(new Shield(SPACE_TEXTURE, sf::Vector2f(randX, randY)));
            break;
        default:
            break;
        }
        // set the direction and speed of the newly added powerup
        powerUpArr.back()->setDirection(sf::Vector2f(0, 1));
        powerUpArr.back()->setSpeed(7);
    }
}

// hmm...
template<class T>
void Game::updateGameObjectArray(std::vector<T*>& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        arr[i]->move();
    }
}

// hmm...
template<class T>
void Game::drawGameObjectArray(std::vector<T*>& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (isOutOfBound(arr[i]) == false)
        {
            window->draw(arr[i]->getSprite());
        }
        else
        {
            deleteObjectFromVector(arr, i);
        }
    }
}

void Game::updateGame()
{
    collisionPlayerProjAndEnemy();

    if (player->hasPowerUp(SHIELD))
    {
        collisionPlayerAndShield();
    }

    collisionEnemyProjAndPlayer();
    collisionEnemyAndPlayer();
    collisionPowerUpAndPlayer();
    enemyRandomShoot();

    tool->update();
    updateGameObjectArray(enemyProjectileArray);
    updateGameObjectArray(playerProjectileArray);
    //if(tool->getScore() == 0){
    //    updateGameObjectArray(enemyArr);
    //    generateEnemy();
    //}
    updateGameObjectArray(enemyArr);
    generateEnemy();
    updateGameObjectArray(powerUpArr);
    generatePowerUp();
    // check all powerup 
    // remove from activePowerUp set 
    // if it passes the duration
    player->removeAllEndedPowerUp();

    updateGameObjectArray(bossProjectileArray);
    if (tool->getScore() == 0) {
        bossRandomShoot();
        //for (int i = 0; i < bossProjectileArray.size(); i++) {
        //    bossProjectileArray[i]->setDirection(sf::Vector2f(0, 1));
        //    bossProjectileArray[i]->setSpeed(7);
        //    bossProjectileArray[i]->move();
        //    window->draw(bossProjectileArray[i]->getSprite());
        //}
    }
}

void Game::drawGame() {
    window->draw(GameBackground);
    window->draw(player->getSprite());
    drawGameObjectArray(enemyProjectileArray);
    drawGameObjectArray(playerProjectileArray);
    drawGameObjectArray(enemyArr);
    drawGameObjectArray(powerUpArr);
    drawGameObjectArray(bossProjectileArray);
    // Demo, put to a function later
    // draw shield if player has SHIELD power up
    if (player->hasPowerUp(SHIELD))
    {
        shieldSprite.setPosition(
            player->getSprite().getPosition() +
            sf::Vector2f(
                -9, -7         // offset
            )
        );
        window->draw(shieldSprite);
    }

    window->draw(boss->getSprite());
    window->draw(ToolBarBackground);
    tool->drawTo(*window);
    window->draw(bossSprite);
    window->display();
}

Game::~Game() {
    delete window;
    delete player;
    delete tool;
    for (int i = 0; i < playerProjectileArray.size(); i++)
    {
        deleteObjectFromVector(playerProjectileArray, i);
    }
    for (int i = 0; i < enemyArr.size(); i++)
    {
        deleteObjectFromVector(enemyArr, i);
    }
    for (int i = 0; i < enemyArr.size(); i++)
    {
        deleteObjectFromVector(powerUpArr, i);
    }
}

void Game::gameLoop() {
    srand(time(0));
    // display menu
    while (!displayMenu()) {}
    // main game loop
    while (window->isOpen())
    {
        sf::Event e;
        while (window->pollEvent(e))
        {
            switch (e.type)
            {
            case sf::Event::Closed:
                window->close();
            case sf::Event::KeyReleased:
                if (e.key.code == sf::Keyboard::Key::Escape)
                {
                    GAME_PAUSED ^= 1;
                    pauseGame();
                }
            }
        }

        if (!GAME_PAUSED)
        {
            handleKeyInput();
            window->clear();
            updateGame();
            drawGame();
        }
        else
        {
            // prevent drawing TOO MUCH CPU power while pause
            sf::sleep(sf::milliseconds(100));
        }
    }
}
