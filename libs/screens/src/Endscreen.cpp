#pragma warning(disable: 4244)
#include<iostream>
#include "Endscreen.h"
#include"ShowHighscore.h"

Endscreen::Endscreen(float width, float height) {
	if (!font.loadFromFile("Samson_Bold_Oblique.ttf")) {
		//handle error
	}

	title.setFont(font);
	title.setCharacterSize(120);
	title.setFillColor(sf::Color::Blue);
	title.setString("GAME OVER");
	title.setPosition(sf::Vector2f(width / 3.60, height / 3.00));

	//back.setFont(font);
	//back.setCharacterSize(80);
	//back.setFillColor(sf::Color::White);
	//back.setString("BACK TO MAIN MENU");
	//back.setPosition(sf::Vector2f(width / 4.2, height / 1.4));

	for (int i = 0; i < choice; i++) {
		buttons[i].setFont(font);
		buttons[i].setCharacterSize(30);
		buttons[i].setFillColor(sf::Color::White);
	}

	buttons[0].setString("RETRY");
	buttons[0].setPosition(sf::Vector2f(width / (MAX + 1) * .80, height / 1.50));
	buttons[1].setString("SHOW HIGHSCORES");
	buttons[1].setPosition(sf::Vector2f(width / (MAX + 1) * 1.55, height / 1.50));
	buttons[2].setString("EXIT");
	buttons[2].setPosition(sf::Vector2f(width / (MAX + 1) * 2.85, height / 1.50));

	selectedItemIndex = 0;
}

Endscreen::~Endscreen() {}

bool Endscreen::work(sf::RenderWindow& window, Endscreen& endscreen, sf::Sprite& s, sf::Sound& sound) {
	ShowHighscore showHighscore(window.getSize().x, window.getSize().y);
    sf::Event event;
	bool flag = false;
	bool inEndscreen = true;
	window.clear();
	window.draw(s);
	endscreen.draw(window);
	while (inEndscreen) {
        // prevent drawing to much CPU time  
        sf::sleep(sf::milliseconds(10));
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Left:
					endscreen.MoveLeft();
					break;
				case sf::Keyboard::Right:
					endscreen.MoveRight();
					break;
				case sf::Keyboard::Return:
					switch(selectedItemIndex) {
                    case 0:
                        std::cout << "Retry" << std::endl;
                        flag = true;
                        inEndscreen = false;
                        break;
					case 1:
						std::cout << "Show Highscore" << std::endl;
						showHighscore.work(window, inEndscreen, event, showHighscore, s, sound);
						inEndscreen = true;
						break;
					case 2:
						std::cout << "Exit" << std::endl;
						window.close();
						inEndscreen = false;
						flag = true;        // leave the loop
						break;
					case sf::Keyboard::BackSpace:
						inEndscreen = false;
						break;
				}
			}
			case sf::Event::MouseButtonReleased:
				if (endscreen.inY(event, window)) {
					if (endscreen.inXRetry(event, window)) {
						std::cout << "Retry" << std::endl;
						flag = true;
						inEndscreen = false;
					}
					else if (endscreen.inXShowHighscore(event, window)) {
						std::cout << "Show Highscore" << std::endl;
						showHighscore.work(window, inEndscreen, event, showHighscore, s, sound);
						inEndscreen = true;
					}
					else if (endscreen.inXExit(event, window)) {
						std::cout << "Exit" << std::endl;
						window.close();
						inEndscreen = false;
						flag = true;        // leave the loop
					}
				}
				else if (endscreen.inXBack(event, window) && endscreen.inYBack(event, window)) {
                    flag = true;
					inEndscreen = false;
				}
				//Changing colors when hovering over the buttons
			case sf::Event::MouseMoved:
				if (endscreen.inYHover(event, window)) {
					if (endscreen.inXRetryHover(event, window)) {
						endscreen.hoverRetry();
					}
					else if (endscreen.inXShowHighscoreHover(event, window)) {
						endscreen.hoverShowHighscore();
					}
					else if (endscreen.inXExitHover(event, window)) {
						endscreen.hoverExit();
					}
				}
				break;
			case sf::Event::Closed:
				window.close();
				exit(0);
			}
			window.draw(s);
			endscreen.draw(window);
			break;
		}
	}
	return flag;
}

bool Endscreen::inY(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseButton.y > window.getSize().y / 1.46 && event.mouseButton.y < window.getSize().y / 1.4;
}
bool Endscreen::inXRetry(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseButton.x > window.getSize().x / ((choice + 1.00) * 1.28) && event.mouseButton.x < window.getSize().x / ((choice + 1.00) * .93);
}
bool Endscreen::inXShowHighscore(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseButton.x > window.getSize().x / ((choice + 1.00) * .65) && event.mouseButton.x < window.getSize().x / ((choice + 1.00) * .432);
}
bool Endscreen::inXExit(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseButton.x > window.getSize().x / ((choice + 1.00) * .353) && event.mouseButton.x < window.getSize().x / ((choice + 1.00) * .327);
}

bool Endscreen::inYHover(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseMove.y > window.getSize().y / 1.46 && event.mouseMove.y < window.getSize().y / 1.4;
}
bool Endscreen::inXRetryHover(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseMove.x > window.getSize().x / ((choice + 1.00) * 1.28) && event.mouseMove.x < window.getSize().x / ((choice + 1.00) * .93);
}
bool Endscreen::inXShowHighscoreHover(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseMove.x > window.getSize().x / ((choice + 1.00) * .65) && event.mouseMove.x < window.getSize().x / ((choice + 1.00) * .432);
}
bool Endscreen::inXExitHover(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseMove.x > window.getSize().x / ((choice + 1.00) * .353) && event.mouseMove.x < window.getSize().x / ((choice + 1.00) * .327);
}

void Endscreen::MoveLeft() {
	if (selectedItemIndex - 1 >= 0) {
		buttons[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		buttons[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Endscreen::MoveRight() {
	if (selectedItemIndex + 2 < choice + 1) {
		buttons[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		buttons[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Endscreen::hoverRetry() {
	for (int i = 0; i < choice; i++) {
		buttons[i].setFillColor(sf::Color::White);
	}
	buttons[0].setFillColor(sf::Color::Red);
	selectedItemIndex = 0;
}
void Endscreen::hoverShowHighscore() {
	for (int i = 0; i < choice; i++) {
		buttons[i].setFillColor(sf::Color::White);
	}
	buttons[1].setFillColor(sf::Color::Red);
	selectedItemIndex = 1;
}
void Endscreen::hoverExit() {
	for (int i = 0; i < choice; i++) {
		buttons[i].setFillColor(sf::Color::White);
	}
	buttons[2].setFillColor(sf::Color::Red);
	selectedItemIndex = 2;
}

bool Endscreen::inYBack(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseButton.y > window.getSize().y / 1.3 && event.mouseButton.y < window.getSize().y / 1.2;
}
bool Endscreen::inXBack(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseButton.x > window.getSize().x / 4.2 && event.mouseButton.x < window.getSize().x / 1.29;
}

void Endscreen::draw(sf::RenderWindow& window) {
	window.draw(title);
	window.draw(buttons[0]);
	window.draw(buttons[1]);
	window.draw(buttons[2]);
	//window.draw(back);
	for (int i = 0; i < choice; i++) {
		window.draw(buttons[i]);
	}
	window.display();
}