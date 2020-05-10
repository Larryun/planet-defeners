#pragma once
#include "GameObject.h"
class Enemy :
	public GameObject
{	

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

	bool isOutOfBound() { return false; }

	
};

