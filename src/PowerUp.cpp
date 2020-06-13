#include <cassert>
#include "PowerUp.h"

using namespace PlanetDefenders;

void PowerUp::restartClock()
{
    // make sure powerUpClock is not null
    assert(powerUpClock);
    powerUpClock->restart();
}

bool PowerUp::isPowerUpEnded()
{
    // make sure powerUpClock is not null
    assert(powerUpClock);
    return powerUpClock->getElapsedTime().asSeconds() >= getDuration();
}
