#include "Animator.hpp"
#include <iostream>

/**
 * @brief Implementation of the Animator class methods for sprite animation handling.
 */

Animator::Animator(const sf::Texture& placeholderTexture) : 
    sf::Sprite(placeholderTexture), 
    m_currentClip(nullptr),
    m_currentFrame(0),
    m_elapsedTime(sf::Time::Zero),    
    m_currentAnimationName(""),
    m_speedMultiplier(1.0f)
{
}

void Animator::loadAnimation(
    const std::string& name,
    const std::vector<std::string>& filenames,
    sf::Time frameTime,
    bool loop)
{
    AnimationClip newClip;
    newClip.baseFrameTime = frameTime;
    newClip.loop = loop;

    for (const std::string& file : filenames) {
        m_textureStorage.emplace_back(); 
        sf::Texture& newTexture = m_textureStorage.back();

        if (newTexture.loadFromFile(file)) {
            newClip.frames.push_back(&newTexture);
        } else {
            std::cerr << "Animator: Failed to load texture: " << file << std::endl;
            m_textureStorage.pop_back();
        }
    }

    if (!newClip.frames.empty()) {
        m_animations[name] = newClip;
    }
}

void Animator::play(const std::string& name, int startFrame) {
    auto it = m_animations.find(name);
    if (it == m_animations.end()) return;

    m_currentClip = &(it->second);
    m_currentAnimationName = name;
    m_elapsedTime = sf::Time::Zero;
    m_clock.restart();
    
    m_currentFrame = startFrame;

    this->setTexture(*m_currentClip->frames[m_currentFrame]);
}

void Animator::stop() {
    m_currentClip = nullptr;
    m_currentAnimationName = "";
}

void Animator::setSpeed(const std::string& speed) {
    if (speed == "rápido") {
        m_speedMultiplier = 0.5f;
    } else if (speed == "lento") {
        m_speedMultiplier = 2.0f;
    } else {
        m_speedMultiplier = 1.0f;
    }
}

void Animator::update() {
    if (m_currentClip == nullptr) return;

    m_elapsedTime += m_clock.restart();

    sf::Time frameTime = m_currentClip->baseFrameTime * m_speedMultiplier;

    if (m_elapsedTime >= frameTime) {
        m_elapsedTime -= frameTime;
        
        m_currentFrame++;

        if (m_currentFrame >= m_currentClip->frames.size()) {
            if (m_currentClip->loop) {
                m_currentFrame = 0;
            } else {
                m_currentFrame = m_currentClip->frames.size() - 1;
                stop();
                return;
            }
        }
        
        this->setTexture(*m_currentClip->frames[m_currentFrame]);
    }
}

bool Animator::isPlaying() const {
    return m_currentClip != nullptr;
}

std::string Animator::getCurrentAnimationName() const {
    return m_currentAnimationName;
}
