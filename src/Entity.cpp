#include <Animator.hpp>
#include <SFML/Graphics.hpp>

/**
 * @brief Represents a game entity with health management and animation capabilities.
 */
class Entity {
private:
    int hp;

public:
    Animator animator;

    void setHP(int health) {
        hp = health;
    }

    void sumHp(int health) {
        hp += health;
    }

    int getHP() {
        return hp;
    }

};
