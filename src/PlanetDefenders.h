#include "Collision.h"
#include "GameObject.h"
#include <iostream>
#include <vector>
/*
    Put constants and function in this namespace
    when you want it to share arcoss header files

    Rebuild the program when you update the namespace, it will compile all classes.
*/
namespace PlanetDefenders {

    // Game Title
    const std::string GAME_TITLE = "Space Invaders?";

    // resources path
    const std::string TEXTURE_BASE_PATH = "resourses/texture/";
    const std::string AUDIO_BASE_PATH = "resourses/sound/";
    const unsigned int FRAME_RATE_LIMIT = 65;

    // PowerUp constants
    const enum PowerUpEnum { HEAL, SHIELD };

    // health restore
    const float HEALTH_RESTORE_AMOUNT = 10;

    // shield duration
    const float SHIELD_DURATION = 5;
    const float SHIELD_HP = 5;

    // Player
    const float PLAYER_INITIAL_HEALTH = 100;

    // Projectile
    const int MAX_PROJECTILE_NUM = 500;
    const int PROJECTILE_TIME_INTERVAL = 100;
    const sf::Time PROJECTILE_TIME_DELTA = sf::milliseconds(PROJECTILE_TIME_INTERVAL);

    // Game Window size
    const unsigned int WINDOW_WIDTH = 1280;
    const unsigned int WINDOW_HEIGHT = 720;


    // utilites functions
    // put these into a libarary?

    // delete object from vector 
    template <class T>
    inline void deleteObjectFromVector(std::vector<T*>& v, int i)
    {
        std::swap(v[i], v.back());
        delete v.back();
        v.pop_back();
    }


    // A collision detection wrapper function
    inline bool checkCollision(GameObject* obj1, GameObject* obj2)
    {
        return Collision::PixelPerfectTest(obj1->getSprite(), obj2->getSprite());
    }

    // check if obj is out of a certain bound
    // can be used to check if obj should be deleted
    inline bool isOutOfBound(GameObject* obj1)
    {
        return
            obj1->getSprite().getPosition().y < -100 ||
            obj1->getSprite().getPosition().x < -100 ||
            obj1->getSprite().getPosition().y > WINDOW_HEIGHT + 100 ||
            obj1->getSprite().getPosition().x > WINDOW_WIDTH + 100;
    }
}