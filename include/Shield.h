#ifndef SHIELD_H
#define SHIELD_H
#include "PowerUp.h"

namespace PlanetDefenders
{
    class Shield : public PowerUp
    {
    public:
        Shield(const sf::Texture& texture, const sf::Vector2f& pos, float duration = 5) :
            PowerUp(
                texture,
                ShieldPowerUpRect,
                pos,
                duration,
                PowerUpType::SHIELD

            )
        {}
    };
}

#endif

