#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Game.h"
#include "Player.h"
#include "Projectile.h"

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


Game::Game()
{
    SPACE_TEXTURE.loadFromFile(TEXTURE_BASE_PATH + "spaceSprites.png");
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE, sf::Style::Close | sf::Style::Resize);
    player = new Player(SPACE_TEXTURE, SHIP_1_TEXTURE_RECT, sf::Vector2f(100, 100));
    clock = new sf::Clock();
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

void Game::initEnemy(const sf::Vector2u windowSize, unsigned int row = 3, unsigned int col = 15)
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
                    static_cast<float>((50 + paddingLeft)* i)
                ) + offset
            );
            newE->getSprite().scale(sf::Vector2f(1.4f, 1.4f));
            enemyArr.push_back(newE);
        }
    }
}

void Game::init()
{
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
    }

}

void Game::handleKeyInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player->move(sf::Vector2f(-0.1f, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player->move(sf::Vector2f(0.1f, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        player->move(sf::Vector2f(0.0f, -0.1f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        player->move(sf::Vector2f(0.0f, 0.1f));
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
    }
}


void Game::drawGameObjectArray(std::vector<GameObject*>& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (isOutOfBound(arr[i]) == false)
        {
            arr[i]->move();
            window->draw(arr[i]->getSprite());
        }
        else
        {
            deleteObjectFromVector(arr, i);
        }
    }
}



void Game::gameLoop()
{
    while (window->isOpen())
    {
        sf::Event e;

        while (window->pollEvent(e))
        {
            switch (e.type)
            {
            case sf::Event::Closed:
                window->close();
            }
        }

        // Handle Key press
        handleKeyInput();
        window->clear();

        // check collision between projectile and enemy
        // delete object if collided
        for (int i = 0; i < projectileArray.size(); i++)
        {
            for (int j = 0; j < enemyArr.size(); j++)
            {
                if (checkCollision(projectileArray[i], enemyArr[j]))
                {
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
            }
        }

        drawGameObjectArray(projectileArray);
        drawGameObjectArray(enemyArr);

        window->draw(player->getSprite());
        window->display();
    }
}
