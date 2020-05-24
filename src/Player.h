#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class Player : public GameObject
{

public:

	Player(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& pos) :
		GameObject(
			texture,
			rect,
			pos,
			sf::Vector2f(0, 0),
			5.0f		// Initial speed
		)
	{ }
	~Player();

};


#endif

