#pragma once
#include "Score.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>


class InputHighscore {
private:
	sf::Font font;
	sf::Text title;
	sf::Text title2;
	sf::Text back;
	sf::Text instruction;
	sf::Text scorePrint;
	sf::Text scoreWord;
	sf::String userInput;
	sf::Text userInputPrint;
public:
	//SFML
	InputHighscore(float width, float height);
	~InputHighscore();
	void draw(sf::RenderWindow& window);
	void work(sf::RenderWindow& window, InputHighscore& inputHighscore, sf::Sprite& s, sf::Sound& sound, int score);
};


namespace CheckScore {
	bool checkScore(int);
	void insertScore(Score*, std::string, int);
	void writeScoresToFile(Score*, unsigned);
	void sort(Score*, unsigned);
	void inputNewScore(int score, std::string name);
}