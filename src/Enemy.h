#pragma once
#include "GameObject.hpp"
#include "Projectile.h"
class Enemy :
	public GameObject
{	
    sf::Clock shootClock;

public:
	Enemy(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& pos) :
		GameObject(
			texture,
			rect,
			pos,
			sf::Vector2f(0, 0.0f),
			0
		)
	{}
	~Enemy();
    //sf::Vector2f getPosition
	bool isOutOfBound() { return false; }

    Projectile* shoot();
	
};

