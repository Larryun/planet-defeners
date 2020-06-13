#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "PlanetDefenders.h"

//using PlanetDefenders::ProjectileType;

namespace PlanetDefenders
{
    class Projectile : public GameObject
    {

        float damage;
        ProjectileType type;

    public:
        static int PROJECTILE_COUNTER;

        Projectile(const sf::Texture& texture, const sf::IntRect& rect,
            const sf::Vector2f& pos, sf::Vector2f dir = sf::Vector2f(0, -1.0f),
            float spd = 10, float damage = 1.0f, ProjectileType type = ProjectileType::BlueRegular) :
            GameObject(
                texture,
                rect,
                pos,
                dir,
                spd
            ), damage(damage), type(type)
        {}

        void setDamage(float d) { damage = d; }
        float getDamage() { return damage; }
        ProjectileType getType() { return type; }
        ~Projectile();
        friend std::ostream& operator<<(std::ostream& output, Projectile& p)
        {
            output << "Projectile at" << " (" << p.getSprite().getPosition().x << ", " 
                   << p.getSprite().getPosition().y << ") "
                   << "Type " << p.type;
            return output;
        }

        bool isOutOfBound() override;
    };
}
#endif

