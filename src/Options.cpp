#include <iostream>
#include "Options.h"

using namespace PlanetDefenders;

Options::Options(float width, float height) {
    if (!font.loadFromFile("Samson_Bold_Oblique.ttf")) {
        //handle error
    }
    title.setFont(font);
    title.setCharacterSize(130);
    title.setFillColor(sf::Color::Blue);
    title.setString("OPTIONS");
    title.setPosition(sf::Vector2f(width / 3.25, height / 20.5));

    instructions.setFont(font);
    instructions.setCharacterSize(30);
    instructions.setFillColor(sf::Color::Red);
    instructions.setString(ins);
    instructions.setPosition(sf::Vector2f(width / 20, height / 1.8));

    back.setFont(font);
    back.setCharacterSize(80);
    back.setFillColor(sf::Color::White);
    back.setString("BACK TO MAIN MENU");
    back.setPosition(sf::Vector2f(width / 4.2, height / 1.4));

    volume[0].setFont(font);
    volume[0].setCharacterSize(50);
    volume[0].setFillColor(sf::Color::Red);
    volume[0].setString("0%");
    volume[0].setPosition(sf::Vector2f(width / 3, height / 3));

    volume[1].setFont(font);
    volume[1].setCharacterSize(50);
    volume[1].setFillColor(sf::Color::White);
    volume[1].setString("25%");
    volume[1].setPosition(sf::Vector2f(width / 2.48, height / 3));

    volume[2].setFont(font);
    volume[2].setCharacterSize(50);
    volume[2].setFillColor(sf::Color::White);
    volume[2].setString("50%");
    volume[2].setPosition(sf::Vector2f(width / 2, height / 3));

    volume[3].setFont(font);
    volume[3].setCharacterSize(50);
    volume[3].setFillColor(sf::Color::White);
    volume[3].setString("75%");
    volume[3].setPosition(sf::Vector2f(width / 1.7, height / 3));

    volume[4].setFont(font);
    volume[4].setCharacterSize(50);
    volume[4].setFillColor(sf::Color::White);
    volume[4].setString("100%");
    volume[4].setPosition(sf::Vector2f(width / 1.48, height / 3));

    volume[5].setFont(font);
    volume[5].setCharacterSize(60);
    volume[5].setFillColor(sf::Color::White);
    volume[5].setString("Volume");
    volume[5].setPosition(sf::Vector2f(width / 8, height / 3.1));

    selectedItemIndex = 0;
}
void Options::work(sf::RenderWindow& window, sf::Event& event, Options& options, sf::Sprite& s, sf::Sound& sound) {
    bool inOptions = true;
    window.clear();
    window.draw(s);
    options.draw(window);
    while (inOptions) {
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                case sf::Keyboard::Left:
                    options.MoveLeft();
                    break;
                case sf::Keyboard::Right:
                    options.MoveRight();
                    break;
                case sf::Keyboard::Return:
                    switch (selectedItemIndex) {
                    case 0:
                        std::cout << "volume 0%" << std::endl;
                        sound.setVolume(0);
                        break;
                    case 1:
                        std::cout << "volume 25%" << std::endl;
                        sound.setVolume(25);
                        break;
                    case 2:
                        std::cout << "volume 50%" << std::endl;
                        sound.setVolume(50);
                        break;
                    case 3:
                        std::cout << "volume 75%" << std::endl;
                        sound.setVolume(75);
                        break;
                    case 4:
                        std::cout << "volume 100%" << std::endl;
                        sound.setVolume(100);
                        break;
                    }
                    break;
                case sf::Keyboard::BackSpace:
                    inOptions = false;
                }
                break;
            case sf::Event::MouseButtonReleased:
                std::cout << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
                std::cout << options.inY(event, window) << std::endl;
                // std::cout << window.getSize().x / ((soundButtons + 1.0) * 0.245) << std::endl;
                if (options.inY(event, window)) {
                    if (options.inX0(event, window)) {
                        std::cout << "volume 0%" << std::endl;
                        sound.setVolume(0);
                    }
                    else if (options.inX25(event, window)) {
                        std::cout << "volume 25%" << std::endl;
                        sound.setVolume(25);
                    }
                    else if (options.inX50(event, window)) {
                        std::cout << "volume 50%" << std::endl;
                        sound.setVolume(50);
                    }
                    else if (options.inX75(event, window)) {
                        std::cout << "volume 75%" << std::endl;
                        sound.setVolume(75);
                    }
                    else if (options.inX100(event, window)) {
                        std::cout << "volume 100%" << std::endl;
                        sound.setVolume(100);
                    }
                }
                else if (options.inXBack(event, window) && options.inYBack(event, window)) {
                    inOptions = false;
                }
                //Changing colors when hovering over the buttons
            case sf::Event::MouseMoved:
                if (options.inYHover(event, window)) {
                    if (options.inX0Hover(event, window)) {
                        options.hover0();
                    }
                    else if (options.inX25Hover(event, window)) {
                        options.hover25();
                    }
                    else if (options.inX50Hover(event, window)) {
                        options.hover50();
                    }
                    else if (options.inX75Hover(event, window)) {
                        options.hover75();
                    }
                    else if (options.inX100Hover(event, window)) {
                        options.hover100();
                    }
                }
                break;
            case sf::Event::Closed:
                window.close();
                exit(0);
            }
            window.draw(s);
            options.draw(window);
            break;
        }
    }
}

// store the window size as you member variable, then you dont need to call getSize() and window parameter
bool Options::inY(sf::Event& event, sf::RenderWindow& window) {
    return event.mouseButton.y > window.getSize().y / 2.8 && event.mouseButton.y < window.getSize().y / 2.45;
}

// you need x position only
bool Options::inX0(sf::Event& event, sf::RenderWindow& window) {
    return event.mouseButton.x > window.getSize().x / ((soundButtons + 1.00) * .43) && event.mouseButton.x < window.getSize().x / ((soundButtons + 1.00) * .38);
}
bool Options::inX25(sf::Event& event, sf::RenderWindow& window) {
    return event.mouseButton.x > window.getSize().x / ((soundButtons + 1.00) * .36) && event.mouseButton.x < window.getSize().x / ((soundButtons + 1.00) * .307);
}
bool Options::inX50(sf::Event& event, sf::RenderWindow& window) {
    return event.mouseButton.x > window.getSize().x / ((soundButtons + 1.00) * .288) && event.mouseButton.x < window.getSize().x / ((soundButtons + 1.00) * .255);
}
bool Options::inX75(sf::Event& event, sf::RenderWindow& window) {
    return event.mouseButton.x > window.getSize().x / ((soundButtons + 1.00) * .245) && event.mouseButton.x < window.getSize().x / ((soundButtons + 1.00) * .22);
}
bool Options::inX100(sf::Event& event, sf::RenderWindow& window) {
    return event.mouseButton.x > window.getSize().x / ((soundButtons + 1.00) * .2115) && event.mouseButton.x < window.getSize().x / ((soundButtons + 1.00) * .19);
}

bool Options::inYHover(sf::Event& event, sf::RenderWindow& window) {
    return event.mouseMove.y > window.getSize().y / 2.8 && event.mouseMove.y < window.getSize().y / 2.45;
}
bool Options::inX0Hover(sf::Event& event, sf::RenderWindow& window) {
    return event.mouseMove.x > window.getSize().x / ((soundButtons + 1.00) * .43) && event.mouseMove.x < window.getSize().x / ((soundButtons + 1.00) * .38);
}
bool Options::inX25Hover(sf::Event& event, sf::RenderWindow& window) {
    return event.mouseMove.x > window.getSize().x / ((soundButtons + 1.00) * .36) && event.mouseMove.x < window.getSize().x / ((soundButtons + 1.00) * .307);
}
bool Options::inX50Hover(sf::Event& event, sf::RenderWindow& window) {
    return event.mouseMove.x > window.getSize().x / ((soundButtons + 1.00) * .288) && event.mouseMove.x < window.getSize().x / ((soundButtons + 1.00) * .255);
}
bool Options::inX75Hover(sf::Event& event, sf::RenderWindow& window) {
    return event.mouseMove.x > window.getSize().x / ((soundButtons + 1.00) * .245) && event.mouseMove.x < window.getSize().x / ((soundButtons + 1.00) * .22);
}
bool Options::inX100Hover(sf::Event& event, sf::RenderWindow& window) {
    return event.mouseMove.x > window.getSize().x / ((soundButtons + 1.00) * .2115) && event.mouseMove.x < window.getSize().x / ((soundButtons + 1.00) * .19);
}

void Options::MoveLeft() {
    if (selectedItemIndex - 1 >= 0) {
        volume[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        volume[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Options::MoveRight() {
    if (selectedItemIndex + 2 < soundButtons) {
        volume[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        volume[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Options::hover0() {
    for (int i = 0; i < soundButtons - 1; i++) {
        volume[i].setFillColor(sf::Color::White);
    }
    volume[0].setFillColor(sf::Color::Red);
    selectedItemIndex = 0;
}
void Options::hover25() {
    for (int i = 0; i < soundButtons - 1; i++) {
        volume[i].setFillColor(sf::Color::White);
    }
    volume[1].setFillColor(sf::Color::Red);
    selectedItemIndex = 1;
}
void Options::hover50() {
    for (int i = 0; i < soundButtons - 1; i++) {
        volume[i].setFillColor(sf::Color::White);
    }
    volume[2].setFillColor(sf::Color::Red);
    selectedItemIndex = 2;
}
void Options::hover75() {
    for (int i = 0; i < soundButtons - 1; i++) {
        volume[i].setFillColor(sf::Color::White);
    }
    volume[3].setFillColor(sf::Color::Red);
    selectedItemIndex = 3;
}
void Options::hover100() {
    for (int i = 0; i < soundButtons - 1; i++) {
        volume[i].setFillColor(sf::Color::White);
    }
    volume[4].setFillColor(sf::Color::Red);
    selectedItemIndex = 4;
}

bool Options::inYBack(sf::Event& event, sf::RenderWindow& window) {
    return event.mouseButton.y > window.getSize().y / 1.3 && event.mouseButton.y < window.getSize().y / 1.2;
}
bool Options::inXBack(sf::Event& event, sf::RenderWindow& window) {
    return event.mouseButton.x > window.getSize().x / 4.2 && event.mouseButton.x < window.getSize().x / 1.29;
}

void Options::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(instructions);
    window.draw(back);
    for (int i = 0; i < soundButtons; i++) {
        window.draw(volume[i]);
    }
    window.display();
}
Options::~Options() {}