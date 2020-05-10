#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Game.h"
#include "Player.h"
#include "Projectile.h"

template <class T>
void deleteObjectFromVector(std::vector<T*>&, int);
template <class T1, class T2>
bool checkCollision(T1&, T2&);


template <class T>
void deleteObjectFromVector(std::vector<T*>& v, int i)
{
	std::swap(v[i], v.back());
	delete v.back();
	v.pop_back();
}


// A wrapper function
template <class T1, class T2>
bool checkCollision(T1& obj1, T2& obj2)
{
	return Collision::PixelPerfectTest(obj1.getSprite(), obj2.getSprite());
}


Game::Game()
{
	SPACE_TEXTURE.loadFromFile(TEXTURE_BASE_PATH + "spaceSprites.png");
	window= new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE, sf::Style::Close | sf::Style::Resize);
	player = new Player(SPACE_TEXTURE, SHIP_1_TEXTURE_RECT, sf::Vector2f(100,100));
	clock = new sf::Clock();
	init();
}

Game::~Game() {
	delete clock;
	delete window;
	for (int i = 0; i < projectileArray.size() ; i++)
	{
		deleteObjectFromVector(projectileArray, i);
	}
	for (int i = 0; i < enemyArr.size() ; i++)
	{
		deleteObjectFromVector(enemyArr, i);
	}
	delete player;
}

void Game::init()
{
	// set the boundary of player
	player->setMovingBoundary(window->getSize());
	window->setFramerateLimit(FRAME_RATE_LIMIT);

	// demo
	// build enemies array
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 15; j++) {
			enemyArr.push_back(
				new Enemy(
					SPACE_TEXTURE,
					ENEMY_RECT,
					sf::Vector2f(
						static_cast<float>(50 + 30 * j),
						static_cast<float>(50 + 30 * i)
					)
				));
		}
	}
	// demo: scaling the player sprite
	player->getSprite().scale(sf::Vector2f(1, 1) * 1.5f);
}

void Game::shoot()
{
	sf::Time elapse_time = clock->getElapsedTime();
	if (elapse_time >= PROJECTILE_TIME_DELTA)
	{
		//std::cout << elapse_time.asMilliseconds() << std::endl;
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
}


template <class T>
void Game::drawGameObjectArray(std::vector<T*>& arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i]->isOutOfBound() == false)
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
			case sf::Event::TextEntered:
				printf("%c", e.text);
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
				if (checkCollision(*projectileArray[i], *enemyArr[j]))
				{
					deleteObjectFromVector(projectileArray, i);
					deleteObjectFromVector(enemyArr, j);
					break;
				}
			}


		}
		drawGameObjectArray(projectileArray);
		drawGameObjectArray(enemyArr);
		
		window->draw(player->getSprite());
		window->display();
	}
}
