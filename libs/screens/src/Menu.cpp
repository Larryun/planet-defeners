#include "Menu.h"

using namespace PlanetDefenders;

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Samson_Bold_Oblique.ttf")) {
		//handle error
	}

	title.setFont(font);
	title.setCharacterSize(160);
	title.setFillColor(sf::Color::Blue);
	title.setString("PLANET DEFENDERS");
	title.setPosition(sf::Vector2f(width / 6.5, height / 3));

	menu[0].setFont(font);
	title.setCharacterSize(100);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("PLAY");
	menu[0].setPosition(sf::Vector2f(width / (MAX + 1) * .8, height / 1.5));

	menu[1].setFont(font);
	title.setCharacterSize(100);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("OPTIONS");
	menu[1].setPosition(sf::Vector2f(width / (MAX + 1) * 1.7, height / 1.5));

	menu[2].setFont(font);
	title.setCharacterSize(100);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("EXIT");
	menu[2].setPosition(sf::Vector2f(width / (MAX + 1) * 2.8, height / 1.5));

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}
//draws all objects
void Menu::draw(sf::RenderWindow& window) {
	window.draw(title);
	for (int i = 0; i < MAX; i++) {
		window.draw(menu[i]);
	}
	window.display();
}
//change colores based off of arrow keys
void Menu::MoveLeft() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveRight() {
	if (selectedItemIndex + 1 < MAX) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
//change colores based off of mouse postion
void Menu::clickMenu() { 
	for (int i = 0; i < MAX; i++) {
		menu[i].setFillColor(sf::Color::White);
	}
	menu[0].setFillColor(sf::Color::Red);
	selectedItemIndex = 0;
}
void Menu::clickOptions() {
	for (int i = 0; i < MAX; i++) {
		menu[i].setFillColor(sf::Color::White);
	}
	menu[1].setFillColor(sf::Color::Red);
	selectedItemIndex = 1;
}
void Menu::clickExit() {
	for (int i = 0; i < MAX; i++) {
		menu[i].setFillColor(sf::Color::White);
	}
	menu[2].setFillColor(sf::Color::Red);
	selectedItemIndex = 2;
}

bool Menu::inY(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseButton.y > window.getSize().y / 1.5 && event.mouseButton.y < window.getSize().y / 1.4;
}
bool Menu::inXPlay(sf::Event& event, sf::RenderWindow& window){
	return event.mouseButton.x > window.getSize().x / ((MAX + 1.00) * 1.27) && event.mouseButton.x < window.getSize().x / ((MAX + 1.00) * .97);
}
bool Menu::inXOptions(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseButton.x > window.getSize().x / ((MAX + 1.00) * .6) && event.mouseButton.x < window.getSize().x / ((MAX + 1.00) * .48);
}
bool Menu::inXExit(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseButton.x > window.getSize().x / ((MAX + 1.00) * .36) && event.mouseButton.x < window.getSize().x / ((MAX + 1.00) * .333);
}

bool Menu::inYHover(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseMove.y > window.getSize().y / 1.5 && event.mouseMove.y < window.getSize().y / 1.4;
}
bool Menu::inXPlayHover(sf::Event& event, sf::RenderWindow& window) {
	return event.mouseMove.x > window.getSize().x / ((MAX + 1.00) * 1.27) && event.mouseMove.x < window.getSize().x / ((MAX + 1.00) * .97);
}
bool Menu::inXOptionsHover(sf::Event & event, sf::RenderWindow & window) {
	return event.mouseMove.x > window.getSize().x / ((MAX + 1.00) * .6) && event.mouseMove.x < window.getSize().x / ((MAX + 1.00) * .48);
}
bool Menu::inXExitHover(sf::Event & event, sf::RenderWindow & window) {
	return event.mouseMove.x > window.getSize().x / ((MAX + 1.00) * .36) && event.mouseMove.x < window.getSize().x / ((MAX + 1.00) * .333);
}