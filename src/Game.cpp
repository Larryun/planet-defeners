#include <iostream>
#include <cassert>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collision.h"
#include "Game.h"
#include "Player.h"
#include "Projectile.h"
#include "ToolBar.hpp"
#include "HealthRestore.h"
#include "Shield.h"

using namespace PlanetDefenders;


void Game::loadAllMusic()
{
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
            enemyProjectileArray.push_back(newProjectile);
        }
    }

}


void Game::initEnemy(const sf::Vector2u windowSize, unsigned int row = 3, unsigned int col = 12)
{
    sf::Vector2f offset(50.0, 50.0);
    float paddingRight = 30;
    float paddingLeft = 15;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            Enemy* newE = new Enemy(
                SPACE_TEXTURE,
                ENEMY_RECT,
                sf::Vector2f(
                    static_cast<float>((50 + paddingRight) * j),
                    static_cast<float>((50 + paddingLeft) * i)
                ) + offset
            );
            newE->getSprite().scale(sf::Vector2f(1.4f, 1.4f));
            enemyArr.push_back(newE);
        }
    }
}


Game::Game()
{
    // window setup
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE, sf::Style::Close | sf::Style::Resize);
    window->setFramerateLimit(FRAME_RATE_LIMIT);

    // sounds setup
    loadAllMusic();
    backgroundMusic.play();
    backgroundMusic.setVolume(20.0f);

    // base texture setup
    SPACE_TEXTURE.loadFromFile(TEXTURE_BASE_PATH + "spaceSprites.png");
    BackgroundTexture.loadFromFile(TEXTURE_BASE_PATH + "spaceBackground.png");

    GameBackground = sf::Sprite(BackgroundTexture);
    GameBackground.setScale(1.3, 1.3);

    // ToolBar
    ToolBarBackgroundTexture.loadFromFile(TEXTURE_BASE_PATH + "toolbar.png");
    ToolBarBackground = sf::Sprite(ToolBarBackgroundTexture, sf::IntRect(0, 0, 204, 720));
    ToolBarBackground.setPosition(sf::Vector2f(1076, 0));
    tool = new ToolBar(sf::Vector2f(980, 0));
    assert(tool);           // Make sure tool is not null

    player = new Player(SPACE_TEXTURE, SHIP_1_TEXTURE_RECT, sf::Vector2f(100, 100));
    player->setMovingBoundary(sf::Vector2u(1076, 720));      // set moving bound so that it wont go over to ToolBar
    player->getSprite().scale(sf::Vector2f(1, 1) * 1.5f);

    // demo
    // build enemies array
    initEnemy(window->getSize());

    shieldSprite = sf::Sprite(SPACE_TEXTURE);
    shieldSprite.setTextureRect(sf::IntRect(134, 0, 45, 45));
    shieldSprite.setScale(1.4, 1.4);
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

void Game::updateGameObjectArray(std::vector<GameObject*>& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        arr[i]->move();
    }
}

void Game::drawGameObjectArray(std::vector<GameObject*>& arr)
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
    updateGameObjectArray(enemyArr);
    updateGameObjectArray(powerUpArr);
    generatePowerUp();
}

void Game::drawGame() {
    window->draw(GameBackground);
    window->draw(ToolBarBackground);
    tool->drawTo(*window);
    window->draw(player->getSprite());
    drawGameObjectArray(enemyProjectileArray);
    drawGameObjectArray(playerProjectileArray);
    drawGameObjectArray(enemyArr);
    drawGameObjectArray(powerUpArr);

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

    // check all powerup 
    // remove from activePowerUp set 
    // if it passes the duration
    player->removeAllEndedPowerUp();
    window->display();
}


void Game::gameLoop() {

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
