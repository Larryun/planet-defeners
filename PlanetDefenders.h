#include "Collision.h"
#include "GameObject.h"
#include <vector>
namespace PlanetDefenders {
    // PowerUp constants
    const enum PowerUpEnum { HEAL, SHIELD };

    // health restore
    const float HEALTH_RESTORE_AMOUNT = 10;

    // shield duration
    const float SHIELD_DURATION = 5;
    const float SHIELD_HP = 5;

    // Player
    const float PLAYER_INITIAL_HEALTH = 100;


    template <class T>
    void deleteObjectFromVector(std::vector<T*>& v, int i);
    bool checkCollision(GameObject*, GameObject*);
}