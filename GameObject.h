/*
	GameObject class definition that handle collision detection(TODO) and other logic
*/
#ifndef MOVABLE_H
#define MOVABLE_H
#include <SFML/Graphics.hpp>

class GameObject : public sf::Shape
{
	// Default values
	const float MOVABLE_WIDTH = 1.0f;
	const float MOVABLE_HEIGHT = 1.0f;
	const float MOVABLE_X_VELOCITY = 0.0f;
	const float MOVABLE_Y_VELOCITY = 0.0f;
	sf::Vector2f velocity;
	sf::Vector2f geometry;

protected:

	// Dummy shape, don't access or change any member of this object
	sf::RectangleShape* dummyShape;

	virtual unsigned int getPointCount() const { return dummyShape->getPointCount(); }
	virtual sf::Vector2f getPoint(unsigned int index) const { return dummyShape->getPoint(index); };
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	GameObject() : 
		dummyShape(new sf::RectangleShape( sf::Vector2f(MOVABLE_X_VELOCITY, MOVABLE_Y_VELOCITY)) ) 
	{}
	GameObject(const sf::Vector2f& pos) : 
		velocity(sf::Vector2f(MOVABLE_X_VELOCITY, MOVABLE_Y_VELOCITY))
	{
		dummyShape = new sf::RectangleShape(sf::Vector2f(MOVABLE_WIDTH, MOVABLE_HEIGHT));
		dummyShape->setPosition(sf::Vector2f(-100, -100));
		this->setPosition(pos);
		// Call update() everytime to activitate changes
		update();
	}

	GameObject(const sf::Vector2f& pos, const sf::Vector2f& shapeSize, const sf::Vector2f& vel) :
		geometry(shapeSize),
		velocity(vel)
	{
		dummyShape = new sf::RectangleShape(shapeSize);
		dummyShape->setPosition(sf::Vector2f(-100, -100));
		this->setPosition(pos);
		// Call update() everytime to activitate changes
		update();
	}

	// Virtual functions
	virtual bool checkBoundry() const;
	virtual void move();
	virtual void move(const sf::Vector2f&);

	// Getters
	const sf::Vector2f getVelocity() const { return velocity;  }
	const sf::Vector2f getSize() const { return dummyShape->getSize(); }

	// Setters
	void setVelocity(sf::Vector2f new_v) { velocity = std::move(new_v); }
	void setGeometry(sf::Vector2f new_g) { geometry = std::move(new_g); }
};

#endif
