#pragma once

#include <Animator.hpp>
#include <SFML/Graphics.hpp>

/**
 * @brief Base class representing a game entity.
 * Combines health management with an integrated Animator for visual representation.
 */
class Entity {
private:
    int hp;

public:
    Animator animator;

    void setHP(int health) {
        hp = health;
    }

    Entity(const sf::Texture& placeholderTexture, int default_hp = 10)
        : animator(placeholderTexture) {
        hp = default_hp;
    }

    void sumHp(int health) {
        hp += health;
    }

    int getHP() {
        return hp;
    }

};
