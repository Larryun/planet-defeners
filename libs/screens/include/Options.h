#ifndef OPTIONS_H
#define OPTIONS_H
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <SFML/Audio.hpp>

#define MAX 3
#define soundButtons 6

namespace PlanetDefenders
{
    class Options
    {
    public:
        Options(float width, float height);
        void MoveLeft();
        void MoveRight();
        bool inY(sf::Event& event, sf::RenderWindow& window);
        bool inX0(sf::Event& event, sf::RenderWindow& window);
        bool inX25(sf::Event& event, sf::RenderWindow& window);
        bool inX50(sf::Event& event, sf::RenderWindow& window);
        bool inX75(sf::Event& event, sf::RenderWindow& window);
        bool inX100(sf::Event& event, sf::RenderWindow& window);
        bool inYHover(sf::Event& event, sf::RenderWindow& window);
        bool inX0Hover(sf::Event& event, sf::RenderWindow& window);
        bool inX25Hover(sf::Event& event, sf::RenderWindow& window);
        bool inX50Hover(sf::Event& event, sf::RenderWindow& window);
        bool inX75Hover(sf::Event& event, sf::RenderWindow& window);
        bool inX100Hover(sf::Event& event, sf::RenderWindow& window);
        bool inYBack(sf::Event& event, sf::RenderWindow& window);
        bool inXBack(sf::Event& event, sf::RenderWindow& window);
        void hover0();
        void hover25();
        void hover50();
        void hover75();
        void hover100();
        void draw(sf::RenderWindow& window);
        void work(sf::RenderWindow& window, sf::Event& event, Options& options, sf::Sprite& s, sf::Sound& sound);
        ~Options();
    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text back;
        sf::Text title;
        sf::Text instructions;
        sf::Text volume[soundButtons];
        std::string ins = "Use the arrows keys to move the ship. Press spacebar to shoot projectiles. \nSurvive as long as you can by dodging enemies and shooting back. Good luck!";
    };
}

#endif
