#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include "GameObject.h"


class Projectile : public GameObject
{
	// Default values
	static const float PROJECTILE_WIDTH;
	static const float PROJECTILE_HEIGHT;
	static const float PROJECTILE_X_VELOCITY;
	static const float PROJECTILE_Y_VELOCITY;
	
public:
	static int PROJECTILE_COUNTER;

	Projectile(const sf::Vector2f& pos) :
		GameObject(
			pos,
			sf::Vector2f(PROJECTILE_WIDTH, PROJECTILE_HEIGHT),
			sf::Vector2f(0, -1.0f),
			5.0f		// Initial speed
		)
	{}

	~Projectile();
};
#endif

