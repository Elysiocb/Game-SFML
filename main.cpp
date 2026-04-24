#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Animator.hpp"
#include "Entity.hpp"
#include "MinhaBiblioteca.hpp"

/**
 * @brief Main entry point for "My Final Stand".
 * Handles game states, combat logic, and rendering using SFML.
 */

enum GameState {
    menu,
    combat,
    gameover
};

enum turn {
    playerTurn,
    playerAction,
    enemyTurn,
    enemyAction,
    finished
};

int main() {

    sf::Clock blinkClock; 
    float hp_initial_size = 300.f;

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "My Final Stand", sf::Style::Resize);
    window.setFramerateLimit(60);

    std::string assetsPath = getPath() + "/assets/images/";

    sf::Font fontF;
    if (!fontF.openFromFile(getPath() + "/assets/fonts/Freshman.ttf")) {
        p("Failed to load font!");
        return -1;
    }

    sf::Font fontK;
    if (!fontK.openFromFile(getPath() + "/assets/fonts/KiwiSoda.ttf")) {
        p("Failed to load font!");
        return -1;
    }
    
    sf::Texture texPlaceholder;
    if (!texPlaceholder.loadFromFile(assetsPath + "placeholder.png")) {
        p("Failed to load placeholder: " + assetsPath + "placeholder.png");
        return -1;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(assetsPath + "bg.png")) {
        p("Failed to load background texture: " + assetsPath + "bg.png");
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    
    float scaleX = (float)window.getSize().x / backgroundTexture.getSize().x;
    float scaleY = (float)window.getSize().y / backgroundTexture.getSize().y;
    backgroundSprite.setScale({scaleX, scaleY});

    GameState currentState = GameState::menu;

    sf::Text text_title(fontK);
    text_title.setString("My Final Stand");
    text_title.setCharacterSize(200);
    text_title.setFillColor(sf::Color::Black);
    text_title.setPosition({350, 250});

    sf::Text text_press(fontK);
    text_press.setString("press z to play");
    text_press.setCharacterSize(60);
    text_press.setFillColor(sf::Color::Black);
    text_press.setPosition({1200, 700});

    sf::Text text_gameover(fontK);
    text_gameover.setString("GAME OVER");
    text_gameover.setCharacterSize(100);
    text_gameover.setPosition({700, 400});
    text_gameover.setFillColor(sf::Color::Black);

    sf::RectangleShape rectangle({1350.f, 300.f});
    rectangle.setPosition({300.f, 250.f});
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(5.f);
    rectangle.setFillColor(sf::Color::Transparent);

    sf::RectangleShape enemy_hp({300.f, 10.f});
    enemy_hp.setPosition({1250.f, 250.f});
    enemy_hp.setFillColor(sf::Color::Green);

    turn currentTurn = turn::playerTurn;
    int turnCount = 1;
    bool actionStarted = false;
    sf::Clock turnClock;
    sf::Text combatText(fontK);
    combatText.setCharacterSize(50);
    combatText.setFillColor(sf::Color::Black);
    combatText.setPosition({800, 100});

    Entity player1(texPlaceholder, 30);
    player1.animator.setPosition({200.f, 400.f});
    player1.animator.setScale({0.8f, 0.8f});

    Entity player2(texPlaceholder, 30);
    player2.animator.setPosition({1200.f, 300.f});
    player2.animator.setScale({0.8f, 0.8f});

    std::vector<std::string> enemy_idle = {
        assetsPath + "enemy_idle_1.png",
        assetsPath + "enemy_idle_2.png",
        assetsPath + "enemy_idle_3.png"
    };

    std::vector<std::string> enemy_attack = {
        assetsPath + "enemy_attack_1.png",
        assetsPath + "enemy_attack_2.png",
        assetsPath + "enemy_attack_3.png"
    };

    std::vector<std::string> enemy_death = {
        assetsPath + "enemy_death_1.png",
        assetsPath + "enemy_death_2.png"
    };

    player1.animator.loadAnimation("idle", enemy_idle, sf::seconds(0.3f), true);
    player1.animator.loadAnimation("attack", enemy_attack, sf::seconds(0.15f), false);
    player1.animator.play("idle");

    player2.animator.loadAnimation("idle", enemy_idle, sf::seconds(0.3f), true);
    player2.animator.loadAnimation("attack", enemy_attack, sf::seconds(0.15f), false);
    player2.animator.loadAnimation("death", enemy_death, sf::seconds(0.25f), false);
    player2.animator.play("idle");

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (event->is<sf::Event::KeyPressed>()) {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }

            switch (currentState) {
                case GameState::menu:
                    if (event->is<sf::Event::KeyReleased>()) {
                        if (event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Z) {
                            currentState = GameState::combat;
                        }
                    }
                    break;
                
                case GameState::combat:
                    if (currentTurn == turn::playerTurn) {
                        if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Z) {
                            currentTurn = turn::playerAction;
                        }
                    }
                    if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::G) {
                        currentState = GameState::gameover;
                    }
                    break;
                
                case GameState::gameover:
                    break;
            }
        }

        switch (currentState) {
            case GameState::menu:
                if (blinkClock.getElapsedTime().asSeconds() >= 1.f) {
                    if (text_press.getFillColor() == sf::Color::Black) text_press.setFillColor(sf::Color::Transparent);
                    else text_press.setFillColor(sf::Color::Black);
                    blinkClock.restart();
                }
                break;
            
            case GameState::combat:
                player1.animator.update();
                player2.animator.update();
                break;

            case GameState::gameover:
                break;
        }

        window.clear();
        window.draw(backgroundSprite);

        if (currentState == GameState::menu) {
            window.draw(text_title);
            window.draw(text_press);
        } else if (currentState == GameState::combat) {
            window.draw(player1.animator);
            window.draw(player2.animator);
            window.draw(enemy_hp);
        } else if (currentState == GameState::gameover) {
            window.draw(text_gameover);
        }

        window.display();
    }

    return 0;
}
