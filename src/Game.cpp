#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collision.h"
#include "Game.h"
#include "Player.h"
#include "Projectile.h"
#include "ToolBar.hpp"

template <class T>
void deleteObjectFromVector(std::vector<T*>&, int);
bool checkCollision(GameObject*, GameObject*);


template <class T>
void deleteObjectFromVector(std::vector<T*>& v, int i)
{
    std::swap(v[i], v.back());
    delete v.back();
    v.pop_back();
}


// A wrapper function
bool checkCollision(GameObject* obj1, GameObject* obj2)
{
    return Collision::PixelPerfectTest(obj1->getSprite(), obj2->getSprite());
}

bool Game::isOutOfBound(GameObject* obj1)
{
    return obj1->getSprite().getPosition().x < -100 ||
        obj1->getSprite().getPosition().x > window->getSize().x + 100 ||
        obj1->getSprite().getPosition().y > window->getSize().y + 100 ||
        obj1->getSprite().getPosition().y < -100;
}

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


Game::Game()
{
    loadAllMusic();
    background = sf::Sprite(BACKGROUND_TEXTURE);
    backgroundMusic.play();
    backgroundMusic.setVolume(20.0f);
    SPACE_TEXTURE.loadFromFile(TEXTURE_BASE_PATH + "spaceSprites.png");
    BACKGROUND_TEXTURE.loadFromFile(TEXTURE_BASE_PATH + "spaceBackground.png");
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE, sf::Style::Close | sf::Style::Resize);
    player = new Player(SPACE_TEXTURE, SHIP_1_TEXTURE_RECT, sf::Vector2f(100, 100));
    clock = new sf::Clock();
    BACKGROUND_TEXTURE.loadFromFile(TEXTURE_BASE_PATH + "menuIdea.png");
    tool = new ToolBar(BACKGROUND_TEXTURE, sf::IntRect(0, 0, 300, 720), sf::Vector2f(980, 0));
    if (tool == nullptr)
        std::cout << "null" << std::endl;
    tool->setTextObject();
    tool->setSprites();
    tool->setHpBar(hp, sf::Color::Red, sf::Vector2f(20.f, (float)hp * 20.f), sf::Vector2f(528.f, 150.f));
    init();
}

Game::~Game() {
    delete clock;
    delete window;
    for (int i = 0; i < projectileArray.size(); i++)
    {
        deleteObjectFromVector(projectileArray, i);
    }
    for (int i = 0; i < enemyArr.size(); i++)
    {
        deleteObjectFromVector(enemyArr, i);
    }
    delete player;
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

void Game::init()
{
    // play backgound music
    // set the boundary of player
    player->setMovingBoundary(window->getSize());
    window->setFramerateLimit(FRAME_RATE_LIMIT);

    // demo
    // build enemies array
    initEnemy(window->getSize());
    // demo: scaling the player sprite
    player->getSprite().scale(sf::Vector2f(1, 1) * 1.5f);
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
                break;
            }
        }


    }
    // Check colliision between enemy and player
    for (int i = 0; i < enemyArr.size(); i++)
    {
        if (checkCollision(player, enemyArr[i]))
        {
            std::cout << "PLAYER COLIDED" << std::endl;
            //hp--; // hp update
        }
    }
    tool->updateTime();
    tool->updateScore(count);
    tool->updateHpBarSize(hp);
    window->draw(tool->getSprite());
    tool->drawTo(*window);


    window->draw(background);
    updateGameObjectArray(projectileArray);
    updateGameObjectArray(enemyArr);
    drawGameObjectArray(projectileArray);
    drawGameObjectArray(enemyArr);
    window->draw(player->getSprite());
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

        // Handle Key press

        if (!GAME_PAUSED)
        {
            handleKeyInput();
            window->clear();
            updateGame();
        }

    }
}
