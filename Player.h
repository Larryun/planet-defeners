#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Player : public GameObject
{
	// Default values
	static const float PLAYER_WIDTH;
	static const float PLAYER_HEIGHT;
	static const float PLAYER_X_VELOCITY;
	static const float PLAYER_Y_VELOCITY;

public:

	Player() : GameObject() {}
	Player(const sf::Vector2f& pos) :
		GameObject(pos,
			sf::Vector2f(PLAYER_WIDTH , PLAYER_HEIGHT),
			sf::Vector2f(PLAYER_X_VELOCITY, PLAYER_Y_VELOCITY)
		)
	{ }
	Player(sf::Vector2f pos, sf::Vector2f geometry, sf::Vector2f vel) :
		GameObject(pos, geometry, vel) {}
	~Player();

};


#endif

