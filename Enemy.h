#pragma once
#include "GameObject.h"
class Enemy :
	public GameObject
{	



public:
	Enemy(const sf::Vector2f& pos) :
		GameObject(
			pos,
			sf::Vector2f(10.0f, 10.0f),
			sf::Vector2f(0, 0.0f),
			0
		)
	{}

	
};

