#pragma once
#include"Score.h"
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <SFML/Audio.hpp>

#define numTopScores 10
class ShowHighscore {
public:
	void assignHighscores();
	//SFML
	ShowHighscore(float width, float height);
	~ShowHighscore();
	bool inYBack(sf::Event& event, sf::RenderWindow& window);
	bool inXBack(sf::Event& event, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void work(sf::RenderWindow& window, bool& inHighscore, sf::Event& event, ShowHighscore& showHighscore, sf::Sprite& s, sf::Sound& sound);
private:
	sf::Font font;
	sf::Text back;
	sf::Text title;
	sf::Text names[numTopScores];
	sf::Text dates[numTopScores];
	sf::Text scores[numTopScores];
};