#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <SFML/Audio.hpp>
#define MAX 3


namespace PlanetDefenders
{
    class Menu
    {
    public:
        Menu(float width, float height);
        void draw(sf::RenderWindow& window);
        void MoveRight();
        void MoveLeft();
        void clickMenu();
        void clickOptions();
        void clickExit();
        bool inY(sf::Event& event, sf::RenderWindow& window);
        bool inXPlay(sf::Event& event, sf::RenderWindow& window);
        bool inXOptions(sf::Event& event, sf::RenderWindow& window);
        bool inXExit(sf::Event& event, sf::RenderWindow& window);
        bool inYHover(sf::Event& event, sf::RenderWindow& window);
        bool inXPlayHover(sf::Event& event, sf::RenderWindow& window);
        bool inXOptionsHover(sf::Event& event, sf::RenderWindow& window);
        bool inXExitHover(sf::Event& event, sf::RenderWindow& window);
        int getPressedItem() { return selectedItemIndex; }
        ~Menu();
    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text menu[MAX];
        sf::Text title;
    };
}
#endif

