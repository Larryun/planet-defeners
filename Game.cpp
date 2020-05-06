#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Player.h"
#include "Projectile.h"

Game::Game()
{
	window= new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE, sf::Style::Close | sf::Style::Resize);
	player = new Player(sf::Vector2f(100,100));
	clock = new sf::Clock();
	init();
}

void Game::init()
{
	player->setBound(window->getSize());
	window->setFramerateLimit(FRAME_RATE_LIMIT);
	player->getShape().setFillColor(sf::Color::Green);
	// demo
	// build enemies array
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 15; j++) {
			enemiesArr.push_back(
				new Enemy(sf::Vector2f(
					static_cast<float>(50 + 30 * j),
					static_cast<float>(50 + 30 * i)
				)));
		}
	}
}

void Game::shoot()
{
	sf::Time elapse_time = clock->getElapsedTime();
	if (elapse_time >= PROJECTILE_TIME_DELTA)
	{
		std::cout << elapse_time.asMilliseconds() << std::endl;
		projectileArray.push_back(
			new Projectile(
				player->getShape().getPosition() + sf::Vector2f(player->getSize().x / 2, 0.0f)
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
		// Example of using setSpeed() to change speed of a GameObject
		// press R the accerlerate
		player->accelerate(1.1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		shoot();
	}
}

void Game::drawProjectileArray(std::vector<Projectile*>& arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (projectileArray[i]->isOutOfBound() == false)
		{
			arr[i]->move();
			window->draw(arr[i]->getShape());
		}
		else
		{
			std::swap(arr[i], arr.back());
			delete arr.back();
			arr.pop_back();
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
		// Draw all enemies
		for (int i = 0; i < enemiesArr.size(); i++) {
			window->draw(enemiesArr[i]->getShape());
		}
		// Draw all projectile
		drawProjectileArray(projectileArray);
		

		window->draw(player->getShape());
		window->display();
	}
}
