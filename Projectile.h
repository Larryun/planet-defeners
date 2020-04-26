#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>

class Projectile : public sf::Drawable
{
private:
	const float X_VELOCITY = 0.0f;
	const float Y_VELOCITY = -0.09f;
	// Change to an image later
	sf::RectangleShape* projectileShape;
	const sf::Vector2f velocity = sf::Vector2f(X_VELOCITY, Y_VELOCITY);
	
public:
	static int PROJECTILE_COUNTER;
	Projectile(sf::Vector2f);
	~Projectile();
	// Inheritated function from Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void update();
	bool checkBoundry();
	sf::Vector2f getPosition();
};
#endif

