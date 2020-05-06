/*
	GameObject class definition that handle collision detection(TODO) and other logic
*/
#ifndef MOVABLE_H
#define MOVABLE_H
#include <SFML/Graphics.hpp>

class GameObject 
{
	// Default values
	const float MOVABLE_WIDTH = 1.0f;
	const float MOVABLE_HEIGHT = 1.0f;
	const float MOVABLE_X_VELOCITY = 0.0f;
	const float MOVABLE_Y_VELOCITY = 0.0f;
	sf::Vector2f velocity;

protected:

	sf::RectangleShape* dummyShape;
	sf::Vector2f direction;
	sf::Vector2u bound;
	float speed;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	GameObject(const sf::Vector2f&);
	GameObject(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&, float);

	void move();
	void move(const sf::Vector2f&);

	// Getters
	const sf::Vector2f getVelocity() const { return speed * direction;  }
	sf::RectangleShape& getShape() { return *dummyShape; }
	sf::Vector2f getSize() { return dummyShape->getSize(); }
	float getSpeed() { return speed; }

	// Setters
	void setSpeed(float const& spd) { speed = spd; }
	void setDirection(const sf::Vector2f& dir) { direction = dir; }
	void setBound(const sf::Vector2u& bound_) { bound = bound_; }

	void accelerate(float a) { setSpeed(getSpeed() + a); }


};

#endif
