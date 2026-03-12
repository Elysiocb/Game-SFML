#include "Animator.hpp"
#include <iostream>

// Construtor: Passa a textura "placeholder" para o "pai" (sf::Sprite)
// ISSO RESOLVE O ERRO DE CONSTRUTOR
Animator::Animator(const sf::Texture& placeholderTexture) : 
    sf::Sprite(placeholderTexture), 
    m_currentClip(nullptr),
    m_currentFrame(0),
    m_elapsedTime(sf::Time::Zero),
    m_speedMultiplier(1.0f) // 1.0f = "normal"
{
}

// "Ensinar" a receita (O "Pré-carregamento")
void Animator::loadAnimation(
    const std::string& name,
    const std::vector<std::string>& filenames,
    sf::Time frameTime,
    bool loop)
{
    AnimationClip newClip;
    newClip.baseFrameTime = frameTime;
    newClip.loop = loop;

    // Itera pelos nomes de arquivo (PNGs)
    for (const std::string& file : filenames) {
        // Cria a textura na nossa lista de armazenamento
        m_textureStorage.emplace_back(); 
        sf::Texture& newTexture = m_textureStorage.back();

        // Carrega o PNG do disco (SÓ UMA VEZ!)
        if (newTexture.loadFromFile(file)) {
            // Salva o PONTEIRO para ela na "lista de frames"
            newClip.frames.push_back(&newTexture);
        } else {
            std::cerr << "Animator: Falha ao carregar textura: " << file << std::endl;
            m_textureStorage.pop_back(); // Remove a textura falha
        }
    }

    // Salva a "receita" completa no "catálogo"
    if (!newClip.frames.empty()) {
        m_animations[name] = newClip;
    }
}

// Seu "play"
void Animator::play(const std::string& name, int startFrame) {
    auto it = m_animations.find(name);
    if (it == m_animations.end()) return; // Animação não existe

    m_currentClip = &(it->second); // Define como "receita" atual
    m_elapsedTime = sf::Time::Zero; // Zera o "cronômetro"
    m_clock.restart();            // Zera o relógio
    
    m_currentFrame = startFrame; // Define o "index" inicial

    // Aplica o primeiro PNG imediatamente
    // 'setTexture' é uma função que NÓS herdamos do sf::Sprite
    this->setTexture(*m_currentClip->frames[m_currentFrame]);
}

// Seu "stop"
void Animator::stop() {
    m_currentClip = nullptr;
}

// Seu "setVelocity"
void Animator::setSpeed(const std::string& speed) {
    if (speed == "rápido") {
        m_speedMultiplier = 0.5f; // Metade do tempo = dobro da velocidade
    } else if (speed == "lento") {
        m_speedMultiplier = 2.0f; // Dobro do tempo = metade da velocidade
    } else {
        m_speedMultiplier = 1.0f; // "normal"
    }
}

void Animator::update() {
    if (m_currentClip == nullptr) return; // Nada tocando

    // 1. Acumula o tempo (IGUAL AO SEU MODO MANUAL)
    m_elapsedTime += m_clock.restart();

    // 2. Calcula o "tempo de espera" real (base * multiplicador)
    sf::Time frameTime = m_currentClip->baseFrameTime * m_speedMultiplier;

    // 3. Verifica se o cronômetro atingiu o tempo de espera
    if (m_elapsedTime >= frameTime) {
        m_elapsedTime -= frameTime; // Reseta o cronômetro
        
        // 4. "somar 1 index a cada tempo" (Sua Lógica!)
        m_currentFrame++;

        // 5. "se a lista de frames acaba volta ao início" (Sua Lógica!)
        if (m_currentFrame >= m_currentClip->frames.size()) {
            if (m_currentClip->loop) {
                m_currentFrame = 0; // Volta ao início
            } else {
                m_currentFrame = m_currentClip->frames.size() - 1;
                stop();
            }
        }
        
        // 6. Aplica o PNG do "index" atual
        this->setTexture(*m_currentClip->frames[m_currentFrame]);
    }
}