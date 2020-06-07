#include "Menu.h"
#include "Options.h"
#include <iostream>

int main() {
	int x = 1280;
	int y = 720;
	sf::RenderWindow window(sf::VideoMode(x, y), "Planet Defenders");

	Menu menu(window.getSize().x, window.getSize().y);
	Options options(window.getSize().x, window.getSize().y);
	sf::Texture t;
	t.loadFromFile("spaceBackground.png");
	sf::Sprite s(t);
	bool inOptions = false;

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("game_music.ogg")) {
		//handle errpr
	}

	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	sound.setLoop(true);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			//using left and right keys to switch between the options
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Left:
					menu.MoveLeft();
					break;
				case sf::Keyboard::Right:
					menu.MoveRight();
					break;
				case sf::Keyboard::Return:
					switch (menu.getPressedItem()) {
					case 0:
						std::cout << "Play button has been pressed" << std::endl;
						break;
					case 1:
						std::cout << "Options button has been pressed" << std::endl;
						options.work(window, inOptions, event, options, s, sound);
						break;
					case 2:
						std::cout << "Exit button has been pressed" << std::endl;
						window.close();
						break;
					}
				}
			//Clicking on a button
			case sf::Event::MouseButtonReleased:
				if (menu.inY(event, window)) {
					if (menu.inXPlay(event, window)){
						std::cout << "PLAY";
					}
					else if (menu.inXOptions(event, window)) {
						std::cout << "Options";
						options.work(window, inOptions, event, options, s, sound);
					}
					else if (menu.inXExit(event, window)) {
						std::cout << "Exit";
						window.close();
					}
				}
			//Changing colors when hovering over the buttons
			case sf::Event::MouseMoved:
				if (menu.inYHover(event,window)) {
					if (menu.inXPlayHover(event,window)) {
						menu.clickMenu();
					}
					else if (menu.inXOptionsHover(event, window)) {
						menu.clickOptions();
					}
					else if (menu.inXExitHover(event, window)) {
						menu.clickExit();
					}
				}
			
			break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.draw(s);
		menu.draw(window);
	}

}