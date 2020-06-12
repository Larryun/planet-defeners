#ifndef HEALTH_RESTORE_H
#define HEALTH_RESTORE_H
#include "PowerUp.h"

using namespace PlanetDefenders;

class HealthRestore : public PowerUp
{
    float healAmount;

public:
    HealthRestore(const sf::Texture& texture, const sf::Vector2f& pos, float duration = 0, float healAmt = 10) :
        PowerUp(
            texture,
            HealthRestoreRect,
            pos,
            duration,
            HEAL
        ), healAmount(healAmt)
    {}
    

    float getHealAmount() const { return healAmount; }

};

#endif
