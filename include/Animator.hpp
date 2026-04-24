#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <list>

/**
 * @brief Class responsible for managing and playback of sprite-based animations.
 * Inherits from sf::Sprite to allow direct transformations and rendering.
 */
class Animator : public sf::Sprite { 
private:
    std::list<sf::Texture> m_textureStorage;

    struct AnimationClip {
        std::vector<sf::Texture*> frames;
        sf::Time baseFrameTime;
        bool loop;
    };

    std::map<std::string, AnimationClip> m_animations;

    sf::Clock m_clock;
    sf::Time m_elapsedTime;

    float m_speedMultiplier;
    AnimationClip* m_currentClip;
    std::string m_currentAnimationName;
    int m_currentFrame;

public:
    Animator(const sf::Texture& placeholderTexture);

    void loadAnimation(
        const std::string& name,
        const std::vector<std::string>& filenames,
        sf::Time frameTime,
        bool loop
    );

    void play(const std::string& name, int startFrame = 0);

    void stop();

    void setSpeed(const std::string& speed);

    void update();

    bool isPlaying() const;

    std::string getCurrentAnimationName() const;

};
