#ifndef PLANET_DEFENDERS_H
#define PLANET_DEFENDERS_H
#include "Collision.h"
#include "GameObject.h"
#include <iostream>
#include <vector>
/*
    Put constants and function in this namespace
    when you want it to share arcoss header files

    Rebuild the program when you update the namespace, it will compile all classes.
*/
namespace PlanetDefenders
{

    // For ToolBar
    const sf::IntRect HpBorderRect = sf::IntRect(228, 48, 41, 279);
    const sf::IntRect ScoreRect = sf::IntRect(208, 0, 96, 20);
    const sf::IntRect TimeRect = sf::IntRect(208, 24, 80, 20);
    const sf::IntRect TheThingThatLooksLikeaTV = sf::IntRect(208, 332, 64, 51);
    const sf::IntRect ToolBarHealPowerUp = sf::IntRect(208, 388, 29, 28);
    const sf::IntRect ToolBarShieldPowerUp = sf::IntRect(208, 388 + 32, 29, 28);
    const sf::IntRect ToolBarWifiPowerUp = sf::IntRect(208, 388 + 32 * 2, 29, 28);
    const sf::IntRect ToolBarDoublePowerUp = sf::IntRect(208, 388 + 32 * 3, 29, 28);

    // PowerUp
    // health restore
    const sf::IntRect HEALTH_RESTORE_RECT = sf::IntRect(100, 48, 20, 20);
    // shield powerup
    const sf::IntRect SHIELD_POWERUP_RECT = sf::IntRect(122, 48, 20, 20);

    // Unused vvvvvvv
    const sf::IntRect CureRect = sf::IntRect(100, 47, 22, 20);
    const sf::IntRect ProtectRect = sf::IntRect(122, 47, 22, 20);
    const sf::IntRect ShipRect = sf::IntRect(122, 47, 22, 20);
    // ???
    const sf::IntRect DeleteShieldRect = sf::IntRect(500, 0, 48, 48);

    // rect for addProtect sprite ??
    const sf::IntRect ShieldRect = sf::IntRect(132, 0, 48, 48);
    // Unused ^^^^^^^


    // hp bar color
    const sf::Color HpBarColor(159, 245, 78);


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
    const sf::Time PlayerShootTimeDelta = sf::milliseconds(100);
    const sf::Time EnemyShootTimeDelta = sf::milliseconds(200);
    const sf::IntRect PROJECTILE_RECT = sf::IntRect(0, 32, 5, 11);


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
    
    inline bool checkCollision(sf::Sprite* sp1, sf::Sprite* sp2)
    {
        return Collision::PixelPerfectTest(*sp1, *sp2);
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
#endif

