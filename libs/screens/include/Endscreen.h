#pragma once
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <SFML/Audio.hpp>

#define MAX 3
#define choice 3
class Endscreen {
public:
	Endscreen(float width, float height);
	~Endscreen();
	void MoveLeft();
	void MoveRight();
	bool inY(sf::Event& event, sf::RenderWindow& window);
	bool inXRetry(sf::Event& event, sf::RenderWindow& window);
	bool inXShowHighscore(sf::Event& event, sf::RenderWindow& window);
	bool inXExit(sf::Event& event, sf::RenderWindow& window);
	bool inYHover(sf::Event& event, sf::RenderWindow& window);
	bool inXRetryHover(sf::Event& event, sf::RenderWindow& window);
	bool inXShowHighscoreHover(sf::Event& event, sf::RenderWindow& window);
	bool inXExitHover(sf::Event& event, sf::RenderWindow& window);
	bool inYBack(sf::Event& event, sf::RenderWindow& window);
	bool inXBack(sf::Event& event, sf::RenderWindow& window);
	void hoverRetry();
	void hoverShowHighscore();
	void hoverExit();
	void draw(sf::RenderWindow& window);
	bool work(sf::RenderWindow& window, Endscreen& endscreen, sf::Sprite& s, sf::Sound& sound);
private:
	int selectedItemIndex;
	sf::Text title;
	sf::Font font;
	sf::Text back;
	sf::Text buttons[choice];
};