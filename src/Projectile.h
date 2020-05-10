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

	Projectile(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& pos) :
		GameObject(
			texture,
			rect,
			pos,
			sf::Vector2f(0, -1.0f),
			5.0f		// Initial speed
		)
	{}

	~Projectile();
	
	bool isOutOfBound() const;

};
#endif

