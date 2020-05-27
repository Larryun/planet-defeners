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
    // sounds setup
    loadAllMusic();
    backgroundMusic.play();
    backgroundMusic.setVolume(20.0f);

    // texture setup
    SPACE_TEXTURE.loadFromFile(TEXTURE_BASE_PATH + "spaceSprites.png");
    BACKGROUND_TEXTURE.loadFromFile(TEXTURE_BASE_PATH + "spaceBackground.png");
    background = sf::Sprite(BACKGROUND_TEXTURE);
    background.setScale(1.3, 1.3);

    // window setup
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE, sf::Style::Close | sf::Style::Resize);
    window->setFramerateLimit(FRAME_RATE_LIMIT);
    //BACKGROUND_TEXTURE.loadFromFile(TEXTURE_BASE_PATH + "menuIdea.png");
    tool = new ToolBar(BACKGROUND_TEXTURE, sf::IntRect(0, 0, 300, 720), sf::Vector2f(980, 0));
    assert(tool);
    //if (tool == nullptr)
    //    std::cout << "null" << std::endl;
    tool->setTextObject();
    tool->setSprites();
    tool->setHpBar(hp, sf::Color::Red, sf::Vector2f(20.f, (float)hp * 20.f), sf::Vector2f(528.f, 150.f));

    // play backgound music
    // set the boundary of player
    player = new Player(SPACE_TEXTURE, SHIP_1_TEXTURE_RECT, sf::Vector2f(100, 100));
    
    // set moving bound so that it wont go over to ToolBar
    player->setMovingBoundary(sf::Vector2u(980, 720));
    player->getSprite().scale(sf::Vector2f(1, 1) * 1.5f);

    // demo
    // build enemies array
    initEnemy(window->getSize());
    // demo: scaling the player sprite

    clock = new sf::Clock();


    // for test
    healPower = new HealthRestore(
        SPACE_TEXTURE,
        HEALTH_RESTORE_RECT,
        sf::Vector2f(500, 200),
        HEAL
    );

    shield = new Shield(
        SPACE_TEXTURE,
        SHIELD_POWERUP_RECT,
        sf::Vector2f(500, 400),
        SHIELD
    );
    powerUpArr.push_back(healPower);
    powerUpArr.push_back(shield);

    shieldSprite = sf::Sprite(SPACE_TEXTURE);
    shieldSprite.setTextureRect(SHIELD_RECT);
    shieldSprite.setScale(1.5, 1.5);

}

Game::~Game() {
    delete clock;
    delete window;
    delete player;
    delete tool;
    for (int i = 0; i < projectileArray.size(); i++)
    {
        deleteObjectFromVector(projectileArray, i);
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


void Game::shoot()
{
    sf::Time elapse_time = clock->getElapsedTime();
    if (elapse_time >= PROJECTILE_TIME_DELTA)
    {
        projectileArray.push_back(
            new Projectile(
                SPACE_TEXTURE,
                PROJECTILE_RECT,
                // x-axis offset by: 2.0f
                player->getSprite().getPosition() + sf::Vector2f((player->getBound().width / 2.0f) - 2.0f, 0.0f)
            )
        );
        clock->restart();
        laserSound.play();
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
        shoot();
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
    for (int i = 0; i < projectileArray.size(); i++)
    {
        for (int j = 0; j < enemyArr.size(); j++)
        {
            if (checkCollision(projectileArray[i], enemyArr[j]))
            {
                enemyHurtSound.play();
                deleteObjectFromVector(projectileArray, i);
                deleteObjectFromVector(enemyArr, j);
                std::cout << "PROJECTILE COLIDED ENEMY" << std::endl;
                break;
            }
        }
    }
    // Check colliision between enemy and player
    for (int i = 0; i < enemyArr.size(); i++)
    {
        if (checkCollision(player, enemyArr[i]))
        {
            std::cout << "PLAYER COLIDED ENEMY" << std::endl;
            std::cout << hp << std::endl;
            player->takeDamage(1);
            //hp--; // hp update
        }
    }

    for (int i = 0; i < powerUpArr.size(); i++)
    {
        if (checkCollision(player, powerUpArr[i]))
        {
            std::cout << "PLAYER COLIDED POWERUP" << std::endl;
            // do not delete powerUp in GameLoop
            player->addPowerUp(dynamic_cast<PowerUp*>(powerUpArr[i]));
            powerUpArr.pop_back();
            break;
        }
    }


    window->draw(background);
    tool->updateTime();
    tool->updateScore(count);
    tool->updateHpBarSize(player->getHp());
    window->draw(tool->getSprite());
    tool->drawTo(*window);

    updateGameObjectArray(projectileArray);
    updateGameObjectArray(enemyArr);

    drawGameObjectArray(projectileArray);
    drawGameObjectArray(enemyArr);
    drawGameObjectArray(powerUpArr);
    window->draw(player->getSprite());

    // draw shield if player has SHIELD power up
    if (player->hasPowerUp(SHIELD))
    {
        shieldSprite.setPosition(
            player->getSprite().getPosition() +
            sf::Vector2f(
                -14, -7
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
        }

    }
}
