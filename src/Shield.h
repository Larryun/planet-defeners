#ifndef SHIELD_H
#define SHIELD_H
#include "PowerUp.h"
class Shield : public PowerUp
{
public:
    Shield(const sf::Texture& texture, const sf::IntRect& rect,
        const sf::Vector2f& pos, PowerUpEnum type,
        float duration = 5) :
        PowerUp(
            texture,
            rect,
            pos,
            duration,
            type
        )
    {}


};

#endif

