#pragma warning(disable: 4244)
#include"ShowHighscore.h"
#include <iostream>
#include<iomanip>
#include<fstream>
#include<string>

using namespace std;

void ShowHighscore::assignHighscores() {
	ifstream scoresFile("ScoresData.txt");
	if (!scoresFile) {
		cerr << "Error opening file ScoresData.txt" << endl;
		exit(-1);
	}

	string line;
	string temp;
	int lineSize;
	for (int i = 0; i < 10; i++) {
		if (scoresFile.eof()) {
			break;
		}
		getline(scoresFile, line);
		temp = line;
		temp.erase(15, temp.size());
		for (int i = 15; i >= 0; i--) {
			if (temp[i] != ' ') {
				break;
			}
			else {
				temp.erase(i, 1);
			}
		}
		names[i].setString(temp);

		temp.erase(0, temp.size());
		for (int i = 0; i < 8; i++) {
			temp.push_back(line[i + 16]);
		}
		dates[i].setString(temp);

		lineSize = line.size();
		temp.erase(0, temp.size());
		for (int i = 29; i < lineSize; i++) {
			temp.push_back(line[i]);
		}
		scores[i].setString(temp);
	}

	scoresFile.close();
}

ShowHighscore::ShowHighscore(float width, float height) {
	if (!font.loadFromFile("Samson_Bold_Oblique.ttf")) {
		//handle error
	}
	title.setFont(font);
	title.setCharacterSize(130);
	title.setFillColor(sf::Color::Blue);
	title.setString("HIGHSCORES");
	title.setPosition(sf::Vector2f(width / 4.30, height / 20.50));

	back.setFont(font);
	back.setCharacterSize(80);
	back.setFillColor(sf::Color::White);
	back.setString("BACK TO ENDSCREEN");
	back.setPosition(sf::Vector2f(width / 4.30, height / 1.40));

	for (int i = 0; i < numTopScores; i++) {
		names[i].setFont(font);
		names[i].setCharacterSize(45);
		names[i].setFillColor(sf::Color::White);
		dates[i].setFont(font);
		dates[i].setCharacterSize(45);
		dates[i].setFillColor(sf::Color::White);
		scores[i].setFont(font);
		scores[i].setCharacterSize(45);
		scores[i].setFillColor(sf::Color::White);

	}
	names[0].setFillColor(sf::Color::Yellow);
	dates[0].setFillColor(sf::Color::Yellow);
	scores[0].setFillColor(sf::Color::Yellow);
	assignHighscores();
    // WOWWWWW HARD CODE
	names[0].setPosition(sf::Vector2f(width / 7.50, height / 4.0));
	names[1].setPosition(sf::Vector2f(width / 7.50, height / 3.4));
	names[2].setPosition(sf::Vector2f(width / 7.50, height / 2.95));
	names[3].setPosition(sf::Vector2f(width / 7.50, height / 2.6));
	names[4].setPosition(sf::Vector2f(width / 7.50, height / 2.33));
	names[5].setPosition(sf::Vector2f(width / 7.50, height / 2.12));
	names[6].setPosition(sf::Vector2f(width / 7.50, height / 1.93));
	names[7].setPosition(sf::Vector2f(width / 7.50, height / 1.78));
	names[8].setPosition(sf::Vector2f(width / 7.50, height / 1.66));
	names[9].setPosition(sf::Vector2f(width / 7.50, height / 1.55));
	scores[0].setPosition(sf::Vector2f(width / 2.00, height / 4.0));
	scores[1].setPosition(sf::Vector2f(width / 2.00, height / 3.4));
	scores[2].setPosition(sf::Vector2f(width / 2.00, height / 2.95));
	scores[3].setPosition(sf::Vector2f(width / 2.00, height / 2.6));
	scores[4].setPosition(sf::Vector2f(width / 2.00, height / 2.33));
	scores[5].setPosition(sf::Vector2f(width / 2.00, height / 2.12));
	scores[6].setPosition(sf::Vector2f(width / 2.00, height / 1.93));
	scores[7].setPosition(sf::Vector2f(width / 2.00, height / 1.78));
	scores[8].setPosition(sf::Vector2f(width / 2.00, height / 1.66));
	scores[9].setPosition(sf::Vector2f(width / 2.00, height / 1.55));
	dates[0].setPosition(sf::Vector2f(width / 1.42, height / 4.0));
	dates[1].setPosition(sf::Vector2f(width / 1.42, height / 3.4));
	dates[2].setPosition(sf::Vector2f(width / 1.42, height / 2.95));
	dates[3].setPosition(sf::Vector2f(width / 1.42, height / 2.6));
	dates[4].setPosition(sf::Vector2f(width / 1.42, height / 2.33));
	dates[5].setPosition(sf::Vector2f(width / 1.42, height / 2.12));
	dates[6].setPosition(sf::Vector2f(width / 1.42, height / 1.93));
	dates[7].setPosition(sf::Vector2f(width / 1.42, height / 1.78));
	dates[8].setPosition(sf::Vector2f(width / 1.42, height / 1.66));
	dates[9].setPosition(sf::Vector2f(width / 1.42, height / 1.55));
}

ShowHighscore::~ShowHighscore() {}

void ShowHighscore::work(sf::RenderWindow& window, bool& inHighscore, sf::Event& event, ShowHighscore& showHighscore, sf::Sprite& s, sf::Sound& sound) {
	inHighscore = true;
	window.clear();
	window.draw(s);
	showHighscore.draw(window);
	while (inHighscore) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::BackSpace) {
					inHighscore = false;
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (showHighscore.inXBack(event, window) && showHighscore.inYBack(event, window)) {
					inHighscore = false;
				}
				break;
				//Changing colors when hovering over the buttons
			case sf::Event::Closed:
				window.close();
				exit(0);
			}
			window.draw(s);
			showHighscore.draw(window);
			break;
		}
	}
}

bool ShowHighscore::inYBack(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseButton.y > window.getSize().y / 1.30 && event.mouseButton.y < window.getSize().y / 1.2;
}
bool ShowHighscore::inXBack(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseButton.x > window.getSize().x / 4.20 && event.mouseButton.x < window.getSize().x / 1.25;
}

void ShowHighscore::draw(sf::RenderWindow& window) {
	window.draw(title);
	window.draw(back);
	for (int i = 0; i < numTopScores; i++) {
		window.draw(names[i]);
		window.draw(scores[i]);
		window.draw(dates[i]);
	}
	window.display();
}