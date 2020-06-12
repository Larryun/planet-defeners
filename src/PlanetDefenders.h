#ifndef PLANET_DEFENDERS_H
#define PLANET_DEFENDERS_H
#include "Collision.h"
#include "GameObject.hpp"
#include <iostream>
#include <vector>
#include <cmath>
/*
    Put constants and function in this namespace
    when you want it to share arcoss header files

    Rebuild the program when you update the namespace, it will compile all classes.
*/
namespace PlanetDefenders
{
    //ship info
    const int SHIP_MAX_HP[4] = { 100, 50, 200, 80 };
    const float SHIP_SPEED[4] = { 0.5, 0.8, 0.3, 0.65};
    const sf::Time SHIP_ATTACK_SPEED[4] = { sf::milliseconds(150), sf::milliseconds(100), sf::milliseconds(200), sf::milliseconds(125) };
    const sf::IntRect SHIP_TEXTURE_RECT[4] = { sf::IntRect(0, 0, 31, 30), sf::IntRect(33, 0, 27, 21), sf::IntRect(62, 0, 39, 25), sf::IntRect(103, 0, 29, 30) };
    const sf::IntRect SHIP_LASER_RECT[4] = { sf::IntRect(0, 33, 5, 11), sf::IntRect(33, 33, 7, 14), sf::IntRect(62, 33, 11, 11), sf::IntRect(103, 33, 3, 12) };

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
    const sf::IntRect HealthRestoreRect = sf::IntRect(100, 48, 20, 20);
    // shield powerup
    const sf::IntRect ShieldPowerUpRect = sf::IntRect(122, 48, 20, 20);

    // Unused vvvvvvv
    const sf::IntRect CureRect = sf::IntRect(100, 47, 22, 20);
    const sf::IntRect ProtectRect = sf::IntRect(122, 47, 22, 20);
    //const sf::IntRect ShipRect = sf::IntRect(122, 47, 22, 20);
    // ???
    const sf::IntRect DeleteShieldRect = sf::IntRect(500, 0, 48, 48);

    // rect for addProtect sprite ??
    const sf::IntRect ShieldRect = sf::IntRect(132, 0, 48, 48);
    // Unused ^^^^^^^

    
    // hp bar color
    const sf::Color HpBarColor(159, 245, 78);


    // Game Title
    const std::string GameTitle = "Space Invaders?";

    // resources path
    const std::string TextureBasePath = "resourses/texture/";
    const std::string AudioBasePath = "resourses/sound/";
    const unsigned int FRAME_RATE_LIMIT = 65;

    // PowerUp constants
    const enum PowerUpType { HEAL, SHIELD };

    // health restore
    const float HealthRestoreAmount = 10;

    // shield duration
    const float ShieldDuration = 5;
    const float ShieldHp = 5;

    // Player
    const float PlayerInitialHealth = 100.0f;
    const float PlayerMaxSpeed = 50.0f;

    // Projectile
    const int MaxProjectileNum = 500;
    const sf::Time PlayerShootTimeDelta = sf::milliseconds(100);
    const sf::Time EnemyShootTimeDelta = sf::milliseconds(200);
    const sf::Time BossShootTimeDelta = sf::milliseconds(300);

    const sf::IntRect EnemyRectEye = sf::IntRect(0, 48, 23, 28);
    const sf::IntRect EnemyRectBlue = sf::IntRect(25, 48, 30, 28);
    const sf::IntRect EnemyRectBoss = sf::IntRect(0, 76, 182, 235);

    const sf::IntRect PlayerProjectileRect = sf::IntRect(0, 32, 5, 11);
    const sf::IntRect ProjectileMiniCircle = sf::IntRect(89, 48, 8, 8);
    const sf::IntRect ProjectileRedCircle = sf::IntRect(60, 48, 16, 16);
    const sf::IntRect ProjectileRedSharp = sf::IntRect(80, 48, 7, 29);

    // Speed
    const float ProjectileRedCircleSpd = 15;
    const float ProjectileRedSharpSpd = 6;

    // Damage
    const float ProjectileRedCircleDamage = 8;
    const float ProjectileRedSharpDamage = 5;

    enum ProjectileType { RedCircle, RedSharp, BlueRegular};
    const unsigned int NumberOfProjectileType = 2; 

    const float BossProjectileDamage = 5;


    // Game Window size
    const unsigned int WindowWidth = 1280;
    const unsigned int WindowHeight = 720;

    // Backdoor constants
    // '['
    const sf::Keyboard::Key BackdoorTriggerKey = sf::Keyboard::Equal;
    const sf::Keyboard::Key InfinityHpKey = sf::Keyboard::Dash;
    const sf::Keyboard::Key AccelerateKey = sf::Keyboard::RBracket;
    const sf::Keyboard::Key DeaccelerateKey = sf::Keyboard::LBracket;
    const sf::Keyboard::Key BiggerProjectile = sf::Keyboard::Quote;


    // utilites functions
    // put these into a libarary?

    template <class T>
    inline void deleteObjectFromVector(std::vector<T*>& v, int i)
    {
        std::swap(v[i], v.back());
        delete v.back();
        v.pop_back();
    }

     //A collision detection wrapper function
    //inline bool checkCollision(GameObject* obj1, GameObject* obj2)
    //{
    //    return Collision::PixelPerfectTest(obj1->getSprite(), obj2->getSprite());
    //}
    //
    //inline bool checkCollision(sf::Sprite* sp1, sf::Sprite* sp2)
    //{
    //    return Collision::PixelPerfectTest(*sp1, *sp2);
    //}


    // check if obj is out of a certain bound
    // can be used to check if obj should be deleted
    inline bool isOutOfBound(GameObject* obj1)
    {
        return
                (obj1->getSprite().getPosition().y < -100 ||
                obj1->getSprite().getPosition().x < -100 ||
                obj1->getSprite().getPosition().y > WindowHeight + 10 ||
                obj1->getSprite().getPosition().x > WindowWidth + 100);
    }

    inline sf::Vector2f normalize(const sf::Vector2f& v)
    {
        float length = sqrt((v.x * v.x) + (v.y * v.y));
        if (length != 0)
            return sf::Vector2f(v.x / length, v.y / length);
        else
            return v;
    }

    // limit a vector
    inline sf::Vector2f truncate(const sf::Vector2f& v, const float MAXIMUM)
    {
        return sf::Vector2f(std::min(v.x, MAXIMUM), std::min(v.y, MAXIMUM));
    }

}
#endif

